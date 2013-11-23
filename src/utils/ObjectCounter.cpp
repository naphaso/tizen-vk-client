/*
 * CheckedObject.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: wolong
 */

#include "ObjectCounter.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

ObjectCounter::ObjectCounter() {
	// TODO Auto-generated constructor stub

}

ObjectCounter::~ObjectCounter() {
	// TODO Auto-generated destructor stub
}

HashMap *ObjectCounter::counterMap = null;


void ObjectCounter::OnConstruct(const String &key) {
	if(counterMap == null) {
		counterMap = new HashMap();
		counterMap->Construct();
	}

	Integer *counter = static_cast<Integer*>(counterMap->GetValue(key));
	if(counter == null) {
		counter = new Integer(0);
		counterMap->Add(new String(key), counter);
	}

	counter->value++;
}

void ObjectCounter::OnDestruct(const String &key) {
	if(counterMap == null) {
		counterMap = new HashMap();
		counterMap->Construct();
	}

	Integer *counter = static_cast<Integer*>(counterMap->GetValue(key));
	if(counter == null) {
		counter = new Integer(0);
		counterMap->Add(new String(key), counter);
	}

	counter->value--;
}

void ObjectCounter::Report() {
	IMapEnumerator *enumerator = counterMap->GetMapEnumeratorN();
	while(enumerator->MoveNext() == E_SUCCESS) {
		AppLog("REPORT %ls: %d", static_cast<String *>(enumerator->GetKey())->GetPointer(), static_cast<Integer *>(enumerator->GetValue())->ToInt());
	}

	delete enumerator;
}
