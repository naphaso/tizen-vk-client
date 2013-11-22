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
#include <FWebJson.h>
#include "VKU.h"

enum AvatarType {
	AVATAR_NORMAL,
	AVATAR_UNREAD,
	HEADER_BLUE,
	BUBBLE_OUT,
	BUBBLE_IN
};

enum PlaceholderType {
	PLACEHOLDER_USER,
	PLACEHOLDER_CHAT
};


class RoundedAvatar:
	public Tizen::Ui::Controls::Panel,
	public Tizen::Ui::IPropagatedTouchEventListener {
public:
	RoundedAvatar(const AvatarType & type, const PlaceholderType & placeholderType = PLACEHOLDER_USER);
	virtual ~RoundedAvatar();

	result Construct(const Tizen::Graphics::Rectangle & rect, const Tizen::Base::String &avatarPath = L"");
	void SetUrl(const Tizen::Base::String & str);

	virtual void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs);
	// Panel
	virtual result OnDraw(void);

	void SetUserJson(Tizen::Web::Json::JsonObject * json);

	// IPropagatedTouchEventListener
	virtual bool OnTouchPressed(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo);
	virtual bool OnTouchReleased(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo);
	virtual bool OnTouchMoved(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo);
	virtual bool OnTouchCanceled(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
	virtual bool OnPreviewTouchPressed(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
	virtual bool OnPreviewTouchReleased(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
	virtual bool OnPreviewTouchMoved(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }

private:
	Tizen::Graphics::Bitmap* pAvatar;
	Tizen::Graphics::Bitmap* pAvatarRounding;
	Tizen::Graphics::Bitmap* pAvatarPlaceholder;

	Tizen::Web::Json::JsonObject *_pUserJson;

	Tizen::Base::String imageUrl;

	bool pressAllowed;
};

#endif /* ROUNDEDAVATAR_H_ */
