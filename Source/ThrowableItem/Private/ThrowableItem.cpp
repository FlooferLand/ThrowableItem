#include "ThrowableItem.h"
#include "ThrowableItemDevice.h"
#include "Misc/MessageDialog.h"
// #define LOCTEXT_NAMESPACE "UThrowableItem"

// Tick to test if the library is working.
// Global variables; Convenience during dev is key
float TestTimer = 0.0;
bool UThrowableItem::TestTick(float delta)
{
	// Update one-self
	Tick();
	
	// Guard
	if (!JslStillConnected(ActiveController))
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			10.0,
			FColor::Green,
			TEXT("Could not find a controller!")
		);
		return false;
	}

	// Showing a colour
	if (TestTimer >= 10.0)
	{
		// Picking a colour
		constexpr int COLORS[3] = {
			0xFF0000, // RED
			0x00FF00, // GREEN
			0x0000FF  // BLUE
		};
		const int color = COLORS[FMath::RandRange(0, 2)];
	
		// Logic
		JslSetLightColour(ActiveController, color);
		TestTimer = 0.0;
	}
	TestTimer += delta * 60;
	return true;
}

void UThrowableItem::Tick()
{
	// Search for new devices and connect them
	int oldConnectedState = ConnectedDevices;
	ConnectedDevices = JslConnectDevices();
	
	// Fire an event when something changed
	if (JslConnectDevices() != oldConnectedState)
	{
		ControllerDeviceState state;
		int diff = ConnectedDevices - oldConnectedState;
		if (diff > 0)
			state = ControllerDeviceState::Added;
		else
			state = ControllerDeviceState::Removed;
	
		OnControllerStateChange(state);
	}
}

#pragma region Construction/destruction
UThrowableItem::UThrowableItem()
{
	// TODO: Make this into a delegate
	// ControllerStateChange.BindRaw(&OnControllerStateChange);
}

UThrowableItem::~UThrowableItem()
{
	JslDisconnectAndDisposeAll();
} 
#pragma endregion

void UThrowableItem::OnControllerStateChange(ControllerDeviceState EventState)
{
	switch (EventState)
	{
	case ControllerDeviceState::Added:
		// TArray<IExternalGameController*> PluginImplementations = IModularFeatures::Get().GetModularFeatureImplementations<IExternalGameController>( IExternalGameController::GetModularFeatureName() );
		// for(auto InputPluginIt = PluginImplementations.CreateIterator(); InputPluginIt; ++InputPluginIt)
		// {
		// 	TSharedPtr<IInputDevice> Device = (*InputPluginIt)->CreateInputDevice(MessageHandler);
		// 	if ( Device.IsValid() )
		// 	{
		// 		Devices.Add(Device);
		// 	}
		// }

		// FMessageDialog::Open(
		// 	EAppMsgType::Ok,
		// 	LOCTEXT(
		// 		"Support error",
		// 		"DualSense features such as the lightbar, haptic feedback, triggers, and such are supported, however.\n"
		// 		"You will currently require an external program such as DS4Windows to use the joysticks and buttons, and you must set the software to give 'passtrough' for all the sensors and thingymajigs for them all to work."
		// 	)
		// );
		
		break;
	case ControllerDeviceState::Removed:
		break;
	}
}
