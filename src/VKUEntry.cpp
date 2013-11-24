//
// This file contains the Tizen application entry point.
//
#include "VKU.h"

#include "ObjectCounter.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

_EXPORT_ int OspMain(int argc, char* pArgv[]) {
	AppLog("Application started.");
	ArrayList args(SingleObjectDeleter);
	args.Construct();
	for (int i = 0; i < argc; i++) {
		args.Add(new (std::nothrow) String(pArgv[i]));
	}

	result r = Tizen::App::UiApp::Execute(VKUApp::CreateInstance, &args);
	TryLog(r == E_SUCCESS,
			"[%s] Application execution failed", GetErrorMessage(r));

	ObjectCounter::Report();

	AppLog("Application finished.");

	return static_cast<int>(r);
}
#ifdef __cplusplus
}
#endif // __cplusplus
