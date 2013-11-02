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

class VKULoginPopup :
	public Tizen::Ui::Controls::Popup,
	public Tizen::Web::Controls::ILoadingListener {
public:
	result Construct();
	void ShowPopup();
	void HidePopup();

	virtual bool OnHttpAuthenticationRequestedN(const Tizen::Base::String& host, const Tizen::Base::String& realm, const Tizen::Web::Controls::AuthenticationChallenge& authentication) { return false; };
	virtual void OnHttpAuthenticationCanceled(void) {};
	virtual void OnLoadingStarted(void) {};
	virtual void OnLoadingCanceled(void) {};
	virtual void OnLoadingErrorOccurred(Tizen::Web::Controls::LoadingErrorType error, const Tizen::Base::String& reason) {};
	virtual void OnLoadingCompleted(void);
	virtual void OnEstimatedProgress(int progress) {};
	virtual void OnPageTitleReceived(const Tizen::Base::String& title) {};
	virtual bool OnLoadingRequested(const Tizen::Base::String& url, Tizen::Web::Controls::WebNavigationType type);
	virtual Tizen::Web::Controls::DecisionPolicy OnWebDataReceived(const Tizen::Base::String& mime, const Tizen::Net::Http::HttpHeader& httpHeader) { return Tizen::Web::Controls::WEB_DECISION_CONTINUE; };
private:
    static const int ID_BUTTON_OPEN_POPUP = 501;
    static const int ID_BUTTON_CLOSE_POPUP = 502;

    Tizen::Web::Controls::Web* pWeb;
};

#endif /* VKULOGINPOPUP_H_ */
