#include "XBOXController.h"


#ifdef WIN32
#ifdef XIN

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace Chorus
{

	XBOXController::XBOXController(int playerNumber,bool clamp)
	{
		// Set the Controller Number
		_controllerNum = playerNumber - 1;
	}

	XINPUT_STATE XBOXController::GetState()
	{
		// Zeroise the state
		ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

		// Get the state
		XInputGetState(_controllerNum, &_controllerState);
		if(m_clamp)
		{
			// Zero value if thumbsticks are within the dead zone 
			if( ( _controllerState.Gamepad.sThumbLX < INPUT_DEADZONE &&
				_controllerState.Gamepad.sThumbLX > -INPUT_DEADZONE ) &&
				( _controllerState.Gamepad.sThumbLY < INPUT_DEADZONE &&
				_controllerState.Gamepad.sThumbLY > -INPUT_DEADZONE ) )
			{
				_controllerState.Gamepad.sThumbLX = 0;
				_controllerState.Gamepad.sThumbLY = 0;
			}

			if( ( _controllerState.Gamepad.sThumbRX < INPUT_DEADZONE &&
				_controllerState.Gamepad.sThumbRX > -INPUT_DEADZONE ) &&
				( _controllerState.Gamepad.sThumbRY < INPUT_DEADZONE &&
				_controllerState.Gamepad.sThumbRY > -INPUT_DEADZONE ) )
			{
				_controllerState.Gamepad.sThumbRX = 0;
				_controllerState.Gamepad.sThumbRY = 0;
			}
		}

		return _controllerState;
	}

	bool XBOXController::IsConnected()
	{
		// Zeroise the state
		ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

		// Get the state
		DWORD Result = XInputGetState(_controllerNum, &_controllerState);

		if(Result == ERROR_SUCCESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void XBOXController::Vibrate(int leftVal, int rightVal)
	{
		// Create a Vibraton State
		XINPUT_VIBRATION Vibration;

		// Zeroise the Vibration
		ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

		// Set the Vibration Values
		Vibration.wLeftMotorSpeed = leftVal;
		Vibration.wRightMotorSpeed = rightVal;

		// Vibrate the controller
		XInputSetState(_controllerNum, &Vibration);
	}

}
#endif
#endif
