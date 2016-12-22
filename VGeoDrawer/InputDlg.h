#pragma once
#include <vector>

using namespace std;

#define STATIC_HEIGHT 15
#define EDIT_HEIGHT 20
#define CTRL_DISTANCE 10
#define CTRL_STEP 7

// CInputDlg dialog

class CInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputDlg)

public:
	CInputDlg(CString strCaption, CWnd* pParent = NULL);   // standard constructor
	CString m_strCaption;
	virtual ~CInputDlg();
	CFont font;
	DLGTEMPLATE m_DialogTemplate;
	int m_Width;

	void AddStatic(CString strText);
	void AddEdit(CString* strValue, DWORD dwStyle=WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP);
	void AddComboBox(CString* strValue, CStringArray* arrItem, DWORD dwStyle=WS_CHILD | WS_VISIBLE);
	vector<CWnd*> m_wnd;
	vector<void*>m_Value;
	vector<CString>m_StaticText;
	vector<DWORD>m_dwStyle;
	vector<CStringArray*>m_comboArray;
	CWnd *m_pParentWnd;

	CButton m_btnOK;
	CButton m_btnCancel;
// Dialog Data
	enum { IDD = IDD_INPUTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnBnClickedOk();
};
