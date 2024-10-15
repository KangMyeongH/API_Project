#pragma once
class KeyManager
{
private:
	KeyManager();
	~KeyManager();

public:
	bool		Key_Pressing(int _iKey);
	bool		Key_Down(int _iKey);
	bool		Key_Up(int _iKey);

	void		Update_Key();

public:
	static		KeyManager* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new KeyManager;
		}

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static		KeyManager* m_pInstance;

	bool		m_bKeyState[VK_MAX];

};

