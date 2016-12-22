// CommandEdit.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "CommandEdit.h"


// CCommandEdit

IMPLEMENT_DYNAMIC(CCommandEdit, CEdit)

CCommandEdit::CCommandEdit()
{

}

CCommandEdit::~CCommandEdit()
{
}


BEGIN_MESSAGE_MAP(CCommandEdit, CEdit)
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CCommandEdit message handlers



void CCommandEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar==13)
	{
		CString str;
		GetWindowText(str);
		SetWindowText(L"");
		m_objArray->AddCommand(str,NULL);
		m_objArray->Calc();
		m_objArray->Draw();
	}

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

int CCommandEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	
	m_Font.CreatePointFont(100,L"Courier New");
	SetFont(&m_Font);


	return 0;
}
