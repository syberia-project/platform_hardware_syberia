#
# Copyright (C) 2021 Syberia Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    SmartCharge.cpp \
    service.cpp

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/include \

LOCAL_SHARED_LIBRARIES := \
    libbase \
    libbinder \
    libhidlbase \
    libutils \
    vendor.syberia.smartcharge@1.0

ifneq ($(TARGET_SMARTCHARGE_CONTROL_NODE),)
  LOCAL_CFLAGS += -DSMARTCHARGE_CONTROL_NODE=\"$(TARGET_SMARTCHARGE_CONTROL_NODE)\"
endif

ifeq ($(TARGET_SMARTCHARGE_REVERSE_LOGIC),true)
  LOCAL_CFLAGS += -DSMARTCHARGE_REVERSE_LOGIC
endif

LOCAL_MODULE := vendor.syberia.smartcharge@1.0-service
LOCAL_INIT_RC := vendor.syberia.smartcharge@1.0-service.rc
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_OWNER := syberia
LOCAL_VINTF_FRAGMENTS := vendor.syberia.smartcharge@1.0-service.xml

include $(BUILD_EXECUTABLE)