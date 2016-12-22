#include "VGObjContainer.h"
#pragma once


// CEventDlg dialog

class CEventDlg : public CDialog
{
	DECLARE_DYNAMIC(CEventDlg)

public:
	CEventDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEventDlg();

// Dialog Data
	enum { IDD = IDD_EVENT_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddevent();
	CVGObjContainer* m_objCont;
public:
	virtual BOOL OnInitDialog();
};
