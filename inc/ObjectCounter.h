/*
 * CheckedObject.h
 *
 *  Created on: Nov 23, 2013
 *      Author: wolong
 */

#ifndef CHECKEDOBJECT_H_
#define CHECKEDOBJECT_H_

#include <FBase.h>

class ObjectCounter {
public:
	ObjectCounter();
	virtual ~ObjectCounter();
	static Tizen::Base::Collection::HashMap *counterMap;
public:
	static void OnConstruct(const Tizen::Base::String &key);
	static void OnDestruct(const Tizen::Base::String &key);
	static void Report();
};

#define CONSTRUCT(classname) ObjectCounter::OnConstruct(classname)
#define DESTRUCT(classname) ObjectCounter::OnDestruct(classname)

#endif /* CHECKEDOBJECT_H_ */
