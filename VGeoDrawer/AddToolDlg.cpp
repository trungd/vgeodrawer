// AddToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "AddToolDlg.h"
#include "EditIconDlg.h"


// CAddToolDlg dialog

IMPLEMENT_DYNAMIC(CAddToolDlg, CDialog)

CAddToolDlg::CAddToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddToolDlg::IDD, pParent)
	, m_ToolName(_T(""))
	, m_Command(_T(""))
	, m_CommandInput(_T(""))
	, m_CommandOutput(_T(""))
	, m_ConstructionInput(_T(""))
	, m_CommandName(_T("New Item"))
	, m_bAddByCommand(FALSE)
	, m_bAddByConstruction(TRUE)
	, m_Description(_T(""))
	, m_bAddTBItem(TRUE)
{

}

CAddToolDlg::~CAddToolDlg()
{
}

void CAddToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITTOOLNAME, m_ToolName);
	DDX_Text(pDX, IDC_EDITCOMMAND, m_Command);
	DDX_Text(pDX, IDC_EDITINPUT2, m_CommandInput);
	DDX_Text(pDX, IDC_EDITOUTPUT2, m_CommandOutput);
	DDX_Text(pDX, IDC_EDITINPUT, m_ConstructionInput);
	DDX_Control(pDX, IDC_EDITOUTPUT, m_ConstructionOutput);
	DDX_Text(pDX, IDC_NAME, m_CommandName);
	DDX_Radio(pDX, IDC_ADD1, m_bAddByCommand);
	DDX_Radio(pDX, IDC_ADD2, m_bAddByConstruction);
	DDX_Text(pDX, IDC_DESCRIPTION, m_Description);
	DDX_Check(pDX, IDC_ADDTBITEM, m_bAddTBItem);
}


BEGIN_MESSAGE_MAP(CAddToolDlg, CDialog)
//	ON_BN_CLICKED(IDOK2, &CAddToolDlg::OnBnClickedOk2)
//ON_BN_CLICKED(ID_ICON_BTN, &CAddToolDlg::OnBnClickedIconBtn)
ON_BN_CLICKED(IDC_EDIT_ICON, &CAddToolDlg::OnBnClickedEditIcon)
ON_BN_CLICKED(IDC_ADD1, &CAddToolDlg::OnBnClickedAdd1)
ON_BN_CLICKED(IDC_ADD2, &CAddToolDlg::OnBnClickedAdd2)
ON_BN_CLICKED(IDC_CHECK2, &CAddToolDlg::OnBnClickedCheck2)
ON_BN_CLICKED(IDOK, &CAddToolDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddToolDlg message handlers

//void CAddToolDlg::OnBnClickedIconBtn()
//{
//	CFileDialog dlgFile(TRUE, NULL , NULL, 
//		OFN_PATHMUSTEXIST,
//		L"Bitmap (*.bmp)|*.bmp|Icon (*.ico)|*.ico|All Files (*.*)|*.*||", this, 0);
//	if (dlgFile.DoModal()==IDOK)
//	{
//		CString path=dlgFile.GetPathName();
//		GetDlgItem(IDC_FILENAME)->SetWindowText(path);
//	}
//}

void CAddToolDlg::OnBnClickedEditIcon()
{
	CEditIconDlg dlg;
	Bitmap bmp(32,32,PixelFormat32bppARGB);
	bmp.FromHBITMAP(hBmp,NULL);
	dlg.bmp=&bmp;
	if (dlg.DoModal()==IDOK)
	{
		dlg.m_IconEditor.m_tmpBitmap->GetHBITMAP(Color::White,&hBmp);
		((CStatic*)GetDlgItem(IDC_STATIC_ICON))->SetBitmap(hBmp);
	}
}

void CAddToolDlg::OnBnClickedAdd1()
{
	BOOL b=((CButton*)GetDlgItem(IDC_ADD1))->GetCheck();
	((CButton*)GetDlgItem(IDC_ADD2))->SetCheck(!b);
	GetDlgItem(IDC_COMBOINPUT)->ShowWindow(b);
	GetDlgItem(IDC_COMBOOUTPUT)->ShowWindow(b);
	GetDlgItem(IDC_EDITINPUT)->ShowWindow(b);
	GetDlgItem(IDC_EDITOUTPUT)->ShowWindow(b);
	GetDlgItem(IDC_BTNADDINPUT)->ShowWindow(b);
	GetDlgItem(IDC_BTNADDOUTPUT)->ShowWindow(b);
	GetDlgItem(IDC_BTNCLEARINPUT)->ShowWindow(b);
	GetDlgItem(IDC_BTNCLEAROUTPUT)->ShowWindow(b);
	GetDlgItem(IDC_STATICINPUT)->ShowWindow(b);
	GetDlgItem(IDC_STATICOUTPUT)->ShowWindow(b);

	if (b) OnBnClickedAdd2();
}

void CAddToolDlg::OnBnClickedAdd2()
{
	BOOL b=((CButton*)GetDlgItem(IDC_ADD2))->GetCheck();
	((CButton*)GetDlgItem(IDC_ADD1))->SetCheck(!b);
	GetDlgItem(IDC_EDITINPUT2)->ShowWindow(b);
	GetDlgItem(IDC_EDITOUTPUT2)->ShowWindow(b);
	GetDlgItem(IDC_EDITCOMMAND)->ShowWindow(b);
	GetDlgItem(IDC_STATICINPUT2)->ShowWindow(b);
	GetDlgItem(IDC_STATICOUTPUT2)->ShowWindow(b);

	if (b) OnBnClickedAdd1();
}

BOOL CAddToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	OnBnClickedAdd1();

	((CEdit*)GetDlgItem(IDC_NAME))->SetSel(0,7);

	hBmp=LoadBitmap(NULL,MAKEINTRESOURCE(IDB_DEFAULTICON));
	((CStatic*)GetDlgItem(IDC_STATIC_ICON))->SetBitmap(hBmp);

	return TRUE;
}

void CAddToolDlg::OnBnClickedCheck2()
{
	BOOL b=((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();
	GetDlgItem(IDC_COMBOCATEGORY)->EnableWindow(b);
	GetDlgItem(IDC_EDIT_ICON)->EnableWindow(b);
	GetDlgItem(IDC_EDITTOOLNAME)->EnableWindow(b);
	GetDlgItem(IDC_STATIC_TOOLNAME)->EnableWindow(b);
	GetDlgItem(IDC_STATIC_CATEGORY)->EnableWindow(b);
	GetDlgItem(IDC_STATICICON)->EnableWindow(b);
	GetDlgItem(IDC_STATIC_TBITEM)->EnableWindow(b);
}

void CAddToolDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CAddToolDlg::OnOK()
{
	CDialog::OnOK();
}
