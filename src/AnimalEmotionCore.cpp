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

#include "AnimalEmotionCore.hpp"

AnimalEmotionCore::AnimalEmotionCore() {

    // Title               : Biochemistry of Hormones that Influences Feelings
    // Author(s)           : Monica Butnariu & Ioan Sarac
    // Published           : 2019
    AddParam("adrenaline", 0);  ///< When need energy, minutes scale
    AddParam("cortisol", 0);    ///< Stress
    AddParam("dopamine", 0);    ///< Happiness and curiosity
    AddParam("melatonin", 0);   ///< When don't need energy, daily scale (opposite side: depression)
    AddParam("oxytocin", 0);    ///< Calm and trust (opposite side: anxiety)
    AddParam("serotonin", 0);   ///< Being kind (opposite side: anger, violence)

    //    Title               : Basic Emotions
    //    Author(s)           : Magda Kowalska
    //    Published           : 2017
    //TODO: conditions
    AddState({.name = "happiness, joy", .conditions = {}});
    AddState({.name = "sadness, grief", .conditions = {}});
    AddState({.name = "anger, rage", .conditions = {}});
    AddState({.name = "fear, anxiety", .conditions = {}});
}
