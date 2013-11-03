/**
 * Name        : VKU
 * Version     :
 * Vendor      :
 * Description :
 */

#include "VKU.h"
#include "VKUFrame.h"
#include "VKUAuthConfig.h"
#include "AppResourceId.h"
#include "SampleRequest.h"
#include "api/VKUApi.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::System;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

VKUApp::VKUApp(void) {
}

VKUApp::~VKUApp(void) {
}

UiApp*
VKUApp::CreateInstance(void) {
	return new VKUApp();
}

bool VKUApp::OnAppInitializing(AppRegistry& appRegistry) {
	PowerManager::SetScreenEventListener(*this);
	return true;
}

bool VKUApp::OnAppInitialized(void) {
	VKUFrame* pVKUFrame = new VKUFrame();
	pVKUFrame->Construct();
	pVKUFrame->SetName(L"VKU");
	AddFrame(*pVKUFrame);

	if(VKUAuthConfig::IsExists()) {
		VKUAuthConfig::Read();

		AppLog("logged!");

//		VKUApi *api = new VKUApi();
//		api->CreateRequest("messages.getDialogs", new SampleRequest())
//				->Put(L"count", L"1")
//				->Submit();
		SceneManager::GetInstance()->GoForward(SceneTransitionId(ID_SCNT_LOGIN_SUCCESS));
	}

	return true;
}

bool VKUApp::OnAppWillTerminate(void) {
	return true;
}

bool VKUApp::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination) {
	// TODO:
	// Deallocate resources allocated by this App for termination.
	// The App's permanent data and context can be saved via appRegistry.
	return true;
}

void VKUApp::OnForeground(void) {
	// TODO:
	// Start or resume drawing when the application is moved to the foreground.
}

void VKUApp::OnBackground(void) {
	// TODO:
	// Stop drawing when the application is moved to the background.
}

void VKUApp::OnLowMemory(void) {
	// TODO:
	// Free unused resources or close the application.
}

void VKUApp::OnBatteryLevelChanged(BatteryLevel batteryLevel) {
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void VKUApp::OnScreenOn(void) {
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void VKUApp::OnScreenOff(void) {
	// TODO:
	// Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device
	// to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a
	// callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}
