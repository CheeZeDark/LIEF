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

#include <LIEF/PE/ParserConfig.hpp>
#include <LIEF/ELF/ParserConfig.hpp>
#include <LIEF/MachO/ParserConfig.hpp>

namespace LIEF {
class Binary;
}

namespace BinaryNinja {
class BinaryView;
class QualifiedName;
class LinearDisassemblyLine;
}

namespace binaryninja {

enum class FileFormat {
  Unknown = 0,
  ELF, PE, MachO, COFF, DSC
};

FileFormat get_file_format(BinaryNinja::BinaryView& bv);

std::unique_ptr<LIEF::Binary> get_bin(BinaryNinja::BinaryView& bv);

std::string to_string(const BinaryNinja::QualifiedName& name);
std::string to_string(BinaryNinja::BinaryView& bv);
std::string to_string(const BinaryNinja::LinearDisassemblyLine& line);

void linear_export(BinaryNinja::BinaryView& bv, const std::string& file);
}
