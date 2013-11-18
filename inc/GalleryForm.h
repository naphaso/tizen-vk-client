/*
 * GalleryForm.h
 *
 *  Created on: Nov 18, 2013
 *      Author: igorglotov
 */

#ifndef GALLERYFORM_H_
#define GALLERYFORM_H_

#include <FUi.h>
#include <FBase.h>
#include <FUiCtrlForm.h>
#include "AppResourceId.h"

class GalleryForm:
	public Tizen::Ui::Controls::Form,
	public Tizen::Ui::Scenes::ISceneEventListener,
	public Tizen::Ui::Controls::IGalleryItemProvider,
	public Tizen::Ui::Controls::IFormBackEventListener {
public:
	GalleryForm();
	virtual ~GalleryForm();
	// form
	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId) {}
	result OnInitializing(void);
	result OnTerminating(void);

	// IFormBackEventListener
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

	// IGalleryItemProvider
	virtual Tizen::Ui::Controls::GalleryItem* CreateItem (int index);
	virtual bool DeleteItem (int index, Tizen::Ui::Controls::GalleryItem *pItem);
	virtual int GetItemCount(void);

	void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs);

	bool Initialize();
private:
	Tizen::Base::String *imageUrl;
	Tizen::Graphics::Bitmap *pBitmap;
};

#endif /* GALLERYFORM_H_ */
