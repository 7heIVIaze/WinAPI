#pragma once
#include "CObject.h"

class CMissile : public CObject
{
private:
	float m_fTheta; // 이동 방향(각도)
	Vector2 m_vDir;
public:
	void SetDirection(float _fTheta) { m_fTheta = _fTheta; }
	void SetDirection(Vector2 _vDir) 
	{ 
		m_vDir = _vDir; 
		m_vDir.Normalize();
	}

public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	CMissile();
	~CMissile();

};

