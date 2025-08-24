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
package lief.generic;

import java.util.OptionalLong;

public class Binary extends lief.Base {
    @Override
    protected native void destroy();

    protected Binary(long impl) {
        super(impl);
    }

    public native long getImageBase();

    public native OptionalLong offsetToVirtualAddress(long offset, long slide);

    public OptionalLong offsetToVirtualAddress(long offset) {
        return offsetToVirtualAddress(offset, /*slide=*/0);
    }

}
