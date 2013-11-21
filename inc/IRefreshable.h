/*
 * IRefreshable.h
 *
 *  Created on: Nov 21, 2013
 *      Author: wolong
 */

#ifndef IREFRESHABLE_H_
#define IREFRESHABLE_H_

class IRefreshable {
public:
	virtual ~IRefreshable() {};
	virtual void OnRefresh() = 0;
};


#endif /* IREFRESHABLE_H_ */
