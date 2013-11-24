/*
 * Settings.h
 *
 *  Created on: Nov 24, 2013
 *      Author: Igor Glotov
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <FBaseObject.h>
#include <FBase.h>

class Settings: public Tizen::Base::Object {
public:
	Settings();
	virtual ~Settings();

	static void SetSetting(const Tizen::Base::String & key, const int value);

	static int GetSetting(const Tizen::Base::String & key);

	static void Read();
	static void Replace();

private:
	static bool IsExists();

	static int sound;
	static int vibe;
	static int resize;

};

#endif /* SETTINGS_H_ */
