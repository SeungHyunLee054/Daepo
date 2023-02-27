
// DaepoView.cpp: CDaepoView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Daepo.h"
#endif

#include "DaepoDoc.h"
#include "DaepoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Input.h"
#include "math.h"

// CDaepoView

IMPLEMENT_DYNCREATE(CDaepoView, CView)

BEGIN_MESSAGE_MAP(CDaepoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_BALSA_LEFT, &CDaepoView::OnBalsaLeft)
	ON_COMMAND(ID_BALSA_RIGHT, &CDaepoView::OnBalsaRight)
	ON_COMMAND(ID_FILE_NEW, &CDaepoView::OnFileNew)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CDaepoView 생성/소멸

CDaepoView::CDaepoView() 
{
	// TODO: 여기에 생성 코드를 추가합니다.
	GetDaepoPos();
	m_sunseo = false;
	m_angleLeft = 0;
	m_velLeft = 0;
	m_angleRight = 0;
	m_velRight = 0;
}

CDaepoView::~CDaepoView()
{
}

BOOL CDaepoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CDaepoView 그리기

void CDaepoView::OnDraw(CDC* pDC)
{
	CDaepoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CBitmap daepo1, daepo2, background, * pold;
	CDC memDC;

	memDC.CreateCompatibleDC(pDC);
	daepo1.LoadBitmap(IDB_BITMAP1);
	daepo2.LoadBitmap(IDB_BITMAP2);
	background.LoadBitmap(IDB_BITMAP3);
	pold = memDC.SelectObject(&background);
	pDC->StretchBlt(0, 0, 960, 640, &memDC, 0, 0, 640, 320, SRCCOPY);
	memDC.SelectObject(pold);
	pold = memDC.SelectObject(&daepo1);
	pDC->TransparentBlt(m_LeftDaepo.x, m_LeftDaepo.y, 50, 40, &memDC, 0, 0, 100, 79, RGB(255, 255, 255));
	memDC.SelectObject(pold);
	pold = memDC.SelectObject(&daepo2);
	pDC->TransparentBlt(m_RightDaepo.x, m_RightDaepo.y, 50, 40, &memDC, 0, 0, 100, 79, RGB(255, 255, 255);
	memDC.SelectObject(pold);
}


// CDaepoView 인쇄

BOOL CDaepoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CDaepoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CDaepoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CDaepoView 진단

#ifdef _DEBUG
void CDaepoView::AssertValid() const
{
	CView::AssertValid();
}

void CDaepoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDaepoDoc* CDaepoView::GetDocument() const// 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDaepoDoc)));
	return (CDaepoDoc*)m_pDocument;
}
#endif //_DEBUG


// CDaepoView 메시지 처리기


void CDaepoView::GetDaepoPos()
{
	// TODO: 여기에 구현 코드 추가.
	m_LeftDaepo.x = rand() % 200;
	m_LeftDaepo.y = 200 + rand() % 300;
	m_RightDaepo.x = 600 + rand() % 200;
	m_RightDaepo.y = 200 + rand() % 300;
}


void CDaepoView::OnBalsaLeft()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CInput dlg;
	dlg.m_angle = m_angleLeft;
	dlg.m_velocity = m_velLeft;
	if (dlg.DoModal() == IDOK) {
		m_sunseo = true;
		t = 0;
		m_angleLeft = dlg.m_angle;
		m_velLeft = dlg.m_velocity;
		SetTimer(1, 20, NULL);
	}
}


void CDaepoView::OnBalsaRight()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CInput dlg;
	dlg.m_angle = m_angleRight;
	dlg.m_velocity = m_velRight;
	if (dlg.DoModal() == IDOK) {
		m_sunseo = false;
		t = 0;
		m_angleRight = dlg.m_angle;
		m_velRight = dlg.m_velocity;
		SetTimer(2, 20, NULL);
	}
}



	void CDaepoView::OnTimer(UINT_PTR nIDEvent)
	{
		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		CClientDC dc(this);
		static int predraw, prev_x, prev_y;

		UpdateData(TRUE);
		double a, v;
		static int x, y;

		if (nIDEvent == 1) {
			x = m_LeftDaepo.x + 50;
			y = m_LeftDaepo.y;

			a = m_angleLeft;
			v = m_velLeft;

			x += (int)(v * cos(3.14 * a / 180.0) * t);
			y -= (int)(v * sin(3.14 * a / 180.0) * t - 0.5 * 9.8 * t * t);

			if (x >= m_RightDaepo.x - 10 && x <= m_RightDaepo.x + 10 && y >= m_RightDaepo.y - 10 && y <= m_RightDaepo.y + 10) {
				KillTimer(1);
				AfxMessageBox(_T("명중입니다!!!"), MB_OK);
				OnFileNew();
				predraw = 0;
				return;
			}

			if (x > 800 || y > 500) {
				KillTimer(1);
				AfxMessageBox(_T("실패했습니다"), MB_OK);
				Invalidate(false);
				predraw = 0;
				return;
			}
		}
		else {
			x = m_RightDaepo.x;
			y = m_RightDaepo.y;

			a = m_angleRight;
			v = m_velRight;

			x += (int)(v * cos(3.14 * a / 180.0) * t);
			y -= (int)(v * sin(3.14 * a / 180.0) * t - 0.5 * 9.8 * t * t);

			if (x >= m_LeftDaepo.x - 10 && x <= m_LeftDaepo.x + 10 && y >= m_LeftDaepo.y - 10 && y <= m_LeftDaepo.y + 10) {
				KillTimer(2);
				AfxMessageBox(_T("명중입니다!!!"), MB_OK);
				OnFileNew();
				predraw = 0;
				return;
			}

			if (x < 0 || y>500) {
				KillTimer(2);
				AfxMessageBox(_T("실패했습니다"), MB_OK);
				Invalidate(false);
				predraw = 0;
				return;
			}
		}

		CBrush brush, * pOldbrush;

		brush.CreateSolidBrush(RGB(255, 255, 255));
		pOldbrush = dc.SelectObject(&brush);

		dc.SetROP2(R2_XORPEN);
		if (predraw)
			dc.Ellipse(prev_x - 10, prev_y - 10, prev_x + 10, prev_y + 10);
		dc.Ellipse(x - 10, y - 10, x + 10, y + 10);
		dc.SelectObject(pOldbrush);
		brush.DeleteObject();
		predraw = 1;
		prev_x = x;
		prev_y = y;

		t += 0.1;

		CView::OnTimer(nIDEvent);
	}



	void CDaepoView::OnFileNew()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		GetDaepoPos();
		Invalidate(false);
	}
