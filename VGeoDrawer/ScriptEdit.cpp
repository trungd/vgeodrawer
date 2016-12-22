// ScriptEdit.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "ScriptEdit.h"


// CScriptEdit

IMPLEMENT_DYNAMIC(CScriptEdit, CEdit)

CScriptEdit::CScriptEdit()
{

}

CScriptEdit::~CScriptEdit()
{
}


BEGIN_MESSAGE_MAP(CScriptEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CScriptEdit message handlers


void CScriptEdit::InitCtrl()
{
	m_Font.CreatePointFont(100,L"Courier New");
	SetFont(&m_Font);
}

void CScriptEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CEdit::OnChar(nChar, nRepCnt, nFlags);
	if (nChar==VK_RETURN)
	{
		int s,e;
		GetSel(s,e);
		if (s!=e) return;

		CString str;

		int pos=LineFromChar(-1)-1;
		int len = LineLength(pos);
		GetLine(pos, str.GetBuffer(len), len);
		str.ReleaseBuffer(len);

		
		if (pos>0)
		{
			CString strReplace;
			while (str.GetLength()>strReplace.GetLength() && 
				str[strReplace.GetLength()]==' ') { strReplace+=L" "; }
						
			if (strReplace.GetLength()!=0)
				ReplaceSel(strReplace);

// 			if (str.GetLength()>strReplace.GetLength() && 
// 				str[strReplace.GetLength()]=='{')
// 				ReplaceSel(L"  ");
			return;
		}
	}
}
