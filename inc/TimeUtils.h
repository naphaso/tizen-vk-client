/*
 * TimeUtils.h
 *
 *  Created on: Nov 12, 2013
 *      Author: igorglotov
 */

#ifndef TIMEUTILS_H_
#define TIMEUTILS_H_

#include <FBase.h>
#include <FLocales.h>
#include <FSystem.h>

class TimeUtils {
public:
	TimeUtils();
	virtual ~TimeUtils();

	static result GetDialogsTime(int time, Tizen::Base::String & str);
	static result SecondsToTimeString(int seconds, Tizen::Base::String & str);
};

#endif /* TIMEUTILS_H_ */
