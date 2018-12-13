// Mywnd.cpp : 구현 파일입니다.
//
#include <stdlib.h>
#include "stdafx.h"
#include "Givedata.h"
#include "Mywnd.h"
#include "ChildView.h"
#pragma comment(lib, "winmm")
#include <mmsystem.h>

// CMywnd

IMPLEMENT_DYNCREATE(CMywnd, CFrameWnd)

CMywnd::CMywnd()
{
	//UI 쓰레드를 Rect 좌표에 맞춰 생성해준다.
	CRect Rect = { 800, 100, 1800, 600 };
	Create(NULL, _T("Climate"), WS_POPUPWINDOW | WS_CAPTION, Rect);
}

CMywnd::~CMywnd()
{
}


BEGIN_MESSAGE_MAP(CMywnd, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CMywnd 메시지 처리기입니다.


void CMywnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CFrameWnd::OnPaint()을(를) 호출하지 마십시오.
	CBitmap Clim;
	BITMAP bmpinfo;
	CBitmap *OldBmp;
	COLORREF colorkey = RGB(255, 255, 255); // 흰색 투명화
	bitmap[1].GetBitmap(&bmpinfo);
	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc); // 메모리에 BMP를 저장
	
	OldBmp = dcmem.SelectObject(&bitmap[aniBmpCount]);
	bitmap[aniBmpCount].GetBitmap(&bmpinfo);
	dc.BitBlt(10, 10, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
	dcmem.SelectObject(&OldBmp);
	
	if (aniBmpCount > 8) {
		// 날씨에 따른 BMP 정보를 가져온다.
		if (target[1]._Weather == _T("구름 조금")) Clim.LoadBitmap(IDB_BITMAP8);
		else if (target[1]._Weather == _T("눈")) Clim.LoadBitmap(IDB_BITMAP9);
		else if (target[1]._Weather == _T("맑음")) Clim.LoadBitmap(IDB_BITMAP11);
		else if (target[1]._Weather == _T("비")) Clim.LoadBitmap(IDB_BITMAP12);
		else if (target[1]._Weather == _T("흐림")) Clim.LoadBitmap(IDB_BITMAP13);
		else if (target[1]._Weather == _T("구름 많음")) Clim.LoadBitmap(IDB_BITMAP14);
		else Clim.LoadBitmap(IDB_BITMAP10); // 눈비
		OldBmp = dcmem.SelectObject(&Clim);
		Clim.GetBitmap(&bmpinfo);
		// 투명화 bmp 출력, 흰색부분은 투명화되어, 도라에몽의 표지판 안에 날씨가 들어감.
		dc.TransparentBlt(150, 35, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, colorkey);
		dcmem.SelectObject(&OldBmp);
	}
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CRect rect;
	rect.SetRect(550, 100, 800, 800);
	CFont cFont;
	cFont.CreateFont(25,                     // 글자높이
		10,                     // 글자너비
		0,                      // 출력각도
		0,                      // 기준 선에서의각도
		FW_HEAVY,              // 글자굵기
		FALSE,                  // Italic 적용여부
		FALSE,                  // 밑줄적용여부
		FALSE,                  // 취소선적용여부
		DEFAULT_CHARSET,       // 문자셋종류
		OUT_DEFAULT_PRECIS,    // 출력정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑정밀도
		DEFAULT_QUALITY,       // 출력문자품질
		DEFAULT_PITCH,         // 글꼴Pitch
		_T("나눔고딕")           // 글꼴
	);
	// DC에CFont Object 설정

	dc.SelectObject(cFont);
	dc.SetBkMode(TRANSPARENT);            //글자 배경 투명하게
	dc.SetTextColor(RGB(0, 0, 0));         //글자색 검정

	int i, drawY = 100;
	CString str[7];
	str[0] = _T("이름:       ") + target[1]._Name;
	str[1] = _T("습도:       ") + target[1]._Humidity;
	str[2] = _T("강수확률: ") + target[1]._Rain;
	str[3] = _T("평균기온: ") + target[1]._TempAve;
	str[4] = _T("시간:       ") + target[1]._Time;
	str[5] = _T("풍향:       ") + target[1]._Wd;
	str[6] = _T("풍속:       ") + target[1]._Ws;
	dc.SetTextColor(RGB(0, 0, 0));
	for (i = 0; i <= 6; i++) {
		rect.SetRect(530, drawY, 950, 800);
		dc.DrawText(str[i], &rect, NULL);
		drawY = drawY + 20;
	}

	dcmem.DeleteDC();
}


void CMywnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	AfxEndThread(0); // UI 쓰레드 제거
	CFrameWnd::OnLButtonDown(nFlags, point);
}

int CMywnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1) 
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	int i = 0;
	aniBmpCount = 0;
	// 도라에몽 애니메이션 BMP 데이터 저장
	bitmap[i++].LoadBitmap(IDB_BITMAP2);
	bitmap[i++].LoadBitmap(IDB_BITMAP3);
	bitmap[i++].LoadBitmap(IDB_BITMAP4);
	bitmap[i++].LoadBitmap(IDB_BITMAP5);
	bitmap[i++].LoadBitmap(IDB_BITMAP6);
	bitmap[i++].LoadBitmap(IDB_BITMAP7);
	bitmap[i++].LoadBitmap(IDB_BITMAP15);
	bitmap[i++].LoadBitmap(IDB_BITMAP16);
	bitmap[i++].LoadBitmap(IDB_BITMAP17);
	bitmap[i++].LoadBitmap(IDB_BITMAP18);
	bitmap[i++].LoadBitmap(IDB_BITMAP19);
	bitmap[i++].LoadBitmap(IDB_BITMAP20);
	bitmap[i++].LoadBitmap(IDB_BITMAP21);
	bitmap[i++].LoadBitmap(IDB_BITMAP22);
	bitmap[i++].LoadBitmap(IDB_BITMAP23);

	PlaySound(L"Doraemon.wav", NULL, SND_ASYNC); // WAV 파일 출력

	SetTimer(0, 100, NULL); // 타이머 시작
	return 0;
}


void CMywnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	aniBmpCount++; // 애니메이션 효과를 카운트해주어서 내줌
	Invalidate(FALSE); // 무효화
	if (aniBmpCount == 14) KillTimer(0); // 애니메이션이 끝날 때 타이머 제거
	CFrameWnd::OnTimer(nIDEvent);
}

BOOL CMywnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(rect);
	//그라데이션 효과를 만들어줌
	int nWidth = rect.Width() - 7;
	int nHeight = rect.Height();
	int nRMax = 254;
	int nGMax = 254;
	int nBMax = 254;
	int nRMin = 50;
	int nGMin = 205;
	int nBMin = 50;
	int nRDiff = nRMax - nRMin;
	int nGDiff = nGMax - nGMin;
	int nBDiff = nBMax - nBMin;

	CRect rcTemp;
	for (int i = 0; i < nHeight; ++i)
	{

		rcTemp.SetRect(0, i, nWidth, i + 1);
		pDC->FillSolidRect(&rcTemp, RGB(
			nRMax - MulDiv(i, nRDiff, nHeight),
			nGMax - MulDiv(i, nGDiff, nHeight),
			nBMax - MulDiv(i, nBDiff, nHeight)));
	}
	return TRUE;
}
