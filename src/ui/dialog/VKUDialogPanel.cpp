#include "AppResourceId.h"
#include "VKUDialogPanel.h"
#include "../../api/VKUApi.h"
#include "VKUDialog.h"
#include "JsonParseUtils.h"
#include "RoundedAvatar.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Web::Json;
using namespace Tizen::System;

VKUDialogPanel::VKUDialogPanel(void) {
	provider = new VKUMessagesListItemProvider();
	pMessagesListView = null;
}

VKUDialogPanel::~VKUDialogPanel(void) {
//	delete provider;
}

bool VKUDialogPanel::Initialize() {
	Panel::Construct(IDC_PANEL_DIALOG);

	return true;
}

result VKUDialogPanel::OnInitializing(void) {
	result r = E_SUCCESS;
	AppLog("VKUDialogPanel::OnInitializing");

	FitToScreen();

	pEditField = static_cast<EditField*>(GetControl(IDC_DIALOGTEXT_EDITFIELD));
	pEditField->AddKeypadEventListener(*this);
	pEditField->AddTextEventListener(*this);
	pEditField->SetFocus();

	/* ! HEADER ITEMS INIT ! */

	pHeaderPanel = static_cast<Panel*>(GetControl(IDC_PANEL_DIALOG_HEADER));

	/* ! END HEADER ITEMS INIT ! */

	// table view init
	pMessagesListView = static_cast<TableView*>(GetControl(
			IDC_DIALOG_MESSAGES_LISTVIEW));
	pMessagesListView->SetItemDividerColor(Color::GetColor(COLOR_ID_BLACK));

	pDialogHistoryListener = new DialogHistoryListener(pMessagesListView, provider);
	pMessageSentListener = new MessageSentListener(pMessagesListView, provider);

	AppLog("Setting pDialogHistoryListener");
	provider->SetListener(pDialogHistoryListener);
	pMessagesListView->SetItemProvider(provider);

	AppLog("End VKUDialogPanel::OnInitializing");

	return r;
}

void VKUDialogPanel::LoadMessages() {
	AppLog("VKUDialogPanel::LoadMessages");

	TryReturnVoid(userJson != null, "VKUDialogPanel: LoadMessages cannot be completed until userId is not set");
	AppLog("Doing VKUDialogPanel::LoadMessages");

	provider->RequestData();
}

void VKUDialogPanel::SetUserJson(JsonObject* apJson) {
	AppLog("VKUDialogPanel::SetUserJson");

	TryReturnVoid(pMessageSentListener != null, "VKUDialogPanel: Fatal - pMessageSentListener is null");
	pMessageSentListener->SetUserJson(apJson);
	provider->SetUserJson(apJson);

	SetHeaderUser(apJson);

	userJson = apJson;

	JsonParseUtils::GetInteger(*userJson, L"id", userId);
}

void VKUDialogPanel::SetUserTyping(bool typing) {
	Label * pStatuslabel = static_cast<Label*>(pHeaderPanel->GetControl(IDC_DIALOG_HEADER_STATUS));

	if (typing) {
		pStatuslabel->SetText(L"Typing...");
	} else {
		int online;
		JsonParseUtils::GetInteger(*userJson, L"online", online);
		pStatuslabel->SetText( (online == 1) ? "Online" : "Offline" );
	}
}

void VKUDialogPanel::SetHeaderUser(JsonObject * userJson) {
	Label * pNameLabel = static_cast<Label*>(pHeaderPanel->GetControl(IDC_DIALOG_HEADER_NAME));
	Panel * pAvatarHolder = static_cast<Panel*>(pHeaderPanel->GetControl(IDC_PANEL_DIALOG_AVATAR));
	Label * pStatuslabel = static_cast<Label*>(pHeaderPanel->GetControl(IDC_DIALOG_HEADER_STATUS));

	String fname, sname, status, avararUrl;
	int online;

	JsonParseUtils::GetInteger(*userJson, L"online", online);
	JsonParseUtils::GetString(*userJson, "first_name", fname);
	JsonParseUtils::GetString(*userJson, "last_name", sname);
	JsonParseUtils::GetString(*userJson, "photo_100", avararUrl);

	fname.Append(L" ");
	fname.Append(sname);

	pStatuslabel->SetText( (online == 1) ? "Online" : "Offline");
	pNameLabel->SetText(fname);

	RoundedAvatar * pRoundedAvatar = new RoundedAvatar(HEADER_BLUE);
	pRoundedAvatar->Construct(Rectangle(0, 0, 80, 80), avararUrl);

	pAvatarHolder->AddControl(pRoundedAvatar);
}

result VKUDialogPanel::OnTerminating(void) {
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void VKUDialogPanel::FitToScreen() {
	AppLog("VKUDialogPanel::FitToScreen");

	VKUDialog *pForm = static_cast<VKUDialog *>(GetParent());

	if (pForm != null) {
		Rectangle clientRect = pForm->GetClientAreaBounds();
		Rectangle rect(0, 0, clientRect.width, clientRect.height);

		SetBounds(rect);
	}

	if (pMessagesListView != null) {
		pMessagesListView->ScrollToItem(pMessagesListView->GetItemCount() - 1);
		pMessagesListView->RequestRedraw(true);
	}

	Invalidate(true);
}

void VKUDialogPanel::OnKeypadActionPerformed(Control &source,
		KeypadAction keypadAction) {
	int userId;

	JsonParseUtils::GetInteger(*userJson, L"id", userId);

	if (keypadAction == KEYPAD_ACTION_SEND) {
		String text = pEditField->GetText();
		VKUApi::GetInstance().CreateRequest(L"messages.send", pMessageSentListener)
				->Put(L"user_id", Integer::ToString(userId))
				->Put(L"message", text)
				->Submit();

		pEditField->Clear();
		pEditField->RequestRedraw(true);
	}
}

void VKUDialogPanel::OnKeypadBoundsChanged(Control &source) {

}

void VKUDialogPanel::OnKeypadClosed(Control &source) {
	AppLog("Keypad closed");
	FitToScreen();
}

void VKUDialogPanel::OnKeypadOpened(Control &source) {
	AppLog("Keypad opened");
	FitToScreen();
}

void VKUDialogPanel::OnKeypadWillOpen(Control &source) {

}

void VKUDialogPanel::OnResponseN(Tizen::Web::Json::JsonObject *object) {
	delete object;
}

void VKUDialogPanel::OnTextValueChanged(const Tizen::Ui::Control& source) {
	DateTime currentDt;
	SystemTime::GetCurrentTime(currentDt);

	long long currentTime = currentDt.GetTicks();

	if (currentTime - lastTypingTime > 5000) {
		VKUApi::GetInstance().CreateRequest(L"messages.setActivity", this)
				->Put(L"user_id", Integer::ToString(userId))
				->Put(L"type", L"typing")
				->Submit();
		lastTypingTime = currentTime;
	}
}

void VKUDialogPanel::OnTextValueChangeCanceled(const Tizen::Ui::Control& source) {

}

void VKUDialogPanel::SetDialogData(JsonObject *dialogData) {
	pDialogHistoryListener->OnResponseN(dialogData);
}
