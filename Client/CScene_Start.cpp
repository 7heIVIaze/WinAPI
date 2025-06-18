#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{

}

void CScene_Start::Enter()
{
	// Player Object 추가
	CObject* pObj = new CPlayer;

	pObj->SetPos(Vector2(640.0f, 384.0f));
	pObj->SetScale(Vector2(100.0f, 100.0f));

	AddObject(pObj, GROUP_TYPE::DEFAULT);

	// Monster Object 추가
	int iMonsterCount = 16;
	float fMoveDist = 25.0f;
	float fObjScale = 50.0f;

	Vector2 vResolution = CCore::GetInst()->GetResolution();
	float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.0f) * 2)) / float(iMonsterCount - 1);

	CMonster* pMonsterObj = nullptr;

	for (int i = 0; i < iMonsterCount; ++i)
	{
		pMonsterObj = new CMonster;
		pMonsterObj->SetPos(Vector2((fMoveDist + fObjScale / 2.0f) + (float)i * fTerm, 50.0f));
		pMonsterObj->SetScale(Vector2(fObjScale, fObjScale));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);

		AddObject(pMonsterObj, GROUP_TYPE::DEFAULT);
	}
}

void CScene_Start::Exit()
{
}
