#pragma once

#define NUM_KEY_MAX (256)

class Input
{
private:

	static BYTE m_OldKeyState[NUM_KEY_MAX];
	static BYTE m_KeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	static BYTE m_KeyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	static BYTE m_KeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	static BYTE m_KeyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N

public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );
	static bool GetKeyRelease(BYTE KeyCode);
		
};
