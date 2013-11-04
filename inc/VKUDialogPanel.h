
#ifndef _VKUDIALOGPANEL_H_
#define _VKUDIALOGPANEL_H_

#include <FBase.h>
#include <FUi.h>
#include "IAPIRequestListener.h"


class VKUDialogPanel :
	public Tizen::Ui::Controls::Panel,
	public Tizen::Ui::IKeypadEventListener,
	public IAPIRequestListener
{

// Construction
public:
	VKUDialogPanel(void);
	virtual ~VKUDialogPanel(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

	void FitToScreen(void);

	// screen keyboard listeners...
	virtual void OnKeypadActionPerformed (Tizen::Ui::Control &source, Tizen::Ui::KeypadAction keypadAction);
	virtual void OnKeypadBoundsChanged (Tizen::Ui::Control &source);
	virtual void OnKeypadClosed (Tizen::Ui::Control &source);
	virtual void OnKeypadOpened (Tizen::Ui::Control &source);
	virtual void OnKeypadWillOpen (Tizen::Ui::Control &source);

	// IAPIRequestListener
	virtual void OnResponseN(Tizen::Web::Json::JsonObject *object);

// Implementation
protected:

// Generated call-back functions
public:

private:
	Tizen::Ui::Controls::EditField* pEditField;

};

#endif
