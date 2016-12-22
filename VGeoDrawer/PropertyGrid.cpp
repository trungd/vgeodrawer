// PropertyGrid.cpp : implementation file
//

#include "stdafx.h"
#include "CustomItem.h"
#include "PropertyGrid.h"
#include "DynDialogEx.h"
#include <algorithm>
#include <shlwapi.h>
#include "gdi+.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_MONTHCAL 1023

// CPropertyGrid

static const int margin = 2;

IMPLEMENT_DYNAMIC(CPropertyGrid, CWnd)
CPropertyGrid::CPropertyGrid()
{
	m_section_id = 0;
	m_item_id = 0;
	m_resizing_gutter = FALSE;
	m_button_pushed = FALSE;
	m_button_depressed = FALSE;
	m_value_clicked = FALSE;
	m_custom_tracking = FALSE;
	m_scroll_enabled = FALSE;
	m_draw_lines = TRUE;
	m_shade_titles = TRUE;
	m_draw_gutter = TRUE;
	m_focus_disabled = TRUE;
	m_bold_modified = FALSE;
	m_bold_editables = FALSE;
	m_display_mode = DM_CATEGORIZED;
	m_control = NULL;

	m_rect_button = CRect(0,0,0,0);
	m_ptLast = CPoint(0,0);

	m_strTrue = "TRUE";
	m_strFalse = "FALSE";
	m_strDate = "Date";
	m_strTime = "Time";
	m_strUndefined = "";
	m_strEmpty = "";

	m_clrBack = GetSysColor(COLOR_WINDOW);
	m_clrShade = GetSysColor(COLOR_3DFACE);
	m_clrText = GetSysColor(COLOR_WINDOWTEXT);
	m_clrTitle = GetSysColor(COLOR_WINDOWTEXT);
	m_clrFocus = GetSysColor(COLOR_HIGHLIGHT);
	m_clrHilite = GetSysColor(COLOR_HIGHLIGHTTEXT);
	m_clrEditable = GetSysColor(COLOR_WINDOWTEXT);
	m_clrDisabled = GetSysColor(COLOR_GRAYTEXT);

	m_focused_section = -1;
	m_focused_item = -1;
}

CPropertyGrid::~CPropertyGrid()
{
}

BEGIN_MESSAGE_MAP(CPropertyGrid, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	ON_WM_VSCROLL()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_PG_COMBOSELCHANGED, OnComboSelChanged)
	ON_MESSAGE(WM_PG_ENDLABELEDIT, OnEditChanged)
	ON_WM_MOUSEWHEEL()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_GETDLGCODE()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

//
// customization
//

bool CPropertyGrid::GetShadeTitles()
{
	return m_shade_titles;
}

void CPropertyGrid::SetShadeTitles(bool shade_titles)
{
	m_shade_titles = shade_titles;
	if (GetSafeHwnd())
		Invalidate();
}

bool CPropertyGrid::GetDrawLines()
{
	return m_draw_lines;
}

void CPropertyGrid::SetDrawLines(bool draw_lines)
{
	m_draw_lines = draw_lines;
	if (GetSafeHwnd())
		Invalidate();
}

bool CPropertyGrid::GetDrawGutter()
{
	return m_draw_gutter;
}

void CPropertyGrid::SetDrawGutter(bool draw_gutter)
{
	m_draw_gutter = draw_gutter;
	if (GetSafeHwnd())
		Invalidate();
}

bool CPropertyGrid::GetFocusDisabled()
{
	return m_focus_disabled;
}

void CPropertyGrid::SetFocusDisabled(bool focus_disabled)
{
	m_focus_disabled = focus_disabled;
	if (GetSafeHwnd())
		Invalidate();
}

bool CPropertyGrid::GetBoldModified()
{
	return m_bold_modified;
}

void CPropertyGrid::SetBoldModified(bool bold_modified)
{
	m_bold_modified = bold_modified;
}

bool CPropertyGrid::GetBoldEditables()
{
	return m_bold_editables;
}

void CPropertyGrid::SetBoldEditables(bool bold_editables)
{
	m_bold_editables = bold_editables;
}

//
// gutter width
//

int CPropertyGrid::GetGutterWidth()
{
	return m_gutter_width;
}

void CPropertyGrid::SetGutterWidth(int gutter_width)
{
	m_gutter_width = gutter_width;
	if (GetSafeHwnd())
		Invalidate();
}

//
// custom colors
//

void CPropertyGrid::SetTextColor(COLORREF clrText)
{
	if (m_clrText == m_clrEditable)
		m_clrEditable = clrText;
	m_clrText = clrText;
	if (GetSafeHwnd())
		Invalidate();
}

void CPropertyGrid::SetTitleColor(COLORREF clrTitle)
{
	m_clrTitle = clrTitle;
	if (GetSafeHwnd())
		Invalidate();
}

void CPropertyGrid::SetBackColor(COLORREF clrBack)
{
	m_clrBack = clrBack;
	if (GetSafeHwnd())
		Invalidate();
}

void CPropertyGrid::SetShadeColor(COLORREF clrShade)
{
	m_clrShade = clrShade;
	if (GetSafeHwnd())
		Invalidate();
}

void CPropertyGrid::SetFocusColor(COLORREF clrFocus)
{
	m_clrFocus = clrFocus;
	if (GetSafeHwnd())
		Invalidate();
}

void CPropertyGrid::SetHiliteColor(COLORREF clrHilite)
{
	m_clrHilite = clrHilite;
	if (GetSafeHwnd())
		Invalidate();
}

void CPropertyGrid::SetEditableColor(COLORREF clrEditable)
{
	m_clrEditable = clrEditable;
	if (GetSafeHwnd())
		Invalidate();
}

void CPropertyGrid::SetDisabledColor(COLORREF clrDisabled)
{
	m_clrDisabled = clrDisabled;
	if (GetSafeHwnd())
		Invalidate();
}

//
// localization
//

void CPropertyGrid::SetTrueFalseStrings(CString strTRUE, CString strFALSE)
{
	m_strTrue = strTRUE;
	m_strFalse = strFALSE;
}

void CPropertyGrid::SetOkCancelStrings(CString strOk, CString strCancel)
{
	m_strOk = strOk;
	m_strCancel = strCancel;
}

void CPropertyGrid::SetDateTimeStrings(CString strDate, CString strTime)
{
	m_strDate = strDate;
	m_strTime = strTime;
}

void CPropertyGrid::SetUndefinedString(CString strUndefined)
{
	m_strUndefined = strUndefined;
}

void CPropertyGrid::SetEmptyString(CString strEmpty)
{
	m_strEmpty = strEmpty;
}

//
// appearance
//

void CPropertyGrid::SetDisplayMode(EDisplayMode display_mode)
{
	m_display_mode = display_mode;
	RecalcLayout();
}

void CPropertyGrid::ExpandAll(bool expand)
{
	for (int i=0;i<m_sections.GetSize();i++)
		m_sections[i]->m_collapsed = !expand;
	RecalcLayout();
}

void CPropertyGrid::ExpandSection(HSECTION hs, bool expand)
{
	CSection* pSection = FindSection(hs);
	if (pSection)
	{
		pSection->m_collapsed = !expand;
		RecalcLayout();
	}
}

bool CPropertyGrid::IsSectionCollapsed(HSECTION hs)
{
	CSection* pSection = FindSection(hs);
	if (pSection)
		return pSection->m_collapsed;
	return FALSE;
}

//
// item management
//

bool CPropertyGrid::CSection::operator==(const HSECTION& section) const
{
	return m_id == section;
}

HSECTION CPropertyGrid::AddSection(CString title, bool collapsed, HSECTION after)
{
	// build it
	CSection* section=new CSection();
	section->m_id = m_section_id;
	section->m_title = title;
	section->m_collapsed = collapsed;

	// insert it
	// if after does not exist then it is appended
	int index=FindSectionIndex(after);
	if (index==-1) m_sections.Add(section);
	else m_sections.InsertAt(index, section);

	// done
	RecalcLayout();
	return m_section_id++;
}

HITEM CPropertyGrid::AddItem(HSECTION hs, EItemType type, CString name, void* pValue, bool editable, bool undefined, HITEM after, bool bPointerValue, bool bPts)
{
	// check section exists
	CSection* it=FindSection(hs);
	if (it == NULL)
		return -1;

	// check item does not already exists
// 	CItem* it2 = it->FindItem(hi)
// 	if (it2 != it->m_items.end())
// 		return -1;

	// build the item
	CItem* item=new CItem();
	item->m_id = m_item_id++;
	item->m_type = type;
	item->m_name = name;
	item->m_editable = editable;
	item->m_undefined = undefined;
	it->m_items.Add(item);

	// assign the value
	if (bPointerValue)
	{
		if (bPts)
		{
			CArray<void*>* vt=(CArray<void*>*)pValue;
			for (int i=0;i<vt->GetSize();i++)
				item->m_pAllValue.Add((*vt)[i]);
			item->m_bPointerValue=true;
		}
		else
		{
			item->m_pAllValue.Add(pValue);
			item->m_bPointerValue=true;
		}
	}
	else
	{
		item->m_bPointerValue=false;
		item->SetValue(pValue);
	}

	// finish and add
	//item.ValidateChanges();
	item->RefreshValue();
	//it->m_items.Add(item);
	RecalcLayout();
	return item->m_id;
}

