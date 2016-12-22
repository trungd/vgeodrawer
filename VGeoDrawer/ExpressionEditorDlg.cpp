// ExpressionEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "ExpressionEditorDlg.h"
#include "MathDraw.h"


// CExpressionEditorDlg dialog

IMPLEMENT_DYNAMIC(CExpressionEditorDlg, CDialog)

CExpressionEditorDlg::CExpressionEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExpressionEditorDlg::IDD, pParent)
	, strExp(_T(""))
{
	bmp=NULL;
}

CExpressionEditorDlg::~CExpressionEditorDlg()
{
}

void CExpressionEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EXP, strExp);
	DDX_Control(pDX, IDC_COMBO_FUNC_NUM, m_cbNum);
	DDX_Control(pDX, IDC_COMBO_FUNC_BOOL, m_cbBool);
	DDX_Control(pDX, IDC_EDIT_EXP, m_Edit);
}


BEGIN_MESSAGE_MAP(CExpressionEditorDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_FUNC_NUM, &CExpressionEditorDlg::OnCbnSelchangeComboFuncNum)
	ON_CBN_SELCHANGE(IDC_COMBO_FUNC_BOOL, &CExpressionEditorDlg::OnCbnSelchangeComboFuncBool)
	ON_EN_CHANGE(IDC_EDIT_EXP, &CExpressionEditorDlg::OnEnChangeEditExp)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CExpressionEditorDlg message handlers

BOOL CExpressionEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cbBool.SetCurSel(0);
	m_cbNum.SetCurSel(0);
	m_Edit.SetFocus();

	return TRUE;  
}

void CExpressionEditorDlg::OnCbnSelchangeComboFuncNum()
{
	if (m_cbNum.GetCurSel()!=0)
	{
		CString strF;
		m_cbNum.GetLBText(m_cbNum.GetCurSel(),strF);
		m_Edit.SetFocus();
		m_Edit.ReplaceSel(strF,TRUE);
		m_cbNum.SetCurSel(0);
	}
}

void CExpressionEditorDlg::OnCbnSelchangeComboFuncBool()
{
	if (m_cbBool.GetCurSel()!=0)
	{
		CString strF;
		m_cbBool.GetLBText(m_cbBool.GetCurSel(),strF);
		m_Edit.SetFocus();
		m_Edit.ReplaceSel(strF,TRUE);
		m_cbBool.SetCurSel(0);
	}
}

void CExpressionEditorDlg::OnEnChangeEditExp()
{
	CString str;
	m_Edit.GetWindowText(str);
	if (bmp!=NULL) delete bmp;
	Font font(L"Times New Roman",12);
	bmp=CMathDraw::DrawExpression(str,Color(0,0,0),&font);
	OnPaint();
}

void CExpressionEditorDlg::OnPaint()
{
	Graphics gr(GetDlgItem(IDC_STATIC_MATH)->m_hWnd);

	CRect rc;
	GetDlgItem(IDC_STATIC_MATH)->GetClientRect(rc);
	Bitmap drawBmp(rc.right,rc.bottom);
	Graphics graph(&drawBmp);

	graph.Clear(Color::White);
	if (bmp!=NULL) graph.DrawImage(bmp,5,5);
	Pen pen(Color(192,192,192));
	graph.DrawRectangle(&pen,0,0,rc.Width()-1,rc.Height()-1);

	gr.DrawImage(&drawBmp,0,0);
	CDialog::OnPaint();
}
