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

#ifndef VENDOR_SYBERIA_SMARTCHARGE_V1_0_SMARTCHARGE_H
#define VENDOR_SYBERIA_SMARTCHARGE_V1_0_SMARTCHARGE_H

#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <vendor/syberia/smartcharge/1.0/ISmartCharge.h>

namespace vendor {
namespace syberia {
namespace smartcharge {
namespace V1_0 {
namespace implementation {

using ::android::sp;
using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;

using ::vendor::syberia::smartcharge::V1_0::ISmartCharge;


struct SmartCharge : public ISmartCharge {
    Return<bool> setChargingEnabled(bool enable) override;
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace smartcharge
}  // namespace syberia
}  // namespace vendor

#endif  // VENDOR_SYBERIA_SMARCHARGE_V1_0_SMARTCHARGE_H