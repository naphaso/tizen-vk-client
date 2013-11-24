/*
 * AttachControl.h
 *
 *  Created on: Nov 23, 2013
 *      Author: Igor Glotov
 */

#ifndef ATTACHCONTROL_H_
#define ATTACHCONTROL_H_

#include <FUi.h>
#include <FGraphics.h>
#include <FBase.h>

#include "AttachElement.h"
#include "IItemsRemovedListener.h"
#include "IElementActionListener.h"

class AttachControl:
	public Tizen::Ui::Controls::Panel,
	public IElementActionListener {
public:
	AttachControl();
	virtual ~AttachControl();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect);

	void SetItemsRemovedListener(IItemsRemovedListener * listener);
	virtual void OnElementRemoveRequest(AttachElement * source);

	result AddElement(AttachElement * element);
	Tizen::Base::Collection::IList * GetElements();
private:
	Tizen::Ui::Controls::ScrollPanel * _scrollPanel;
	Tizen::Ui::HorizontalBoxLayout * _itemLayout;

	IItemsRemovedListener *_listener;
	bool _locationAdded;
};

#endif /* ATTACHCONTROL_H_ */
