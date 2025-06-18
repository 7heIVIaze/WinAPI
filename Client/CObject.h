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
	virtual void update() = 0;
	virtual void render(HDC _dc);

public:
	CObject();
	virtual ~CObject(); // 부모 클래스이기 때문에 가상 함수로 설정해야 함.


};