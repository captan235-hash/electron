// Copyright (c) 2025 Microsoft, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_UTILITY_API_ELECTRON_LOCAL_AI_HANDLER_H_
#define ELECTRON_SHELL_UTILITY_API_ELECTRON_LOCAL_AI_HANDLER_H_

#include <optional>

#include "base/functional/callback_forward.h"
#include "v8/include/v8-forward.h"

namespace electron::api::local_ai_handler {

using PromptAPIHandler =
    base::RepeatingCallback<v8::Local<v8::Object>(v8::Local<v8::Value>)>;

void SetPromptAPIHandler(v8::Isolate* isolate, const PromptAPIHandler& handler);

[[nodiscard]] std::optional<PromptAPIHandler>& GetPromptAPIHandler();

}  // namespace electron::api::local_ai_handler

#endif  // ELECTRON_SHELL_UTILITY_API_ELECTRON_LOCAL_AI_HANDLER_H_
