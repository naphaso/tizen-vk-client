/*
 * MessagePhotoElement.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#include "MessagePhotoElement.h"
#include "SceneRegister.h"
#include "VKU.h"
#include "ObjectCounter.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Base::Collection;
using namespace Tizen::Base;

MessagePhotoElement::MessagePhotoElement() {
	CONSTRUCT(L"MessagePhotoElement");
	pImageView = null;
}

MessagePhotoElement::~MessagePhotoElement() {
	DESTRUCT(L"MessagePhotoElement");
}

result MessagePhotoElement::Construct(const Tizen::Graphics::Rectangle & rect, Tizen::Base::String & imageUrl) {
	result r = E_SUCCESS;
	r = Panel::Construct(rect);
	r = SetSize(Dimension(rect.width, rect.height));

	url = imageUrl;
	pImageView = new WebImageView();
	r = pImageView->Construct(rect, imageUrl);

	r = AddControl(pImageView);
	SetPropagatedTouchEventListener(this);

	return r;
}

void MessagePhotoElement::SetUrl(Tizen::Base::String & aurl) {
	url = aurl;
}

result MessagePhotoElement::OnDraw() {
	result r = Panel::OnDraw();

	Canvas *pCanvas = GetCanvasN();

	if (pCanvas) {
		pCanvas->SetForegroundColor(Color::GetColor(COLOR_ID_GREEN));
		pCanvas->DrawRectangle(pCanvas->GetBounds());

		delete pCanvas;
	}

	return r;
}

bool MessagePhotoElement::OnTouchPressed(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) {
	pressAllowed = true;
	return true;
}

bool MessagePhotoElement::OnTouchReleased(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) {
	if (!pressAllowed)
		return true;

	SceneManager* pSceneManager = SceneManager::GetInstance();

	ArrayList* pList = new (std::nothrow) ArrayList(SingleObjectDeleter);
	String *pUrl = new String(url);

	pList->Construct(1);
	pList->Add(pUrl);

	pSceneManager->GoForward(ForwardSceneTransition(SCENE_GALLERY, SCENE_TRANSITION_ANIMATION_TYPE_ZOOM_IN, SCENE_HISTORY_OPTION_ADD_HISTORY), pList);

	return true;
}

bool MessagePhotoElement::OnTouchMoved(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) {
	pressAllowed = false;
	return false;
}

