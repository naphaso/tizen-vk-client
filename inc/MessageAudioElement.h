/*
 * MessageAudioElement.h
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#ifndef MESSAGEAUDIOELEMENT_H_
#define MESSAGEAUDIOELEMENT_H_

#include "MessageElement.h"
#include <FGraphics.h>
#include <FUi.h>
#include <FWebJson.h>
#include <FBase.h>

class MessageAudioElement:
	public MessageElement,
	public Tizen::Ui::IActionEventListener {
public:
	MessageAudioElement();
	virtual ~MessageAudioElement();

	void InitStatics();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect, Tizen::Web::Json::JsonObject * json);

	virtual MessageElementType GetElementType() { return MESSAGE_TYPE_AUDIO; }
//	virtual result OnDraw(void);

	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

private:
	Tizen::Web::Json::JsonObject * _pAudioJson;
	Tizen::Ui::Controls::Button * _pPlayPauseButton;

	static Tizen::Graphics::Bitmap * _pPlayNormalBitmap;
	static Tizen::Graphics::Bitmap * _pPlayPressedBitmap;
	static Tizen::Graphics::Bitmap * _pPauseNormalBitmap;
	static Tizen::Graphics::Bitmap * _pPausePressedBitmap;

	bool isPlaying;

};

#endif /* MESSAGEAUDIOELEMENT_H_ */
