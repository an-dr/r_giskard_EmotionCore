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

#include "GenericEmotionCore/GenericEmotionCore.hpp"

using namespace std;


emotion_core_err_t GenericEmotionCore::UpdateCurrentEmotionalState() {
    EmotionalStateDescriptorsList_t::const_iterator est_it;
    for (est_it = states.GetList().begin(); est_it != states.GetList().end(); est_it++) {
        if (CheckState(&*est_it)) {
            SetState(&*est_it);
            return NO_ERROR;
        }
    }
    SetState(nullptr);
    return NO_ERROR;
}

emotion_core_err_t GenericEmotionCore::WriteSensorData(SensorDataStruct_t data) {
    RETURN_ON_ERROR(UpdateCoreParamsFromSensorData(data));
    RETURN_ON_ERROR(UpdateParamsTotal());
    RETURN_ON_ERROR(UpdateCurrentEmotionalState());
    return NO_ERROR;
}

const EmotionalStateDescriptorStruct_t *GenericEmotionCore::GetState() {
    if (_EmotionalState_p != NULL) {
        return _EmotionalState_p;
    } else {
        return &_non_specified_state;
    }
}

const CoreParamsMap_t *GenericEmotionCore::GetParams() {
    return _params_total.GetParams();
}

emotion_core_err_t GenericEmotionCore::WriteTempImpact(const TemporaryCoreImpact_t &data) {
    _params_tempImpacts.push_back(data);
    RETURN_ON_ERROR(UpdateParamsTotal());
    RETURN_ON_ERROR(UpdateCurrentEmotionalState());
    return NO_ERROR;
}

emotion_core_err_t GenericEmotionCore::UpdateCoreParamsFromSensorData(const SensorDataStruct_t &data) {
    float old_s_val                        = _sensorValues[data.sensor_name];
    float new_s_val                        = data.value;
    float delta_s_val                      = new_s_val - old_s_val;
    const InDataDescriptorStruct_t *in_dsc = GetDescriptorForInData(data);
    if (!in_dsc) {
        return ERROR_WRONGSTATE;
    }
    for (auto i = in_dsc->weights.begin(); i != in_dsc->weights.end(); i++) {
        float val_delta = i->weight * delta_s_val;
        _params_sensorsImpacts.IncrementParam(i->core_param_name, val_delta);
    }
    _sensorValues[data.sensor_name] = new_s_val;
    return NO_ERROR;
}

const InDataDescriptorStruct_t *GenericEmotionCore::GetDescriptorForInData(const SensorDataStruct_t &data) const {
    InDataDescriptorsList_t::const_iterator indsc_it;
    for (indsc_it = inDataDescriptors.GetList().begin(); indsc_it != inDataDescriptors.GetList().end(); indsc_it++) {
        if (indsc_it->sensor_name == data.sensor_name) {
            return &*indsc_it;
        }
    }
    return nullptr;
}

emotion_core_err_t GenericEmotionCore::CheckParamVsCondition(const string &par_name, const float &par_val, const ConditionStruct_t &cond) {
    if (par_name != cond.param) {
        return ERROR_INVAL;
    }
    if (par_val == cond.value) {
        if ((cond.op == EQUALS) || (cond.op == GREATER_THAN_OR_EQUAL) ||
            (cond.op == LESS_THAN_OR_EQUAL)) {
            return NO_ERROR;
        }
    } else if (par_val < cond.value) {
        if ((cond.op == LESS_THAN) || (cond.op == LESS_THAN_OR_EQUAL)) {
            return NO_ERROR;
        }
    } else {
        if ((cond.op == GREATER_THAN) || (cond.op == GREATER_THAN_OR_EQUAL)) {
            return NO_ERROR;
        }
    }
    return ERROR_FAIL;
}

