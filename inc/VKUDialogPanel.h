
#ifndef _VKUDIALOGPANEL_H_
#define _VKUDIALOGPANEL_H_

#include <FBase.h>
#include <FUi.h>



class VKUDialogPanel :
	public Tizen::Ui::Controls::Panel
{

// Construction
public:
	VKUDialogPanel(void);
	virtual ~VKUDialogPanel(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:

// Generated call-back functions
public:

};

#endif
