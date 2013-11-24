/*
 * Settings.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: Igor Glotov
 */

#include "Settings.h"
#include "VKU.h"

using namespace Tizen::Base;
using namespace Tizen::Io;

int Settings::sound = 0;
int Settings::vibe = 0;
int Settings::resize = 0;

Settings::Settings() {
	// TODO Auto-generated constructor stub

}

Settings::~Settings() {
	// TODO Auto-generated destructor stub
}

bool Settings::IsExists() {
	String sPath(VKUApp::GetInstance()->GetAppDataPath() + L"settings.ini");
	return File::IsFileExist(sPath);
}

void Settings::Replace() {
	String sPath(VKUApp::GetInstance()->GetAppDataPath() + L"settings.ini");

	if (IsExists()) {
		File::Remove(sPath);
	}

	Registry reg;
	reg.Construct(sPath, true);

	reg.AddSection(L"settings");
	reg.AddValue(L"settings", L"sound", sound);
	reg.AddValue(L"settings", L"vibe", vibe);
	reg.AddValue(L"settings", L"resize", resize);

	reg.Flush();
}

void Settings::Read() {
	String sPath(VKUApp::GetInstance()->GetAppDataPath() + L"settings.ini");
	Registry reg;
	reg.Construct(sPath, true);

	reg.GetValue(L"settings", L"sound", sound);
	reg.GetValue(L"settings", L"vibe", vibe);
	reg.GetValue(L"settings", L"resize", resize);
}

void Settings::SetSetting(const String &key, const int value) {
	Settings::Read();

	if (key == L"sound")
		sound = value;
	else if (key == L"vibe")
		vibe = value;
	else if (key == L"resize")
		resize = value;

	Settings::Replace();
}


int Settings::GetSetting(const Tizen::Base::String & key) {
	Settings::Read();
	if (key == L"sound")
		return sound;
	else if (key == L"vibe")
		return vibe;
	else if (key == L"resize")
		return resize;

	return 0;
}
