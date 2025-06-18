#include "pch.h"
#include "CMonster.h"
#include "CTimeManager.h"

CMonster::CMonster()
	: m_fSpeed(100.0f)
	, m_vCenterPos(Vector2(0, 0))
	, m_fMaxDistance(50.0f)
	, m_iDirection(1)
{
}

CMonster::~CMonster()
{
}

void CMonster::update()
{
	Vector2 vCurPos = GetPos();

	// 진행 방향에 맞춰서 시간당 m_fSpeed 만큼 이동
	vCurPos.x += fDeltaTime * m_fSpeed * m_iDirection;

	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;

	// 배회 거리 기준량을 넘었는지 검사
	if (0.0f < fDist)
	{
		// 방향 변경
		m_iDirection *= -1;
		vCurPos.x += m_iDirection * fDist;
	}

	SetPos(vCurPos);
}