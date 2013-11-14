/*
 * LoginPanel.h
 *
 *  Created on: Nov 14, 2013
 *      Author: igorglotov
 */

#ifndef LOGINPANEL_H_
#define LOGINPANEL_H_

#include <FUi.h>
#include <FBase.h>
#include <FUiCtrlPanel.h>

#include "VKULoginPopup.h"
#include "IAuthListener.h"

class LoginPanel:
	public Tizen::Ui::Controls::Panel,
 	public Tizen::Ui::IActionEventListener,
 	public IAuthListener {
public:

	bool Initialize();

	// base stuff
	result OnInitializing(void);
	result OnTerminating(void);

	// panel
	LoginPanel();
	virtual ~LoginPanel();

	// IAuthListener
	virtual void OnLoginSuccess(const Tizen::Base::String &accessToken, const Tizen::Base::String &expiresIn, const Tizen::Base::String &userId);
	virtual void OnLoginError(const Tizen::Base::String &error, const Tizen::Base::String &description);
	virtual void OnSignupSuccess(const Tizen::Base::String &accessToken, const Tizen::Base::String &expiresIn, const Tizen::Base::String &userId);
	virtual void OnSignupError(const Tizen::Base::String &error, const Tizen::Base::String &description);

	// IActionEventListener
	void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
private:
	VKULoginPopup* pPopup;
};

#endif /* LOGINPANEL_H_ */
