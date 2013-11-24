/*
 * MessageAudioElement.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#include "MessageAudioElement.h"
#include "JsonParseUtils.h"
#include "VKU.h"
#include "ObjectCounter.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base;
using namespace Tizen::Web::Json;
using namespace Tizen::App;

Tizen::Graphics::Bitmap* MessageAudioElement::_pPlayNormalBitmap = null;
Tizen::Graphics::Bitmap* MessageAudioElement::_pPlayPressedBitmap = null;
Tizen::Graphics::Bitmap* MessageAudioElement::_pPauseNormalBitmap = null;
Tizen::Graphics::Bitmap* MessageAudioElement::_pPausePressedBitmap = null;

static const int ACTION_ID_PLAYPAUSE = 111;

MessageAudioElement::MessageAudioElement() {
	CONSTRUCT(L"MessageAudioElement");
	isPlaying = false;
}

MessageAudioElement::~MessageAudioElement() {
	DESTRUCT(L"MessageAudioElement");
	VKUApp::GetInstance()->GetService()->ResetCurrentAudioElement(this);
}

void MessageAudioElement::InitStatics() {
	AppResource* pAppResource = VKUApp::GetInstance()->GetAppResource();

	if (_pPlayNormalBitmap == null) {
		_pPlayNormalBitmap = pAppResource->GetBitmapN(L"btn_play_normal.png");
	}

	if (_pPlayPressedBitmap == null) {
		_pPlayPressedBitmap = pAppResource->GetBitmapN(L"btn_play_press.png");
	}

	if (_pPauseNormalBitmap == null) {
		_pPauseNormalBitmap = pAppResource->GetBitmapN(L"btn_pause_normal.png");
	}

	if (_pPausePressedBitmap == null) {
		_pPausePressedBitmap = pAppResource->GetBitmapN(L"btn_pause_press.png");
	}
}

result MessageAudioElement::Construct(const Tizen::Graphics::Rectangle & rect, JsonObject * audioJson, int out) {
	result r = E_SUCCESS;
	String url;
	Bitmap *progressPoint;
	InitStatics();

	_pAudioJson = audioJson->CloneN();

	RelativeLayout layout;
	Label * pAuthorLabel, * pNameLabel;

	String title, artist;

	JsonParseUtils::GetString(*_pAudioJson, L"title", title);
	JsonParseUtils::GetString(*_pAudioJson, L"artist", artist);

	layout.Construct();
	r = Panel::Construct(layout, rect);
	TryCatch(r == E_SUCCESS, , "Panel::Construct");

	_pPlayPauseButton = new Button();
//	TryCatch(r == E_SUCCESS, , "Failed GetTextExtent");
	r = _pPlayPauseButton->Construct(Rectangle(0, 0, 71, 71), L"");
	TryCatch(r == E_SUCCESS, , "Failed _pPlayPauseButton->Construct");
	_pPlayPauseButton->SetNormalBackgroundBitmap(*_pPlayNormalBitmap);
	_pPlayPauseButton->SetPressedBackgroundBitmap(*_pPlayPressedBitmap);
	_pPlayPauseButton->SetActionId(ACTION_ID_PLAYPAUSE);
	_pPlayPauseButton->AddActionEventListener(*this);

	pAuthorLabel = new Label();
	r = pAuthorLabel->Construct(Rectangle(0, 0, rect.width, 45), artist);
	TryCatch(r == E_SUCCESS, , "Failed pAuthorLabel->Construct");
	pAuthorLabel->SetTextConfig(40, LABEL_TEXT_STYLE_BOLD);
	pAuthorLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);

	pNameLabel = new Label();
	r = pNameLabel->Construct(Rectangle(0, 0, rect.width, 40), title);
	TryCatch(r == E_SUCCESS, , "Failed pNameLabel->Construct");
	pNameLabel->SetTextConfig(35, LABEL_TEXT_STYLE_NORMAL);
	pNameLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);

	_slider = new Slider();
	r = _slider->Construct(Rectangle(0, 0, rect.width - 60, 60),BACKGROUND_STYLE_NONE, false, 0, 100);
	progressPoint = VKUApp::GetInstance()->GetAppResource()->GetBitmapN(L"progress_point.png");
	r = _slider->SetThumbBitmap(SLIDER_THUMB_STATUS_NORMAL, *progressPoint);
	TryCatch(r == E_SUCCESS, , "failed to construct slider");
	delete progressPoint;

	if(out) {
		_slider->SetBarBackgroundColor(Color(0x384f6c, false));
	} else {
		_slider->SetBarBackgroundColor(Color(0x4c6d96, false));
	}

	_slider->SetThumbTextColor(SLIDER_THUMB_STATUS_NORMAL, Color(0, 0, 0, 0));
	//_slider->AddSliderEventListener(*this);
	_slider->AddAdjustmentEventListener(*this);

	r = AddControl(_pPlayPauseButton);
	TryCatch(r == E_SUCCESS, , "Failed AddControl _pPlayPauseButton");
	r = AddControl(pAuthorLabel);
	TryCatch(r == E_SUCCESS, , "Failed AddControl pAuthorLabel");
	r = AddControl(pNameLabel);
	TryCatch(r == E_SUCCESS, , "Failed AddControl pNameLabel");
	r = AddControl(_slider);
	TryCatch(r == E_SUCCESS, , "Failed AddControl _slider");

	r = layout.SetRelation(*_pPlayPauseButton, this, RECT_EDGE_RELATION_LEFT_TO_LEFT);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetRelation(*_pPlayPauseButton, this, RECT_EDGE_RELATION_TOP_TO_TOP);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetMargin(*_pPlayPauseButton, 10, 0, 10, 0);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetMargin");
	r = layout.SetCenterAligned(*_pPlayPauseButton, CENTER_ALIGN_VERTICAL);

	r = layout.SetRelation(*pAuthorLabel, _pPlayPauseButton, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetRelation(*pAuthorLabel, this, RECT_EDGE_RELATION_TOP_TO_TOP);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetMargin(*pAuthorLabel, 10, 0, 10, 0);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetMargin");

	r = layout.SetRelation(*pNameLabel, _pPlayPauseButton, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetRelation(*pNameLabel, pAuthorLabel, RECT_EDGE_RELATION_TOP_TO_BOTTOM);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetMargin(*pNameLabel, 10, 0, 10, 0);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetMargin");

	r = layout.SetRelation(*_slider, pNameLabel, RECT_EDGE_RELATION_TOP_TO_BOTTOM);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetRelation(*_slider, _pPlayPauseButton, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetMargin(*_slider, 0, 0, 10, 0);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetMargin");


	r = SetSize(Dimension(rect.width, 180));
	TryCatch(r == E_SUCCESS, , "Failed SetSize(Dimension");



	JsonParseUtils::GetString(*_pAudioJson, L"url", url);
	if(VKUApp::GetInstance()->GetService()->IsAudioCurrent(url)) {
		VKUApp::GetInstance()->GetService()->SetCurrentAudioElement(this);
	}

	return r;

CATCH:
	AppLogException("MessageTextElement::SetText is failed. %s", GetErrorMessage(r));
	return r;
}

void MessageAudioElement::OnActionPerformed(const Tizen::Ui::Control& source, int actionId) {
	AppLog("MessageAudioElement::OnActionPerformed");


	if (!isPlaying) {
		isPlaying = !isPlaying;

		String url;
		JsonParseUtils::GetString(*_pAudioJson, L"url", url);

		VKUApp::GetInstance()->GetService()->PlayAudio(url);
		VKUApp::GetInstance()->GetService()->SetCurrentAudioElement(this);

		_pPlayPauseButton->SetNormalBackgroundBitmap(*_pPauseNormalBitmap);
		_pPlayPauseButton->SetPressedBackgroundBitmap(*_pPausePressedBitmap);
		_pPlayPauseButton->RequestRedraw(true);
	} else {
		isPlaying = !isPlaying;

		VKUApp::GetInstance()->GetService()->PauseAudio();

		_pPlayPauseButton->SetNormalBackgroundBitmap(*_pPlayNormalBitmap);
		_pPlayPauseButton->SetPressedBackgroundBitmap(*_pPlayPressedBitmap);
		_pPlayPauseButton->RequestRedraw(true);
	}
}

//result MessageAudioElement::OnDraw() {
//	Canvas *pCanvas = GetCanvasN();
//
//	if (pCanvas) {
//		pCanvas->SetForegroundColor(Color::GetColor(COLOR_ID_YELLOW));
//		pCanvas->DrawRectangle(pCanvas->GetBounds());
//
//		delete pCanvas;
//	}
//
//	return E_SUCCESS;
//}

void MessageAudioElement::OnProgress(int progress) {
	_slider->SetValue(progress);
	_slider->RequestRedraw(true);

	if(!isPlaying) {
		isPlaying = !isPlaying;

		_pPlayPauseButton->SetNormalBackgroundBitmap(*_pPauseNormalBitmap);
		_pPlayPauseButton->SetPressedBackgroundBitmap(*_pPausePressedBitmap);
		_pPlayPauseButton->RequestRedraw(true);
	}
}

void MessageAudioElement::OnReset() {
	_slider->SetValue(0);
	_slider->RequestRedraw(true);
	if(isPlaying) {
		isPlaying = false;
		_pPlayPauseButton->SetNormalBackgroundBitmap(*_pPlayNormalBitmap);
		_pPlayPauseButton->SetPressedBackgroundBitmap(*_pPlayPressedBitmap);
		_pPlayPauseButton->RequestRedraw(true);
	}
}


/*
void MessageAudioElement::OnSliderBarMoved(Slider& source, int value) {
	AppLog("PLAYER slider moved to %d", value);
	VKUApp::GetInstance()->GetService()->SeekAudio(value);
}*/


void MessageAudioElement::OnAdjustmentValueChanged(const Tizen::Ui::Control& source, int adjustment) {
	AppLog("PLAYER slider moved to %d", adjustment);
	VKUApp::GetInstance()->GetService()->SeekAudio(adjustment);
}