HITEM CPropertyGrid::AddCustomItem(HSECTION section, CString name, ICustomItem* pItem, bool editable, HITEM after)
{
	pItem->m_pGrid = this;
	return AddItem(section, IT_CUSTOM, name, pItem, editable, FALSE, after, TRUE);
}

HITEM CPropertyGrid::AddStringItem(HSECTION section, CString name, CString value, bool editable, HITEM after)
{
	return AddItem(section, IT_STRING, name, &value, editable, FALSE, after, FALSE);
}

HITEM CPropertyGrid::AddStringItemPs(HSECTION section, CString name, CArray<void*>& value, bool editable, HITEM after)
{
	return AddItem(section, IT_STRING, name, &value, editable, FALSE, after, TRUE, TRUE);
}

HITEM CPropertyGrid::AddStringItemP(HSECTION section, CString name, CString* value, bool editable, HITEM after)
{
	return AddItem(section, IT_STRING, name, value, editable, FALSE, after, TRUE);
}

HITEM CPropertyGrid::AddTextItem(HSECTION section, CString name, CString value, bool editable, HITEM after)
{
	return AddItem(section, IT_TEXT, name, &value, editable, FALSE, after, FALSE);
}

HITEM CPropertyGrid::AddTextItemP(HSECTION section, CString name, CString* value, bool editable, HITEM after)
{
	return AddItem(section, IT_TEXT, name, value, editable, FALSE, after, TRUE);
}

HITEM CPropertyGrid::AddIntegerItem(HSECTION section, CString name, int value, CString format, bool editable, bool undefined, HITEM after)
{
	HITEM it = AddItem(section, IT_INTEGER, name, &value, editable, undefined, after,FALSE);
	if (format!=L"")
	{
		CItem* pItem = FindItem(it);
		if (pItem) pItem->m_options.Add(format);
	}
	return it;
}

HITEM CPropertyGrid::AddIntegerItemP(HSECTION section, CString name, int* value, CString format, bool editable, bool undefined, HITEM after)
{
	HITEM it = AddItem(section, IT_INTEGER, name, value, editable, undefined, after,TRUE);
	if (format!=L"")
	{
		CItem* pItem = FindItem(it);
		if (pItem) pItem->m_options.Add(format);
	}
	return it;
}

HITEM CPropertyGrid::AddIntegerItemPs(HSECTION section, CString name, CArray<void*>& value, CString format, bool editable, bool undefined, HITEM after)
{
	HITEM it = AddItem(section, IT_INTEGER, name, &value, editable, undefined, after,TRUE, TRUE);
	if (format!=L"")
	{
		CItem* pItem = FindItem(it);
		if (pItem) pItem->m_options.Add(format);
	}
	return it;
}

HITEM CPropertyGrid::AddDoubleItem(HSECTION section, CString name, double value, CString format, bool editable, bool undefined, HITEM after)
{
	HITEM it = AddItem(section, IT_DOUBLE, name, &value, editable, undefined, after, FALSE);
	if (format!=L"")
	{
		CItem* pItem = FindItem(it);
		if (pItem) pItem->m_options.Add(format);
	}
	return it;
}

HITEM CPropertyGrid::AddDoubleItemP(HSECTION section, CString name, double* value, CString format, bool editable, bool undefined, HITEM after)
{
	HITEM it = AddItem(section, IT_DOUBLE, name, value, editable, undefined, after, TRUE);
	if (format!=L"")
	{
		CItem* pItem = FindItem(it);
		if (pItem) pItem->m_options.Add(format);
	}
	return it;
}

HITEM CPropertyGrid::AddDoubleItemPs(HSECTION section, CString name, CArray<void*>& value, CString format, bool editable, bool undefined, HITEM after)
{
	HITEM it = AddItem(section, IT_DOUBLE, name, &value, editable, undefined, after, TRUE, TRUE);
	if (format!=L"")
	{
		CItem* pItem = FindItem(it);
		if (pItem) pItem->m_options.Add(format);
	}
	return it;
}

HITEM CPropertyGrid::AddComboItem(HSECTION section, CString name, const CStringArray& values, int cur, bool editable, bool undefined, HITEM after)
{
	HITEM it = AddItem(section, IT_COMBO, name, &cur, editable, undefined, after, FALSE);
	CItem* pItem = FindItem(it);
	if (pItem) pItem->m_options.Append(values);
	return it;
}

HITEM CPropertyGrid::AddComboItemP(HSECTION section, CString name, const CStringArray& values, int* cur, bool editable, bool undefined, HITEM after)
{
	HITEM it = AddItem(section, IT_COMBO, name, cur, editable, undefined, after, TRUE);
	CItem* pItem = FindItem(it);
	if (pItem) pItem->m_options.Append(values);
	return it;
}

HITEM CPropertyGrid::AddComboItemPs(HSECTION section, CString name, const CStringArray& values, CArray<void*>& cur, bool editable, bool undefined, HITEM after)
{
	HITEM it = AddItem(section, IT_COMBO, name, &cur, editable, undefined, after, TRUE, TRUE);
	CItem* pItem = FindItem(it);
	if (pItem) pItem->m_options.Append(values);
	return it;
}

HITEM CPropertyGrid::AddBoolItem(HSECTION section, CString name, bool value, bool editable, bool undefined, HITEM after)
{
	return AddItem(section, IT_BOOLEAN, name, &value, editable, undefined, after, FALSE);
}

HITEM CPropertyGrid::AddBoolItemP(HSECTION section, CString name, bool* value, bool editable, bool undefined, HITEM after)
{
	return AddItem(section, IT_BOOLEAN, name, value, editable, undefined, after, TRUE);
}

HITEM CPropertyGrid::AddBoolItemPs(HSECTION section, CString name, CArray<void*>& value, bool editable, bool undefined, HITEM after)
{
	return AddItem(section, IT_BOOLEAN, name, &value, editable, undefined, after, TRUE, TRUE);
}

HITEM CPropertyGrid::AddColorItem(HSECTION section, CString name, COLORREF value, bool editable, bool undefined, HITEM after)
{
	return AddItem(section, IT_COLOR, name, &value, editable, undefined, after, FALSE);
}

HITEM CPropertyGrid::AddColorItemP(HSECTION section, CString name, Color* value, bool editable, bool undefined, HITEM after)
{
	return AddItem(section, IT_COLOR, name, value, editable, undefined, after, TRUE);
}

HITEM CPropertyGrid::AddColorItemPs(HSECTION section, CString name, CArray<void*>& value, bool editable, bool undefined, HITEM after)
{
	return AddItem(section, IT_COLOR, name, &value, editable, FALSE, after, TRUE, TRUE);
}

HITEM CPropertyGrid::AddFontItem(HSECTION section, CString name, LOGFONT value, bool editable, bool undefined, HITEM after)
{
	return AddItem(section, IT_FONT, name, &value, editable, undefined, after, FALSE);
}

HITEM CPropertyGrid::AddFontItemP(HSECTION section, CString name, LOGFONT* value, bool editable, bool undefined, HITEM after)
{
	return AddItem(section, IT_FONT, name, value, editable, undefined, after, TRUE);
}

HITEM CPropertyGrid::AddFontItemPs(HSECTION section, CString name, CArray<void*>& value, bool editable, bool undefined, HITEM after)
{
	return AddItem(section, IT_FONT, name, &value, editable, undefined, after, TRUE, TRUE);
}

void CPropertyGrid::ResetContents()
{
	for (int i=0;i<m_sections.GetSize();i++) delete m_sections[i];
	m_sections.RemoveAll();
	m_section_id = 0;
	m_item_id = 0;
	RecalcLayout();
}

void CPropertyGrid::RemoveAllItems()
{
	for (int i=0;i<m_sections.GetSize();i++)
	{
		for (int j=0;j<m_sections[i]->m_items.GetSize();j++)
			delete m_sections[i]->m_items[j];
		m_sections[i]->m_items.RemoveAll();
	}
}

bool CPropertyGrid::RemoveSection(HSECTION hs)
{
	int it = FindSectionIndex(hs);
	if (it == -1) return false;
	delete m_sections[it];
	m_sections.RemoveAt(it);
	return true;
}

bool CPropertyGrid::RemoveItem(HITEM item)
{
	for (int i=0;i<m_sections.GetSize();i++)
	{
		int index=m_sections[i]->FindItemIndex(item);
		if (index!=-1)
		{
			delete m_sections[i]->m_items[index];
			m_sections[i]->m_items.RemoveAt(index);
			return true;
		}
	}
	return false;
}

