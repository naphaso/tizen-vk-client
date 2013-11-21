#ifndef _VKUCONTACTSPANEL_H_
#define _VKUCONTACTSPANEL_H_

#include <FBase.h>
#include <FUi.h>

#include "ContactsRetrieveListener.h"
#include "ContactsTableProvider.h"
#include "VKUAuthConfig.h"
#include "Requests.h"


class VKUContactsPanel: public Tizen::Ui::Controls::Panel {

// Construction
public:
	VKUContactsPanel(void);
	virtual ~VKUContactsPanel(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:

// Generated call-back functions
public:

	void ClearItems();

private:
	ContactsRetrieveListener* pContactsRetrieveListener;
	ContactsTableProvider* pProvider;
};

#endif
