// ButtonCmdEditor.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "ButtonCmdEditor.h"


// CButtonCmdEditor dialog

IMPLEMENT_DYNAMIC(CButtonCmdEditor, CDialog)

CButtonCmdEditor::CButtonCmdEditor(CWnd* pParent /*=NULL*/)
	: CDialog(CButtonCmdEditor::IDD, pParent)
{

}

CButtonCmdEditor::~CButtonCmdEditor()
{
}

void CButtonCmdEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT, m_Edit);
	DDX_Text(pDX,IDC_EDIT,m_Text);
}


BEGIN_MESSAGE_MAP(CButtonCmdEditor, CDialog)
END_MESSAGE_MAP()


// CButtonCmdEditor message handlers

BOOL CButtonCmdEditor::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Edit.InitCtrl();
	m_Edit.m_cmdArray=m_cmdArray;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
