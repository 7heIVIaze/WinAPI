#pragma once


class CObject
{
private:
	Vector2 m_vPos;
	Vector2 m_vScale;

public:
	void SetPos(Vector2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vector2 _vScale) { m_vScale = _vScale; }

	Vector2 GetPos() { return m_vPos; }
	Vector2 GetScale() { return m_vScale; }

public:
	CObject();
	~CObject();


};