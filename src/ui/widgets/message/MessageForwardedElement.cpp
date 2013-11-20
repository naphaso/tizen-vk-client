/*
 * MessageForwardedElement.cpp
 *
 *  Created on: Nov 20, 2013
 *      Author: Igor Glotov
 */

#include "MessageForwardedElement.h"
#include "RichTextPanel.h"
#include "JsonParseUtils.h"
#include "TimeUtils.h"
#include "VKUApi.h"
#include "Requests.h"
#include <cstdlib>
#include <ctime>

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base;
using namespace Tizen::Web::Json;
using namespace Tizen::Graphics;

MessageForwardedElement::MessageForwardedElement() {
	// TODO Auto-generated constructor stub
	srand(time(NULL));
}

MessageForwardedElement::~MessageForwardedElement() {
	// TODO Auto-generated destructor stub
}

result MessageForwardedElement::Construct(const Rectangle & rect, Tizen::Web::Json::JsonObject * forwardedMessage, int out) {
	result r = E_SUCCESS;

	int totalHeight, totalWidth;
	int textWidthDiff, maxTextEl;
	RelativeLayout layout;
	RichTextPanel *pTextPanel;
	Label *pTimeLabel;
	Panel *pMarker;
	AppLog("Milestone0");

	String userName, messageBody, timeString;
	JsonParseUtils::GetString(*forwardedMessage, L"body", messageBody);

	int userId, timeStamp;
	JsonParseUtils::GetInteger(*forwardedMessage, L"user_id", userId);
	userName = L"id" + Integer::ToString(userId);

	JsonParseUtils::GetInteger(*forwardedMessage, L"date", timeStamp);
	TimeUtils::GetDialogsTime(timeStamp, timeString);

	AppLog("Message from [%ls] %ls: %ls", timeString.GetPointer(), userName.GetPointer(), messageBody.GetPointer());


	r = layout.Construct();
	TryCatch(r == E_SUCCESS, , "Failed layout.Construct");

	r = Panel::Construct(layout, rect, GROUP_STYLE_NONE);
	TryCatch(r == E_SUCCESS, , "Failed Panel::Construct");

	_nameLabel = new Label();
	r = _nameLabel->Construct(Rectangle(0, 0, rect.width, 50), userName);
	TryCatch(r == E_SUCCESS, , "Failed _nameLabel->Construct");
	_nameLabel->SetMargin(0, 0);
	_nameLabel->SetTextConfig(_nameLabel->GetTextSize(), LABEL_TEXT_STYLE_BOLD);
	_nameLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);

	pTimeLabel = new Label();
	r = pTimeLabel->Construct(Rectangle(0, 0, rect.width, 30), timeString);
	pTimeLabel->SetMargin(0, 0);
	TryCatch(r == E_SUCCESS, , "Failed pTimeLabel->Construct");

	_avatar = new RoundedAvatar(out == 1 ? BUBBLE_OUT : BUBBLE_IN);
	r = _avatar->Construct(Rectangle(0, 0, 100, 100));
	TryCatch(r == E_SUCCESS, , "Failed _avatar->Construct");

	pMarker = new Panel();
	r = pMarker->Construct(Rectangle(0, 0, 5, 50), GROUP_STYLE_NONE);
	TryCatch(r == E_SUCCESS, , "Failed pMarker->Construct");
	pMarker->SetBackgroundColor(Color(0x569cda, false));


	r = AddControl(_nameLabel);
	TryCatch(r == E_SUCCESS, , "Failed AddControl");
	r = AddControl(pTimeLabel);
	TryCatch(r == E_SUCCESS, , "Failed AddControl");
	r = AddControl(_avatar);
	TryCatch(r == E_SUCCESS, , "Failed AddControl");
	r = AddControl(pMarker);
	TryCatch(r == E_SUCCESS, , "Failed AddControl");

	r = layout.SetRelation(*pMarker, this, RECT_EDGE_RELATION_LEFT_TO_LEFT);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");

	r = layout.SetRelation(*_avatar, pMarker, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetRelation(*_avatar, this, RECT_EDGE_RELATION_TOP_TO_TOP);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetMargin(*_avatar, 10, 0, 0, 0);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");

	r = layout.SetRelation(*_nameLabel, _avatar, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetRelation(*_nameLabel, this, RECT_EDGE_RELATION_TOP_TO_TOP);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetMargin(*_nameLabel, 10, 0, 0, 0);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetHorizontalFitPolicy(*_nameLabel, FIT_POLICY_CONTENT);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");

	r = layout.SetRelation(*pTimeLabel, _avatar, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetRelation(*pTimeLabel, _nameLabel, RECT_EDGE_RELATION_TOP_TO_BOTTOM);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetMargin(*pTimeLabel, 10, 0, 0, 0);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetHorizontalFitPolicy(*pTimeLabel, FIT_POLICY_CONTENT);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");

	// AND THEN WE KNOW HOW TO FIT THAT TEXT SHIT...

	textWidthDiff = pMarker->GetWidth() + 10 + _avatar->GetWidth() + 10;
	pTextPanel = new RichTextPanel();
	r = pTextPanel->Construct(Dimension(rect.width - textWidthDiff, 100000), messageBody);
	TryCatch(r == E_SUCCESS, , "Failed pTextPanel->Construct");

	r = AddControl(pTextPanel);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");

	r = layout.SetRelation(*pTextPanel, _avatar, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetRelation(*pTextPanel, pTimeLabel, RECT_EDGE_RELATION_TOP_TO_BOTTOM);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetMargin(*pTextPanel, 10, 0, 10, 0);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");

	totalHeight = _nameLabel->GetHeight() + 10 + pTimeLabel->GetHeight() + pTextPanel->GetHeight();

	// WTF IS THIS SHIT
	maxTextEl = (pTimeLabel->GetWidth() > _nameLabel->GetWidth()) ? pTimeLabel->GetWidth() : _nameLabel->GetWidth();
	maxTextEl = maxTextEl > pTextPanel->GetWidth() ? maxTextEl : pTextPanel->GetWidth();
	totalWidth = pMarker->GetWidth() + 10 + _avatar->GetWidth() + 10 + maxTextEl;

	r = pMarker->SetBounds(0, 0, pMarker->GetWidth(), totalHeight);
	TryCatch(r == E_SUCCESS, , "Failed AddControl");

	// FIXME: FUCK THAT SHIT
	r = SetSize(500, totalHeight);
	TryCatch(r == E_SUCCESS, , "Failed AddControl");

	RequestUser(userId);
	return r;

CATCH:
	AppLogException("MessageForwardedElement::Construct is failed. %s", GetErrorMessage(r));
	return r;
}

void MessageForwardedElement::RequestUser(int userId) {
	_requestId = rand() % 999999 + 200;
	VKUApi::GetInstance().CreateRequest("users.get", this)
		->Put(L"user_id", Integer::ToString(userId))
		->Put(L"fields", L"photo_100")
		->Submit(_requestId);
}

void MessageForwardedElement::OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *object) {
	if (requestId == _requestId) {
		JsonArray *userArray;

		JsonParseUtils::GetArray(object, L"response", userArray);

		JsonObject *userObject;
		JsonParseUtils::GetObject(userArray, 0, userObject);

		String firstName, photoUrl;
		JsonParseUtils::GetString(*userObject, L"first_name", firstName);
		JsonParseUtils::GetString(*userObject, L"photo_100", photoUrl);

		_avatar->SetUrl(photoUrl);
		_nameLabel->SetText(firstName);
		_nameLabel->RequestRedraw(true);
	}
}

void MessageForwardedElement::OnError() {

}
