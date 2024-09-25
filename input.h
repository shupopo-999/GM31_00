#pragma once
#include <dinput.h>


#define NUM_KEY_MAX (256)

class Input
{
private:

	static BYTE m_OldKeyState[NUM_KEY_MAX];
	static BYTE m_KeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	static BYTE m_KeyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	static BYTE m_KeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	static BYTE m_KeyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N

	static LPDIRECTINPUT8			g_pDInput;
	static LPDIRECTINPUTDEVICE8		pMouse;			// mouse
	static DIMOUSESTATE2			mouseState;		// �}�E�X�̃_�C���N�g�ȏ��
	static DIMOUSESTATE2			mouseTrigger;	// �����ꂽ�u�Ԃ���ON

public:
	static void Init();
	HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow);
	static void UnInit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );
	static bool GetKeyRelease(BYTE KeyCode);

	BOOL MouseLPressed(void);
	BOOL MouseLTriggered(void);
	BOOL MouseRPressed(void);
	BOOL MouseRTriggered(void);
	BOOL MouseCPressed(void);
	BOOL MouseCTriggered(void);


	// �}�E�X�̃|�W�V�����擾
	long GetMouseX(void) {
		return mouseState.lX;
	}
	long GetMouseY(void) {
		return mouseState.lY;
	}
	long GetMouseZ(void) {
		return mouseState.lZ;
	}
		
};
