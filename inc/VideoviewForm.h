/*
 * VideoviewForm.h
 *
 *  Created on: Nov 18, 2013
 *      Author: igorglotov
 */

#ifndef VIDEOVIEWFORM_H_
#define VIDEOVIEWFORM_H_

#include <FUiUiConfigurationTypes.h>
#include <FUi.h>
#include <FBase.h>
#include <FMedia.h>
#include <FWebJson.h>

class VideoviewForm;

#include "IAPIRequestListener.h"

class VideoviewForm:
	public Tizen::Ui::Controls::Form,
	public Tizen::Ui::Controls::IFormBackEventListener,
	public Tizen::Ui::Scenes::ISceneEventListener,
	public Tizen::Media::IPlayerEventListener,
	public Tizen::Media::IPlayerVideoEventListener,
	public IAPIRequestListener {

public:
	VideoviewForm();
	virtual ~VideoviewForm();

	// form
	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId) {}
	result OnInitializing(void);
	result OnTerminating(void);

	// IFormBackEventListener
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

	bool Initialize();

protected:
    // IPlayerEventListener
    virtual void OnPlayerOpened(result r);
    virtual void OnPlayerEndOfClip(void) {}
    virtual void OnPlayerBuffering(int percent) {}
    virtual void OnPlayerErrorOccurred(Tizen::Media::PlayerErrorReason r) {}
    virtual void OnPlayerInterrupted(void) {}
    virtual void OnPlayerReleased(void) {}
    virtual void OnPlayerSeekCompleted(result r) {}
    virtual void OnPlayerAudioFocusChanged (void) {}

    // IPlayerVideoEventListener
	virtual void OnVideoFrameDecoded(Tizen::Media::Player& src,
			Tizen::Graphics::BitmapPixelFormat bitmapPixelFormat,
			const Tizen::Graphics::Dimension& dim, const byte* pBuffer, int sizeOfBuffer, result r) {};

	// IAPIRequestListener
	virtual void OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *object);
	virtual void OnError(result r);


	void PlayUrl(const Tizen::Base::String &url);
private:
	Tizen::Ui::Controls::Panel* pOverlayRegionSamplePanel;
	Tizen::Ui::Controls::OverlayRegion *pOverlayRegion;
	Tizen::Media::Player* pPlayer;
};

#endif /* VIDEOVIEWFORM_H_ */
