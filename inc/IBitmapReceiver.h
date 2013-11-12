#ifndef I_BITMAP_RECEIVER_H
#define I_BITMAP_RECEIVER_H

#include <FGraphics.h>

class IBitmapReceiver {
	virtual void UpdateBitmap(Tizen::Graphics::Bitmap *bitmap) = 0;
	virtual ~IBitmapReceiver() {};
};

#endif