int CPropertyGrid::GetNumSections()
{
	return int(m_sections.GetSize());
}

int CPropertyGrid::GetSectionSize(HSECTION hs)
{
	CSection* pSection = FindSection(hs);
	if (pSection) return pSection->m_items.GetSize();
	return 0;
}

// void CPropertyGrid::ValidateChanges()
// {
// 	for (CArray<CSection>::iterator it = m_sections.begin(); it != m_sections.end(); ++it)
// 	{
// 		for (CArray<CItem>::iterator it2 = it->m_items.begin(); it2 != it->m_items.end(); ++it2)
// 			it2->ValidateChanges();
// 	}
// }

CPropertyGrid::CSection* CPropertyGrid::FindSection(HSECTION hs) const
{
	for (int i=0;i<m_sections.GetSize();i++)
	{
		if (m_sections[i]->m_id==hs) return m_sections[i];
	}
	return NULL;
}

int CPropertyGrid::FindSectionIndex(HSECTION hs)
{
	for (int i=0;i<m_sections.GetSize();i++)
	{
		if (m_sections[i]->m_id==hs) return i;
	}
	return -1;
}

CPropertyGrid::CItem* CPropertyGrid::FindItem(HITEM hi) const
{
	for (int i=0;i<m_sections.GetSize();i++)
	{
		for (int j=0;j<m_sections[i]->m_items.GetSize();j++)
		{
			if (m_sections[i]->m_items[j]->m_id==hi) return m_sections[i]->m_items[j];
		}
	}
	return NULL;
}

CPropertyGrid::CSection* CPropertyGrid::FindSectionByItem(HITEM hi)
{
	for (int i=0;i<m_sections.GetSize();i++)
	{
		if (m_sections[i]->FindItem(hi)) return m_sections[i];
	}
	return NULL;
}

bool CPropertyGrid::GetItemValue(HITEM item, CString& strValue) const
{
	// get the item
	CItem* pItem = FindItem(item);
	if (pItem == NULL) return FALSE;
	if (pItem->m_undefined) return FALSE;

	// check
	if (pItem->m_type == IT_STRING || pItem->m_type == IT_TEXT)
	{
		strValue = *(CString*)pItem->m_pAllValue[0];
		return TRUE;
	}
	else if (pItem->m_type == IT_COMBO)
	{
		if (*(int*)pItem->m_pAllValue[0] < 0 || *(int*)pItem->m_pAllValue[0] > int(pItem->m_options.GetSize())-1) return FALSE;
		strValue = pItem->m_options[*(int*)pItem->m_pAllValue[0]];
		return TRUE;
	}
	return FALSE;
}

bool CPropertyGrid::GetItemValue(HITEM item, int& nValue) const
{
	// get the item
	CItem* pItem = FindItem(item);
	if (pItem == NULL) return FALSE;
	if (pItem->m_undefined) return FALSE;

	// check
	if (pItem->m_type == IT_COMBO || pItem->m_type == IT_INTEGER)
	{
		nValue = *(int*)pItem->m_pAllValue[0];
		return TRUE;
	}
	if (pItem->m_type == IT_BOOLEAN)
	{
		nValue = *(bool*)pItem->m_pAllValue[0];
		return TRUE;
	}

	return FALSE;
}

bool CPropertyGrid::GetItemValue(HITEM item, double& dValue) const
{
	// get the item
	CItem* pItem = FindItem(item);
	if (pItem == NULL) return FALSE;
	if (pItem->m_undefined) return FALSE;

	// check
	if (pItem->m_type == IT_DOUBLE)
	{
		dValue = *(double*)pItem->m_pAllValue[0];
		return TRUE;
	}
	return FALSE;
}

// bool CPropertyGrid::GetItemValue(HITEM item, bool& bValue) const
// {
//   // get the item
//   CItem* pItem = FindItem(item);
//   if (pItem == NULL) return FALSE;
//   if (pItem->m_undefined) return FALSE;
// 
//   // check
//   if (pItem->m_type == IT_boolEAN)
//   {
//     bValue = *(bool*)pItem->m_pValue;
//     return TRUE;
//   }
//   return FALSE;
// }

bool CPropertyGrid::GetItemValue(HITEM item, COLORREF& clrValue) const
{
	// get the item
	CItem* pItem = FindItem(item);
	if (pItem == NULL) return FALSE;
	if (pItem->m_undefined) return FALSE;

	// check
	if (pItem->m_type == IT_COLOR)
	{
		clrValue = *(COLORREF*)pItem->m_pAllValue[0];
		return TRUE;
	}
	return FALSE;
}

bool CPropertyGrid::GetItemValue(HITEM item, LOGFONT& lfValue) const
{
	// get the item
	CItem* pItem = FindItem(item);
	if (pItem == NULL) return FALSE;
	if (pItem->m_undefined) return FALSE;

	// check
	if (pItem->m_type == IT_FONT)
	{
		lfValue = *(LOGFONT*)pItem->m_pAllValue[0];
		return TRUE;
	}
	return FALSE;
}

// bool CPropertyGrid::SetItemValue(HITEM item, const CString strValue)
// {
// 	// get the item
// 	CItem* pItem = FindItem(item);
// 	if (pItem == NULL) return FALSE;
// 
// 	// check
// 	if (pItem->m_type == IT_STRING || pItem->m_type == IT_TEXT)
// 	{
// 		*(CString*)pItem->m_pValue = strValue;
// 		pItem->m_undefined = FALSE;
// 		Invalidate();
// 		return TRUE;
// 	}
// 	return FALSE;
// }
// 
// bool CPropertyGrid::SetItemValue(HITEM item, const CString strValue)
// {
// 	// get the item
// 	CItem* pItem = FindItem(item);
// 	if (pItem == NULL) return FALSE;
// 
// 	// check
// 	if (pItem->m_type == IT_STRING || pItem->m_type == IT_TEXT)
// 	{
// 		*(CString*)pItem->m_pValue = strValue;
// 		pItem->m_undefined = FALSE;
// 		Invalidate();
// 		return TRUE;
// 	}
// 	return FALSE;
// }
// 
// bool CPropertyGrid::SetItemValue(HITEM item, const int nValue)
// {
// 	// get the item
// 	CItem* pItem = FindItem(item);
// 	if (pItem == NULL) return FALSE;
// 
// 	// check
// 	if (pItem->m_type == IT_COMBO || pItem->m_type == IT_INTEGER)
// 	{
// 		*(int*)pItem->m_pValue = nValue;
// 		pItem->m_undefined = FALSE;
// 		Invalidate();
// 		return TRUE;
// 	}
// 	if (pItem->m_type == IT_boolEAN)
// 	{
// 		*(bool*)pItem->m_pValue = nValue;
// 		pItem->m_undefined = FALSE;
// 		Invalidate();
// 		return TRUE;
// 	}
// 
// 	return FALSE;
// }
// 
// bool CPropertyGrid::SetItemValue(HITEM item, const double dValue)
// {
// 	// get the item
// 	CItem* pItem = FindItem(item);
// 	if (pItem == NULL) return FALSE;
// 
// 	// check
// 	if (pItem->m_type == IT_DOUBLE)
// 	{
// 		*(double*)pItem->m_pValue = dValue;
// 		pItem->m_undefined = FALSE;
// 		Invalidate();
// 		return TRUE;
// 	}
// 	return FALSE;
// }
// 
// // bool CPropertyGrid::SetItemValue(HITEM item, const bool bValue)
// // {
// //   // get the item
// //   CItem* pItem = FindItem(item);
// //   if (pItem == NULL) return FALSE;
// // 
// //   // check
// //   if (pItem->m_type == IT_boolEAN)
// //   {
// //     *(bool*)pItem->m_pValue = bValue;
// //     pItem->m_undefined = FALSE;
// //     Invalidate();
// //     return TRUE;
// //   }
// //   return FALSE;
// // }
// 
// 
// bool CPropertyGrid::SetItemValue(HITEM item, const COLORREF clrValue)
// {
// 	// get the item
// 	CItem* pItem = FindItem(item);
// 	if (pItem == NULL) return FALSE;
// 
// 	// check
// 	if (pItem->m_type == IT_COLOR)
// 	{
// 		*(COLORREF*)pItem->m_pValue = clrValue;
// 		pItem->m_undefined = FALSE;
// 		Invalidate();
// 		return TRUE;
// 	}
// 	return FALSE;
// }
// 
// bool CPropertyGrid::SetItemValue(HITEM item, const LOGFONT lfValue)
// {
// 	// get the item
// 	CItem* pItem = FindItem(item);
// 	if (pItem == NULL) return FALSE;
// 
// 	// check
// 	if (pItem->m_type == IT_FONT)
// 	{
// 		memcpy(&*(LOGFONT*)pItem->m_pValue, &lfValue, sizeof(LOGFONT));
// 		pItem->m_undefined = FALSE;
// 		Invalidate();
// 		return TRUE;
// 	}
// 	return FALSE;
// }

