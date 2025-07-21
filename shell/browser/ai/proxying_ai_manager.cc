// Copyright (c) 2025 Microsoft, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "shell/browser/ai/proxying_ai_manager.h"

#include <utility>

#include "base/notimplemented.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/weak_document_ptr.h"
#include "mojo/public/cpp/bindings/callback_helpers.h"
#include "shell/browser/api/electron_api_session.h"
#include "shell/browser/session_preferences.h"
#include "third_party/blink/public/mojom/ai/ai_common.mojom.h"
#include "third_party/blink/public/mojom/ai/ai_language_model.mojom.h"

namespace electron {

ProxyingAIManager::ProxyingAIManager(content::BrowserContext* browser_context,
                                     content::RenderFrameHost* rfh)
    : browser_context_(browser_context),
      rfh_(rfh ? rfh->GetWeakDocumentPtr() : content::WeakDocumentPtr()) {}

ProxyingAIManager::~ProxyingAIManager() = default;

void ProxyingAIManager::AddReceiver(
    mojo::PendingReceiver<blink::mojom::AIManager> receiver) {
  receivers_.Add(this, std::move(receiver));
}

void ProxyingAIManager::CanCreateLanguageModel(
    blink::mojom::AILanguageModelCreateOptionsPtr options,
    CanCreateLanguageModelCallback callback) {
  auto* session_prefs =
      SessionPreferences::FromBrowserContext(browser_context_);
  DCHECK(session_prefs);

  auto cb = mojo::WrapCallbackWithDefaultInvokeIfNotRun(
      std::move(callback),
      blink::mojom::ModelAvailabilityCheckResult::kUnavailableUnknown);

  if (session_prefs->HasLocalAIHandler()) {
    // Proxy the call through to the utility process
    auto& ai_manager = session_prefs->GetLocalAIHandler()->GetAIManager();
    if (ai_manager.is_bound()) {
      ai_manager->CanCreateLanguageModel(std::move(options), std::move(cb));
      return;
    }
  }
}

void ProxyingAIManager::CreateLanguageModel(
    mojo::PendingRemote<blink::mojom::AIManagerCreateLanguageModelClient>
        client,
    blink::mojom::AILanguageModelCreateOptionsPtr options) {
  // TODO - Implement language model creation logic
}

void ProxyingAIManager::CanCreateSummarizer(
    blink::mojom::AISummarizerCreateOptionsPtr options,
    CanCreateSummarizerCallback callback) {
  std::move(callback).Run(
      blink::mojom::ModelAvailabilityCheckResult::kUnavailableUnknown);
}

void ProxyingAIManager::CreateSummarizer(
    mojo::PendingRemote<blink::mojom::AIManagerCreateSummarizerClient> client,
    blink::mojom::AISummarizerCreateOptionsPtr options) {
  NOTIMPLEMENTED();
}

void ProxyingAIManager::GetLanguageModelParams(
    GetLanguageModelParamsCallback callback) {
  // TODO - Implement this properly
  std::move(callback).Run(nullptr);
}

void ProxyingAIManager::CanCreateWriter(
    blink::mojom::AIWriterCreateOptionsPtr options,
    CanCreateWriterCallback callback) {
  std::move(callback).Run(
      blink::mojom::ModelAvailabilityCheckResult::kUnavailableUnknown);
}

void ProxyingAIManager::CreateWriter(
    mojo::PendingRemote<blink::mojom::AIManagerCreateWriterClient> client,
    blink::mojom::AIWriterCreateOptionsPtr options) {
  NOTIMPLEMENTED();
}

void ProxyingAIManager::CanCreateRewriter(
    blink::mojom::AIRewriterCreateOptionsPtr options,
    CanCreateRewriterCallback callback) {
  std::move(callback).Run(
      blink::mojom::ModelAvailabilityCheckResult::kUnavailableUnknown);
}

void ProxyingAIManager::CreateRewriter(
    mojo::PendingRemote<blink::mojom::AIManagerCreateRewriterClient> client,
    blink::mojom::AIRewriterCreateOptionsPtr options) {
  NOTIMPLEMENTED();
}

void ProxyingAIManager::CanCreateProofreader(
    blink::mojom::AIProofreaderCreateOptionsPtr options,
    CanCreateProofreaderCallback callback) {
  std::move(callback).Run(
      blink::mojom::ModelAvailabilityCheckResult::kUnavailableUnknown);
}

void ProxyingAIManager::CreateProofreader(
    mojo::PendingRemote<blink::mojom::AIManagerCreateProofreaderClient> client,
    blink::mojom::AIProofreaderCreateOptionsPtr options) {
  NOTIMPLEMENTED();
}

void ProxyingAIManager::AddModelDownloadProgressObserver(
    mojo::PendingRemote<blink::mojom::ModelDownloadProgressObserver>
        observer_remote) {
  NOTIMPLEMENTED();
}

}  // namespace electron
