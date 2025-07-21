// Copyright (c) 2025 Microsoft, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "shell/utility/api/electron_api_local_ai_handler.h"

#include <optional>

#include "base/no_destructor.h"
#include "shell/common/gin_converters/callback_converter.h"
#include "shell/common/gin_helper/dictionary.h"
#include "shell/common/gin_helper/error_thrower.h"
#include "shell/common/node_includes.h"
#include "v8/include/v8.h"

namespace electron::api::local_ai_handler {

void SetPromptAPIHandler(v8::Isolate* isolate,
                         const PromptAPIHandler& handler) {
  // TODO - validate handler
  // TODO - Real implementation
  // TODO - Store handler
  // auto foo = handler.Run(v8::Null(isolate));
  GetPromptAPIHandler() = handler;
}

std::optional<PromptAPIHandler>& GetPromptAPIHandler() {
  static base::NoDestructor<std::optional<PromptAPIHandler>> prompt_api_handler;
  return *prompt_api_handler;
}

}  // namespace electron::api::local_ai_handler

namespace {

void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
  v8::Isolate* const isolate = v8::Isolate::GetCurrent();
  gin_helper::Dictionary dict{isolate, exports};
  dict.SetMethod("setPromptAPIHandler",
                 &electron::api::local_ai_handler::SetPromptAPIHandler);
}

}  // namespace

NODE_LINKED_BINDING_CONTEXT_AWARE(electron_utility_local_ai_handler, Initialize)
