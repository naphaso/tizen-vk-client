/*
 * MessageLocationElement.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: Igor Glotov
 */

#include "MessageLocationElement.h"
#include "WebImageView.h"
#include "JsonParseUtils.h"

using namespace Tizen::Web::Json;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

MessageLocationElement::MessageLocationElement() {
	// TODO Auto-generated constructor stub
	baseUrl = "";
}

MessageLocationElement::~MessageLocationElement() {
	// TODO Auto-generated destructor stub
}

result MessageLocationElement::Construct(const Tizen::Graphics::Rectangle & rect, Tizen::Web::Json::JsonObject * location) {
	result r = E_SUCCESS;
	baseUrl = "http://maps.googleapis.com/maps/api/staticmap?center={COORDINATES}&zoom=14&size=400x400&markers=color:black%7Csize:normal%7C{COORDINATES}&sensor=false";
	//browserUrl = "https://maps.google.com/?ll=&t=m&z=14";
	browserUrl = "http://maps.google.com/?saddr={COORDINATES}&daddr={COORDINATES}&output=embed";
	r = Panel::Construct(rect);
	r = SetSize(Dimension(rect.width, rect.height));

	String locationStr;
	JsonParseUtils::GetString(*location, L"coordinates", locationStr);
	locationStr.Replace(L" ", L",");

	baseUrl.Replace(L"{COORDINATES}", locationStr);
	browserUrl.Replace(L"{COORDINATES}", locationStr);

	WebImageView * mapView = new WebImageView();
	mapView->Construct(Rectangle(0, 0, 400, 400), baseUrl);

	r = AddControl(mapView);

	SetPropagatedTouchEventListener(this);

	popup = new BrowserPopup();
	popup->Construct();
	popup->SetShowState(false);


	return r;
}

bool MessageLocationElement::OnTouchPressed(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) {
	AppLog("MessageLocationElement::OnTouchReleased");
	touchAllowed = true;
	return true;
}

bool MessageLocationElement::OnTouchReleased(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) {
	AppLog("MessageLocationElement::OnTouchReleased");
	if (!touchAllowed)
		return true;

	AppLog("MessageLocationElement::OnTouchReleased stuff");

	popup->Show();
	popup->SetUrl(browserUrl);
	popup->SetShowState(true);
	Invalidate(true);

	return true;
}

bool MessageLocationElement::OnTouchMoved(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) {
	AppLog("MessageLocationElement::OnTouchReleased");

	touchAllowed = false;
	return false;
}