int CPropertyGrid::GetTextMargin()
{
	return 2*margin;
}

CFont* CPropertyGrid::GetFontNormal()
{
	return &m_fntNormal;
}

CFont* CPropertyGrid::GetFontBold()
{
	return &m_fntBold;
}

//
// creation and window stuff
//

void CPropertyGrid::InitControl()
{
	// first gutter
	CRect rc;
	GetClientRect(&rc);
	m_gutter_width = rc.Width()/2;

	// check if already done
	if (m_fntNormal.GetSafeHandle() == NULL)
	{
		// fonts
		LOGFONT lf;
		if (GetParent() && GetParent()->GetFont())
		{
			CFont* pFont = GetParent()->GetFont();
			pFont->GetLogFont(&lf);
			m_fntNormal.CreateFontIndirect(&lf);
			lf.lfWeight = FW_BOLD;
			m_fntBold.CreateFontIndirect(&lf);
		}
		else
		{
			m_fntNormal.CreatePointFont(85, L"Tahoma");
			m_fntNormal.GetLogFont(&lf);
			lf.lfWeight = FW_BOLD;
			m_fntBold.CreateFontIndirect(&lf);
		}
	}

	// get line height
	CDC* pDC = GetDC();
	CFont* pOldFont = pDC->SelectObject(&m_fntNormal);
	m_line_height = pDC->GetTextExtent(L"Gg").cy + 2*margin;
	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);

	// styles
	ModifyStyle(0, WS_CLIPCHILDREN);

	// try to get some strings
	if (m_strOk.IsEmpty())
	{
		m_strOk = "OK";
		if (GetParent() && GetParent()->GetDlgItem(IDOK))
		{
			CString strOk;
			GetParent()->GetDlgItem(IDOK)->GetWindowText(strOk);
			m_strOk = strOk;
		}
	}
	if (m_strCancel.IsEmpty())
	{
		m_strCancel = "Cancel";
		if (GetParent() && GetParent()->GetDlgItem(IDCANCEL))
		{
			CString strCancel;
			GetParent()->GetDlgItem(IDCANCEL)->GetWindowText(strCancel);
			m_strCancel = strCancel;
		}
	}
}

int CPropertyGrid::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;
	InitControl();
	return 0;
}

void CPropertyGrid::PreSubclassWindow()
{
	InitControl();
	CWnd::PreSubclassWindow();
}

void CPropertyGrid::OnDestroy()
{
	DeleteEditControl();
	CWnd::OnDestroy();
}

void CPropertyGrid::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (m_scrollbar.GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(&rect);
		m_scrollbar.MoveWindow(rect.right - GetSystemMetrics(SM_CXVSCROLL), rect.top, GetSystemMetrics(SM_CXVSCROLL), rect.Height());
		RecalcLayout();
	}
}

//
// painting
//

BOOL CPropertyGrid::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

// bool item_alpha_sort(CArray<CPropertyGrid::CItem>::iterator it1, CArray<CPropertyGrid::CItem>::iterator it2)
// {
// 	return (it1->m_name.Compare(it2->m_name) < 0);
// }

void CPropertyGrid::OnPaint()
{
	// stuff needed
	const int sign_size = 8;

	// the scrollbar offset
	int top = GetScrollOffset();

	// the rect
	CRect rc_dummy;
	GetClientRect(&rc_dummy);
	if (m_scroll_enabled)
		rc_dummy.right -= GetSystemMetrics(SM_CXVSCROLL);

	// make sure we do not modify this one
	// because we use it to bitblt
	const CRect rc(rc_dummy);

	// stuff for flicker free drawing
	CDC dcMem;
	CBitmap bmpMem;
	CPaintDC dc(this);

	// create and configure the memdc
	dcMem.CreateCompatibleDC(&dc);
	bmpMem.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	CBitmap* pOldBmp = dcMem.SelectObject(&bmpMem);

	// brush needed
	CBrush brushTitle;
	brushTitle.CreateSolidBrush(m_clrTitle);

	// pen needed
	CPen penShade(PS_SOLID, 1, m_clrShade);
	CPen penTitle(PS_SOLID, 1, m_clrTitle);

	// to make sure we won't leak gdi resources
	CBrush* pOldBrush = dcMem.SelectObject(&brushTitle);
	CPen* pOldPen = dcMem.SelectObject(&penShade);
	CFont* pOldFont = dcMem.SelectObject(&m_fntNormal);

	// needed
	int w = rc.Width();

	// blank
	dcMem.FillSolidRect(rc, m_clrBack);
	dcMem.SetBkMode(TRANSPARENT);

	// empty text
	if (m_sections.IsEmpty())
	{
		CRect rect = rc;
		rect.top += 10;
		rect.DeflateRect(rect.Width()/4, 0);
		dcMem.DrawText(m_strEmpty, rect, DT_CENTER|DT_WORDBREAK|DT_NOPREFIX);
	}
	else
	{
		// needed
		int sign_left = margin;

		// we start here
		int y = -top;

		// alphabetical needs special
		if (m_display_mode == DM_ALPHABETICAL)
		{
			/*
			// put all the items in a CArray
						CArray<CArray<CItem>::iterator> lst;
						for (CArray<CSection>::iterator it = m_sections.begin(); it != m_sections.end(); ++it)
						{
							for (CArray<CItem>::iterator it2 = it->m_items.begin(); it2 != it->m_items.end(); ++it2)
								lst.Add(it2);
						}
			
						// sort the CArray
						sort(lst.begin(), lst.end(), item_alpha_sort);
			
						// display the items
						for (CArray<CArray<CItem>::iterator>::iterator it2 = lst.begin(); it2 != lst.end(); ++it2)
						{
							// first reset
							(*it2)->m_rcName.SetRectEmpty();
							(*it2)->m_rcValue.SetRectEmpty();
			
							// draw if visible
							(*it2)->m_rcName = CRect(0, y, w, y+m_line_height);
							CRect rcInter = (*it2)->m_rcName;
							rcInter.IntersectRect(rc, rcInter);
							if (!rcInter.IsRectEmpty())
								DrawItem(dcMem, w, sign_left+sign_size, y, *it2);
			
							// next line
							y += m_line_height;
						}*/
			
		}
		else
		{
			// next iterate on sections
			for (int i=0;i<m_sections.GetSize();i++)
			{
				CSection* it=m_sections[i];
				if (it->m_items.GetSize()==0) continue;
				// reset
				it->m_rcSign.SetRectEmpty();
				it->m_rcTitle.SetRectEmpty();

				// is visible?
				it->m_rcTitle = CRect(0, y, w, y+m_line_height);
				CRect rcInter = it->m_rcTitle;
				rcInter.IntersectRect(rcInter, rc);
				if (m_display_mode == DM_CATEGORIZED && !rcInter.IsRectEmpty())
				{
					// first shade rect
					if (m_shade_titles)
						dcMem.FillSolidRect(0, y, w, m_line_height, m_clrShade);

					// now draw a separator lines
					if (m_draw_lines)
					{
						dcMem.SelectObject(&penShade);
						dcMem.MoveTo(0, y);
						dcMem.LineTo(w+1, y);
						dcMem.MoveTo(0, y+m_line_height);
						dcMem.LineTo(w+1, y+m_line_height);
					}

					// now draw gutter
					if (m_draw_gutter)
					{
						dcMem.SelectObject(&penShade);
						dcMem.MoveTo(m_gutter_width, y);
						dcMem.LineTo(m_gutter_width, y+m_line_height+1);
					}

					// now draw collapse sign
					int sign_top = y+margin+2;
					dcMem.SelectObject(&penTitle);
					it->m_rcSign = CRect(sign_left, sign_top, sign_left+sign_size+1, sign_top+sign_size+1);
					dcMem.FrameRect(it->m_rcSign, &brushTitle);
					dcMem.MoveTo(sign_left+2, sign_top+sign_size/2);
					dcMem.LineTo(sign_left+2+sign_size/2+1, sign_top+sign_size/2);
					if (it->m_collapsed)
					{
						dcMem.MoveTo(sign_left+sign_size/2, sign_top+2);
						dcMem.LineTo(sign_left+sign_size/2, sign_top+2+sign_size/2+1);
					}

					// prepare draw text
					int title_left = sign_left+sign_size+2*margin;
					int title_top = y;
					dcMem.SelectObject(&m_fntBold);
					it->m_rcTitle = CRect(title_left, title_top, w, title_top+m_line_height);

					// draw focus rect
					if (m_focused_section == it->m_id)
					{
						CSize sz = dcMem.GetTextExtent(it->m_title);
						int rect_left = title_left;
						int rect_top = title_top+(m_line_height-sz.cy)/2;
						int rect_width = sz.cx+3*margin;
						int rect_height = sz.cy;
						dcMem.DrawFocusRect(CRect(rect_left, rect_top, rect_left+rect_width, rect_top+rect_height));
					}

					// now draw text
					dcMem.SetTextColor(m_clrTitle);
					dcMem.DrawText(it->m_title, CRect(title_left+GetTextMargin(), title_top, w, title_top+m_line_height), DT_END_ELLIPSIS|DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX); 
				}

				// next line
				if (m_display_mode == DM_CATEGORIZED)
					y+=m_line_height;

				// iterate on items
				if (!it->m_collapsed || m_display_mode != DM_CATEGORIZED)
				{
					for (int j=0;j<it->m_items.GetSize();j++)
					{
						CItem* it2=it->m_items[j];
						// reset
						it2->m_rcName.SetRectEmpty();
						it2->m_rcValue.SetRectEmpty();

						// is visible?
						it2->m_rcName = CRect(0, y, w, y+m_line_height);
						CRect rcInter = it2->m_rcName;
						rcInter.IntersectRect(rc, rcInter);
						if (!rcInter.IsRectEmpty())
							DrawItem(dcMem, w, sign_left+sign_size, y, it2);

						// next line
						y+=m_line_height;
					}
				}
			}
		}
	}

	// Blt the changes to the screen DC.
	dc.BitBlt(rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, &dcMem, 0, 0, SRCCOPY);

	// Done with off-screen bitmap and DC.
	dcMem.SelectObject(pOldBmp);
	dcMem.SelectObject(pOldFont);
	dcMem.SelectObject(pOldPen);
	dcMem.SelectObject(pOldBrush);
	bmpMem.DeleteObject();
	dcMem.DeleteDC();

	// Validate All
	ValidateRgn(NULL);
	ValidateRect(NULL);
}

