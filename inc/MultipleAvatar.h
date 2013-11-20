/*
 * MultipleAvatar.h
 *
 *  Created on: Nov 20, 2013
 *      Author: Igor Glotov
 */

#ifndef MULTIPLEAVATAR_H_
#define MULTIPLEAVATAR_H_

#include <FUi.h>
#include <FBase.h>
#include "RoundedAvatar.h"

class MultipleAvatar: public Tizen::Ui::Controls::Panel {
public:
	MultipleAvatar();
	virtual ~MultipleAvatar();

	result Constrcut(const Tizen::Graphics::Rectangle & rect, AvatarType avatarType, Tizen::Base::Collection::ArrayList* pAvatars,
			PlaceholderType placeholderType = PLACEHOLDER_USER);

private:
	Tizen::Base::Collection::ArrayList * _pAvatars;
};

#endif /* MULTIPLEAVATAR_H_ */
