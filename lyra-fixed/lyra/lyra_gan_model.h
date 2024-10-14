/*
 * Copyright 2022 Google LLC
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

#ifndef LYRA_LYRA_GAN_MODEL_H_
#define LYRA_LYRA_GAN_MODEL_H_

#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

#include "include/ghc/filesystem.hpp"
#include "lyra/generative_model_interface.h"
#include "lyra/tflite_model_wrapper.h"

namespace chromemedia {
namespace codec {

// This class wraps a LyraGAN TFLite model to generate samples.
class LyraGanModel : public GenerativeModel {
 public:
  // Returns a nullptr on failure.
  static std::unique_ptr<LyraGanModel> Create(
      const ghc::filesystem::path& model_path, int num_features);

  ~LyraGanModel() override {}

 private:
  explicit LyraGanModel(std::unique_ptr<TfLiteModelWrapper> model,
                        int num_features);

  bool RunConditioning(const std::vector<float>& features) override;

  std::optional<std::vector<int16_t>> RunModel(int num_samples) override;

  const std::unique_ptr<TfLiteModelWrapper> model_;
};

}  // namespace codec
}  // namespace chromemedia

#endif  // LYRA_LYRA_GAN_MODEL_H_
