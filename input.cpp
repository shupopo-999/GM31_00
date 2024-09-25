
#include "main.h"
#include "input.h"
					
BYTE Input::m_OldKeyState[NUM_KEY_MAX];
BYTE Input::m_KeyState[NUM_KEY_MAX];
BYTE Input::m_KeyStateTrigger[NUM_KEY_MAX];
BYTE Input::m_KeyStateRepeat[NUM_KEY_MAX];
BYTE Input::m_KeyStateRelease[NUM_KEY_MAX];

LPDIRECTINPUT8			Input::g_pDInput = NULL;
LPDIRECTINPUTDEVICE8	Input::pMouse = nullptr;
DIMOUSESTATE2			Input::mouseState = {};		// �}�E�X�̃_�C���N�g�ȏ��
DIMOUSESTATE2			Input::mouseTrigger = {};	// �����ꂽ�u�Ԃ���ON

void Input::Init()
{

	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );
}


void Input::UnInit()
{


}

void Input::Update()
{

	memcpy( m_OldKeyState, m_KeyState, 256 );

	GetKeyboardState( m_KeyState );

	HRESULT result;
	// �O��̒l�ۑ�
	DIMOUSESTATE2 lastMouseState = mouseState;
	// �f�[�^�擾
	result = pMouse->GetDeviceState(sizeof(mouseState), &mouseState);
	if (SUCCEEDED(result))
	{
		mouseTrigger.lX = mouseState.lX;
		mouseTrigger.lY = mouseState.lY;
		mouseTrigger.lZ = mouseState.lZ;
		// �}�E�X�̃{�^�����
		for (int i = 0; i < 8; i++)
		{
			mouseTrigger.rgbButtons[i] = ((lastMouseState.rgbButtons[i] ^
				mouseState.rgbButtons[i]) & mouseState.rgbButtons[i]);
		}
	}
	else	// �擾���s
	{
		// �A�N�Z�X���𓾂Ă݂�
		result = pMouse->Acquire();
	}
	return (void)result;
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

// �}�E�X�̓��͏���
BOOL Input::MouseLPressed(void){
	return (BOOL)(mouseState.rgbButtons[0] & 0x80);	// �����ꂽ�Ƃ��ɗ��r�b�g������
}
BOOL Input::MouseLTriggered(void){
	return (BOOL)(mouseTrigger.rgbButtons[0] & 0x80);
}
BOOL Input::MouseRPressed(void){
	return (BOOL)(mouseState.rgbButtons[1] & 0x80);
}
BOOL Input::MouseRTriggered(void){
	return (BOOL)(mouseTrigger.rgbButtons[1] & 0x80);
}
BOOL Input::MouseCPressed(void){
	return (BOOL)(mouseState.rgbButtons[2] & 0x80);
}
BOOL Input::MouseCTriggered(void){
	return (BOOL)(mouseTrigger.rgbButtons[2] & 0x80);
}
