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

void CObject::render(HDC _dc)
{
	Rectangle(_dc, (int)(m_vPos.x - m_vScale.x / 2.0f), (int)(m_vPos.y - m_vScale.y / 2.0f),
		(int)(m_vPos.x + m_vScale.x / 2.0f), (int)(m_vPos.y + m_vScale.y / 2.0f));
}