void CPropertyGrid::DrawItem(CDC& dc, int w, int x, int y, CItem* it)
{
	// brush needed
	CBrush brushText;
	brushText.CreateSolidBrush(m_clrText);

	// pen needed
	CPen penShade(PS_SOLID, 1, m_clrShade);

	// to make sure we won't leak gdi resources
	CBrush* pOldBrush = dc.SelectObject(&brushText);
	CPen* pOldPen = dc.SelectObject(&penShade);
	CFont* pOldFont = dc.SelectObject(&m_fntNormal);

	// first shade rect
	if (m_shade_titles)
		dc.FillSolidRect(0, y, x+2*margin, m_line_height, m_clrShade);

	// now draw a separator line
	if (m_draw_lines)
	{
		dc.SelectObject(&penShade);
		dc.MoveTo(0, y+m_line_height);
		dc.LineTo(w+1, y+m_line_height);
	}

	// now draw gutter
	if (m_draw_gutter)
	{
		dc.SelectObject(&penShade);
		dc.MoveTo(m_gutter_width, y);
		dc.LineTo(m_gutter_width, y+m_line_height+1);
	}

	// needed
	int name_left = x+2*margin+GetTextMargin();
	int name_right = m_gutter_width-1;
	int value_left = m_gutter_width;
	int value_right = w;

	// is being edited?
	if (m_focused_item == it->m_id && it->m_editable && GetEditMode(*it) != EM_CUSTOM)
	{
		value_right -= m_line_height;

		// the rect of the button
		m_rect_button = CRect(w-m_line_height, y, w, y+m_line_height);

		UINT pushed = m_button_depressed?DFCS_PUSHED:0;

		// now draw the button
		switch (GetEditMode(*it))
		{
		case EM_MODAL:
			// draw a button
			dc.DrawFrameControl(m_rect_button, DFC_BUTTON, DFCS_BUTTONPUSH|pushed);
			dc.SelectObject(&m_fntBold);
			dc.DrawText(L"...", m_rect_button, DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);
			break;

		case EM_DROPDOWN:
			// draw an arrow
			dc.DrawFrameControl(m_rect_button, DFC_SCROLL, DFCS_SCROLLDOWN|pushed);
			break;

		case EM_INPLACE:
			// whole area is edit
			m_rect_button.left = m_gutter_width;
			break;

		default:
			ASSERT(FALSE);
		}
	}

	// update the rects
	it->m_rcName = CRect(0, y, m_gutter_width, y+m_line_height);
	it->m_rcValue = CRect(value_left, y, value_right, y+m_line_height);
	CRect rcValue = it->m_rcValue;
	rcValue.left += GetTextMargin();

	// focused
	if (m_focused_item == it->m_id)
	{
		int rect_left = name_left-2*margin;
		int rect_right = name_right;
		dc.FillSolidRect(rect_left, y, rect_right-rect_left+1, m_line_height, m_clrFocus);
		dc.SetTextColor(m_clrHilite);
	}
	else
	{
		dc.SetTextColor(m_clrText);
	}

	// put name and value
	dc.SelectObject(&m_fntNormal);
	dc.DrawText(it->m_name, -1, CRect(name_left, y, name_right, y+m_line_height), DT_END_ELLIPSIS|DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);

	// get back to normal text
	if (it->m_editable) dc.SetTextColor(m_clrEditable);
	else dc.SetTextColor(m_clrDisabled);

	// custom item
	if (it->m_type == IT_CUSTOM)
	{
		int save = dc.SaveDC();
		((ICustomItem*)it->m_pAllValue[0])->DrawItem(dc, it->m_rcValue, m_focused_item == it->m_id);
		dc.RestoreDC(save);
	}
	else
	{
		// modified flag
		bool modified;

		// now draw text
		CString strValue;
		if (it->m_undefined) strValue = m_strUndefined;
		else {
		switch (it->m_type)
		{
		case IT_STRING:
			{
				modified = (*(CString*)it->m_pAllValue[0] != *(CString*)it->m_pValue_old);

				// now draw text
				strValue = *(CString*)it->m_pAllValue[0];

				break;
			}

		case IT_TEXT:
			{
				modified = (*(CString*)it->m_pAllValue[0] != *(CString*)it->m_pValue_old);

				// now draw text
				strValue = *(CString*)it->m_pAllValue[0];

				strValue.Replace( L"\r\n", L"¶");
				break;
			}

		case IT_INTEGER:
			{
				CString strTemp;
				CString strFormat = L"%d";
				if (it->m_options.GetSize()) strFormat = it->m_options[0];
				strTemp.Format(strFormat, *(int*)it->m_pAllValue[0]);
				strValue = strTemp;
				modified = (*(int*)it->m_pAllValue[0] != *(int*)it->m_pValue_old);
				break;
			}

		case IT_DOUBLE:
			{
				CString strTemp;
				CString strFormat = L"%g";
				if (it->m_options.GetSize()) strFormat = it->m_options[0];
				strTemp.Format(strFormat, *(double*)it->m_pAllValue[0]);
				strValue = strTemp;
				modified = (*(double*)it->m_pAllValue[0] != *(double*)it->m_pValue_old);
				break;
			}

		case IT_BOOLEAN:
			{
				strValue = *(bool*)it->m_pAllValue[0] ? m_strTrue : m_strFalse;
				modified = (*(bool*)it->m_pAllValue[0] != *(bool*)it->m_pValue_old);
				break;
			}

		case IT_COMBO:
			{
				if (*(int*)it->m_pAllValue[0]>=0 && *(int*)it->m_pAllValue[0]<int(it->m_options.GetSize()))
					strValue = it->m_options[*(int*)it->m_pAllValue[0]];
				modified = (*(int*)it->m_pAllValue[0] != *(int*)it->m_pValue_old);
				break;
			}

		case IT_COLOR:
			{
				// draw a sample rectangle
				CRect rc = rcValue;
				rc.DeflateRect(0,2,0,2);
				rc.top++;
				rc.right = rc.left + m_line_height;
				dc.FrameRect(rc, &brushText);
				rc.DeflateRect(1,1);
				dc.FillSolidRect(rc, ((Color*)it->m_pAllValue[0])->ToCOLORREF());
				rcValue.left = rc.right + 3*margin;

				// update the text
				CString strTemp;
				strTemp.Format(L"%d; %d; %d", GetRValue(*(COLORREF*)it->m_pAllValue[0]), GetGValue(*(COLORREF*)it->m_pAllValue[0]), GetBValue(*(COLORREF*)it->m_pAllValue[0]));
				strValue = strTemp;
				modified = (*(COLORREF*)it->m_pAllValue[0] != *(COLORREF*)it->m_pValue_old);
				break;
			}

		case IT_FONT:
			{
				CString strTemp;
				strTemp.Format(L"%s; %dpt", (*(LOGFONT*)it->m_pAllValue[0]).lfFaceName, -MulDiv((*(LOGFONT*)it->m_pAllValue[0]).lfHeight, 72, dc.GetDeviceCaps(LOGPIXELSY)));

// 				Font* font=(Font*)it->m_pAllValue[0];
// 				FontFamily family; font->GetFamily(&family);
// 				WCHAR fontName[LF_FACESIZE];
// 				family.GetFamilyName(fontName);
// 				strTemp.Format(L"%s; %dpt", fontName, font->GetSize());

				strValue = strTemp;
				modified = (memcmp(&(*(LOGFONT*)it->m_pAllValue[0]), &(*(LOGFONT*)it->m_pValue_old), sizeof(LOGFONT))!=0);
				break;
			}
		} }

		// we must also take undefined state change into account
		modified |= (it->m_undefined != it->m_undefined_old);

		// set proper font
		if (modified && m_bold_modified) dc.SelectObject(&m_fntBold);
		else if (it->m_editable && m_bold_editables) dc.SelectObject(&m_fntBold);
		else dc.SelectObject(&m_fntNormal);

		// now draw it
		dc.DrawText(strValue, -1, rcValue, DT_END_ELLIPSIS|DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);
	}

	// clean up
	dc.SelectObject(pOldFont);
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
}

