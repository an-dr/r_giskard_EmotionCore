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

typedef struct {
    float change_per_sec;    ///< coefficient proportional the time how long the impact will take place
    std::string param_name;  ///< name of a parameter affected by the impact
    float delta_value;       ///< how much will be added to the given parameter
} TemporaryCoreImpact_t;

typedef std::list<TemporaryCoreImpact_t> TemporaryCoreImpactsList_t;