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
#include <vector>
#include "error_t.h"
#include "GenericEmotionCore/CoreParams.hpp"
#include "GenericEmotionCore/EmotionalStateDescriptors.hpp"
#include "GenericEmotionCore/InDataDescriptors.hpp"
#include "GenericEmotionCore/TemporaryCoreImpact.hpp"

class GenericEmotionCore {
private:
    const EmotionalStateDescriptorStruct_t *_EmotionalState_p;  ///< NULL means - non-specified state

    EmotionalStateDescriptorStruct_t _non_specified_state; // FIXME bad idea, do it better

    CoreParams _params_total;

    /**
    * @brief base names and values of the core parameters. You cannot add a Temporary impact or Sensor data using parameter name beside this list
    */
    CoreParams _params_base;

    CoreParams _params_sensorsImpacts;

    TemporaryCoreImpactsList_t _params_tempImpacts;

    std::map<std::string, float> _sensorValues;

    /**
    * @brief Set current Emotion state based on set EmotionalStates object and current _coreState
    * @return
    */
    error_t UpdateCurrentEmotionalState();

    error_t UpdateParamsTotal();

    const InDataDescriptorStruct_t *GetDescriptorForInData(const SensorDataStruct_t &data) const;

    error_t UpdateCoreParamsFromSensorData(const SensorDataStruct_t &data);

    error_t UpdateCoreParamsWithTimeUpdate(const int &time_duration_ms);

    static error_t CheckParamVsCondition(const std::string &par_name,
                                         const float &par_val,
                                         const ConditionStruct_t &cond);

    bool CheckState(const EmotionalStateDescriptorStruct_t *emo);

    error_t SetState(const EmotionalStateDescriptorStruct_t *state);

protected:
public:
    GenericEmotionCore();

    InDataDescriptors inDataDescriptors;  ///< an object storing description of input data

    EmotionalStateDescriptors states;  ///< an object storing possible Emotion states

    error_t AddParam(const std::string &name, float default_value);

    error_t AddState(EmotionalStateDescriptorStruct_t newState);

    error_t AddSensorDataDescriptor(const InDataDescriptorStruct_t &newDescriptor);


    /**
     * @brief Update current Emotion state using set InDataDescriptors and input data
     * @param data sensor name and current value
     * @return
     */
    error_t WriteSensorData(SensorDataStruct_t data);

    /**
     * @brief
     * @param data
     * @return
     */
    error_t WriteTempImpact(const TemporaryCoreImpact_t &data);

    /**
     * @brief Get a constant pointer to current Emotion state
     * @return pointer to the state
     */
    const EmotionalStateDescriptorStruct_t *GetState();

    error_t WriteTime(const int &time_duration_ms);
    //    TODO:
    //    EmotionCore(const InDataDescriptorsList_t &descriptors, const EmotionalStatesList_t &states);
    //    EmotionalStateStruct_t GetState();
    //    EmotionCore(vector<EmotionalStateStruct_t> states);
    //    EmotionCore(vector<InDataDescriptorStruct_t> descriptors);
    //    int AddEmotionalStates(vector<EmotionalStateStruct_t> states);
};
