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

#ifndef COMMON_SMARTCHARGE_H
#define COMMON_SMARTCHARGE_H

#ifndef SMARTCHARGE_CONTROL_NODE
#define CHARGE_CONTROL_PATH "/sys/class/power_supply/battery/charging_enabled"
#else
#define CHARGE_CONTROL_PATH SMARTCHARGE_CONTROL_NODE
#endif

#ifdef SMARTCHARGE_REVERSE_LOGIC
#define SMARTCHARGE_REVERSE_LOGIC
#endif

#define SUSPEND_LEVEL 85
#define RESUME_LEVEL 80

#endif // COMMON_SMARTCHARGE_H