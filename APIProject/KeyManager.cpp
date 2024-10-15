#include "pch.h"
#include "KeyManager.h"

KeyManager* KeyManager::m_pInstance = nullptr;

KeyManager::KeyManager()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

KeyManager::~KeyManager()
{
}

bool KeyManager::Key_Pressing(int _iKey)
{
	if (GetAsyncKeyState(_iKey) & 0x8000)
		return true;

	return false;
}

bool KeyManager::Key_Down(int _iKey)
{
	if ((!m_bKeyState[_iKey]) && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	return false;
}

bool KeyManager::Key_Up(int _iKey)
{
	if ((m_bKeyState[_iKey]) && !(GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	return false;
}

void KeyManager::Update_Key()
{
	for (int i = 0; i < VK_MAX; ++i)
	{
		if (GetAsyncKeyState(i) & 0x8000)
			m_bKeyState[i] = true;

		if (!(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = false;
	}
}
