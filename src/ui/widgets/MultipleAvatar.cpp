/*
 * MultipleAvatar.cpp
 *
 *  Created on: Nov 20, 2013
 *      Author: Igor Glotov
 */

#include "MultipleAvatar.h"
#include "ObjectCounter.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

MultipleAvatar::MultipleAvatar() {
	CONSTRUCT(L"MultipleAvatar");
}

MultipleAvatar::~MultipleAvatar() {
	DESTRUCT(L"MultipleAvatar");
}

result MultipleAvatar::Constrcut(const Rectangle & rect, AvatarType avatarType, Tizen::Base::Collection::ArrayList* pAvatars,
		PlaceholderType placeholderType) {
	result r = E_SUCCESS;

	RelativeLayout layout;
	layout.Construct();

	r = Panel::Construct(layout, rect, GROUP_STYLE_NONE);

	int avatarCount = pAvatars->GetCount() > 4 ? 4 : pAvatars->GetCount();

	Rectangle signleAvRect(0, 0, rect.width/2, rect.height/2);

	if (avatarCount == 2) {
		RoundedAvatar *pAvatar1 = new RoundedAvatar(avatarType, placeholderType);
		String *pPath1 = dynamic_cast<String *>(pAvatars->GetAt(0));
		pAvatar1->Construct(Rectangle(0, 0, signleAvRect.width+5, signleAvRect.width+5), *pPath1);

		RoundedAvatar *pAvatar2 = new RoundedAvatar(avatarType, placeholderType);
		String *pPath2 = dynamic_cast<String *>(pAvatars->GetAt(1));
		pAvatar2->Construct(Rectangle(0, 0, signleAvRect.width+5, signleAvRect.width+5), *pPath2);

		r = AddControl(pAvatar1);
		r = AddControl(pAvatar2);

		layout.SetRelation(*pAvatar1, this, RECT_EDGE_RELATION_LEFT_TO_LEFT);
		layout.SetRelation(*pAvatar1, this, RECT_EDGE_RELATION_TOP_TO_TOP);

		layout.SetRelation(*pAvatar2, this, RECT_EDGE_RELATION_BOTTOM_TO_BOTTOM);
		layout.SetRelation(*pAvatar2, this, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);

	} else if (avatarCount == 3) {
		RoundedAvatar *pAvatar1 = new RoundedAvatar(avatarType, placeholderType);
		String *pPath1 = dynamic_cast<String *>(pAvatars->GetAt(0));
		pAvatar1->Construct(signleAvRect, *pPath1);

		RoundedAvatar *pAvatar2 = new RoundedAvatar(avatarType, placeholderType);
		String *pPath2 = dynamic_cast<String *>(pAvatars->GetAt(1));
		pAvatar2->Construct(signleAvRect, *pPath2);

		RoundedAvatar *pAvatar3 = new RoundedAvatar(avatarType, placeholderType);
		String *pPath3 = dynamic_cast<String *>(pAvatars->GetAt(2));
		pAvatar3->Construct(signleAvRect, *pPath3);

		r = AddControl(pAvatar1);
		r = AddControl(pAvatar2);
		r = AddControl(pAvatar3);

		layout.SetRelation(*pAvatar1, this, RECT_EDGE_RELATION_LEFT_TO_LEFT);
		layout.SetRelation(*pAvatar1, this, RECT_EDGE_RELATION_TOP_TO_TOP);

		layout.SetRelation(*pAvatar2, this, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);
		layout.SetRelation(*pAvatar2, this, RECT_EDGE_RELATION_TOP_TO_TOP);

		layout.SetRelation(*pAvatar3, this, RECT_EDGE_RELATION_BOTTOM_TO_BOTTOM);
		layout.SetCenterAligned(*pAvatar3, CENTER_ALIGN_HORIZONTAL);
	} else if (avatarCount == 4) {
		RoundedAvatar *pAvatar1 = new RoundedAvatar(avatarType, placeholderType);
		String *pPath1 = dynamic_cast<String *>(pAvatars->GetAt(0));
		pAvatar1->Construct(signleAvRect, *pPath1);

		RoundedAvatar *pAvatar2 = new RoundedAvatar(avatarType, placeholderType);
		String *pPath2 = dynamic_cast<String *>(pAvatars->GetAt(1));
		pAvatar2->Construct(signleAvRect, *pPath2);

		RoundedAvatar *pAvatar3 = new RoundedAvatar(avatarType, placeholderType);
		String *pPath3 = dynamic_cast<String *>(pAvatars->GetAt(2));
		pAvatar3->Construct(signleAvRect, *pPath3);

		RoundedAvatar *pAvatar4 = new RoundedAvatar(avatarType, placeholderType);
		String *pPath4 = dynamic_cast<String *>(pAvatars->GetAt(3));
		pAvatar4->Construct(signleAvRect, *pPath4);

		r = AddControl(pAvatar1);
		r = AddControl(pAvatar2);
		r = AddControl(pAvatar3);
		r = AddControl(pAvatar4);

		layout.SetRelation(*pAvatar1, this, RECT_EDGE_RELATION_LEFT_TO_LEFT);
		layout.SetRelation(*pAvatar1, this, RECT_EDGE_RELATION_TOP_TO_TOP);

		layout.SetRelation(*pAvatar2, this, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);
		layout.SetRelation(*pAvatar2, this, RECT_EDGE_RELATION_TOP_TO_TOP);

		layout.SetRelation(*pAvatar3, this, RECT_EDGE_RELATION_BOTTOM_TO_BOTTOM);
		layout.SetRelation(*pAvatar3, this, RECT_EDGE_RELATION_LEFT_TO_LEFT);

		layout.SetRelation(*pAvatar4, this, RECT_EDGE_RELATION_BOTTOM_TO_BOTTOM);
		layout.SetRelation(*pAvatar4, this, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);
	}

	return r;
}
