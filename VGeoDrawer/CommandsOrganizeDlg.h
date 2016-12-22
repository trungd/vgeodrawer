#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "commandarray.h"
#include "CmdEdit\CmdEdit.h"

// CCommandsOrganizeDlg dialog

class CCommandsOrganizeDlg : public CDialog
{
	DECLARE_DYNAMIC(CCommandsOrganizeDlg)

public:
	CCommandsOrganizeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCommandsOrganizeDlg();
	CCommandArray m_CommandArray;

// Dialog Data
	enum { IDD = IDD_COMMANDS_ORGANIZE };

private:
	HTREEITEM geoItem;
	HTREEITEM standardItem;
	HTREEITEM expItem;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void OnOK();

	DECLARE_MESSAGE_MAP()
public:
	CButton m_NewBtn;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	CTreeCtrl m_Tree;
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
	CCmdEdit m_Edit;
	afx_msg void OnBnClickedNew();
//	afx_msg void OnTvnBeginlabeleditTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnDeleteitemTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangingTree(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnTvnEndlabeleditTree(NMHDR *pNMHDR, LRESULT *pResult);
	int GetCmd(HTREEITEM item);
	afx_msg void OnTvnKeydownTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDelete();
	CTabCtrl m_Tab;
//	afx_msg void OnTcnSelchangeTabCommand(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEdit();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedCancel();
	CEdit m_Input;
	CEdit m_Output;
	CEdit m_Description;
	CEdit m_Name;
	void SaveTreeItem(HTREEITEM item);
	void FillTree();
	HTREEITEM GetTopParent(HTREEITEM item);
	CFont m_Font;
public:
	CEdit m_Condition;
public:
	afx_msg void OnTvnGetdispinfoTreeCommand(NMHDR *pNMHDR, LRESULT *pResult);
};
