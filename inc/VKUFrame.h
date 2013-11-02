#ifndef _VKU_FRAME_H_
#define _VKU_FRAME_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>
#include <FUiIme.h>
#include <FGraphics.h>
#include <gl.h>

class VKUFrame
	: public Tizen::Ui::Controls::Frame
{
public:
	VKUFrame(void);
	virtual ~VKUFrame(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
};

#endif	//_VKU_FRAME_H_
