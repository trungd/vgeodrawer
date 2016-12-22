#pragma once
#include "cmdedit\cmdedit.h"
#include "CommandArray.h"


// CButtonCmdEditor dialog

class CButtonCmdEditor : public CDialog
{
	DECLARE_DYNAMIC(CButtonCmdEditor)

public:
	CButtonCmdEditor(CWnd* pParent = NULL);   // standard constructor
	virtual ~CButtonCmdEditor();

// Dialog Data
	enum { IDD = IDD_CMD_BUTTON_EDITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CCmdEdit m_Edit;
	CString m_Text;
	CCommandArray* m_cmdArray;
public:
	virtual BOOL OnInitDialog();
};
