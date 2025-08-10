
/* Copyright 2017 - 2025 R. Thomas
 * Copyright 2017 - 2025 Quarkslab
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
#include "COFF/pyCOFF.hpp"

#include "LIEF/COFF/utils.hpp"

#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include "nanobind/extra/stl/pathlike.h"

namespace LIEF::COFF::py {

void init_utils(nb::module_& m) {
  lief_mod->def("is_coff",
    [] (nb::PathLike path) { return is_coff(path); },
    "Check if the given file is a COFF"_doc,
    "file"_a
  );
}
}
