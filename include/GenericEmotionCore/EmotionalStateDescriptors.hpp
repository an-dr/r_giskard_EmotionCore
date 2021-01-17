// *************************************************************************
//
// Copyright (c) 2021 Andrei Gramakov. All rights reserved.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include <list>
#include <string>
#include "CoreParams.hpp"
#include "EmotionalStateDescriptors_types.hpp"
#include "InDataDescriptors.hpp"
#include "error_t.h"


class EmotionalStateDescriptors {
private:
    EmotionalStateDescriptorsList_t _list;

public:
    EmotionalStateDescriptors();

    error_t Add(EmotionalStateDescriptorStruct_t newState);

    error_t Remove(std::string name);

    const EmotionalStateDescriptorStruct_t *Get(std::string name) const;

    const EmotionalStateDescriptorsList_t &GetList() const;

    error_t GetParamsSet(in_params_t &params_holder) const;

    int Size();

    EmotionalStateDescriptorStruct_t operator[](int num);
};
