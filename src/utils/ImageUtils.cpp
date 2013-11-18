/*
 * ImageUtils.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: igorglotov
 */

#include "ImageUtils.h"
#include <math.h>

using namespace Tizen::Graphics;

ImageUtils::ImageUtils() {
	// TODO Auto-generated constructor stub

}

ImageUtils::~ImageUtils() {
	// TODO Auto-generated destructor stub
}


const Rectangle ImageUtils::ScaleTo(int widthTo, const Rectangle & size) {
	double scaleFactor = (double) size.width / widthTo;

	int newHeight = round((double)size.height / scaleFactor);

	return Rectangle(0, 0, widthTo, newHeight);
}
