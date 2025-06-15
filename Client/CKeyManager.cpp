#include "pch.h"
#include "CKeyManager.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT, //	LEFT,
	VK_RIGHT, //RIGHT,
	VK_UP, //UP,
	VK_DOWN, //DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',
	
	VK_MENU, //ALT,
	VK_CONTROL, //CLTR,
	VK_LSHIFT, //LSHIFT,
	VK_SPACE, //SPACE,
	VK_RETURN, //ENTER,
	VK_ESCAPE, //ESC,

	//LAST,
};

CKeyManager::CKeyManager()
{ 
}

CKeyManager::~CKeyManager()
{

}

void CKeyManager::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo({ KEY_STATE::NONE, false }));
	}

}

void CKeyManager::update()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		// 키가 눌려 있다.
		if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
		{
			// 이전에도 눌렀다.
			if (m_vecKey[i].bPrevPush)
			{
				m_vecKey[i].eState = KEY_STATE::HOLD;
			}
			// 이전에는 안 눌렀다.
			else
			{
				m_vecKey[i].eState = KEY_STATE::TAP;
			}

			m_vecKey[i].bPrevPush = true;
		}
		// 키가 안 눌려있다.
		else
		{
			// 이전에는 눌렀다.
			if (m_vecKey[i].bPrevPush)
			{
				m_vecKey[i].eState = KEY_STATE::RELEASE;
			}
			// 이전에도 안 눌렀다.
			else
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}

			m_vecKey[i].bPrevPush = false;
		}
	}
}