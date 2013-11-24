/*
 * SaneProgressBar.h
 *
 *  Created on: Nov 24, 2013
 *      Author: Igor Glotov
 */

#ifndef SANEPROGRESSBAR_H_
#define SANEPROGRESSBAR_H_

#include <FUi.h>
#include <FGraphics.h>

class SaneProgressBar: public Tizen::Ui::Controls::Panel {
public:
	SaneProgressBar();
	virtual ~SaneProgressBar();

	void SetProgress(int progress) { current = progress; RequestRedraw(true); }

	virtual result Construct(const Tizen::Graphics::Rectangle & rect, int max, int min);
	virtual result OnDraw();
private:
	int min;
	int max;
	int current;
};

#endif /* SANEPROGRESSBAR_H_ */
