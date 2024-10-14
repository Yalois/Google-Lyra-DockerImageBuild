/*
 * Copyright 2021 Google LLC
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

#ifndef LYRA_RESAMPLER_INTERFACE_H_
#define LYRA_RESAMPLER_INTERFACE_H_

#include <cstdint>
#include <vector>

#include "absl/types/span.h"

namespace chromemedia {
namespace codec {

class ResamplerInterface {
 public:
  virtual ~ResamplerInterface() {}

  virtual std::vector<int16_t> Resample(absl::Span<const int16_t> audio) = 0;

  virtual void Reset() = 0;

  virtual int input_sample_rate_hz() const = 0;

  virtual int target_sample_rate_hz() const = 0;

  virtual int samples_until_steady_state() const = 0;
};

}  // namespace codec
}  // namespace chromemedia

#endif  // LYRA_RESAMPLER_INTERFACE_H_
