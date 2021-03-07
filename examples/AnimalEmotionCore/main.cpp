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

#include <cstdio>
#include "AnimalEmotionCore/AnimalEmotionCore.hpp"


#define PRINT_STATE                                                                   \
    do {                                                                              \
        for (auto i = core.GetParams()->begin(); i != core.GetParams()->end(); ++i) { \
            printf("    %s  : \t%.2f\n", i->first.c_str(), i->second);                \
        }                                                                             \
    } while (0)


int main() {

    AnimalEmotionCore core = AnimalEmotionCore();

    /* Adding data descriptors */
    InDataDescriptorStruct_t light_sensor = {
            .sensor_name = "light_detector",
            .val_min     = 0,
            .val_max     = 255,
            .weights     = {
                    {.core_param_name = "adrenaline", .weight = -0.2},
                    {.core_param_name = "dopamine", .weight = 0.3},
                    {.core_param_name = "serotonin", .weight = 0.2},
            }};
    InDataDescriptorStruct_t proximity = {
            .sensor_name = "proximity_sensor",
            .val_min     = 0,
            .val_max     = 255,
            .weights     = {
                    {.core_param_name = "adrenaline", .weight = 0.3},
                    {.core_param_name = "cortisol", .weight = 0.3},
                    {.core_param_name = "dopamine", .weight = -0.3},
            }};
    core.AddSensorDataDescriptor(light_sensor);
    core.AddSensorDataDescriptor(proximity);

    TemporaryCoreImpact_t bad_thought = {
            .change_per_sec = 5,
            .param_name     = "cortisol",
            .delta_value    = 30};

    printf("\nInitial state:\n");
    PRINT_STATE;

    core.WriteTempImpact(bad_thought);
    printf("\nRight after a temprorary impact:\n");
    printf("    time: %d ms\n", core.time_ms);
    PRINT_STATE;

    core.WriteTime(500);
    printf("\n500 ms later:\n");
    printf("    time: %d ms\n", core.time_ms);
    PRINT_STATE;

    core.WriteTime(100000);
    printf("\n> 100sec later:\n");
    printf("    time: %d ms\n", core.time_ms);
    PRINT_STATE;


    core.WriteSensorData({"light_detector", 0x120});
    printf("\nLight was significantly increased:\n");
    PRINT_STATE;

    core.WriteSensorData({"light_detector", 60});
    printf("\nLight was slightly decreased:\n");
    PRINT_STATE;


    core.WriteSensorData({"proximity_sensor", 300});
    printf("\nWe've put something close to the robot:\n");
    PRINT_STATE;

    core.WriteSensorData({"proximity_sensor", 0});
    core.WriteSensorData({"light_detector", 0});
    printf("\nRemoved light and the obstacle:\n");
    PRINT_STATE;

    return 0;
}