#pragma once
#include "IInputDeviceModule.h"

/// Adds controller support
class FThrowableItemModule : public IModuleInterface // IInputDeviceModule
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
