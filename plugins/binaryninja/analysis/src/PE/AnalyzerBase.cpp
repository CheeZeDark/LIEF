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
#include "PE/AnalyzerBase.hpp"
#include "LIEF/PE.hpp"

namespace analysis_plugin::pe {
uint64_t AnalyzerBase::get_va(uint64_t rva) const {
  if (rva > pe_.imagebase()) {
    return rva;
  }
  return pe_.imagebase() + rva;
}

uint64_t AnalyzerBase::translate_addr(uint64_t addr) const {
  if (addr >= pe_.imagebase()) {
    return (addr - pe_.imagebase()) + bv_.GetImageBase();
  }
  return addr;
}
}
