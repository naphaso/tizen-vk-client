/*
 * AttachPhotoElement.h
 *
 *  Created on: Nov 24, 2013
 *      Author: Igor Glotov
 */

#ifndef ATTACHPHOTOELEMENT_H_
#define ATTACHPHOTOELEMENT_H_

#include "AttachElement.h"
#include "LocalImageView.h"
#include "FileUploader.h"

class AttachPhotoElement:
	public AttachElement,
	public PhotoUploadTrait {
public:
	AttachPhotoElement();
	virtual ~AttachPhotoElement();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect, const Tizen::Base::String &url);

	// PhotoUploadTrait
	virtual void OnUploadError(result r);
	virtual void OnUploadSuccess(Tizen::Web::Json::JsonObject *savedPhoto);
	virtual void OnUploadProgress(long long currentLength, long long totalLength);
private:
	Tizen::Base::String _url;
	LocalImageView * _icon;

	Tizen::Ui::Controls::Progress* _pProgress;
};

#endif /* ATTACHPHOTOELEMENT_H_ */
