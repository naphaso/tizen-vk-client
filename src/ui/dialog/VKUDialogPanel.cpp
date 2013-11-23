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

static const int ACTION_ID_ATTACH = 1234;

VKUDialogPanel::VKUDialogPanel(void) {
	_provider = new VKUMessagesListItemProvider();
	_messagesTableView = null;
	_dialogJson = null;
	_lastTypingTime = 0;
	_attachControlPanel = null;
}

VKUDialogPanel::~VKUDialogPanel(void) {
	delete _provider;

//	if (_dialogJson)
//		delete _dialogJson;
}

bool VKUDialogPanel::Initialize() {
	Panel::Construct(IDC_PANEL_DIALOG);

	return true;
}

result VKUDialogPanel::OnInitializing(void) {
	result r = E_SUCCESS;
	AppLog("VKUDialogPanel::OnInitializing");

	FitToScreen();

	_editField = static_cast<EditField*>(GetControl(IDC_DIALOGTEXT_EDITFIELD, true));
	_editField->AddKeypadEventListener(*this);
	_editField->AddTextEventListener(*this);
	_editField->SetFocus();

	_attachButton = dynamic_cast<Button *>(GetControl(IDC_BUTTON_ATTACH, true));
	_attachButton->SetActionId(ACTION_ID_ATTACH);
	_attachButton->AddActionEventListener(*this);

	Panel * pullToRefreshPanel = dynamic_cast<Panel *>(GetControl(IDC_PANEL_DIALOG_PULL, true));

	/* ! HEADER ITEMS INIT ! */

	_headerPanel = static_cast<Panel*>(GetControl(IDC_PANEL_DIALOG_HEADER));

	/* ! END HEADER ITEMS INIT ! */

	// table view init
	_messagesTableView = static_cast<TableView*>(GetControl(
			IDC_DIALOG_MESSAGES_LISTVIEW));
	_messagesTableView->SetItemDividerColor(Color::GetColor(COLOR_ID_BLACK));

	_messageSentListener = new MessageSentListener();

	typingTimer.Construct(*this);

	_pullToRefresh.Construct(_messagesTableView, pullToRefreshPanel, this, PULL_TO_REFRESH_DIRECTION_BOTTOM);
	SetPropagatedTouchEventListener(&_pullToRefresh);

	AppLog("End VKUDialogPanel::OnInitializing");

	return r;
}

void VKUDialogPanel::OnActionPerformed(const Tizen::Ui::Control& source, int actionId) {
	if (actionId == ACTION_ID_ATTACH) {
		ShowAttachPanel();

		AttachElement * pElement = new AttachElement();
		pElement->Construct(Rectangle(0, 0, 200, 200));

		_attachControlPanel->AddElement(pElement);
	}
}

result VKUDialogPanel::ShowAttachPanel() {
	result r = E_SUCCESS;

	if (_attachControlPanel != null)
		return r;

	RelativeLayout *layout;
	Panel * editBoxPanel;

	_attachControlPanel = new AttachControl();
	r = _attachControlPanel->Construct(Rectangle(0, 0, GetBounds().width, 220));
	TryCatch(r == E_SUCCESS, , "Failed _attachControlPanel->Construct");

	layout = dynamic_cast<RelativeLayout *>(GetLayoutN());
	editBoxPanel = dynamic_cast<Panel *>(GetControl(IDC_PANEL_DIALOG_EDITOR));

	r = AddControl(_attachControlPanel);
	TryCatch(r == E_SUCCESS, , "Failed AddControl");

	_attachControlPanel->SetItemsRemovedListener(this);

	r = layout->SetRelation(*_attachControlPanel, editBoxPanel, RECT_EDGE_RELATION_BOTTOM_TO_TOP);
	TryCatch(r == E_SUCCESS, , "Failed layout->SetRelation");

	delete layout;

	return r;
CATCH:
	AppLogException("VKUDialogPanel::ShowAttachPanel is failed. %s", GetErrorMessage(r));
	return r;
}

void VKUDialogPanel::OnAllItemsRemoved() {
	if (_attachControlPanel == null)
		return;

	RemoveControl(*_attachControlPanel);
	_attachControlPanel = null;
}

void VKUDialogPanel::LoadMessages() {
	AppLog("VKUDialogPanel::LoadMessages");

	_provider->RequestUpdateHistory();
}

void VKUDialogPanel::LoadNewMessage(int messageId) {
	AppLog("VKUDialogPaden::LoadNewMessage(%d)", messageId);

	_provider->RequestNewMessage(messageId);
}

void VKUDialogPanel::SetDialogJson(JsonObject* dialogJson) {
	AppLog("VKUDialogPanel::SetUserJson");
	AppAssert(dialogJson);
	JsonParseUtils::GetDialogPeerId(dialogJson, _peerId);

	TryReturnVoid(_messageSentListener != null, "VKUDialogPanel: Fatal - pMessageSentListener is null");

	JsonObject *chatJson = null;

	result r = JsonParseUtils::GetObject(dialogJson, L"chat_json", chatJson);
	if (r != E_SUCCESS)
		chatJson = null;

	_provider->Construct(_peerId, chatJson, _messagesTableView);
	_messagesTableView->SetItemProvider(_provider);
	_messagesTableView->AddTableViewItemEventListener(*_provider);
	_messagesTableView->AddScrollEventListener(*_provider);
	_messagesTableView->ScrollToItem(_provider->GetItemCount() - 1);

	_messageSentListener->Construct(_messagesTableView, _provider, dialogJson);

	SetHeaderUser(dialogJson);

	_dialogJson = dialogJson;

	_messagesTableView->UpdateTableView();
	_messagesTableView->ScrollToItem(_messagesTableView->GetItemCount() - 1);
}

