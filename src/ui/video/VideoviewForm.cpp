/*
 * VideoviewForm.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: igorglotov
 */

#include "VideoviewForm.h"
#include "AppResourceId.h"
#include "VKU.h"
#include "SceneRegister.h"
#include "ObjectCounter.h"
#include "JsonParseUtils.h"
#include "VKUApi.h"
#include "Requests.h"

using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Base;
using namespace Tizen::Graphics;
using namespace Tizen::Media;
using namespace Tizen::Base::Utility;
using namespace Tizen::Web::Json;

VideoviewForm::VideoviewForm() {
	CONSTRUCT(L"VideoviewForm");
}

VideoviewForm::~VideoviewForm() {
	DESTRUCT(L"VideoviewForm");
}

result VideoviewForm::OnInitializing(void) {
	result r = E_SUCCESS;

	// Sets an overlay region area
	int widthVideo = 720;
	int HeightVideo = 480;
	Rectangle overlayRectangle(0, 100, widthVideo, HeightVideo);

	// Evaluates bounds of overlay region
	bool modified = false;
	OverlayRegion::EvaluateBounds(OVERLAY_REGION_EVALUATION_OPTION_GREATER_THAN, overlayRectangle, modified);

	// Gets an overlay region
	pOverlayRegion = GetOverlayRegionN(overlayRectangle, OVERLAY_REGION_TYPE_NORMAL);

	// Gets buffer information
	BufferInfo bufferInfo;
	pOverlayRegion->GetBackgroundBufferInfo(bufferInfo);

	// Gets a video file path
	String videoFilePath = App::GetInstance()->GetAppResourcePath() + L"tizen.mp4";
	Uri playUri;

	Label* pLabel = new Label();
//	Button* pButton = new Button();

	// Creates an instance of Player
	pPlayer = new Player();
	r = pPlayer->Construct(*this, &bufferInfo);
	TryCatch(r == E_SUCCESS, , "Failed pPlayer->Construct");

	pPlayer->SetLooping(true);

	/*
	playUri.SetUri(L"http://cs518400v4.vk.me/u16423084/videos/442a33813f.720.mp4");
	TryCatch(r == E_SUCCESS, , "Failed pPlayer->Play()");

	AppLog("Opening URI");
	r = pPlayer->OpenUrl(playUri);
	TryCatch(r == E_SUCCESS, , "Failed pPlayer->Play()");

	r = pPlayer->Play();
	TryCatch(r == E_SUCCESS, , "Failed pPlayer->Play()");

	AppLog("Playing...");
	*/

	// Creates instaces of Button and Label and adds controls to the panel
	pLabel->Construct(Rectangle(0, 50, 400, 80),L"OverlayRegion Sample");
	pLabel->SetTextColor(Color::GetColor(COLOR_ID_RED));
	AddControl(pLabel);

//	pButton->Construct(Rectangle(positionX + widthVideo - 200, positionX + HeightVideo - 100, 180, 80),L"BUTTON");
//	AddControl(pButton);

	return r;
CATCH:
	AppLogException("CreateItem is failed. %s", GetErrorMessage(r));
	return r;
}

result VideoviewForm::OnTerminating(void) {
    result r = E_SUCCESS;

    // Deallocates controls
    if (pPlayer)
    {
        r = pPlayer->Close();
        delete pPlayer;
    }

    return r;
}

bool VideoviewForm::Initialize() {
	Form::Construct(IDF_VIDEOVIEW);

	SceneManager* pSceneManager = SceneManager::GetInstance();
	pSceneManager->AddSceneEventListener(SCENE_VIDEOVIEW, *this);

	SetFormBackEventListener(this);

	return true;
}

void VideoviewForm::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
							   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs) {
	result r;
	int videoId;
	int ownerId;
	JsonObject *videoObject;
	String fullVideoId;


	videoObject = static_cast<JsonObject *>(pArgs->GetAt(0));

	r = JsonParseUtils::GetInteger(*videoObject, L"id", videoId);
	r = JsonParseUtils::GetInteger(*videoObject, L"owner_id", ownerId);

	delete pArgs;


	fullVideoId.Append(ownerId);
	fullVideoId.Append(L"_");
	fullVideoId.Append(videoId);

	AppLog("activated, videoid: %ls", fullVideoId.GetPointer());

	VKUApi::GetInstance().CreateRequest(L"execute.getVideo", this)
			->Put(L"video_id", fullVideoId)
			->Put(L"owner_id", Integer::ToString(ownerId))
			->Submit(REQUEST_GET_VIDEO);
	/*
	 * 	playUri.SetUri(L"http://cs518400v4.vk.me/u16423084/videos/442a33813f.720.mp4");
	TryCatch(r == E_SUCCESS, , "Failed pPlayer->Play()");

	AppLog("Opening URI");
	r = pPlayer->OpenUrl(playUri);
	TryCatch(r == E_SUCCESS, , "Failed pPlayer->Play()");

	r = pPlayer->Play();
	TryCatch(r == E_SUCCESS, , "Failed pPlayer->Play()");

	AppLog("Playing...");
	 */
}

void VideoviewForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source) {
	AppLog("You can't leave Omsk");
	SceneManager* pSceneManager = SceneManager::GetInstance();
	pSceneManager->GoBackward(BackwardSceneTransition(SCENE_TRANSITION_ANIMATION_TYPE_ZOOM_OUT));
}


// IAPIRequestListener
void VideoviewForm::OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *object) {
	if(requestId != REQUEST_GET_VIDEO) {
		return;
	}

	result r;
	JsonObject *response;
	JsonObject *files;
	String videoUrl;

	ByteBuffer buffer;
	JsonWriter::Compose(object, buffer);
	AppLog("response: %s", buffer.GetPointer());

	r = JsonParseUtils::GetObject(object, L"response", response);
	TryCatch(r == E_SUCCESS, , "failed to get response from object");

	r = JsonParseUtils::GetObject(response, L"files", files);
	TryCatch(r == E_SUCCESS, , "failed to get files from response");

	if(JsonParseUtils::GetString(*files, L"mp4_360", videoUrl) == E_SUCCESS) {
		PlayUrl(videoUrl);
		return;
	}

	if(JsonParseUtils::GetString(*files, L"mp4_240", videoUrl) == E_SUCCESS) {
		PlayUrl(videoUrl);
		return;
	}

	if(JsonParseUtils::GetString(*files, L"mp4_480", videoUrl) == E_SUCCESS) {
		PlayUrl(videoUrl);
		return;
	}

	r = E_FILE_NOT_FOUND;

	CATCH:
	AppLogException("failed to play video: %s", GetErrorMessage(r));
	return;
}



void VideoviewForm::OnError(result r) {
	AppLog("error on open video: %s", GetErrorMessage(r));
}

void VideoviewForm::PlayUrl(const String &url) {
	result r;

	AppLog("Opening URI");
	r = pPlayer->OpenUrlAsync(url);
	TryCatch(r == E_SUCCESS, , "Failed pPlayer->OpenUrlAsync()");

	return;
	CATCH:
	AppLogException("failed to open url: %s", GetErrorMessage(r));
	return;
}

void VideoviewForm::OnPlayerOpened(result r) {
	if(r == E_SUCCESS) {
		pPlayer->Play();
	} else {
		AppLogException("failed to open video: %s", GetErrorMessage(r));
	}
}
