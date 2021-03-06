#include "VKUFormFactory.h"
#include "VKUMainForm.h"
#include "AppResourceId.h"
#include "VKULogin.h"
#include "VKUDialog.h"
#include "GalleryForm.h"
#include "VideoviewForm.h"
#include "UserForm.h"
#include "ObjectCounter.h"

using namespace Tizen::Ui::Scenes;

VKUFormFactory::VKUFormFactory(void) {
	CONSTRUCT(L"VKUFormFactory");
}

VKUFormFactory::~VKUFormFactory(void) {
	DESTRUCT(L"VKUFormFactory");
}

Tizen::Ui::Controls::Form* VKUFormFactory::CreateFormN(
		const Tizen::Base::String& formId,
		const Tizen::Ui::Scenes::SceneId& sceneId) {
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	Tizen::Ui::Controls::Form* pNewForm = null;

	if (formId == IDF_MAIN) {
		VKUMainForm* pForm = new (std::nothrow) VKUMainForm();
		pForm->Initialize();
		pNewForm = pForm;
	} else if (formId == IDF_LOGIN) {
		VKULogin* pForm = new (std::nothrow) VKULogin();
		pForm->Initialize();
		pNewForm = pForm;
	} else if (formId == IDF_DIALOG) {
		VKUDialog* pForm = new (std::nothrow) VKUDialog();
		pForm->Initialize();
		pNewForm = pForm;
	} else if (formId == IDF_IMAGEVIEW) {
		GalleryForm *pForm = new (std::nothrow) GalleryForm();
		pForm->Initialize();
		pNewForm = pForm;
	} else if (formId == IDF_VIDEOVIEW) {
		VideoviewForm *pForm = new (std::nothrow) VideoviewForm();
		pForm->Initialize();
		pNewForm = pForm;
	} else if (formId == IDF_USER) {
		UserForm *pForm = new (std::nothrow) UserForm();
		pForm->Initialize();
		pNewForm = pForm;
	}

	return pNewForm;
}
