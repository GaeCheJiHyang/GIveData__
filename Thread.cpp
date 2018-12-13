// Thread.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Givedata.h"
#include "Thread.h"
#include "Mywnd.h"


// CThread

IMPLEMENT_DYNCREATE(CThread, CWinThread)

CThread::CThread()
{
}

CThread::~CThread()
{
}

BOOL CThread::InitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 초기화를 수행합니다.
	//프레임 윈도우 객체를 동적으로 생성 

	CRuntimeClass* pRuntimeClass = RUNTIME_CLASS(CMywnd);

	CObject* pObject = pRuntimeClass->CreateObject();

	// 객체를 성공적으로 생성했는지 여부 확인 

	ASSERT(pObject->IsKindOf(RUNTIME_CLASS(CMywnd)));

	// 프레임 윈도우 객체의 주소를 저장한 후, 윈도우가 화면에 보이도록 한다. 

	m_pMainWnd = (CWnd *)pObject;

	m_pMainWnd->ShowWindow(SW_SHOW);

	m_pMainWnd->UpdateWindow();

	return TRUE;
}

int CThread::ExitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 정리를 수행합니다.
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThread, CWinThread)
END_MESSAGE_MAP()


// CThread 메시지 처리기입니다.
