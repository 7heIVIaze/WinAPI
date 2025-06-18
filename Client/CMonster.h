#pragma once
#include "CObject.h"
class CMonster : public CObject
{
private:
	float m_fSpeed;
	Vector2 m_vCenterPos;
	float m_fMaxDistance;
	int m_iDirection; // 1 ~ -1

public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void SetMoveDistance(float _fMoveDistance) { m_fMaxDistance = _fMoveDistance; }

	void SetCenterPos(Vector2 _vPos) { m_vCenterPos = _vPos; }
public:
	virtual void update();

public:
	CMonster();
	~CMonster();

};

