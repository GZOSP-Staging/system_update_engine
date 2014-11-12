// Copyright (c) 2013 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UPDATE_ENGINE_MOCK_HARDWARE_H_
#define UPDATE_ENGINE_MOCK_HARDWARE_H_

#include <string>
#include <vector>

#include "update_engine/fake_hardware.h"

#include <gmock/gmock.h>

namespace chromeos_update_engine {

// A mocked, fake implementation of HardwareInterface.
class MockHardware : public HardwareInterface {
 public:
  MockHardware() {
    // Delegate all calls to the fake instance
    ON_CALL(*this, BootKernelDevice())
      .WillByDefault(testing::Invoke(&fake_,
            &FakeHardware::BootKernelDevice));
    ON_CALL(*this, BootDevice())
      .WillByDefault(testing::Invoke(&fake_,
            &FakeHardware::BootDevice));
    ON_CALL(*this, IsBootDeviceRemovable())
      .WillByDefault(testing::Invoke(&fake_,
            &FakeHardware::IsBootDeviceRemovable));
    ON_CALL(*this, GetKernelDevices())
      .WillByDefault(testing::Invoke(&fake_,
            &FakeHardware::GetKernelDevices));
    ON_CALL(*this, IsKernelBootable(testing::_, testing::_))
      .WillByDefault(testing::Invoke(&fake_,
            &FakeHardware::IsKernelBootable));
    ON_CALL(*this, MarkKernelUnbootable(testing::_))
      .WillByDefault(testing::Invoke(&fake_,
            &FakeHardware::MarkKernelUnbootable));
    ON_CALL(*this, IsOfficialBuild())
      .WillByDefault(testing::Invoke(&fake_,
            &FakeHardware::IsOfficialBuild));
    ON_CALL(*this, IsNormalBootMode())
      .WillByDefault(testing::Invoke(&fake_,
            &FakeHardware::IsNormalBootMode));
    ON_CALL(*this, IsOOBEComplete(testing::_))
      .WillByDefault(testing::Invoke(&fake_,
            &FakeHardware::IsOOBEComplete));
    ON_CALL(*this, GetHardwareClass())
      .WillByDefault(testing::Invoke(&fake_,
            &FakeHardware::GetHardwareClass));
    ON_CALL(*this, GetFirmwareVersion())
      .WillByDefault(testing::Invoke(&fake_,
            &FakeHardware::GetFirmwareVersion));
    ON_CALL(*this, GetECVersion())
      .WillByDefault(testing::Invoke(&fake_,
            &FakeHardware::GetECVersion));
    ON_CALL(*this, GetPowerwashCount())
      .WillByDefault(testing::Invoke(&fake_,
            &FakeHardware::GetPowerwashCount));
  }

  ~MockHardware() override {}

  // Hardware overrides.
  MOCK_CONST_METHOD0(BootKernelDevice, std::string());
  MOCK_CONST_METHOD0(BootDevice, std::string());
  MOCK_CONST_METHOD0(IsBootDeviceRemovable, bool());
  MOCK_CONST_METHOD0(GetKernelDevices, std::vector<std::string>());
  MOCK_CONST_METHOD2(IsKernelBootable,
               bool(const std::string& kernel_device, bool* bootable));
  MOCK_METHOD1(MarkKernelUnbootable,
               bool(const std::string& kernel_device));
  MOCK_CONST_METHOD0(IsOfficialBuild, bool());
  MOCK_CONST_METHOD0(IsNormalBootMode, bool());
  MOCK_CONST_METHOD1(IsOOBEComplete, bool(base::Time* out_time_of_oobe));
  MOCK_CONST_METHOD0(GetHardwareClass, std::string());
  MOCK_CONST_METHOD0(GetFirmwareVersion, std::string());
  MOCK_CONST_METHOD0(GetECVersion, std::string());
  MOCK_CONST_METHOD0(GetPowerwashCount, int());

  // Returns a reference to the underlying FakeHardware.
  FakeHardware& fake() {
    return fake_;
  }

 private:
  // The underlying FakeHardware.
  FakeHardware fake_;

  DISALLOW_COPY_AND_ASSIGN(MockHardware);
};


}  // namespace chromeos_update_engine

#endif  // UPDATE_ENGINE_MOCK_HARDWARE_H_
