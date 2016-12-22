#include "StdAfx.h"
#include "PropertyTextItem.h"
#include "TextEditorDlg.h"

CPropertyTextItem::CPropertyTextItem(void)
{
}

CPropertyTextItem::~CPropertyTextItem(void)
{
}

CPropertyGrid::EEditMode CPropertyTextItem::GetEditMode()
{
	return CPropertyGrid::EM_MODAL;
}

void CPropertyTextItem::DrawItem( CDC& dc, CRect rc, bool focused )
{
	CString str=m_obj->m_Text;
	str.Replace(L"\r\n",L"¶");
	dc.DrawText(L" "+str, rc, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS|DT_NOPREFIX);
}

bool CPropertyTextItem::OnEditItem()
{
	CTextEditorDlg dlg;
	dlg.m_Text=m_obj->m_Text;
	if (dlg.DoModal()==IDOK);
	{
		m_obj->m_Text=dlg.m_Text;
	}
	return TRUE;
}