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

#ifndef LYRA_NO_OP_PREPROCESSOR_H_
#define LYRA_NO_OP_PREPROCESSOR_H_

#include <cstdint>
#include <vector>

#include "absl/types/span.h"
#include "lyra/preprocessor_interface.h"

namespace chromemedia {
namespace codec {

// A pass-through preprocessor that does nothing to the input.
class NoOpPreprocessor : public PreprocessorInterface {
 public:
  // Returns a copy of the input.
  std::vector<int16_t> Process(absl::Span<const int16_t> input,
                               int sample_rate_hz) override {
    return std::vector<int16_t>(input.begin(), input.end());
  }
};

}  // namespace codec
}  // namespace chromemedia

#endif  // LYRA_NO_OP_PREPROCESSOR_H_
