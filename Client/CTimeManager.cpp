#include "pch.h"
#include "CTimeManager.h"

#include "CCore.h"

CTimeManager::CTimeManager()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_deltaTime(0.0)
	, m_dAcc(0.0)
	, m_iCallCount(0)
	, m_iFPS(0)
{

}

CTimeManager::~CTimeManager()
{

}

void CTimeManager::init()
{
	// 현재 카운트
	QueryPerformanceCounter(&m_llPrevCount); // 초당 세는 단위가 천만 단위.
	
	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency); // 여기에 시간 개념이 들어가있음.
	
}

void CTimeManager::update()
{
	QueryPerformanceCounter(&m_llCurCount); // 초당 세는 단위가 천만 단위.

	// 이전 프레임의 카운트 값과 현재 프레임의 카운트 값의 차이를 구한다.
	m_deltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	// 이전 카운트 값을 현개 값으로 갱신(다음 번을 위하여)
	m_llPrevCount = m_llCurCount;

	// FPS는 1 / deltaTime으로 구하는 것은 불안정함(deltaTime이 한 프레임마다 튀거나 느릴 수도 있기 때문) => 따라서 직접 세는 것이 더 안정적.

	++m_iCallCount;
	m_dAcc += m_deltaTime; // deltaTime 누적

	// 1초에 한 번
	if (m_dAcc >= 1.0)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.0;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS: %d, DeltaTime: %lf", m_iFPS, m_deltaTime);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
