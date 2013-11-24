/*
 * VKULoginPopup.h
 *
 *  Created on: Nov 2, 2013
 *      Author: Igor Glotov
 */

#ifndef VKULOGINPOPUP_H_
#define VKULOGINPOPUP_H_
#include <FUi.h>
#include <FWeb.h>
#include <FIo.h>

class VKULoginPopup;

#include "IAuthListener.h"

class VKULoginPopup :
	public Tizen::Ui::Controls::Popup,
	public Tizen::Web::Controls::ILoadingListener,
	public Tizen::Ui::IPropagatedKeyEventListener {
public:
	VKULoginPopup();
	virtual ~VKULoginPopup(void);

	result Construct();

	void ShowPopup();
	void HidePopup();

	void StartLogin(IAuthListener *listener);
	void StartSignup(IAuthListener *listener);

	// ILoadingListener
	virtual bool OnHttpAuthenticationRequestedN(const Tizen::Base::String& host, const Tizen::Base::String& realm, const Tizen::Web::Controls::AuthenticationChallenge& authentication) { return false; };
	virtual void OnHttpAuthenticationCanceled(void) {};
	virtual void OnLoadingStarted(void) {};
	virtual void OnLoadingCanceled(void) {};
	virtual void OnLoadingErrorOccurred(Tizen::Web::Controls::LoadingErrorType error, const Tizen::Base::String& reason) {};
	virtual void OnLoadingCompleted(void);
	virtual void OnEstimatedProgress(int progress) {};
	virtual void OnPageTitleReceived(const Tizen::Base::String& title) {};
	virtual bool OnLoadingRequested(const Tizen::Base::String& url, Tizen::Web::Controls::WebNavigationType type) { return false; };
	virtual Tizen::Web::Controls::DecisionPolicy OnWebDataReceived(const Tizen::Base::String& mime, const Tizen::Net::Http::HttpHeader& httpHeader) { return Tizen::Web::Controls::WEB_DECISION_CONTINUE; };

	// IPropagatedKeyEventListener
	virtual bool OnKeyPressed(Tizen::Ui::Control& source,
							 const Tizen::Ui::KeyEventInfo& keyEventInfo) {return false;};
	virtual bool OnKeyReleased(Tizen::Ui::Control& source,
							  const Tizen::Ui::KeyEventInfo& keyEventInfo);
	virtual bool OnPreviewKeyPressed(Tizen::Ui::Control& source,
									const Tizen::Ui::KeyEventInfo& keyEventInfo) {return false;};
	virtual bool OnPreviewKeyReleased(Tizen::Ui::Control& source,
									 const Tizen::Ui::KeyEventInfo& keyEventInfo) {return false;};
	virtual bool TranslateKeyEventInfo(Tizen::Ui::Control& source,
									  Tizen::Ui::KeyEventInfo& keyEventInfo) {return false;};
private:

    Tizen::Web::Controls::Web* pWeb;
    IAuthListener *authListener;
};

#endif /* VKULOGINPOPUP_H_ */
