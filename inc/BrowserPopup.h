/*
 * BrowserPopup.h
 *
 *  Created on: Nov 23, 2013
 *      Author: Igor Glotov
 */

#ifndef BROWSERPOPUP_H_
#define BROWSERPOPUP_H_

#include <FUi.h>
#include <FBase.h>
#include <FWeb.h>

class BrowserPopup:
	public Tizen::Ui::Controls::Popup,
	public Tizen::Ui::IPropagatedKeyEventListener {
public:
	BrowserPopup();
	virtual ~BrowserPopup();

	result Construct();

	void SetUrl(const Tizen::Base::String & uri);

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
	Tizen::Web::Controls::Web *pWeb;
};

#endif /* BROWSERPOPUP_H_ */
