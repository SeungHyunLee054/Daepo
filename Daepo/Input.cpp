// Input.cpp: 구현 파일
//

#include "pch.h"
#include "Daepo.h"
#include "Input.h"
#include "afxdialogex.h"


// CInput 대화 상자

IMPLEMENT_DYNAMIC(CInput, CDialog)

CInput::CInput(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_velocity(0)
	, m_angle(0)
{

}

CInput::~CInput()
{
}

void CInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_VELOCITY, m_velocity);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_angle);
}


BEGIN_MESSAGE_MAP(CInput, CDialog)
END_MESSAGE_MAP()


// CInput 메시지 처리기
