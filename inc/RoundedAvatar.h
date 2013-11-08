/*
 * RoundedAvatar.h
 *
 *  Created on: Nov 8, 2013
 *      Author: igorglotov
 */

#ifndef ROUNDEDAVATAR_H_
#define ROUNDEDAVATAR_H_

#include <FUiCtrlPanel.h>
#include <FUi.h>
#include "VKU.h"

enum AvatarType {
	LIST_BLACK,
	HEADER_BLUE
};

class RoundedAvatar: public Tizen::Ui::Controls::Panel {
public:
	RoundedAvatar(const AvatarType & type);
	virtual ~RoundedAvatar();

	result Construct(Tizen::Graphics::Rectangle & rect, Tizen::Base::String & avatarPath);

	// Panel
	virtual result OnDraw(void);

private:
	Tizen::Graphics::Bitmap* pAvatarRounding;
};

#endif /* ROUNDEDAVATAR_H_ */
