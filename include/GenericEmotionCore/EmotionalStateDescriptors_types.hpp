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
#include <map>
#include <set>
#include <string>
#include <vector>

/**
 * @brief Conditional operators
 */
typedef enum {
    EQUALS = 0x0,
    NOT_EQUALS,
    GREATER_THAN,
    GREATER_THAN_OR_EQUAL,
    LESS_THAN,
    LESS_THAN_OR_EQUAL
} ConditionalOperatorsEnum_t;

/**
 * @brief Describes a condition of a parameter, e.g. (Parameter A <= 1.234)
 */
typedef struct {
    std::string param;
    ConditionalOperatorsEnum_t op;
    float value;
} ConditionStruct_t;

/**
 * @brief Container for storing several conditions
 */
typedef std::vector<ConditionStruct_t> ConditionsVector_t;

typedef struct {
    std::string name;
    ConditionsVector_t conditions;
} EmotionalStateDescriptorStruct_t;

typedef std::list<EmotionalStateDescriptorStruct_t> EmotionalStateDescriptorsList_t;