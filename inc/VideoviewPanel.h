/*
 * VideoviewPanel.h
 *
 *  Created on: Nov 18, 2013
 *      Author: igorglotov
 */

#ifndef VIDEOVIEWPANEL_H_
#define VIDEOVIEWPANEL_H_

#include <FUiCtrlPanel.h>

class VideoviewPanel: public Tizen::Ui::Controls::Panel {
public:
	VideoviewPanel();
	virtual ~VideoviewPanel();

	bool Initialize();

};

#endif /* VIDEOVIEWPANEL_H_ */
