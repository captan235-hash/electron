// Copyright (c) 2025 Microsoft, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "shell/utility/ai/utility_ai_manager.h"

#include <utility>

#include "base/notimplemented.h"
#include "shell/utility/api/electron_api_local_ai_handler.h"
#include "third_party/blink/public/mojom/ai/ai_common.mojom.h"
#include "third_party/blink/public/mojom/ai/ai_language_model.mojom.h"
#include "v8/include/v8.h"

namespace electron {

UtilityAIManager* UtilityAIManager::Create(
    mojo::PendingReceiver<blink::mojom::AIManager> receiver) {
  static UtilityAIManager* instance = new UtilityAIManager(std::move(receiver));
  return instance;
}

UtilityAIManager::UtilityAIManager(
    mojo::PendingReceiver<blink::mojom::AIManager> receiver) {
  DCHECK(receiver.is_valid());
  receiver_.Bind(std::move(receiver));
}

UtilityAIManager::~UtilityAIManager() = default;

void UtilityAIManager::CanCreateLanguageModel(
    blink::mojom::AILanguageModelCreateOptionsPtr options,
    CanCreateLanguageModelCallback callback) {
  auto& foo = electron::api::local_ai_handler::GetPromptAPIHandler();

  if (!foo.has_value()) {
    // If no handler is set, we cannot create a language model.
    std::move(callback).Run(
        blink::mojom::ModelAvailabilityCheckResult::kUnavailableUnknown);
    return;
  } else {
    // If a handler is set, we can create a language model.
    // TODO - Real implementation
    std::move(callback).Run(
        blink::mojom::ModelAvailabilityCheckResult::kDownloadable);
  }

  // TODO - Proper implementation that lets the developer determine if it's
  // available std::move(callback).Run(
  //    blink::mojom::ModelAvailabilityCheckResult::kDownloadable);
}

void UtilityAIManager::CreateLanguageModel(
    mojo::PendingRemote<blink::mojom::AIManagerCreateLanguageModelClient>
        client,
    blink::mojom::AILanguageModelCreateOptionsPtr options) {
  // TODO - Implement language model creation logic
}

void UtilityAIManager::CanCreateSummarizer(
    blink::mojom::AISummarizerCreateOptionsPtr options,
    CanCreateSummarizerCallback callback) {
  std::move(callback).Run(
      blink::mojom::ModelAvailabilityCheckResult::kUnavailableUnknown);
}

void UtilityAIManager::CreateSummarizer(
    mojo::PendingRemote<blink::mojom::AIManagerCreateSummarizerClient> client,
    blink::mojom::AISummarizerCreateOptionsPtr options) {
  NOTIMPLEMENTED();
}

void UtilityAIManager::GetLanguageModelParams(
    GetLanguageModelParamsCallback callback) {
  // TODO - Implement this properly
  std::move(callback).Run(nullptr);
}

void UtilityAIManager::CanCreateWriter(
    blink::mojom::AIWriterCreateOptionsPtr options,
    CanCreateWriterCallback callback) {
  std::move(callback).Run(
      blink::mojom::ModelAvailabilityCheckResult::kUnavailableUnknown);
}

void UtilityAIManager::CreateWriter(
    mojo::PendingRemote<blink::mojom::AIManagerCreateWriterClient> client,
    blink::mojom::AIWriterCreateOptionsPtr options) {
  NOTIMPLEMENTED();
}

void UtilityAIManager::CanCreateRewriter(
    blink::mojom::AIRewriterCreateOptionsPtr options,
    CanCreateRewriterCallback callback) {
  std::move(callback).Run(
      blink::mojom::ModelAvailabilityCheckResult::kUnavailableUnknown);
}

void UtilityAIManager::CreateRewriter(
    mojo::PendingRemote<blink::mojom::AIManagerCreateRewriterClient> client,
    blink::mojom::AIRewriterCreateOptionsPtr options) {
  NOTIMPLEMENTED();
}

void UtilityAIManager::CanCreateProofreader(
    blink::mojom::AIProofreaderCreateOptionsPtr options,
    CanCreateProofreaderCallback callback) {
  std::move(callback).Run(
      blink::mojom::ModelAvailabilityCheckResult::kUnavailableUnknown);
}

void UtilityAIManager::CreateProofreader(
    mojo::PendingRemote<blink::mojom::AIManagerCreateProofreaderClient> client,
    blink::mojom::AIProofreaderCreateOptionsPtr options) {
  NOTIMPLEMENTED();
}

void UtilityAIManager::AddModelDownloadProgressObserver(
    mojo::PendingRemote<blink::mojom::ModelDownloadProgressObserver>
        observer_remote) {
  NOTIMPLEMENTED();
}

}  // namespace electron
