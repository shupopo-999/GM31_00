
#include "main.h"
#include "input.h"
					
BYTE Input::m_OldKeyState[NUM_KEY_MAX];
BYTE Input::m_KeyState[NUM_KEY_MAX];
BYTE Input::m_KeyStateTrigger[NUM_KEY_MAX];
BYTE Input::m_KeyStateRepeat[NUM_KEY_MAX];
BYTE Input::m_KeyStateRelease[NUM_KEY_MAX];

void Input::Init()
{

	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );

}

void Input::Uninit()
{


}

void Input::Update()
{

	memcpy( m_OldKeyState, m_KeyState, 256 );

	GetKeyboardState( m_KeyState );

}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

bool Input::GetKeyRelease(BYTE KeyCode)
{
	return (m_KeyStateRelease[KeyCode] & 0x80) ? true : false;
}