/*
 * ImageUtils.h
 *
 *  Created on: Nov 18, 2013
 *      Author: igorglotov
 */

#ifndef IMAGEUTILS_H_
#define IMAGEUTILS_H_

#include <FGraphics.h>

class ImageUtils {
public:
	ImageUtils();
	virtual ~ImageUtils();

	static const Tizen::Graphics::Rectangle ScaleTo(int width, const Tizen::Graphics::Rectangle & size);
};

#endif /* IMAGEUTILS_H_ */
