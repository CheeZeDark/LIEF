/* Copyright 2022 - 2025 R. Thomas
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

#include <jni_bind.h>
#include "jni/lief/generic/Binary.hpp"
#include "jni/lief/macho/Header.hpp"

#include <LIEF/MachO/Binary.hpp>
#include <LIEF/Abstract/Parser.hpp>

namespace lief_jni::macho {

class Binary : public generic::Binary {
  public:
  using generic::Binary::Binary;
  using lief_t = LIEF::MachO::Binary;
  static constexpr jni::Class kClass {
    "lief/macho/Binary",
    jni::Constructor{ jlong{} },
  };

  static jobject jni_parse(JNIEnv* env, jobject thiz, jstring path) {
    jni::ThreadGuard TG;
    jni::LocalString jpath = path;
    return Binary::create<Binary>(
      LIEF::Parser::parse(
        std::string(jpath.Pin().ToString())
      )
    );
  }

  static jobject jni_get_header(JNIEnv* env, jobject thiz) {
    return Header::create(
      &from_jni(thiz)->cast<lief_t>().header()
    );
  }

  static int register_natives(JNIEnv* env);

  static void jni_destroy(JNIEnv* env, jobject thiz) {
    destroy(thiz);
  }
};
}
