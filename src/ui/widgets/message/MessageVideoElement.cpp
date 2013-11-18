/*
 * MessageVideoElement.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#include "MessageVideoElement.h"
#include "JsonParseUtils.h"
#include "VKU.h"
#include "TimeUtils.h"

using namespace Tizen::Graphics;
using namespace Tizen::Web::Json;
using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

MessageVideoElement::MessageVideoElement() {
	pVideoObject = null;
	pPlayBtn = null;
	pImageView = null;
}

MessageVideoElement::~MessageVideoElement() {
	if (pVideoObject)
		delete pVideoObject;
}

result MessageVideoElement::Construct(const Tizen::Graphics::Rectangle & rect, JsonObject * pObject) {
	result r = E_SUCCESS;

	String videoDurationStr;
	int videoDuration;

	RelativeLayout layout;
	layout.Construct();

	r = Panel::Construct(layout, rect);
	r = SetSize(Dimension(rect.width, rect.height));

	pVideoObject = pObject->CloneN();

	String thumbUrl;
	r = JsonParseUtils::GetString(*pVideoObject, L"photo_320", thumbUrl);
	if (r != E_SUCCESS)
		r = JsonParseUtils::GetString(*pVideoObject, L"photo_130", thumbUrl);

	r = JsonParseUtils::GetInteger(*pVideoObject, L"duration", videoDuration);
	r = TimeUtils::SecondsToTimeString(videoDuration, videoDurationStr);

	pDurationLabel = new Label();
	pDurationLabel->Construct(Rectangle(0, 0, 35, 40), videoDurationStr);
	pDurationLabel->SetTextConfig(25, LABEL_TEXT_STYLE_NORMAL);
	pDurationLabel->SetMargin(5, 10);
	pDurationLabel->SetBackgroundColor(Color(0, 0, 0, 200));
	pDurationLabel->SetTextColor(Color::GetColor(COLOR_ID_WHITE));

	pImageView = new WebImageView();
	r = pImageView->Construct(rect, thumbUrl);

	pPlayBtn = new LocalImageView();
	pPlayBtn->Construct(Rectangle(0, 0, 80, 80), L"btn_play_video.png");

	r = AddControl(pImageView);
	r = AddControl(pPlayBtn);
	r = AddControl(pDurationLabel);

	r = layout.SetCenterAligned(*pPlayBtn, CENTER_ALIGN_VERTICAL);
	r = layout.SetCenterAligned(*pPlayBtn, CENTER_ALIGN_HORIZONTAL);
	r = layout.SetHorizontalFitPolicy(*pDurationLabel, FIT_POLICY_CONTENT);
	r = layout.SetRelation(*pDurationLabel, *this, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);
	r = layout.SetRelation(*pDurationLabel, *this, RECT_EDGE_RELATION_BOTTOM_TO_BOTTOM);
	r = layout.SetMargin(*pDurationLabel, 0, 10, 0, 10);

	return r;
}

//result MessageVideoElement::OnDraw() {
//	result r = Panel::OnDraw();
//	Canvas *pCanvas = GetCanvasN();
//
//	if (pCanvas) {
////		r = pCanvas->SetForegroundColor(Color::GetColor(COLOR_ID_RED));
////		r = pCanvas->DrawRectangle(pCanvas->GetBounds());
//		Rectangle canvasRect = pCanvas->GetBounds();
//		r = pCanvas->DrawBitmap(Point(canvasRect.width/2, canvasRect.height/2), *pPlayBtn);
//		delete pCanvas;
//	}
//
//	return r;
//}
