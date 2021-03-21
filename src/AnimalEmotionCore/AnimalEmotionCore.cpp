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

#include "AnimalEmotionCore/AnimalEmotionCore.hpp"

AnimalEmotionCore::AnimalEmotionCore() {

    // Title               : Biochemistry of Hormones that Influences Feelings
    // Author(s)           : Monica Butnariu & Ioan Sarac
    // Published           : 2019
    // TODO: set values based on real human data
    AddParam("adrenaline", 100);  ///< When need energy, minutes scale
    AddParam("cortisol", 100);    ///< Stress
    AddParam("dopamine", 100);    ///< Happiness and curiosity
    AddParam("melatonin", 100);   ///< When don't need energy, daily scale (opposite side: depression)
    AddParam("oxytocin", 100);    ///< Calm and trust (opposite side: anxiety)
    AddParam("serotonin", 100);   ///< Being kind (opposite side: anger, violence)

    //    Title               : Basic Emotions
    //    Author(s)           : Magda Kowalska
    //    Published           : 2017
    //TODO: conditions
    AddState({.name = "happiness, joy", .conditions = {}});
    AddState({.name = "sadness, grief", .conditions = {}});
    AddState({.name = "anger, rage", .conditions = {}});
    AddState({.name = "fear, anxiety", .conditions = {}});

    UpdateCoreParamsWithTimeUpdate(0);
    UpdateParamsTotal();
    UpdateCurrentEmotionalState();
}


emotion_core_err_t AnimalEmotionCore::UpdateParamsTotal() {
    float val;
    for (auto i = _params_base.GetParams()->begin(); i != _params_base.GetParams()->end(); i++) {
        val = _params_base.GetParam(i->first);
        val += _params_sensorsImpacts.GetParam(i->first);
        for (auto i_tmp = _params_tempImpacts.begin(); i_tmp != _params_tempImpacts.end(); i_tmp++) {
            if (i_tmp->param_name == i->first) {
                val += i_tmp->delta_value;
            }
        }
        if (val < 0) {
            val = 0;
        }
        RETURN_ON_ERROR(_params_total.SetParam(i->first, val));
    }
    return NO_ERROR;
}
