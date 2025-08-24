/* Copyright 2025 R. Thomas
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include <memory>
#include "../Analyzer.hpp"

#include "LIEF/MachO.hpp"

namespace analysis_plugin::macho {
class Analyzer : public analysis_plugin::Analyzer {
  public:
  Analyzer() = delete;
  Analyzer(std::unique_ptr<LIEF::MachO::Binary> impl, BinaryNinja::BinaryView& bv);

  void run() override;

  static std::unique_ptr<Analyzer> from_bv(BinaryNinja::BinaryView& bv);

  ~Analyzer() override = default;

  protected:
  std::unique_ptr<LIEF::MachO::Binary> macho_;
};
}
