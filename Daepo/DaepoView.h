
// DaepoView.h: CDaepoView 클래스의 인터페이스
//

#pragma once


class CDaepoView : public CView
{
protected: // serialization에서만 만들어집니다.
	CDaepoView();
	DECLARE_DYNCREATE(CDaepoView)

// 특성입니다.
public:
	CDaepoDoc* GetDocument() const;

	POINT m_LeftDaepo, m_RightDaepo;
	double t;
	int m_angleLeft, m_velLeft;
	int m_angleRight, m_velRight;
	BOOL m_sunseo;
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	

	virtual ~CDaepoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	void GetDaepoPos();
	afx_msg void OnBalsaLeft();
	afx_msg void OnBalsaRight();
	afx_msg void OnFileNew();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // DaepoView.cpp의 디버그 버전
inline CDaepoDoc* CDaepoView::GetDocument() const
   { return reinterpret_cast<CDaepoDoc*>(m_pDocument); }
#endif

