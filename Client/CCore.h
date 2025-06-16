#pragma once

// 싱글톤 패턴
// 객체의 생성을 1개로 제한
// 언제 어디서든 쉽게 접근 가능. 
// extern 키워드로는 지역 변수로도 만들 수도 있는 등 객체 생성 방지가 안 됨. 즉 extern으로는 불가.
// static 키워드가 붙은 멤버 함수는 객체를 통해서 호출할 수도 있고, 객체가 없어도 호출이 가능함. 즉 static으로(내 생각이 맞았다!)
// 정적 멤버 함수는 this 키워드가 없기 때문에 멤버에 접근 불가. 대신 정적 멤버(static 키워드가 붙은 멤버)는 접근 가능

// 정적 ( 데이터 영역 ) => 선언한 내부에서만 접근 가능. 따라서 데이터 영역에 딱 하나만 존재.
// (함수 내에서 선언 시 함수 내에서만, 파일(cpp) 내에서 선언시 해당 파일 내에서만, 클래스 내에서 선언 시 해당 클래스 내에서만)
// public 키워드를 주는 경우, 클래스 안에서 접근해서 외부에서도 변경 가능.
// 선언한 이후 클래스 밖에서 반드시 초기화해줘야 함. 안 하면 링크 에러 뜸.

class CCore
{
	SINGLE(CCore);
private:
	HWND m_hWnd;			// 메인 윈도우 핸들.
	POINT m_ptResolution;	// 메인 윈도우 해상도
	HDC m_hDC;				// 메인 윈도우에 draw할 Device Context

	HBITMAP m_hBit; 
	HDC m_memDC;

public:
	int init(HWND _hWnd, POINT _ptResolution);

	void progress();

private:
	void update();

	
public:
	HWND GetMainHwnd() { return m_hWnd; }
};


//class CCore
//{
//private:
//	// CCore* m_pInst;
//public:
//	// 정적 멤버 함수
//	static CCore* GetInstance()
//	{
//		// 최초 호출된 경우
//		if (nullptr == m_pInst)
//		{
//			m_pInst = new CCore;
//		}
//
//		// 두 번 이상 호출된 경우엔 인스턴스 생성 안 시킴.
//		return m_pInst;
//	}
//
//	static void Release()
//	{
//		if (nullptr != m_pInst)
//		{
//			delete m_pInst;
//			m_pInst = nullptr;
//		}
//	}
//
//private:
//	CCore();
//	~CCore();
//};

