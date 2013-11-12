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
#include <FBase.h>
#include "VKU.h"

enum AvatarType {
	LIST_BLACK,
	HEADER_BLUE
};

class RoundedAvatar: public Tizen::Ui::Controls::Panel {
public:
	RoundedAvatar(const AvatarType & type);
	virtual ~RoundedAvatar();

	result Construct(const Tizen::Graphics::Rectangle & rect, const Tizen::Base::String &avatarPath);


	virtual void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs);
	// Panel
	virtual result OnDraw(void);

private:
	Tizen::Graphics::Bitmap* pAvatarRounding;
	Tizen::Base::String imageUrl;
};

#endif /* ROUNDEDAVATAR_H_ */
