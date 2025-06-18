#pragma once
#include "CObject.h"

class CMissile : public CObject
{
private:
	float m_fDirection;

public:
	void SetDirection(bool _bUp)
	{
		if (_bUp)
		{
			m_fDirection = -1.0f;
		}
		else
		{
			m_fDirection = 1.0f;
		}
	}

public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	CMissile();
	~CMissile();

};

