#pragma once

#include "CoreMinimal.h"
#include "ThrowableItemDevice.h"
#include "UObject/Object.h"
#include "ThrowableItemLibrary/JoyShockLibrary.h"
#include "ThrowableItem.generated.h"

// Macros
#define GetThrowableItemLib() \
	GetGameInstance()->GetSubsystem<UThrowableItem>()

enum class ControllerDeviceState;
/** Abstract class to allow DualSense support */
UCLASS()
class THROWABLEITEM_API UThrowableItem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:	
	/// Global connected device stuff
	int ConnectedDevices = 0;
	int ActiveController = 0;
	TArray<IExternalGameController*> Devices;
	
	/// Run this in your Tick to test out if the library is working.
	/// Calls `UThrowableItem::Tick` on it's own.
	/// The controller Light Bar should flash red, green, and blue (epilepsy warning)
	/// - Will also return true if the test succeeded
	bool TestTick(float delta);

	/// Checks for new controllers, connects them, updates state, etc.
	void Tick();
	
	// Events
	// UDELEGATE()
	// DECLARE_DELEGATE(ControllerStateChange)

	// Event instances
	void OnControllerStateChange(ControllerDeviceState EventState);

	// Constructor/Destructor
	UThrowableItem();
	~UThrowableItem();
};

/// Global DLL handle
inline void* JoyShockHandle = nullptr;

// Enums
enum class ControllerDeviceState { Added, Removed };

