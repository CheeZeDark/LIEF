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
#include <cassert>
#include <optional>
#include <string>
#include <binaryninja/binaryninjaapi.h>

namespace analysis_plugin {
class TypeBuilder {
  public:
  using cache_t = std::unordered_map<std::string, BinaryNinja::Ref<BinaryNinja::Type>>;
  static constexpr auto TYPE_PREFIX = "LIEF";
  TypeBuilder() = delete;
  TypeBuilder(BinaryNinja::BinaryView& bv) :
    bv_(bv)
  {}

  static std::string format_type(std::string name) {
    return std::string(TYPE_PREFIX) + '_' + std::move(name);
  }

  static std::string format_type(const char* name) {
    return format_type(std::string(name));
  }

  BinaryNinja::Ref<BinaryNinja::Type> void_ty() {
    return BinaryNinja::Type::VoidType();
  }

  BinaryNinja::Ref<BinaryNinja::Type> u8() {
    return BinaryNinja::Type::IntegerType(/*width=*/1, /*sign=*/false, "uint8_t");
  }

  BinaryNinja::Ref<BinaryNinja::Type> u16() {
    return BinaryNinja::Type::IntegerType(/*width=*/2, /*sign=*/false, "uint16_t");
  }

  BinaryNinja::Ref<BinaryNinja::Type> u32() {
    return BinaryNinja::Type::IntegerType(/*width=*/4, /*sign=*/false, "uint32_t");
  }

  BinaryNinja::Ref<BinaryNinja::Type> u64() {
    return BinaryNinja::Type::IntegerType(/*width=*/8, /*sign=*/false, "uint64_t");
  }

  BinaryNinja::Ref<BinaryNinja::Type> ptr_t()
  {
    return BinaryNinja::Type::IntegerType(bv_.GetAddressSize(), /*sign=*/false, "uintptr_t");
  }

  BinaryNinja::Ref<BinaryNinja::Type> void_ptr_t()
  {
    return BinaryNinja::Type::PointerType(bv_.GetDefaultArchitecture(), BinaryNinja::Type::VoidType());
  }

  BinaryNinja::Ref<BinaryNinja::Type> make_pointer(
      BinaryNinja::Ref<BinaryNinja::Type> type, BinaryNinja::Architecture* arch = nullptr)
  {
    BinaryNinja::Architecture* target_arch = arch;
    if (target_arch == nullptr) {
      target_arch = bv_.GetDefaultArchitecture();
    }
    return BinaryNinja::Type::PointerType(target_arch, type);
  }


  BinaryNinja::Ref<BinaryNinja::Type> make_const_pointer(
      BinaryNinja::Ref<BinaryNinja::Type> type, BinaryNinja::Architecture* arch = nullptr)
  {
    BinaryNinja::Architecture* target_arch = arch;
    if (target_arch == nullptr) {
      target_arch = bv_.GetDefaultArchitecture();
    }
    return BinaryNinja::Type::PointerType(target_arch, type, /*cnst=*/true);
  }

  BinaryNinja::Ref<BinaryNinja::Type>
    generic_func_ptr_t(BinaryNinja::Architecture* arch = nullptr)
  {
    using namespace BinaryNinja;

    Architecture* target_arch = arch;
    if (target_arch == nullptr) {
      target_arch = bv_.GetDefaultArchitecture();
    }

    assert(target_arch != nullptr);

    Confidence<Ref<Type>> ret_type = Type::VoidType();
    ret_type.SetConfidence(BN_MINIMUM_CONFIDENCE);

    Confidence<Ref<CallingConvention>> CC = bv_.GetDefaultPlatform()->GetDefaultCallingConvention();
    CC.SetConfidence(BN_MINIMUM_CONFIDENCE);

    return Type::PointerType(target_arch, Type::FunctionType(ret_type, CC, {}));
  }

  virtual std::string default_type_src() const {
    return "lief";
  }

  virtual BinaryNinja::Ref<BinaryNinja::Type> get_or_create(const std::string& name);
  virtual BinaryNinja::Ref<BinaryNinja::Type> get(const std::string& name);

  template<class T>
  BinaryNinja::Ref<T> get_as(BinaryNinja::Ref<BinaryNinja::Type> type) {
    if constexpr (std::is_same_v<T, BinaryNinja::Structure>) {
      if (auto U = type->GetStructure()) {
        return U;
      }

      if (auto U = type->GetNamedTypeReference()) {
        return get_as<T>(bv_.GetTypeById(U->GetTypeId()));
      }
    }
    return nullptr;
  }

  BinaryNinja::Ref<BinaryNinja::Type>
    create_struct(BinaryNinja::Structure& S, const std::string& name,
                  std::optional<std::string> typedef_ = std::nullopt);

  virtual ~TypeBuilder() = default;

  protected:
  BinaryNinja::BinaryView& bv_;
  cache_t cache_;
};
}
