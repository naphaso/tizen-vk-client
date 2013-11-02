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

class VKULoginPopup :
	public Tizen::Ui::Controls::Popup {
public:
	result Construct();
	void ShowPopup();

private:
    static const int ID_BUTTON_OPEN_POPUP = 501;
    static const int ID_BUTTON_CLOSE_POPUP = 502;

    Tizen::Web::Controls::Web* pWeb;
};

#endif /* VKULOGINPOPUP_H_ */
