#ifndef I_READ_EVENT_LISTENER_H_
#define I_READ_EVENT_LISTENER_H_

class IReadEventListener {
public:
	virtual ~IReadEventListener() {};
	virtual void OnReadEvent(int messageId) = 0;
};

#endif // I_READ_EVENT_LISTENER_H_
