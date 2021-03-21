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

#include "GenericEmotionCore/GenericEmotionCore.hpp"

class AnimalEmotionCore : private GenericEmotionCore {
protected:
    using GenericEmotionCore::UpdateParamsTotal;
    emotion_core_err_t UpdateParamsTotal();
public:
    AnimalEmotionCore();
    using GenericEmotionCore::time_ms;
    using GenericEmotionCore::AddSensorDataDescriptor;
    using GenericEmotionCore::GetParams;
    using GenericEmotionCore::GetState;
    using GenericEmotionCore::WriteSensorData;
    using GenericEmotionCore::WriteTempImpact;
    using GenericEmotionCore::WriteTime;
};
