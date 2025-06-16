#include "pch.h"
#include "CObject.h"
#include "CKeyManager.h"
#include "CTimeManager.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

void CObject::update()
{
	if (CKeyManager::GetInst()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
	{
		m_vPos.y -= 200.0f * fDeltaTime;
	}
	if (CKeyManager::GetInst()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
	{
		m_vPos.y += 200.0f * fDeltaTime;
	}
	if (CKeyManager::GetInst()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
	{
		m_vPos.x -= 200.0f * fDeltaTime;
	}
	if (CKeyManager::GetInst()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
	{
		m_vPos.x += 200.0f * fDeltaTime;
	}
}

void CObject::render(HDC _dc)
{
	Rectangle(_dc, (int)(m_vPos.x - m_vScale.x / 2.0f), (int)(m_vPos.y - m_vScale.y / 2.0f),
		(int)(m_vPos.x + m_vScale.x / 2.0f), (int)(m_vPos.y + m_vScale.y / 2.0f));
}