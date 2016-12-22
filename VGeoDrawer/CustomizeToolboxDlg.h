#pragma once
#include "EditIconDlg.h"
#include "afxcmn.h"
#include "resource.h"
#include "InputDlg.h"
#include "CommandArray.h"
#include "afxwin.h"

// CCustomizeToolboxDlg dialog

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
class CCustomizeToolboxDlg : public CDialog
{
	DECLARE_DYNAMIC(CCustomizeToolboxDlg)

public:
	CCustomizeToolboxDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCustomizeToolboxDlg();
	CCommandArray m_cmdArray;

// Dialog Data
	enum { IDD = IDD_CUSTOMIZE_TOOLBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	
public:
	CTreeCtrl m_TreeCtrl;
	CTreeCtrl m_TreeItemCtrl;
protected:
	virtual void OnOK();
protected:
	int m_nDefaultIconIndex;
	CString strOldText;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedBtnChangeIcon();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtndown();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnNMDblclkItemlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnremove();
	afx_msg void OnBnClickedBtnup();
	void MoveTreeItem(HTREEITEM hItem, HTREEITEM hNewParent, HTREEITEM hInsertAfter);
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRemove();
	afx_msg void OnTvnSelchangedItemlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnAddItemCommand();
	CTreeCtrl m_CommandList;
	afx_msg void OnTvnKeydownCommandList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnBeginlabeleditItemlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnEndlabeleditItemlist(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnTvnKeydownItemlist(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
};