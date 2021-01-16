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

#include <map>
#include <string>
#include "CoreParams_types.hpp"
#include "InDataDescriptors.hpp"
#include "error_t.h"

typedef std::map<std::string, float> CoreParamsMap_t;

class CoreParams {
private:
    CoreParamsMap_t _map;

public:
    bool IsParamExists(const std::string &name);

    error_t AddParam(const std::string &name);

    error_t AddParam(const std::string &name, float init_value);

    error_t IncrementParam(const std::string &name, float value);

    error_t LoadParamsSet(const in_params_t &params_set);

    float GetParam(const std::string &name);

    const CoreParamsMap_t *GetParams();

    error_t RemoveAllParams();

    error_t SetParam(const std::string &name, float value);
};
