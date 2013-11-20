/*
 * MessageForwardedElement.h
 *
 *  Created on: Nov 20, 2013
 *      Author: Igor Glotov
 */

#ifndef MESSAGEFORWARDEDELEMENT_H_
#define MESSAGEFORWARDEDELEMENT_H_

#include <FUi.h>
#include <FWeb.h>
#include <FBase.h>

#include "IAPIRequestListener.h"
#include "RoundedAvatar.h"
#include "MessageElement.h"

class MessageForwardedElement:
	public MessageElement,
	public IAPIRequestListener {
public:
	MessageForwardedElement();
	virtual ~MessageForwardedElement();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect, Tizen::Web::Json::JsonObject * forwardedMessage, int out);

	virtual void OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *object);
	virtual void OnError();

	virtual MessageElementType GetElementType() { return MESSAGE_TYPE_FORWARD; }
private:
	void RequestUser(int userId);
	void ProcessUserJson(Tizen::Web::Json::JsonObject * userObject);

	Tizen::Web::Json::JsonObject * _forwardedMessage;

	Tizen::Ui::Controls::Label * _nameLabel;
	RoundedAvatar * _avatar;
	int _requestId;
};

#endif /* MESSAGEFORWARDEDELEMENT_H_ */
