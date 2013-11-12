/*
 * TimeUtils.cpp
 *
 *  Created on: Nov 12, 2013
 *      Author: igorglotov
 */

#include "TimeUtils.h"

using namespace Tizen::Base;
using namespace Tizen::Locales;
using namespace Tizen::System;

TimeUtils::TimeUtils() {
	// TODO Auto-generated constructor stub

}

TimeUtils::~TimeUtils() {
	// TODO Auto-generated destructor stub
}

result TimeUtils::GetDialogsTime(int time, String & str) {
	result r = E_SUCCESS;

	LocaleManager localeManager;
	localeManager.Construct();

	TimeZone timeZone = localeManager.GetSystemTimeZone();
	Calendar* pCalendar = Calendar::CreateInstanceN(timeZone, CALENDAR_GREGORIAN);

	DateTime dateTime;
	dateTime.SetValue(1970, 1, 1, 0, 0, 0);
	dateTime.AddMilliseconds((long long)time*1000);

	DateTime now;
	pCalendar->SetTime(dateTime);

	DateTimeFormatter* pDateFormatter = DateTimeFormatter::CreateTimeFormatterN(localeManager.GetSystemLocale(), DATE_TIME_STYLE_SHORT);

	pDateFormatter->Format(*pCalendar, str);

	delete pDateFormatter;
	delete pCalendar;

	return r;
}
