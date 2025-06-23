#include "pch.h"
#include "CPlayer.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CMissile.h"

void CPlayer::update()
{
	Vector2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.0f * fDeltaTime;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.0f * fDeltaTime;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.0f * fDeltaTime;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.0f * fDeltaTime;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);
}

void CPlayer::CreateMissile()
{
	Vector2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2;

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vector2(25.0f, 25.0f));
	pMissile->SetDirection(Vector2(-1.0f, -7.0f));

	CScene* pCurScene = CSceneManager::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}
