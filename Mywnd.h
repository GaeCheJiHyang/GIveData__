#pragma once


// CMywnd 프레임입니다.

class CMywnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMywnd)
protected:
	CMywnd();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMywnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CBitmap bitmap[14]; // 도라에몽 애니메이션 BMP
	UINT aniBmpCount; // 애니메이션 카운트
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};