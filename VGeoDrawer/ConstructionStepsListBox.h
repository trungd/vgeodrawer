#pragma once


// CConstructionStepsListBox

class CConstructionStepsListBox : public CListBox
{
	DECLARE_DYNAMIC(CConstructionStepsListBox)

public:
	CConstructionStepsListBox();
	virtual ~CConstructionStepsListBox();
	int strNumSize;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	afx_msg void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
	void GetMaxStringSize();
public:
	afx_msg void OnPaint();
};


