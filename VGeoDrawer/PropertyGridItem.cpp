#include "stdafx.h"
#include "PropertyGrid.h"
#include "CustomItem.h"
#include "gdi+.h"
#include "appfunc.h"

CPropertyGrid::CItem::CItem()
{
	m_pValue_old=NULL;
}

CPropertyGrid::CItem::~CItem()
{
	if (!m_bPointerValue && m_pAllValue.GetSize()!=0) delete m_pAllValue[0];
	if (m_pValue_old!=NULL) delete m_pValue_old;
}

BOOL CPropertyGrid::CItem::CompareFont(LOGFONT* f1, LOGFONT* f2)
{
	//return TRUE;
	return memcmp(f1,f2,sizeof(LOGFONT))==0;
}

void CPropertyGrid::CItem::RefreshValue()
{
	// undefined ?
	int i;
	for (i=0;i<m_pAllValue.GetSize();i++)
	{
		if (m_type==IT_INTEGER || m_type==IT_COMBO) if (*(int*)m_pAllValue[i]!=*(int*)m_pAllValue[0]) break;
		if (m_type==IT_DOUBLE) if (*(double*)m_pAllValue[i]!=*(double*)m_pAllValue[0]) break;
		if (m_type==IT_STRING) if (*(CString*)m_pAllValue[i]!=*(CString*)m_pAllValue[0]) break;
		if (m_type==IT_BOOLEAN) if (*(bool*)m_pAllValue[i]!=*(bool*)m_pAllValue[0]) break;
		if (m_type==IT_COLOR) if ((*(Color*)m_pAllValue[i]).GetValue()!=(*(Color*)m_pAllValue[0]).GetValue()) break;
		if (m_type==IT_FONT) if (!CompareFont((LOGFONT*)m_pAllValue[i],(LOGFONT*)m_pAllValue[0])) break;
	}

	m_undefined=!(i==m_pAllValue.GetSize());

	//save the values
	m_undefined_old = m_undefined;
	if (m_pValue_old!=NULL) delete m_pValue_old;
	if (m_type==IT_INTEGER || m_type==IT_COMBO) { int* vl=new int; m_pValue_old=vl; *vl=*(int*)m_pAllValue[0]; }
	if (m_type==IT_DOUBLE) { double* vl=new double; m_pValue_old=vl; *vl=*(double*)m_pAllValue[0]; }
	if (m_type==IT_STRING || m_type==IT_TEXT) { CString* vl=new CString(); m_pValue_old=vl; *vl=*(CString*)m_pAllValue[0]; }
	if (m_type==IT_BOOLEAN) { bool* vl=new bool; m_pValue_old=vl; *vl=*(bool*)m_pAllValue[0]; }
	if (m_type==IT_COLOR) { Color* vl=new Color(); m_pValue_old=vl; *vl=*(Color*)m_pAllValue[0]; }
	if (m_type==IT_FONT) { LOGFONT* vl=new LOGFONT; m_pValue_old=vl; memcpy(vl, (LOGFONT*)m_pAllValue[0], sizeof(LOGFONT)); }
	//if (m_type==IT_FONT) { m_pValue_old=((Font*)m_pAllValue[0])->Clone(); }

	// callback for custom
	if (m_type == IT_CUSTOM)
		((ICustomItem*)m_pAllValue[0])->ValidateChanges();
}

bool CPropertyGrid::CItem::operator==(const HITEM& item) const
{
	return m_id == item;
}

bool CPropertyGrid::CItem::operator==(const CString& name) const
{
	return m_name == name;
}

