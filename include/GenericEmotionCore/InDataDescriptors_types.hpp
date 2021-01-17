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
#include <set>
#include <string>
#include <vector>

/**
 * @brief Describes the data coming from a sensor, e.g. {"light sensor 1", 10}
 */
typedef struct {
    std::string sensor_name;
    float value;
} SensorDataStruct_t;

/**
 * @brief Mind data is a data temporary affecting core parameters.
 */
typedef struct {
    std::string param_name;
    float delta_impact;
    float time_param;
} MindDataStruct_t;


typedef std::set<std::string> in_params_t;

typedef struct {
    std::string core_param_name;
    float weight;
} SensorDataWeightStruct_t;

typedef std::vector<SensorDataWeightStruct_t> SensorDataWeightsVector_t;

/**
 * The value from the sensor can affect several core parameters at once
 */
typedef struct {
    std::string sensor_name;
    int val_min;
    int val_max;
    SensorDataWeightsVector_t weights;
} InDataDescriptorStruct_t;
typedef std::list<InDataDescriptorStruct_t> InDataDescriptorsList_t;
