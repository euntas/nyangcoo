
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "nyangcoo.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	SceneManager::GetInstance().LoadScene(CString("Scene_Start"));

	return TRUE;
}

void CChildView::OnPaint() 
{
	++theApp.CallCount;

	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	Graphics MainG(dc);

	CRect rc;
	GetClientRect(rc);
	Rect rc2(rc.left, rc.top, rc.Width(), rc.Height());

	Bitmap BackBuffer(rc.Width(), rc.Height(), PixelFormat32bppARGB);
	Graphics MemG(&BackBuffer);

	SolidBrush br(Color(255, 0, 0, 0));
	SolidBrush WhiteBrush(Color(255, 255, 255, 255));

	MemG.FillRectangle(&WhiteBrush, rc2);

	SceneManager::GetInstance().ViewRC = rc2;
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SceneManager::GetInstance().RenderScene(&MemG);
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.

	// 실제 화면에 그려준다
	MainG.DrawImage(&BackBuffer, 0, 0, rc.Width(), rc.Height());
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CWinThread* pThread = AfxBeginThread(&CnyangcooApp::funcThread, NULL);

	return 0;
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return true;
	//return CWnd::OnEraseBkgnd(pDC);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SceneManager::GetInstance().SendLButtonDown(nFlags, point);

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (SceneManager::GetInstance().GetCurScene()->getName() == "Scene_Start")
	{
		SceneManager::GetInstance().SendMouseMove(nFlags, point);
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SceneManager::GetInstance().SendKeyDown(nChar, nRepCnt, nFlags);

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
