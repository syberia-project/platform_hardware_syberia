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

Return<bool> SmartCharge::setChargingEnabled(bool enable) {
    set(CHARGE_CONTROL_PATH, enable ? 1 : 0);
    return true;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace smartcharge
}  // namespace syberia
}  // namespace vendor