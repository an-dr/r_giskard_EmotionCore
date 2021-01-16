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
#include "GenericEmotionCore.hpp"


int main()
{

    GenericEmotionCore core = GenericEmotionCore();
    core.AddParam("activity", 0);
    core.AddParam("happiness", 0);


    /* Adding Emotion states */
    EmotionalStateDescriptorStruct_t state_panic = {
            .name       = "in panic",
            .conditions = {
                    {"activity", GREATER_THAN, 50},
                    {"happiness", LESS_THAN_OR_EQUAL, 0},
            }
    };
    EmotionalStateDescriptorStruct_t state_happiness = {
            .name       = "happy",
            .conditions = {
                    {"activity", LESS_THAN, 10},
                    {"happiness", GREATER_THAN, 50},
            }
    };
    EmotionalStateDescriptorStruct_t state_calm = {
            .name       = "calm",
            .conditions = {
                    {"activity", LESS_THAN, 10},
                    {"activity", GREATER_THAN, -10},
                    {"happiness", LESS_THAN, 10},
                    {"happiness", GREATER_THAN, -10},
            }
    };
    core.AddState(state_panic);
    core.AddState(state_happiness);
    core.AddState(state_calm);

    /* Adding data descriptors */
    InDataDescriptorStruct_t light_sensor = {
            .sensor_name = "light_detector",
            .val_min     = 0,
            .val_max     = 255,
            .weights     = {
                    {.core_param_name = "activity", .weight = -0.2},
                    {.core_param_name = "happiness", .weight = 0.3},
            }
    };
    InDataDescriptorStruct_t proximity = {
            .sensor_name = "proximity_sensor",
            .val_min     = 0,
            .val_max     = 255,
            .weights     = {
                    {.core_param_name = "activity", .weight = 0.3},
                    {.core_param_name = "happiness", .weight = -0.3},
            }
    };
    core.AddSensorDataDescriptor(light_sensor);
    core.AddSensorDataDescriptor(proximity);

    TemporaryCoreImpact_t bad_thought = {
            .change_per_sec = 5,
            .param_name = "happiness",
            .delta_value = -30
    };
    core.WriteTempImpact(bad_thought);
    core.WriteTime(500);
    core.WriteTime(2000);
    core.WriteTime(100000);

    /* Write sensor data */

    printf("Zakhar is %s\n", core.GetState()->name.c_str());

    /*  >>>>>>>>>>> Zakhar is calm - in empty dark space */
    core.WriteSensorData({"light_detector", 0x10});//increasing light
    core.WriteSensorData({"light_detector", 0x50});
    core.WriteSensorData({"light_detector", 0x100});
    core.WriteSensorData({"light_detector", 0x120});


    /*  >>>>>>>>>>> MAXIMUM LIGHT HERE - Zakhar is happy! */
    printf("Zakhar is %s\n", core.GetState()->name.c_str());

    core.WriteSensorData({"light_detector", 60});// decreasing light a bit
    /* >>>>>>>>>>> Zakhar is confused */
    printf("Zakhar is %s\n", core.GetState()->name.c_str());



    core.WriteSensorData({"proximity_sensor", 60});// place near Zakhar some obstacle
    /* >>>>>>>>>>> Zakhar is calm - Zakhar is calm in a relatively small half-dark space */

    core.WriteSensorData({"proximity_sensor", 200});// getting closer the obstacle
    core.WriteSensorData({"proximity_sensor", 300});// super close!
    /* >>>>>>>>>>> Zakhar is panicking, CLAUSTROPHOBIA!! */
    printf("Zakhar is %s\n", core.GetState()->name.c_str());

    //remove light and the obstacle
    core.WriteSensorData({"proximity_sensor", 0});
    core.WriteSensorData({"light_detector", 0});
    /*  >>>>>>>>>>> Zakhar is calm - in empty dark space */
    printf("Zakhar is %s\n", core.GetState()->name.c_str());

    return 0;
}