//
// mouse interaction
//

void CPropertyGrid::OnLButtonDown(UINT nFlags, CPoint point)
{
	// destroy edit
	SetFocus();
	DeleteEditControl();

	// click on button?
	if (m_rect_button.PtInRect(point))
	{
		m_button_pushed = TRUE;
		m_button_depressed = TRUE;
		SetCapture();
		Invalidate();
		return;
	}

	// click on button?
	if (m_focused_item != -1)
	{
		CItem* pItem = FindItem(m_focused_item);
		if (   pItem && pItem->m_type == IT_CUSTOM
			&& GetEditMode(*pItem) == EM_CUSTOM
			&& ((ICustomItem*)pItem->m_pAllValue[0])->OnLButtonDown(pItem->m_rcValue, point))
		{
			m_custom_tracking = TRUE;
			SetCapture();
			Invalidate();
			return;
		}
	}

	// resizing gutter?
	if (abs(point.x-m_gutter_width)<3)
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
		m_resizing_gutter = TRUE;
		m_ptLast = point;
		SetCapture();
		Invalidate();
		return;
	}

	// disable focus
	m_focused_item = -1;
	m_focused_section = -1;
	m_rect_button.SetRectEmpty();

	// did we click on a section
	if (m_display_mode == DM_CATEGORIZED)
	{
		for (int i=0;i<m_sections.GetSize();i++)
		{
			CSection* it=m_sections[i];
			if (it->m_items.GetSize()==0) continue;
			if (it->m_rcSign.PtInRect(point))
			{
				it->m_collapsed = !it->m_collapsed;
				m_focused_section = it->m_id;
				RecalcLayout();
				return;
			}
			else if (it->m_rcTitle.PtInRect(point))
			{
				m_focused_section = it->m_id;
				Invalidate();
				return;
			}
		}
	}

	// focus
	for (int i=0;i<m_sections.GetSize();i++)
	{
		CSection* it=m_sections[i];
		if (!it->m_collapsed || m_display_mode != DM_CATEGORIZED)
		{
			for (int j=0;j<it->m_items.GetSize();j++)
			{
				CItem* it2=it->m_items[j];
				if (it2->m_rcName.PtInRect(point) || it2->m_rcValue.PtInRect(point))
				{
					if (it2->m_editable || m_focus_disabled)
					{
						m_focused_item = it2->m_id;
						if (it2->m_rcValue.PtInRect(point))
							m_value_clicked = (GetEditMode(*it2) == EM_INPLACE || GetEditMode(*it2) == EM_DROPDOWN);
						Invalidate();
						return;
					}
				}
			}
		}
	}

	CWnd::OnLButtonDown(nFlags, point);
	Invalidate();
}

void CPropertyGrid::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_focused_item != -1)
	{
		CItem* pItem = FindItem(m_focused_item);
		if (pItem)
		{
			if (pItem->m_type == IT_BOOLEAN)
			{
				if (!pItem->m_undefined)
				{
					*(bool*)pItem->m_pAllValue[0] = !*(bool*)pItem->m_pAllValue[0];
					GetOwner()->SendMessage(WM_PG_ITEMCHANGED, pItem->m_id);
					Invalidate();
				}
			}
			else if (pItem->m_type == IT_COMBO)
			{
				if (!pItem->m_undefined)
				{
					*(int*)pItem->m_pAllValue[0] = (*(int*)pItem->m_pAllValue[0]+1)%int(pItem->m_options.GetSize());
					GetOwner()->SendMessage(WM_PG_ITEMCHANGED, pItem->m_id);
					Invalidate();
				}
			}
			else if (GetEditMode(*pItem) == EM_MODAL)
			{
				EditFocusedItem();
			}
		}
	}
	else if (m_focused_section != -1)
	{
		CSection* pSection = FindSection(m_focused_section);
		if (pSection)
		{
			pSection->m_collapsed = !pSection->m_collapsed;
			Invalidate();
		}
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}

void CPropertyGrid::OnMouseMove(UINT nHitTest, CPoint point)
{
	if (m_custom_tracking)
	{
		CItem* pItem = FindItem(m_focused_item);
		if (pItem)
		{
			((ICustomItem*)pItem->m_pAllValue[0])->OnMouseMove(pItem->m_rcValue, point);
			Invalidate();
		}
	}
	else if (m_button_pushed)
	{
		m_button_depressed = m_rect_button.PtInRect(point)?TRUE:FALSE;
		Invalidate();
	}
	else if (m_resizing_gutter)
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
		m_gutter_width += point.x-m_ptLast.x;
		CRect rc;
		GetClientRect(&rc);
		if (m_gutter_width<rc.Width()/5) m_gutter_width = rc.Width()/5;
		if (m_gutter_width>4*rc.Width()/5) m_gutter_width = 4*rc.Width()/5;
		m_ptLast = point;
		Invalidate();
	}
	else if (!m_control)
	{
		if (abs(point.x-m_gutter_width)<3) ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
		else ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	}

	CWnd::OnMouseMove(nHitTest, point);
}

void CPropertyGrid::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_custom_tracking)
	{
		m_custom_tracking = FALSE;
		ReleaseCapture();
		Invalidate();
		CItem* pItem = FindItem(m_focused_item);
		if (pItem)
			((ICustomItem*)pItem->m_pAllValue[0])->OnLButtonUp(pItem->m_rcValue, point);
	}
	else if (m_button_pushed || m_value_clicked)
	{
		BOOL pushed=m_button_pushed;
		m_button_pushed = FALSE;
		m_button_depressed = FALSE;
		ReleaseCapture();
		Invalidate();

		if (m_rect_button.PtInRect(point) || (m_value_clicked && m_focused_item != -1 && FindItem(m_focused_item) && FindItem(m_focused_item)->m_rcValue.PtInRect(point)))
		{
			m_value_clicked = FALSE;
			CItem* pItem = FindItem(m_focused_item);
			if (pItem)
			{
				if (GetEditMode(*pItem) == EM_DROPDOWN && pushed)
				{
					if (pItem->m_type == IT_CUSTOM)
					{
						CRect rc = m_rect_button;
						rc.left = m_gutter_width;
						((ICustomItem*)pItem->m_pAllValue[0])->ShowDropDown(rc);
					}
					else
					{
						// the combo rect
						CRect rc = m_rect_button;
						rc.left = m_gutter_width;
						rc.top += m_line_height;
						rc.bottom = rc.top + 100;

						// create it
						m_control = new CPropertyGridCombo();
						CPropertyGridCombo* pCombo = (CPropertyGridCombo*)m_control;
						pCombo->Create(WS_CHILD, rc, this, 0);
						pCombo->SetColors(m_clrBack, m_clrText, m_clrFocus, m_clrHilite);
						pCombo->SetFont(&m_fntNormal);

						if (pItem->m_type == IT_BOOLEAN)
						{
							pCombo->AddString(m_strTrue);
							pCombo->AddString(m_strFalse);
							if (!pItem->m_undefined)
								pCombo->SetCurSel(*(bool*)pItem->m_pAllValue[0]?0:1);
						}
						else
						{
							for (int i=0;i<pItem->m_options.GetSize();i++)
								pCombo->AddString(pItem->m_options[i]);
							if (!pItem->m_undefined)
								pCombo->SetCurSel(*(int*)pItem->m_pAllValue[0]);
						}
						pCombo->ShowWindow(SW_SHOW);
					}
				}
				else if (GetEditMode(*pItem) == EM_INPLACE)
				{
					// the in-place edit rect
					CRect rc = m_rect_button;
					rc.left++;
					rc.top += margin;

					// the value
					CString strValue;
					if (pItem->m_type == IT_STRING)
					{
						strValue = *(CString*)pItem->m_pAllValue[0];
					}
					else if (pItem->m_type == IT_INTEGER)
					{
						if (!pItem->m_undefined)
						{
							CString strTemp;
							strTemp.Format(L"%d", *(int*)pItem->m_pAllValue[0]);
							strValue = strTemp;
						}
					}
					else if (pItem->m_type == IT_DOUBLE)
					{
						if (!pItem->m_undefined)
						{
							CString strTemp;
							strTemp.Format(L"%g", *(double*)pItem->m_pAllValue[0]);
							strValue = strTemp;
						}
					}
					else if (pItem->m_type == IT_CUSTOM)
					{
						strValue = ((ICustomItem*)pItem->m_pAllValue[0])->GetStringForInPlaceEdit();
					}
					else
					{
						ASSERT(FALSE);
					}

					// create it
					m_control = new CPropertyGridInPlaceEdit(this, rc, WS_CHILD, 1000, strValue);
					CPropertyGridInPlaceEdit* pEdit = (CPropertyGridInPlaceEdit*)m_control;
					pEdit->SetColors(m_clrBack, m_clrText);
					pEdit->SetFont(&m_fntNormal);
					pEdit->ShowWindow(SW_SHOW);
				}
				else if (GetEditMode(*pItem) == EM_MODAL)
				{
					EditFocusedItem();
				}
				else if (GetEditMode(*pItem) == EM_CUSTOM)
				{
					((ICustomItem*)pItem->m_pAllValue[0])->OnLButtonUp(pItem->m_rcValue, point);
				}
// 				else
// 				{
// 					ASSERT(FALSE);
// 				}
			}
		}
	}
	else if (m_resizing_gutter)
	{
		ReleaseCapture();
		m_resizing_gutter = FALSE;
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	}

	CWnd::OnLButtonUp(nFlags, point);
}

