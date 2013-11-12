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

enum PlaceholderType {
	PLACEHOLDER_USER,
	PLACEHOLDER_CHAT
};


class RoundedAvatar: public Tizen::Ui::Controls::Panel {
public:
	RoundedAvatar(const AvatarType & type, const PlaceholderType & placeholderType = PLACEHOLDER_USER);
	virtual ~RoundedAvatar();

	result Construct(const Tizen::Graphics::Rectangle & rect, const Tizen::Base::String &avatarPath);


	virtual void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs);
	// Panel
	virtual result OnDraw(void);

private:
	Tizen::Graphics::Bitmap* pAvatar;
	Tizen::Graphics::Bitmap* pAvatarRounding;
	Tizen::Graphics::Bitmap* pAvatarPlaceholder;

	Tizen::Base::String imageUrl;
};

#endif /* ROUNDEDAVATAR_H_ */
