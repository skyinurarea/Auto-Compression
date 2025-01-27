# Copyright (c) 2021 - present / Neuralmagic, Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


import logging
from typing import List, Optional

from pydantic import BaseModel, Field

from sparseml.core.event import Event
from sparseml.core.modifier.base import ModifierInterface
from sparseml.core.modifier.modifier import Modifier
from sparseml.core.state import State


__all__ = ["StageModifiers"]

_LOGGER = logging.getLogger(__name__)


class StageModifiers(ModifierInterface, BaseModel):
    """
    Represents a collection of modifiers that are applied together as a stage.

    :param modifiers: The modifiers to apply as a stage
    :param index: The index of the stage, if applicable
    :param group: The group name of the stage, if applicable
    :param applied: Flag for indicating if this stage has has already been
    applied to the model, through structure initialization or finalization
    """

    modifiers: List["Modifier"] = Field(default_factory=list)
    index: Optional[int] = None
    group: Optional[str] = None
    applied: bool = False

    @property
    def initialized_structure(self) -> bool:
        """
        :return: True if any of the stage modifiers have initialized structure,
            False otherwise
        """
        return any(mod.initialized_structure for mod in self.modifiers)

    @property
    def initialized(self) -> bool:
        """
        :return: True if all of the stage modifiers have been initialized,
            False otherwise
        """
        return all(mod.initialized for mod in self.modifiers)

    @property
    def finalized(self) -> bool:
        """
        :return: True if all of the stage modifiers have been finalized,
            False otherwise
        """
        return all(mod.finalized for mod in self.modifiers)

    @property
    def unique_id(self) -> str:
        """
        :return: ID for stage containing the name and index
        """
        return self.group + "_" + str(self.index)

    def check_initialized(self):
        """
        Check if all of the stage modifiers have been initialized, and log a warning
        if not. This warning is expected when loading an input recipe during finetuning
        """

        at_least_one_initialized = False
        for modifier in self.modifiers:
            if modifier.initialized:
                at_least_one_initialized = True
        if not at_least_one_initialized:
            modifier_names = [type(mod).__name__ for mod in self.modifiers]
            _LOGGER.warning(
                f"Found no initialized modifiers in stage {self.group}. "
                "Found the following uninitialized modifiers: "
                f"{modifier_names}"
            )

    def calculate_start(self) -> float:
        """
        :return: The minimum start time of all the stage modifiers
        """
        return min(
            mod.calculate_start()
            for mod in self.modifiers
            if mod.calculate_start() >= 0
        )

    def calculate_end(self) -> float:
        """
        :return: The maximum end time of all the stage modifiers, or -1 if none of the
        modifiers have set ends
        """
        return max(mod.calculate_end() for mod in self.modifiers)

    def pre_initialize_structure(self, state: "State", **kwargs):
        """
        Pre initialize the structure for all stage modifiers mark the stage applied

        :param state: The current state of the training
        :param kwargs: Additional kwargs to pass to the modifier(s)
            pre_initialize_structure method
        """
        for modifier in self.modifiers:
            modifier.pre_initialize_structure(state, **kwargs)

        self.applied = True

    def initialize(self, state: "State", **kwargs):
        """
        Initialize all the stage modifiers

        :param state: The state of current session
        :param kwargs: Additional kwargs to pass to the modifier(s)
            initialize method
        """

        if self.applied:
            return

        for modifier in self.modifiers:
            modifier.initialize(state, **kwargs)

    def finalize(self, state: "State", **kwargs):
        """
        Finalize all the stage modifiers and mark the stage as applied

        :param state: The state of current session
        :param kwargs: Additional kwargs to pass to the modifier(s)
            finalize method
        """

        if self.applied:
            return

        for modifier in self.modifiers:
            modifier.finalize(state, **kwargs)

        self.applied = True

    def update_event(self, state: "State", event: "Event", **kwargs):
        """
        Propagate the event to all the stage modifiers

        :param state: The state of current session
        :param event: The event to propagate
        :param kwargs: Additional kwargs to pass to the modifier(s)
            update_event method
        """

        if self.applied:
            return

        for modifier in self.modifiers:
            modifier.update_event(state, event, **kwargs)
