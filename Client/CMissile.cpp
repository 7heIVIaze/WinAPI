#include "pch.h"
#include "CMissile.h"
#include "CTimeManager.h"

CMissile::CMissile()
	: m_fDirection(1.0f)
{

}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vector2 vPos = GetPos();

	vPos.y += 600.0f * fDeltaTime * m_fDirection;

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