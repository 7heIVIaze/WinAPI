#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeManager.h"
#include "CKeyManager.h"

CObject g_obj;


CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정.
	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); // 리턴 값이 너무 커질 경우, 이런 식으로 인자로 주소로 받아서 주도록 설정.

	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	m_hDC = GetDC(m_hWnd);

	// 이중 버퍼링 용도의 비트맵과 DC 생성.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y); 
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	// Manager 초기화
	CTimeManager::GetInst()->init();
	CKeyManager::GetInst()->init();

	g_obj.SetPos(Vector2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2)));
	g_obj.SetScale(Vector2(100, 100));

	return S_OK;
}

void CCore::progress()
{
	// Manager Update
	CTimeManager::GetInst()->update();

	CKeyManager::GetInst()->update();

	update();

	render();
}

void CCore::update()
{
	Vector2 vPos = g_obj.GetPos();
	if (CKeyManager::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::TAP)
	{
		vPos.x -= 200.0f;// *fDeltaTime;
	}

	if (CKeyManager::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::TAP)
	{
		vPos.x += 200.0f;// *fDeltaTime;
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	// 화면 Clear

	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);


	// 그리기
	Vector2 vPos = g_obj.GetPos();
	Vector2 vScale = g_obj.GetScale();

	Rectangle(m_memDC, int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.y / 2.f));

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY); // 프레임 방어가 잘 되고 있는 거임.
}