bool GenericEmotionCore::CheckState(const EmotionalStateDescriptorStruct_t *emo) {
    bool res = false;
    emotion_core_err_t comp_result;
    for (auto conds_it = emo->conditions.begin(); conds_it != emo->conditions.end(); conds_it++) {
        for (auto core_param_it = _params_total.GetParams()->begin();
             core_param_it != _params_total.GetParams()->end();
             core_param_it++) {
            comp_result = CheckParamVsCondition(core_param_it->first, core_param_it->second, *conds_it);
            if (comp_result == ERROR_FAIL) {
                return false;  // if any fail - return false
            } else if (comp_result == ERROR_INVAL) {
                continue;  // non-comparable params
            } else {
                res = true;
            }
        }
    }
    return res;
}

emotion_core_err_t GenericEmotionCore::UpdateCoreParamsWithTimeUpdate(const int &time_duration_ms) {
    float change;
    for (auto it = _params_tempImpacts.begin(); it != _params_tempImpacts.end();) {
        change = abs((*it).change_per_sec) * time_duration_ms * 0.001;
        if (it->delta_value < 0) {
            it->delta_value += change;
            if (it->delta_value > 0) {
                it = _params_tempImpacts.erase(it);
                continue;
            }
        }
        if (it->delta_value > 0) {
            it->delta_value -= change;
            if (it->delta_value < 0) {
                it = _params_tempImpacts.erase(it);
                continue;
            }
        }
        if (it->delta_value == 0) {
            it = _params_tempImpacts.erase(it);
            continue;
        }
        it++;
    }
    return NO_ERROR;
}

emotion_core_err_t GenericEmotionCore::WriteTime(const int &time_duration_ms) {
    RETURN_ON_ERROR(UpdateCoreParamsWithTimeUpdate(time_duration_ms));
    time_ms += time_duration_ms;
    RETURN_ON_ERROR(UpdateParamsTotal());
    RETURN_ON_ERROR(UpdateCurrentEmotionalState());
    return NO_ERROR;
}

emotion_core_err_t GenericEmotionCore::SetState(const EmotionalStateDescriptorStruct_t *state) {
    _EmotionalState_p = state;
    return NO_ERROR;
}

GenericEmotionCore::GenericEmotionCore() : _EmotionalState_p(nullptr),
                                           _non_specified_state({.name = "non-specified", .conditions = {}}),
                                           time_ms(0) {}

emotion_core_err_t GenericEmotionCore::UpdateParamsTotal() {
    float val;
    for (auto i = _params_base.GetParams()->begin(); i != _params_base.GetParams()->end(); i++) {
        val = _params_base.GetParam(i->first);
        val += _params_sensorsImpacts.GetParam(i->first);
        for (auto i_tmp = _params_tempImpacts.begin(); i_tmp != _params_tempImpacts.end(); i_tmp++) {
            if (i_tmp->param_name == i->first) {
                val += i_tmp->delta_value;
            }
        }
        RETURN_ON_ERROR(_params_total.SetParam(i->first, val));
    }
    return NO_ERROR;
}

emotion_core_err_t GenericEmotionCore::AddParam(const string &name, float default_value) {
    RETURN_ON_ERROR(_params_base.AddParam(name, default_value));
    RETURN_ON_ERROR(_params_sensorsImpacts.AddParam(name, 0));
    RETURN_ON_ERROR(_params_total.AddParam(name, 0));
    return NO_ERROR;
}
emotion_core_err_t GenericEmotionCore::AddState(EmotionalStateDescriptorStruct_t newState) {
    for (auto i = newState.conditions.begin(); i != newState.conditions.end(); i++) {
        if (!_params_base.IsParamExists(i->param)) {
            CRITICAL_ERROR(ERROR_NOENT, "Parameter in the Emotion State Descriptor is not represented in this core yet.");
        }
    }
    RETURN_ON_ERROR(states.Add(newState));
    RETURN_ON_ERROR(UpdateCurrentEmotionalState());
    return NO_ERROR;
}
emotion_core_err_t GenericEmotionCore::AddSensorDataDescriptor(const InDataDescriptorStruct_t &newDescriptor) {
    for (auto i = newDescriptor.weights.begin(); i != newDescriptor.weights.end(); i++) {
        if (!_params_base.IsParamExists(i->core_param_name)) {
            CRITICAL_ERROR(ERROR_NOENT, "Parameter in the Data Descriptor is not represented in this core yet.");
        }
    }
    return inDataDescriptors.Add(newDescriptor);
}