//
// keyboard interaction
//

UINT CPropertyGrid::OnGetDlgCode()
{
	return CWnd::OnGetDlgCode()|DLGC_WANTCHARS|DLGC_WANTARROWS;
}

void CPropertyGrid::MoveForward(HSECTION& focused_section, HITEM& focused_item)
{
	for (int pass = 0; pass<2; pass++)
	{
		bool found = FALSE;

		bool stop_on_next_valid = FALSE;
		if (focused_section == -1 && focused_item == -1)
			stop_on_next_valid = TRUE;

		for (int i=0;i<m_sections.GetSize();i++)
		{
			CSection* it=m_sections[i];
			if (m_display_mode == DM_CATEGORIZED)
			{
				if (it->m_id == focused_section)
				{
					stop_on_next_valid = TRUE;
				}
				else if (stop_on_next_valid)
				{
					focused_section = it->m_id;
					focused_item = -1;
					found = TRUE;
					break;
				}
			}

			if (!it->m_collapsed || m_display_mode != DM_CATEGORIZED)
			{
				for (int j=0;j<it->m_items.GetSize();j++)
				{
					CItem* it2=it->m_items[j];
					if (it2->m_id == focused_item)
					{
						stop_on_next_valid = TRUE;
					}
					else if (stop_on_next_valid)
					{
						if (it2->m_editable || m_focus_disabled)
						{
							focused_section = -1;
							focused_item = it2->m_id;
							found = TRUE;
							break;
						}
					}
				}

				if (found)
					break;
			}
		}

		if (found)
			break;

		focused_section = -1;
		focused_item = -1;
	}
}

void CPropertyGrid::FocusNextItem()
{
	// simple move forward
	MoveForward(m_focused_section, m_focused_item);

	// ensure visible
	CRect rc(0,0,0,0);
	if (m_focused_section != -1 && FindSection(m_focused_section)) rc = FindSection(m_focused_section)->m_rcTitle;
	else if (m_focused_item != -1 && FindItem(m_focused_item)) rc = FindItem(m_focused_item)->m_rcName;
	if (!rc.IsRectEmpty())
	{
		CRect rect;
		GetClientRect(&rect);
		rect.IntersectRect(rc, rect);
		if (rect.Height() != m_line_height)
			OnVScroll(SB_THUMBPOSITION, rc.top, &m_scrollbar);
	}

	// done
	Invalidate();
}

void CPropertyGrid::FocusPrevItem()
{
	for (int i=0;i<m_sections.GetSize();i++)
	{
		CSection* it=m_sections[i];
		if (m_display_mode == DM_CATEGORIZED)
		{
			HSECTION focused_section = it->m_id;
			HITEM focused_item = -1;
			MoveForward(focused_section, focused_item);
			if (focused_section == m_focused_section && focused_item == m_focused_item)
			{
				m_focused_section = it->m_id;
				m_focused_item = -1;
				break;
			}
		}

		if (!it->m_collapsed || m_display_mode != DM_CATEGORIZED)
		{
			bool found = FALSE;
			for (int j=0;j<it->m_items.GetSize();j++)
			{
				CItem* it2=it->m_items[j];
				if (!it2->m_editable && !m_focus_disabled)
					continue;

				HSECTION focused_section = -1;
				HITEM focused_item = it2->m_id;
				MoveForward(focused_section, focused_item);
				if (focused_section == m_focused_section && focused_item == m_focused_item)
				{
					m_focused_section = -1;
					m_focused_item = it2->m_id;
					found = TRUE;
					break;
				}
			}

			if (found)
				break;
		}
	}

	// ensure visible
	CRect rc(0,0,0,0);
	if (m_focused_section != -1 && FindSection(m_focused_section)) rc = FindSection(m_focused_section)->m_rcTitle;
	else if (m_focused_item != -1 && FindItem(m_focused_item)) rc = FindItem(m_focused_item)->m_rcName;
	if (!rc.IsRectEmpty())
	{
		CRect rect;
		GetClientRect(&rect);
		rect.IntersectRect(rc, rect);
		if (rect.Height() != m_line_height)
			OnVScroll(SB_THUMBPOSITION, rc.top, &m_scrollbar);
	}

	// done
	Invalidate();
}

void CPropertyGrid::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == '*')
	{
		ExpandAll(TRUE);
	}
	else if (nChar == '/')
	{
		ExpandAll(FALSE);
	}
	else if (nChar == '+' || nChar == '-')
	{
		if (m_focused_section != -1)
		{
			CSection* pSection = FindSection(m_focused_section);
			if (pSection) pSection->m_collapsed = (nChar=='-');
			RecalcLayout();
		}
	}

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

void CPropertyGrid::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DOWN)
	{
		FocusNextItem();
	}
	else if (nChar == VK_UP)
	{
		FocusPrevItem();
	}
	else if (nChar == VK_LEFT)
	{
		if (m_focused_section != -1 && FindSection(m_focused_section) && FindSection(m_focused_section)->m_collapsed == FALSE)
		{
			ExpandSection(m_focused_section, FALSE);
		}
		else
		{
			FocusPrevItem();
		}
	}
	else if (nChar == VK_RIGHT)
	{
		if (m_focused_section != -1 && FindSection(m_focused_section) && FindSection(m_focused_section)->m_collapsed == TRUE)
		{
			ExpandSection(m_focused_section, TRUE);
		}
		else
		{
			FocusNextItem();
		}
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

//
// scrolling
//

void CPropertyGrid::RecalcLayout()
{
	// save current scroll offset
	int offset = GetScrollOffset();

	// total height
	int height = 0;
	for (int i=0;i<m_sections.GetSize();i++)
	{
		CSection* it=m_sections[i];
		if (it->m_items.GetSize()==0) continue;
		if (m_display_mode == DM_CATEGORIZED)
			height += m_line_height;
		if (!it->m_collapsed || m_display_mode != DM_CATEGORIZED)
			height += int(it->m_items.GetSize())*m_line_height;
	}

	// client rect
	CRect rc;
	GetClientRect(&rc);
	if (height < rc.Height())
	{
		if (m_scrollbar.GetSafeHwnd() != NULL)
		{
			m_scrollbar.EnableScrollBar(ESB_DISABLE_BOTH);
			m_scrollbar.ShowScrollBar(FALSE);
		}
		m_scroll_enabled = FALSE;
	}
	else
	{
		if (m_scrollbar.GetSafeHwnd() == NULL)
		{
			CRect rect = rc;
			rect.left = rect.right - GetSystemMetrics(SM_CXVSCROLL);
			m_scrollbar.Create(WS_CHILD|SBS_VERT, rect, this, 1000);
		}

		m_scrollbar.EnableScrollBar(ESB_ENABLE_BOTH);

		SCROLLINFO info;
		info.cbSize = sizeof(SCROLLINFO);
		info.fMask = SIF_ALL;
		info.nMin = 0;
		info.nMax = height;
		info.nPage = rc.Height();
		info.nPos = min(offset, height);
		info.nTrackPos = 2;
		m_scrollbar.SetScrollInfo(&info);

		m_scrollbar.ShowScrollBar();
		m_scroll_enabled = TRUE;
	}

	if (GetSafeHwnd())
		Invalidate();
}

int CPropertyGrid::GetScrollOffset()
{
	if (m_scrollbar && m_scrollbar.IsWindowEnabled() == TRUE)
		return m_scrollbar.GetScrollPos();
	return 0;
}

void CPropertyGrid::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// check
	if (!m_scroll_enabled) return;
	if (pScrollBar != &m_scrollbar) return;
	if (nSBCode == SB_ENDSCROLL) return;

	// set focus to us
	SetFocus();

	// get the scroll info
	SCROLLINFO info;
	info.cbSize = sizeof(SCROLLINFO);
	info.fMask = SIF_ALL;
	m_scrollbar.GetScrollInfo(&info);
	int min = info.nMin;
	int pos = info.nPos;
	int max = info.nMax-info.nPage;

	// the entire rect
	CRect rect;
	GetClientRect(&rect);
	int h = rect.Height();

	// the rect without the scrollbar
	CRect rc(0,0,rect.right-GetSystemMetrics(SM_CXVSCROLL),rect.bottom);

	switch(nSBCode)
	{
	case SB_TOP:
		pScrollBar->SetScrollPos(min);
		break;

	case SB_BOTTOM:
		pScrollBar->SetScrollPos(max);
		break;

	case SB_LINEDOWN:
		if (pos+m_line_height>=max) pScrollBar->SetScrollPos(max);
		else pScrollBar->SetScrollPos(pos+m_line_height);
		break;

	case SB_LINEUP:
		if (pos-m_line_height<=min) pScrollBar->SetScrollPos(min);
		else pScrollBar->SetScrollPos(pos-m_line_height);
		break;

	case SB_PAGEDOWN:
		if (pos+h>=max) pScrollBar->SetScrollPos(max);
		else pScrollBar->SetScrollPos(pos+h);
		break;

	case SB_PAGEUP:
		if (pos-h<=min) pScrollBar->SetScrollPos(min);
		else pScrollBar->SetScrollPos(pos-h);
		break;

	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		int diff = nPos - pos;
		if (diff == 0) return;
		if (pos <= min && diff<0) return;
		if (pos >= max && diff>0) return;
		pScrollBar->SetScrollPos(nPos);
	}

	Invalidate();

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);

}

