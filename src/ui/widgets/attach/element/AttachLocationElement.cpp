/*
 * AttachLocationElement.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: Igor Glotov
 */

#include "AttachLocationElement.h"
#include <FLocations.h>

using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::App;
using namespace Tizen::Base::Collection;
using namespace Tizen::Web::Json;
using namespace Tizen::Locations;

AttachLocationElement::AttachLocationElement() {
	_icon = null;
}

AttachLocationElement::~AttachLocationElement() {
	AppLog("PIZDA AttachLocationElement::~AttachLocationElement");
}

result AttachLocationElement::Construct(const Tizen::Graphics::Rectangle & rect) {
	result r = E_SUCCESS;
	AttachElement::Construct(rect);
	RelativeLayout * layout = dynamic_cast<RelativeLayout *>(GetLayoutN());

	_icon = new LocalImageView();
	_icon->Construct(Rectangle(0, 0, 72, 72), "icon_location.png");
	r = AddControl(_icon);
	r = layout->SetCenterAligned(*_icon, CENTER_ALIGN_HORIZONTAL);
	r = layout->SetCenterAligned(*_icon, CENTER_ALIGN_VERTICAL);

	Label *label = new Label();
	label->Construct(Rectangle(0, 0, rect.width, 30), L"My location");
	label->SetTextConfig(30, LABEL_TEXT_STYLE_NORMAL);

	r = AddControl(label);
	r = layout->SetRelation(*label, this, RECT_EDGE_RELATION_BOTTOM_TO_BOTTOM);
	r = layout->SetCenterAligned(*label, CENTER_ALIGN_HORIZONTAL);
	r = layout->SetMargin(*label, 0, 0, 0, 10);

	SetUploaded(true);
	_loading = false;

	delete layout;
	return r;
}

double AttachLocationElement::GetLng() {
	AppLog("AttachLocationElement::GetLng");

	Location location = LocationProvider::GetLastKnownLocation();
	return location.GetCoordinates().GetLongitude();
}

double AttachLocationElement::GetLat() {
	AppLog("AttachLocationElement::GetLat");
	Location location = LocationProvider::GetLastKnownLocation();
	return location.GetCoordinates().GetLatitude();
}

