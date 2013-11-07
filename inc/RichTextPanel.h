/*
 * RichTextPanel.h
 *
 *  Created on: Nov 7, 2013
 *      Author: igorglotov
 */

#ifndef RICHTEXTPANEL_H_
#define RICHTEXTPANEL_H_

#include <FUi.h>
#include <FUiCtrlPanel.h>
#include <FBase.h>

class RichTextPanel: public Tizen::Ui::Controls::Panel {
public:
	RichTextPanel();
	virtual ~RichTextPanel();

	result Construct(const Tizen::Graphics::Dimension& dim, const Tizen::Base::String & text);
	result OnDraw(void);

private:
	Tizen::Graphics::EnrichedText* enrichedText;
};

#endif /* RICHTEXTPANEL_H_ */
