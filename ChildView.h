
// ChildView.h : CChildView 클래스의 인터페이스
//


#pragma once


// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
// 작업입니다.
public:
	CWinThread* WThread;
// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
typedef struct inform {
	CString _Time;        //pubData   시간
	CString _Name;        //category   도시이름
	CString _TempAve;     //temp      평균기온
	CString _Weather;     //wfKor      날씨
	CString _Rain;        //pop      강수확률
	CString _Ws;          //ws      풍속
	CString _Wd;          //wdKor      풍향
	CString _Humidity;    //reh      습도
}inform;
extern inform target[2]; // 전역 구조체 변수