BOOL CPropertyGrid::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int steps = abs(zDelta)/WHEEL_DELTA;
	for (int i=0; i<3*steps; i++)
	{
		if (zDelta>0) OnVScroll(SB_LINEUP, 0, &m_scrollbar);
		if (zDelta<0) OnVScroll(SB_LINEDOWN, 0, &m_scrollbar);
	}

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

//
// editing
//

CPropertyGrid::EEditMode CPropertyGrid::GetEditMode(CItem& item)
{
	switch (item.m_type)
	{
	case IT_CUSTOM:
		return ((ICustomItem*)item.m_pAllValue[0])->GetEditMode();

	case IT_STRING:
	case IT_INTEGER:
	case IT_DOUBLE:
		return EM_INPLACE;

	case IT_COMBO:
	case IT_BOOLEAN:
		return EM_DROPDOWN;

	case IT_TEXT:
	case IT_COLOR:
	case IT_FONT:
		return EM_MODAL;

	default:
		ASSERT(FALSE);
		return EM_CUSTOM;
	}
}

void CPropertyGrid::DeleteEditControl()
{
	// destroy edit
	if (m_control)
	{
		if (m_control->GetSafeHwnd())
			m_control->DestroyWindow();
		delete m_control;
		m_control = NULL;
	}
}

LRESULT CPropertyGrid::OnComboSelChanged(WPARAM wParam, LPARAM lParam)
{
	CItem* pItem = FindItem(m_focused_item);
	if (pItem)
	{
		pItem->SetValue((void*)&wParam);
		if (pItem->m_type == IT_BOOLEAN)
		{
			//*(bool*)pItem->m_pValue = (wParam == 0);
			pItem->m_undefined = FALSE;
			GetOwner()->SendMessage(WM_PG_ITEMCHANGED, pItem->m_id);
			DeleteEditControl();
			Invalidate();
		}
		else if (pItem->m_type == IT_COMBO)
		{
			//*(int*)pItem->m_pValue = int(wParam);
			pItem->m_undefined = FALSE;
			GetOwner()->SendMessage(WM_PG_ITEMCHANGED, pItem->m_id);
			DeleteEditControl();
			Invalidate();
		}
		else
		{
			ASSERT(FALSE);
		}
	}
	return 0;
}

LRESULT CPropertyGrid::OnEditChanged(WPARAM wParam, LPARAM lParam)
{
	CItem* pItem = FindItem(m_focused_item);
	if (pItem)
	{
		if (pItem->m_type == IT_STRING)
		{
			pItem->SetValue((void*)&wParam);
			pItem->m_undefined = FALSE;
			GetOwner()->SendMessage(WM_PG_ITEMCHANGED, pItem->m_id);
			DeleteEditControl();
			Invalidate();
		}
		else if (pItem->m_type == IT_INTEGER)
		{
			if (strlen((char*)wParam))
			{
				int i=_wtoi(*(CString*)&wParam);
				pItem->SetValue(&i);
				pItem->m_undefined = FALSE;
				GetOwner()->SendMessage(WM_PG_ITEMCHANGED, pItem->m_id);
			}
			DeleteEditControl();
			Invalidate();
		}
		else if (pItem->m_type == IT_DOUBLE)
		{
			if (strlen((char*)wParam))
			{
				double d=_wtof(*(CString*)&wParam);
				pItem->SetValue(&d);
				pItem->m_undefined = FALSE;
				GetOwner()->SendMessage(WM_PG_ITEMCHANGED, pItem->m_id);
			}
			DeleteEditControl();
			Invalidate();
		}
		else if (pItem->m_type == IT_CUSTOM)
		{
			if (((ICustomItem*)pItem->m_pAllValue[0])->OnItemEdited(CString((LPCTSTR)wParam)))
				GetOwner()->SendMessage(WM_PG_ITEMCHANGED, pItem->m_id);
			DeleteEditControl();
			Invalidate();
		}
		else
		{
			ASSERT(FALSE);
		}
	}
	return 0;
}

void CPropertyGrid::EditFocusedItem()
{
	CItem* pItem = FindItem(m_focused_item);
	if (pItem)
	{
		if (!pItem->m_editable)
			return;

		if (pItem->m_type == IT_TEXT)
		{
			CDynDialogEx dlg(GetParent());
			dlg.SetUseSystemButtons(FALSE);
			dlg.SetWindowTitle(pItem->m_name);
			dlg.SetFont(&m_fntNormal);
			CString strValue = pItem->m_undefined ? L"" : *(CString*)pItem->m_pAllValue[0];
			dlg.AddDlgControl(L"EDIT", strValue, STYLE_EDIT|WS_VSCROLL|WS_HSCROLL|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_LEFT|ES_MULTILINE|ES_WANTRETURN, EXSTYLE_EDIT, CRect(7, 7, 200, 100), (void*) &strValue);
			dlg.AddDlgControl(L"BUTTON", m_strOk, STYLE_BUTTON, EXSTYLE_BUTTON, CRect(56, 106, 106, 120), NULL, IDOK); 
			dlg.AddDlgControl(L"BUTTON", m_strCancel, STYLE_BUTTON, EXSTYLE_BUTTON, CRect(110, 106, 160, 120), NULL, IDCANCEL); 
			if (dlg.DoModal() == IDOK)
			{
				//*(CString*)pItem->m_pValue = LPCTSTR(strValue);
				pItem->SetValue(&strValue);
				pItem->m_undefined = FALSE;
				GetOwner()->SendMessage(WM_PG_ITEMCHANGED, pItem->m_id);
				Invalidate();
			}
		}
		else if (pItem->m_type == IT_COLOR)
		{
			CColorDialog dlg(pItem->m_undefined ? RGB(0,0,0) : *(COLORREF*)pItem->m_pAllValue[0], 0, GetParent());
			if (dlg.DoModal() == IDOK)
			{
				//*(COLORREF*)pItem->m_pValue = dlg.GetColor();
				COLORREF clr=dlg.GetColor();
				pItem->SetValue(&clr);
				pItem->m_undefined = FALSE;
				GetOwner()->SendMessage(WM_PG_ITEMCHANGED, pItem->m_id);
				Invalidate();
			}
		}
		else if (pItem->m_type == IT_FONT)
		{
			Graphics gr(AfxGetMainWnd()->m_hWnd);
			CFontDialog dlg(pItem->m_undefined ? NULL : (LOGFONT*)pItem->m_pAllValue[0], CF_EFFECTS|CF_SCREENFONTS, NULL, GetParent());
			if (dlg.DoModal() == IDOK)
			{
				//LOGFONT lgFont;
				//dlg.GetCurrentFont(&lgFont);
				pItem->SetValue(dlg.m_cf.lpLogFont);
				//memcpy(&*(LOGFONT*)pItem->m_pValue, dlg.m_cf.lpLogFont, sizeof(LOGFONT));
				pItem->m_undefined = FALSE;
				GetOwner()->SendMessage(WM_PG_ITEMCHANGED, pItem->m_id);
				Invalidate();
			}
		}
		else if (pItem->m_type == IT_CUSTOM)
		{
			if (((ICustomItem*)pItem->m_pAllValue[0])->OnEditItem())
			{
				GetOwner()->SendMessage(WM_PG_ITEMCHANGED, pItem->m_id);
				Invalidate();
			}
		}
		else
		{
			ASSERT(FALSE);
		}
	}
}
