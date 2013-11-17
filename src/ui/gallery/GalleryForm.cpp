/*
 * GalleryForm.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: igorglotov
 */

#include "GalleryForm.h"
#include "SceneRegister.h"
#include "VKU.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base::Collection;
using namespace Tizen::Graphics;
using namespace Tizen::Ui::Scenes;

GalleryForm::GalleryForm() {

}

GalleryForm::~GalleryForm() {

}

result GalleryForm::OnInitializing(void) {
	result r = E_SUCCESS;

	return r;
}

result GalleryForm::OnTerminating(void) {
	return E_SUCCESS;
}

bool GalleryForm::Initialize() {
	Form::Construct(IDF_IMAGEVIEW);

	SceneManager* pSceneManager = SceneManager::GetInstance();
	pSceneManager->AddSceneEventListener(SCENE_GALLERY, *this);

	SetFormBackEventListener(this);

	return true;
}

void GalleryForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source) {
	AppLog("You can't leave Omsk");
}

void GalleryForm::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
							   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs) {
	if (pArgs != null) {
		imageUrl = static_cast<String* > (pArgs->GetAt(0));
		AppLog("ImageUrl %ls", imageUrl->GetPointer());
		VKUApp::GetInstance()->GetBitmapCache()->TakeBitmap(*imageUrl, this);
	}
}

Tizen::Ui::Controls::GalleryItem* GalleryForm::CreateItem(int index) {
	GalleryItem *pItem;

	pItem = new GalleryItem();
	pItem->Construct(*pBitmap);

	return pItem;
}

bool GalleryForm::DeleteItem (int index, Tizen::Ui::Controls::GalleryItem *pItem) {
	delete pItem;
	return true;
}

int GalleryForm::GetItemCount(void) {
	return 1;
}

void GalleryForm::OnUserEventReceivedN(RequestId requestId, IList* pArgs) {
	AppLog("GalleryForm::OnUserEventReceivedN");

	if(requestId == BITMAP_LOADED) {
		pBitmap = static_cast<Bitmap *>(pArgs->GetAt(0));

		Gallery *pGallery = static_cast<Gallery *>(GetControl(IDC_GALLERY, true));
		pGallery->SetItemProvider(*this);

		RequestRedraw();
	}

	delete pArgs;
}
