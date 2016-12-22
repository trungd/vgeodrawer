#include "StdAfx.h"
#include "PropertyButtonCmd.h"
#include "ButtonCmdEditor.h"

CPropertyButtonCmdItem::CPropertyButtonCmdItem(void)
{
}

CPropertyButtonCmdItem::~CPropertyButtonCmdItem(void)
{
}

CPropertyGrid::EEditMode CPropertyButtonCmdItem::GetEditMode()
{
	return CPropertyGrid::EM_MODAL;
}

void CPropertyButtonCmdItem::DrawItem( CDC& dc, CRect rc, bool focused )
{
	CString str=m_obj->m_Command;
	str.Replace(L"\r\n",L"¶");
	dc.DrawText(L" "+str, rc, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS|DT_NOPREFIX);
}

bool CPropertyButtonCmdItem::OnEditItem()
{
	CButtonCmdEditor dlg;
	dlg.m_Text=m_obj->m_Command;
	dlg.m_cmdArray=m_cmdArray;
	if (dlg.DoModal()==IDOK)
	{
		m_obj->m_Command=dlg.m_Text;
	}
	return TRUE;
}