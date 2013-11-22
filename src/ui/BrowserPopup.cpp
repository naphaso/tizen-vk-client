/*
 * BrowserPopup.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: Igor Glotov
 */

#include "BrowserPopup.h"

using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Web::Controls;
using namespace Tizen::Base::Utility;
using namespace Tizen::Io;
using namespace Tizen::Ui;

BrowserPopup::BrowserPopup() {
	// TODO Auto-generated constructor stub

}

BrowserPopup::~BrowserPopup() {
	// TODO Auto-generated destructor stub
}

result BrowserPopup::Construct() {
	AppLog("BrowserPopup::Construct");
	result r = E_SUCCESS;

	r = Popup::Construct(false, Dimension(600, 800));

	pWeb = new (std::nothrow) Web();
	TryCatch(r == GetLastResult(), r = GetLastResult(), "Failed Construct");

	r = pWeb->Construct(GetClientAreaBounds());
	TryCatch(r == E_SUCCESS, , "Failed Construct");

	r = AddControl(pWeb);
	TryCatch(r == E_SUCCESS, , "Failed AddControl");


	SetPropagatedKeyEventListener(this);

	return r;
CATCH:
	AppLogException("Construct is failed. %s", GetErrorMessage(r));
	return r;
}

void BrowserPopup::SetUrl(const Tizen::Base::String & uri) {
	AppLog("BrowserPopup::ShowBrowser");

	pWeb->LoadUrl(uri);
}

bool BrowserPopup::OnKeyReleased(Control& source, const KeyEventInfo& keyEventInfo) {
   KeyCode key = keyEventInfo.GetKeyCode();
   if (key == KEY_BACK || key == KEY_ESC)
   {
      Popup* pPopup = static_cast< Popup * >(&source);
      pPopup->SetShowState(false);
      pPopup->Invalidate(true);
   }

   return false;
}
