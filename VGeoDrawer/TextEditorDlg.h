#pragma once
#include "afxwin.h"
#include "resource.h"
#include "gdi+.h"


// CTextEditorDlg dialog

class CTextEditorDlg : public CDialog
{
	DECLARE_DYNAMIC(CTextEditorDlg)

public:
	CTextEditorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTextEditorDlg();

// Dialog Data
	enum { IDD = IDD_TEXTEDITORDLG };

	Bitmap* bmp;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg void OnBnClickedBtnPreview();
public:
	afx_msg void OnPaint();
public:
	CString m_Text;
public:
	afx_msg void OnEnChangeEditText();
public:
	BOOL m_bPreview;
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedFont();
	void UpdateFontString();
public:
	Font* m_Font;
public:
	virtual BOOL OnInitDialog();
};
