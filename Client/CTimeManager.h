#pragma once

class CTimeManager
{
	SINGLE(CTimeManager);
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double m_deltaTime; // 프레임 사이의 시간값
	double m_dAcc; // deltaTime 누적(1초 체크를 위하여)
	UINT m_iCallCount; // 초당 호출 횟수
	UINT m_iFPS; // FPS

	// FPS
	// 1 프레임 당 시간 (Delta Time)
public:
	void init();
	void update();

public:
	double GetDeltaTime() { return m_deltaTime; }
	float GetfDeltaTime() { return (float)m_deltaTime; }
};

