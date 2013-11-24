/*
 * AttachPhotoElement.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: Igor Glotov
 */

#include "AttachPhotoElement.h"

using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::App;
using namespace Tizen::Base::Collection;
using namespace Tizen::Web::Json;

AttachPhotoElement::AttachPhotoElement() {
	// TODO Auto-generated constructor stub

}

AttachPhotoElement::~AttachPhotoElement() {
	// TODO Auto-generated destructor stub
}

result AttachPhotoElement::Construct(const Tizen::Graphics::Rectangle & rect, const Tizen::Base::String &url) {
	result r = E_SUCCESS;
	r = AttachElement::Construct(rect);
	RelativeLayout * layout = dynamic_cast<RelativeLayout *>(GetLayoutN());

	_url = String(url);
	int slash = -111;
//	r = _url.LastIndexOf(L'/', 0, slash);
	for (int i=0; i<_url.GetLength(); i++) {
		wchar_t sym;
		_url.GetCharAt(i, sym);

		if (sym == L'/')
			slash = i;
	}

	slash++;

	String fileName;
	_url.SubString(slash, fileName);

	_icon = new LocalImageView();
	_icon->Construct(Rectangle(0, 0, 72, 72), "icon_photo.png");
//	r = layout->SetCenterAligned(*_icon, CENTER_ALIGN_VERTICAL);

	Label *label = new Label();
	label->Construct(Rectangle(0, 0, rect.width, 40), fileName);
	label->SetTextConfig(30, LABEL_TEXT_STYLE_NORMAL);

	_pProgress = new Progress();
	_pProgress->Construct(Rectangle(0, 0, rect.width, 20), 0, 100);
	_pProgress->SetValue(0);

	r = AddControl(label);
	r = AddControl(_icon);
	r = AddControl(_pProgress);

	r = layout->SetCenterAligned(*_icon, CENTER_ALIGN_HORIZONTAL);

	r = layout->SetRelation(*_icon, this, RECT_EDGE_RELATION_TOP_TO_TOP);
	r = layout->SetMargin(*_icon, 0, 0, 20, 0);

	r = layout->SetRelation(*label, _icon, RECT_EDGE_RELATION_TOP_TO_BOTTOM);
	r = layout->SetCenterAligned(*label, CENTER_ALIGN_HORIZONTAL);
	r = layout->SetMargin(*label, 10, 10, 10, 0);

	r = layout->SetRelation(*_pProgress, label, RECT_EDGE_RELATION_TOP_TO_BOTTOM);
	r = layout->SetMargin(*_pProgress, 10, 10, 10, 0);
	r = layout->SetCenterAligned(*_pProgress, CENTER_ALIGN_HORIZONTAL);

	StartUpload(_url);

	return r;
}

void AttachPhotoElement::OnUploadError(result r) {
	AppLog("Error %s", GetErrorMessage(r));
}

void AttachPhotoElement::OnUploadSuccess(Tizen::Web::Json::JsonObject *savedPhoto) {
	ByteBuffer buffer;
	buffer.Construct(100000);

	JsonWriter::Compose(savedPhoto, buffer);

	AppLog("Upload success! %s", buffer.GetPointer());
	RemoveControl(_pProgress);
}

void AttachPhotoElement::OnUploadProgress(long long currentLength, long long totalLength) {
	AppLog("Upload progress %lld of %lld", currentLength, totalLength);
	double perc = (double) currentLength / (double) totalLength;
	_pProgress->SetValue((int) (perc * 100));
	_pProgress->RequestRedraw(true);
}