void CPropertyGrid::CItem::ValidateChanges()
{
	/*
		// save the values
			m_undefined_old = m_undefined;
			if (m_pValue_old!=NULL) delete m_pValue_old;
			if (m_type==IT_INTEGER || m_type==IT_COMBO) { int* vl=new int; m_pValue_old=vl; *vl=*(int*)m_pValue; }
			if (m_type==IT_DOUBLE) { double* vl=new double; m_pValue_old=vl; *vl=*(double*)m_pValue; }
			if (m_type==IT_STRING || m_type==IT_TEXT) { CString* vl=new CString(); m_pValue_old=vl; *vl=*(CString*)m_pValue; }
			if (m_type==IT_boolEAN) { bool* vl=new bool; m_pValue_old=vl; *vl=*(bool*)m_pValue; }
			if (m_type==IT_COLOR) { COLORREF* vl=new COLORREF; m_pValue_old=vl; *vl=*(COLORREF*)m_pValue; }
			if (m_type==IT_FONT) { LOGFONT* vl=new LOGFONT; m_pValue_old=vl; memcpy(vl, (LOGFONT*)m_pValue, sizeof(LOGFONT)); }
		
			// callback for custom
			if (m_type == IT_CUSTOM)
				((ICustomItem*)m_pValue)->ValidateChanges();*/
		
}

void CPropertyGrid::CItem::SetValue(void* pValue)
{
	if (m_bPointerValue)
	{
		for (int i=0;i<m_pAllValue.GetSize();i++)
		{
			switch (m_type)
			{
			case IT_STRING:
			case IT_TEXT:
				*(CString*)m_pAllValue[i]=*(CString*)pValue; break;
			case IT_COMBO:
			case IT_INTEGER:
				*(int*)m_pAllValue[i]=*(int*)pValue; break;
			case IT_DOUBLE: 
				*(double*)m_pAllValue[i]=*(double*)pValue; break;
			case IT_BOOLEAN:
				*(bool*)m_pAllValue[i]=!*(bool*)pValue; break; // 0 - True
			case IT_COLOR:
				(*(Color*)m_pAllValue[i]).SetFromCOLORREF(*(COLORREF*)pValue); break;
			case IT_FONT:
				//delete ((Font*)m_pAllValue[i]);
				//m_pAllValue[i]=new Font(AfxGetMainWnd()->GetDC()->m_hDC,(LOGFONTA*)pValue);
				//break;
				memcpy(m_pAllValue[i], pValue, sizeof(LOGFONT)); break;
			}
		}
	}
	else
	{
		if (m_pAllValue.GetSize()==0)
		{
			if (m_type == IT_CUSTOM) { m_pAllValue.Add(pValue);	}
			else if (m_type == IT_STRING || m_type == IT_TEXT) { CString* vl=new CString(); m_pAllValue.Add(vl); *vl=*(CString*)pValue; }
			else if (m_type == IT_COMBO || m_type == IT_INTEGER) { int* vl=new int; m_pAllValue.Add(vl); *vl=*(int*)pValue; }
			else if (m_type == IT_DOUBLE) { double* vl=new double; m_pAllValue.Add(vl); *vl=*(double*)pValue; }
			else if (m_type == IT_BOOLEAN) { bool* vl=new bool; m_pAllValue.Add(vl); *vl=*(bool*)pValue; }
			else if (m_type == IT_COLOR) { Color* vl=new Color; m_pAllValue.Add(vl); (*(Color*)vl).SetFromCOLORREF(*(COLORREF*)pValue); }
			else if (m_type == IT_FONT) { LOGFONT* vl=new LOGFONT; m_pAllValue.Add(vl); memcpy(vl, pValue, sizeof(LOGFONT)); }
		}
		else
		{
			if (m_type == IT_STRING || m_type == IT_TEXT) { *(CString*)m_pAllValue[0]=*(CString*)pValue; }
			else if (m_type == IT_COMBO || m_type == IT_INTEGER) { *(int*)m_pAllValue[0]=*(int*)pValue; }
// 			else if (m_type == IT_DOUBLE) { double* vl=new double; m_pAllValue.Add(vl); *vl=*(double*)pValue; }
// 			else if (m_type == IT_BOOLEAN) { bool* vl=new bool; m_pAllValue.Add(vl); *vl=*(bool*)pValue; }
// 			else if (m_type == IT_COLOR) { Color* vl=new Color; m_pAllValue.Add(vl); (*(Color*)vl).SetFromCOLORREF(*(COLORREF*)pValue); }
// 			else if (m_type == IT_FONT) { LOGFONT* vl=new LOGFONT; m_pAllValue.Add(vl); memcpy(vl, pValue, sizeof(LOGFONT)); }
		}
	}
}