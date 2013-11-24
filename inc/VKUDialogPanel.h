
#ifndef _VKUDIALOGPANEL_H_
#define _VKUDIALOGPANEL_H_

#include <FBase.h>
#include <FUi.h>
#include "IAPIRequestListener.h"
#include "VKUMessagesListItemProvider.h"
#include "MessageSentListener.h"
#include "Requests.h"
#include "PullToRefreshTrait.h"
#include "AttachControl.h"
#include "IItemsRemovedListener.h"

class VKUDialogPanel :
	public Tizen::Ui::Controls::Panel,
	public Tizen::Ui::IKeypadEventListener,
	public Tizen::Ui::ITextEventListener,
	public Tizen::Base::Runtime::ITimerEventListener,
	public Tizen::Ui::IActionEventListener,
	public IAPIRequestListener,
	public IRefreshable,
	public IItemsRemovedListener
{

// Construction
public:
	VKUDialogPanel(void);
	virtual ~VKUDialogPanel(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

	void FitToScreen(void);
	result ShowAttachPanel(void);

	// IItemsRemovedListener
	virtual void OnAllItemsRemoved();

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

	// ITimerEventListener
	virtual void OnTimerExpired(Tizen::Base::Runtime::Timer& timer);

	// IActionEventListener
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	// custom methods
	void LoadMessages();
	void LoadNewMessage(int messageId);
	void SetDialogJson(Tizen::Web::Json::JsonObject * userJson);
	void SetHeaderUser(Tizen::Web::Json::JsonObject * userJson);
	void SetUserTyping(bool typing);

	void SetDialogData(Tizen::Web::Json::JsonArray *dialogData);

	void OnTyping();

	// IRefreshable
	virtual void OnRefresh();
// Implementation
protected:

// Generated call-back functions
public:

private:
	Tizen::Ui::Controls::EditArea* _editField;
	VKUMessagesListItemProvider* _provider;
	MessageSentListener* _messageSentListener;
	Tizen::Web::Json::JsonObject* _dialogJson;
	Tizen::Ui::Controls::TableView* _messagesTableView;
	Tizen::Ui::Controls::Panel * _headerPanel;
	Tizen::Ui::Controls::Button *_attachButton;

	Tizen::Base::Runtime::Timer typingTimer;

	long long _lastTypingTime;
	int _peerId;
	int online;

	AttachControl * _attachControlPanel;

	PullToRefreshTrait _pullToRefresh;
};

#endif
