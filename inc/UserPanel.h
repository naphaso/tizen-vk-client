/*
 * UserPanel.h
 *
 *  Created on: Nov 22, 2013
 *      Author: Igor Glotov
 */

#ifndef USERPANEL_H_
#define USERPANEL_H_

#include <FUiCtrlPanel.h>

class UserPanel: public Tizen::Ui::Controls::Panel {
public:
	UserPanel();
	virtual ~UserPanel();
	bool Initialize();
};

#endif /* USERPANEL_H_ */
