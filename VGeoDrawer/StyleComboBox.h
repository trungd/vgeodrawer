#pragma once


// CStyleComboBox

class CStyleComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CStyleComboBox)

public:
	CStyleComboBox();
	virtual ~CStyleComboBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	void SetLineStyleComboBox();
public:
	afx_msg int OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct);
};


