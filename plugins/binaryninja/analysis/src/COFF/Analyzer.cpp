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
#include "binaryninja/analysis/COFF/Analyzer.hpp"
#include "log.hpp"
#include "binaryninja/analysis/COFF/TypeBuilder.hpp"

#include <binaryninja/binaryninjaapi.h>
#include <binaryninja/binaryninjacore.h>

using namespace LIEF;

namespace analysis_plugin::coff {
Analyzer::Analyzer(std::unique_ptr<LIEF::COFF::Binary> impl, BinaryNinja::BinaryView& bv) :
  analysis_plugin::Analyzer(bv, std::make_unique<TypeBuilder>(bv)),
  coff_(std::move(impl))
{
}

std::unique_ptr<Analyzer> Analyzer::from_bv(BinaryNinja::BinaryView& bv) {
  static const COFF::ParserConfig CONFIG = COFF::ParserConfig::all();
  std::string filename = bv.GetFile()->GetOriginalFilename();

  std::unique_ptr<COFF::Binary> coff = COFF::Parser::parse(filename, CONFIG);
  if (coff == nullptr) {
    BN_ERR("Can't parse '{}'", filename);
    return nullptr;
  }

  return std::make_unique<Analyzer>(std::move(coff), bv);
}

void Analyzer::run() {

}
}
