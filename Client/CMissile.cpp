#include "pch.h"
#include "CMissile.h"
#include "CTimeManager.h"

CMissile::CMissile()
	: m_fTheta(M_PI / 4.0f)
	, m_vDir(Vector2(1.0f, 1.0f))
{
	m_vDir.Normalize();
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vector2 vPos = GetPos();

	/*vPos.x += 600.0f * cosf(m_fTheta) * fDeltaTime;
	vPos.y -= 600.0f * sinf(m_fTheta) * fDeltaTime;*/

	vPos.x += 600.0f * m_vDir.x * fDeltaTime;
	vPos.y += 600.0f * m_vDir.y * fDeltaTime;

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vector2	vPos = GetPos();
	Vector2 vScale = GetScale();

	// 오브젝트를 원으로 그려주는 함수.
	Ellipse(_dc, (int)(vPos.x - vScale.x / 2.0f), (int)(vPos.y - vScale.y / 2.0f),
		(int)(vPos.x + vScale.x / 2.0f), (int)(vPos.y + vScale.y / 2.0f));
}