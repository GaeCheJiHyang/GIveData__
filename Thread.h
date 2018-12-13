#pragma once



// CThread

class CThread : public CWinThread
{
	DECLARE_DYNCREATE(CThread)

protected:
	CThread();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


