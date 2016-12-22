#include "VGObject.h"
#include "VGObjContainer.h"

#pragma once

class CVGObjContainer;

#define ITEM_BORDER 3

class CPageListBox : public CListBox
{
	DECLARE_DYNAMIC(CPageListBox)

public:
	CPageListBox();
	virtual ~CPageListBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	void FillList();
public:
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
public:
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
	afx_msg void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
public:
	afx_msg int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
public:
	CArray<CVGObjContainer*>* m_contArr;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void RefreshItemSize();
	void DrawItemBitmap(int nIndex);
	void ResetBitmapArray();
public:
	int* m_PadWidth;
	int* m_PadHeight;
private:
	CArray<Bitmap*> m_bmpArray;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};