void VKUDialogPanel::SetUserTyping(bool typing) {
	Label * pStatuslabel = static_cast<Label*>(_headerPanel->GetControl(IDC_DIALOG_HEADER_STATUS));

	if (typing) {
		pStatuslabel->SetText(L"Typing...");
	} else {
		int online;

		JsonObject *userJson;
		JsonParseUtils::GetObject(_dialogJson, L"user_json", userJson);

		JsonParseUtils::GetInteger(*userJson, L"online", online);
		pStatuslabel->SetText( (online == 1) ? L"Online" : L"Offline" );
	}
	pStatuslabel->RequestRedraw(true);
}

void VKUDialogPanel::SetHeaderUser(JsonObject * dialogJson) {
	Label *pNameLabel = static_cast<Label*>(_headerPanel->GetControl(IDC_DIALOG_HEADER_NAME));
	Panel *pAvatarHolder = static_cast<Panel*>(_headerPanel->GetControl(IDC_PANEL_DIALOG_AVATAR));
	Label *pStatuslabel = static_cast<Label*>(_headerPanel->GetControl(IDC_DIALOG_HEADER_STATUS));

	JsonObject *userJson;
	JsonParseUtils::GetObject(dialogJson, L"user_json", userJson);

	JsonObject *chatJson;
	result r = JsonParseUtils::GetObject(dialogJson, L"chat_json", chatJson);

	// if we failed to get chat, so this is user
	if (r != E_SUCCESS) {
		String fname, sname, status, avararUrl;
		int online;

		JsonParseUtils::GetInteger(*userJson, L"online", online);
		JsonParseUtils::GetString(*userJson, L"first_name", fname);
		JsonParseUtils::GetString(*userJson, L"last_name", sname);
		JsonParseUtils::GetString(*userJson, L"photo_100", avararUrl);

		fname.Append(L" ");
		fname.Append(sname);

		pStatuslabel->SetText( (online == 1) ? L"Online" : L"Offline");
		pNameLabel->SetText(fname);

		RoundedAvatar * pRoundedAvatar = new RoundedAvatar(HEADER_BLUE);
		pRoundedAvatar->Construct(Rectangle(0, 0, 80, 80), avararUrl);

		pAvatarHolder->AddControl(pRoundedAvatar);
	} else { // this is chat
		String name, status, avatarTemp;

		JsonParseUtils::GetString(*chatJson, L"title", name);
		JsonParseUtils::GetString(*chatJson, L"type", status);
		JsonParseUtils::GetString(*userJson, L"photo_100", avatarTemp);

		pStatuslabel->SetText(status);
		pNameLabel->SetText(name);

		RoundedAvatar * pRoundedAvatar = new RoundedAvatar(HEADER_BLUE);
		pRoundedAvatar->Construct(Rectangle(0, 0, 80, 80), avatarTemp);
		pAvatarHolder->AddControl(pRoundedAvatar);
	}
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

	AppLog("VKUDialogPanel::FitToScreen done");

	Invalidate(true);
}

void VKUDialogPanel::OnKeypadActionPerformed(Control &source,
		KeypadAction keypadAction) {


	if (keypadAction == KEYPAD_ACTION_SEND) {
		String text = _editField->GetText();
		if (_peerId < 2000000000) {
			VKUApi::GetInstance().CreateRequest(L"messages.send", _messageSentListener)
					->Put(L"user_id", Integer::ToString(_peerId))
					->Put(L"message", text)
					->Submit(REQUEST_SEND_MESSAGE);
		} else {
			VKUApi::GetInstance().CreateRequest(L"messages.send", _messageSentListener)
					->Put(L"chat_id", Integer::ToString(_peerId-2000000000))
					->Put(L"message", text)
					->Submit(REQUEST_SEND_MESSAGE);
		}

		_editField->Clear();
		_editField->RequestRedraw(true);
	}
}

void VKUDialogPanel::OnKeypadBoundsChanged(Control &source) {
	AppLog("Keypad OnKeypadBoundsChanged");

}

void VKUDialogPanel::OnKeypadClosed(Control &source) {
	AppLog("Keypad OnKeypadClosed");
	FitToScreen();
}

void VKUDialogPanel::OnKeypadOpened(Control &source) {
	AppLog("Keypad OnKeypadOpened");
	FitToScreen();
}

void VKUDialogPanel::OnKeypadWillOpen(Control &source) {
	AppLog("Keypad OnKeypadWillOpen");

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
				->Put(L"user_id", Integer::ToString(_peerId))
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

void VKUDialogPanel::OnRefresh() {
	AppLog("pull to refresh messages");
}

