/*
 * VKULoginPopup.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: Igor Glotov
 */

#include "VKULoginPopup.h"

using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Web::Controls;

result VKULoginPopup::Construct()
{
    result r = E_SUCCESS;

    Popup::Construct(true, Dimension(600,800));

    pWeb = new (std::nothrow) Web();
    Rectangle rect = GetClientAreaBounds();
    pWeb->Construct(rect);

    AddControl(pWeb);


	SetTitleText(L"Popup Test");
	RequestRedraw(true);
	return r;

CATCH:
    AppLogException("Construct is failed.", GetErrorMessage(r));
	return r;
}

void VKULoginPopup::ShowPopup() {
	SetShowState(true);
	Show();
	pWeb->LoadUrl(L"http://ya.ru");
}
