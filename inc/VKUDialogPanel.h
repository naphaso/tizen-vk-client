
#ifndef _VKUDIALOGPANEL_H_
#define _VKUDIALOGPANEL_H_

#include <FBase.h>
#include <FUi.h>
#include "IAPIRequestListener.h"
#include "VKUMessagesListItemProvider.h"
#include "MessageSentListener.h"
#include "Requests.h"

class VKUDialogPanel :
	public Tizen::Ui::Controls::Panel,
	public Tizen::Ui::IKeypadEventListener,
	public Tizen::Ui::ITextEventListener,
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
	virtual void OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *object);

	// ITextEventListener
	virtual void OnTextValueChanged(const Tizen::Ui::Control& source);
	virtual void OnTextValueChangeCanceled(const Tizen::Ui::Control& source);

	// custom methods
	void LoadMessages();
	void LoadNewMessage(int messageId);
	void SetUserJson(Tizen::Web::Json::JsonObject * userJson);
	void SetHeaderUser(Tizen::Web::Json::JsonObject * userJson);
	void SetUserTyping(bool typing);

	void SetDialogData(Tizen::Web::Json::JsonArray *dialogData);
// Implementation
protected:

// Generated call-back functions
public:

private:
	Tizen::Ui::Controls::EditField* _editField;
	VKUMessagesListItemProvider* _provider;
	MessageSentListener* _messageSentListener;
	Tizen::Web::Json::JsonObject* _userJson;
	Tizen::Ui::Controls::TableView* _messagesTableView;
	Tizen::Ui::Controls::Panel * _headerPanel;

	long long _lastTypingTime;
	int userId;
};

#endif
