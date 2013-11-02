#ifndef _VKU_PANEL_FACTORY_H_
#define _VKU_PANEL_FACTORY_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>
#include <FUiIme.h>
#include <FGraphics.h>
#include <gl.h>


class VKUPanelFactory
	: public Tizen::Ui::Scenes::IPanelFactory
{
public:
	VKUPanelFactory(void);
	virtual ~VKUPanelFactory(void);

	virtual Tizen::Ui::Controls::Panel* CreatePanelN(const Tizen::Base::String& panelId, const Tizen::Ui::Scenes::SceneId& sceneId);
};

#endif // _VKU_PANEL_FACTORY_H_
