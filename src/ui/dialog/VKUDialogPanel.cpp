#include "AppResourceId.h"
#include "VKUDialogPanel.h"
#include "VKUApi.h"
#include "VKUDialog.h"
#include "JsonParseUtils.h"
#include "RoundedAvatar.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Web::Json;
using namespace Tizen::System;

VKUDialogPanel::VKUDialogPanel(void) {
	_provider = new VKUMessagesListItemProvider();
	_messagesTableView = null;
	_userJson = null;
	_lastTypingTime = 0;
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

	_editField = static_cast<EditField*>(GetControl(IDC_DIALOGTEXT_EDITFIELD));
	_editField->AddKeypadEventListener(*this);
	_editField->AddTextEventListener(*this);
	_editField->SetFocus();

	/* ! HEADER ITEMS INIT ! */

	_headerPanel = static_cast<Panel*>(GetControl(IDC_PANEL_DIALOG_HEADER));

	/* ! END HEADER ITEMS INIT ! */

	// table view init
	_messagesTableView = static_cast<TableView*>(GetControl(
			IDC_DIALOG_MESSAGES_LISTVIEW));
	_messagesTableView->SetItemDividerColor(Color::GetColor(COLOR_ID_BLACK));

	_messageSentListener = new MessageSentListener();

	typingTimer.Construct(*this);

	AppLog("End VKUDialogPanel::OnInitializing");

	return r;
}

void VKUDialogPanel::LoadMessages() {
	AppLog("VKUDialogPanel::LoadMessages");

	_provider->RequestUpdateHistory();
}

void VKUDialogPanel::LoadNewMessage(int messageId) {
	AppLog("VKUDialogPaden::LoadNewMessage(%d)", messageId);

	_provider->RequestNewMessage(messageId);
}

void VKUDialogPanel::SetUserJson(JsonObject* userJson) {
	AppLog("VKUDialogPanel::SetUserJson");

	TryReturnVoid(_messageSentListener != null, "VKUDialogPanel: Fatal - pMessageSentListener is null");
	_provider->Construct(userJson, _messagesTableView);
	_messagesTableView->SetItemProvider(_provider);
	_messagesTableView->AddTableViewItemEventListener(*_provider);
	_messagesTableView->AddScrollEventListener(*_provider);
	_messagesTableView->ScrollToItem(_provider->GetItemCount() - 1);

	_messageSentListener->Construct(_messagesTableView, _provider, userJson);

	SetHeaderUser(userJson);

	_userJson = userJson;

	JsonParseUtils::GetInteger(*userJson, L"id", userId);
}

void VKUDialogPanel::SetUserTyping(bool typing) {
	Label * pStatuslabel = static_cast<Label*>(_headerPanel->GetControl(IDC_DIALOG_HEADER_STATUS));

	if (typing) {
		pStatuslabel->SetText(L"Typing...");
	} else {
		pStatuslabel->SetText( (online == 1) ? "Online" : "Offline" );
	}
	pStatuslabel->RequestRedraw(true);
}

void VKUDialogPanel::SetHeaderUser(JsonObject * userJson) {
	Label *pNameLabel = static_cast<Label*>(_headerPanel->GetControl(IDC_DIALOG_HEADER_NAME));
	Panel *pAvatarHolder = static_cast<Panel*>(_headerPanel->GetControl(IDC_PANEL_DIALOG_AVATAR));
	Label *pStatuslabel = static_cast<Label*>(_headerPanel->GetControl(IDC_DIALOG_HEADER_STATUS));

	String fname, sname, status, avararUrl;

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

	if (_messagesTableView != null) {
		_messagesTableView->ScrollToItem(_messagesTableView->GetItemCount() - 1);
		_messagesTableView->RequestRedraw(true);
	}

	Invalidate(true);
}

void VKUDialogPanel::OnKeypadActionPerformed(Control &source,
		KeypadAction keypadAction) {


	if (keypadAction == KEYPAD_ACTION_SEND) {
		String text = _editField->GetText();
		VKUApi::GetInstance().CreateRequest(L"messages.send", _messageSentListener)
				->Put(L"user_id", Integer::ToString(userId))
				->Put(L"message", text)
				->Submit(REQUEST_SEND_MESSAGE);

		_editField->Clear();
		_editField->RequestRedraw(true);
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

void VKUDialogPanel::OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *object) {
	if(requestId == REQUEST_SET_ACTIVITY) {

	}
	delete object;
}

void VKUDialogPanel::OnTextValueChanged(const Tizen::Ui::Control& source) {
	DateTime currentDt;
	SystemTime::GetCurrentTime(currentDt);

	long long currentTime = currentDt.GetTicks();

	if (currentTime - _lastTypingTime > 5000) {
		VKUApi::GetInstance().CreateRequest(L"messages.setActivity", this)
				->Put(L"user_id", Integer::ToString(userId))
				->Put(L"type", L"typing")
				->Submit(REQUEST_SET_ACTIVITY);
		_lastTypingTime = currentTime;
	}
}

void VKUDialogPanel::OnTextValueChangeCanceled(const Tizen::Ui::Control& source) {

}

void VKUDialogPanel::OnTimerExpired(Timer& timer) {
	SetUserTyping(false);
}

void VKUDialogPanel::OnTyping() {
	SetUserTyping(true);

	typingTimer.Cancel();
	typingTimer.Start(10000);
}

