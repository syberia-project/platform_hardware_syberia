/*
 * Copyright (C) 2021 Syberia Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "smartcharge@1.0-service"

#include "SmartCharge.h"
#include <android-base/logging.h>
#include <fstream>
#include <iostream>
#include "smartcharge.h"

namespace vendor {
namespace syberia {
namespace smartcharge {
namespace V1_0 {
namespace implementation {

/*
 * Write value to path and close file.
 */
template <typename T>
static void set(const std::string& path, const T& value) {
    std::ofstream file(path);

    if (!file) {
        PLOG(ERROR) << "Failed to open: " << path;
        return;
    }

    LOG(DEBUG) << "write: " << path << " value: " << value;

    file << value << std::endl;

    if (!file) {
        PLOG(ERROR) << "Failed to write: " << path << " value: " << value;
    }
}

template <typename T>
static T get(const std::string& path, const T& def) {
    std::ifstream file(path);

    if (!file) {
        PLOG(ERROR) << "Failed to open: " << path;
        return def;
    }

    T result;

    file >> result;

    if (file.fail()) {
        PLOG(ERROR) << "Failed to read: " << path;
        return def;
    } else {
        LOG(DEBUG) << "read: " << path << " value: " << result;
        return result;
    }
}

SmartCharge::SmartCharge()
    : mSuspended(false),
      mEnabled(false),
      mResumeLevel(RESUME_LEVEL),
      mSuspendLevel(SUSPEND_LEVEL),
      mCapacity(0) {
}

Return<bool> SmartCharge::setSmartChargeEnabled(bool enable) {
    if (enable != mEnabled) {
        LOG(INFO) << "SmartCharge enabled: " << enable;
        mEnabled = enable;
        suspendIfNeeded();
    }
    return true;
}

Return<bool> SmartCharge::getChargingEnable() {
#ifdef SMARTCHARGE_REVERSE_LOGIC
    return get(CHARGE_CONTROL_PATH, 0) == 0;
#else
    return get(CHARGE_CONTROL_PATH, 0) > 0;
#endif
}

void SmartCharge::suspendIfNeeded() {
    if ((!getChargingEnable() && (mCapacity <= mResumeLevel)) ||
            !mEnabled || (mEnabled && (mSuspendLevel > mCapacity))) {
#ifdef SMARTCHARGE_REVERSE_LOGIC
        set(CHARGE_CONTROL_PATH, 0);
#else
        set(CHARGE_CONTROL_PATH, 1);
#endif
        LOG(INFO) << "Charging enabled";
    }

    if (mEnabled && getChargingEnable() && (mCapacity >= mSuspendLevel)) {
        LOG(INFO) << "Charging disabled";
#ifdef SMARTCHARGE_REVERSE_LOGIC
        set(CHARGE_CONTROL_PATH, 1);
#else
        set(CHARGE_CONTROL_PATH, 0);
#endif
    }
}

Return<bool> SmartCharge::updateCapacity(int32_t capacity) {
    if (capacity != mCapacity) {
        LOG(INFO) << "Updating capacity: " << capacity;
        mCapacity = capacity;
        suspendIfNeeded();
    }
    return true;
}

Return<int32_t> SmartCharge::getResumeLevel() {
    return mResumeLevel;
}

Return<int32_t> SmartCharge::getSuspendLevel() {
    return mSuspendLevel;
}

Return<bool> SmartCharge::updateBatteryLevels(int32_t suspendLevel, int32_t resumeLevel) {
    mSuspendLevel = suspendLevel;
    mResumeLevel = resumeLevel;
    LOG(INFO) << "Suspend level: " << mSuspendLevel;
    LOG(INFO) << "Resume level: " << mResumeLevel;
    suspendIfNeeded();
    return true;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace smartcharge
}  // namespace syberia
}  // namespace vendor