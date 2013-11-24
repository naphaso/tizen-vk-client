/*
 * EmojiPopup.h
 *
 *  Created on: Nov 24, 2013
 *      Author: wolong
 */

#ifndef EMOJIPOPUP_H_
#define EMOJIPOPUP_H_

#include <FUi.h>

class EmojiPopup : public Tizen::Ui::IPropagatedKeyEventListener, public Tizen::Ui::IActionEventListener {
public:
	EmojiPopup(Tizen::Ui::Controls::EditArea *editArea);
	virtual ~EmojiPopup();

	static void Show(Tizen::Ui::Controls::EditArea *editArea);


	// key listener
	// IPropagatedKeyEventListener
	virtual bool OnKeyPressed(Tizen::Ui::Control& source,
							 const Tizen::Ui::KeyEventInfo& keyEventInfo) {return false;};
	virtual bool OnKeyReleased(Tizen::Ui::Control& source,
							  const Tizen::Ui::KeyEventInfo& keyEventInfo);
	virtual bool OnPreviewKeyPressed(Tizen::Ui::Control& source,
									const Tizen::Ui::KeyEventInfo& keyEventInfo) {return false;};
	virtual bool OnPreviewKeyReleased(Tizen::Ui::Control& source,
									 const Tizen::Ui::KeyEventInfo& keyEventInfo) {return false;};
	virtual bool TranslateKeyEventInfo(Tizen::Ui::Control& source,
									  Tizen::Ui::KeyEventInfo& keyEventInfo) {return false;};

	// actions
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
private:
	void Start();
	Tizen::Ui::Controls::EditArea *_editArea;
	static Tizen::Ui::Controls::Popup *_popup;

};

#endif /* EMOJIPOPUP_H_ */
