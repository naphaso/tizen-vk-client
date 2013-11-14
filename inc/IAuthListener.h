/*
 * IAuthListener.h
 *
 *  Created on: Nov 2, 2013
 *      Author: wolong
 */

#ifndef IAUTHLISTENER_H_
#define IAUTHLISTENER_H_

#include <FBase.h>

class IAuthListener {
public:
	virtual ~IAuthListener(void) {}
	virtual void OnLoginSuccess(const Tizen::Base::String &accessToken, const Tizen::Base::String &expiresIn, const Tizen::Base::String &userId) = 0;
	virtual void OnLoginError(const Tizen::Base::String &error, const Tizen::Base::String &description) = 0;

	virtual void OnSignupSuccess(const Tizen::Base::String &accessToken, const Tizen::Base::String &expiresIn, const Tizen::Base::String &userId) = 0;
	virtual void OnSignupError(const Tizen::Base::String &error, const Tizen::Base::String &description) = 0;
};

#endif /* IAUTHLISTENER_H_ */
