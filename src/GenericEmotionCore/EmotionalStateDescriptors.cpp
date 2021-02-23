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

#include <algorithm>
#include "GenericEmotionCore/EmotionalStateDescriptors.hpp"

using namespace std;

emotion_core_err_t EmotionalStateDescriptors::Add(EmotionalStateDescriptorStruct_t newState) {
    for (auto i = _list.begin(); i != _list.end(); i++) {
        if (newState.name == i->name) {
            return ERROR_EXIST;  // state already exists
        }
    }
    _list.push_back(newState);
    return NO_ERROR;
}

emotion_core_err_t EmotionalStateDescriptors::Remove(string name) {
    for (auto i = _list.begin(); i != _list.end(); i++) {
        if (name == i->name) {
            _list.erase(i);
            return NO_ERROR;
        }
    }
    return ERROR_NOTEXIST;  // state didn't exists
}

const EmotionalStateDescriptorStruct_t *EmotionalStateDescriptors::Get(string name) const {
    for (auto i = _list.begin(); i != _list.end(); i++) {
        if (name == i->name) {
            return &*i;
        }
    }
    return nullptr;  // state didn't exists
}

emotion_core_err_t EmotionalStateDescriptors::GetParamsSet(in_params_t &params_holder) const {
    for (auto i_est = _list.begin(); i_est != _list.end(); i_est++) {
        for (auto i_cond = i_est->conditions.begin(); i_cond != i_est->conditions.end(); i_cond++) {
            params_holder.insert(i_cond->param);
        }
    }
    return NO_ERROR;
}

const EmotionalStateDescriptorsList_t &EmotionalStateDescriptors::GetList() const {
    return _list;
}

int EmotionalStateDescriptors::Size() {
    return _list.size();
}

EmotionalStateDescriptorStruct_t EmotionalStateDescriptors::operator[](int num) {
    return *(std::next(_list.begin(), num));
}

EmotionalStateDescriptors::EmotionalStateDescriptors() : _list() {}
