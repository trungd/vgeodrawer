// MathDrawDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "MathDrawDlg.h"
#include "MathDraw.h"


// CMathDrawDlg dialog

IMPLEMENT_DYNAMIC(CMathDrawDlg, CDialog)

CMathDrawDlg::CMathDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMathDrawDlg::IDD, pParent)
	, m_bLaTex(FALSE)
{
	bmp=NULL;
}

CMathDrawDlg::~CMathDrawDlg()
{
}

void CMathDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TOOLBAR, m_staticTBar);
	DDX_Check(pDX, IDC_CHECK1, m_bLaTex);
	DDX_Control(pDX, IDC_EDIT, m_Edit);
}


BEGIN_MESSAGE_MAP(CMathDrawDlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT, &CMathDrawDlg::OnEnChangeEdit)
	ON_WM_PAINT()
	ON_COMMAND(ID_MATH_EDITOR_EXPONENT,OnExponent)
	ON_COMMAND(ID_MATH_EDITOR_SUB_TEXT,OnSubText)
	ON_COMMAND(ID_MATH_EDITOR_FRACTION,OnFraction)
	ON_COMMAND(ID_MATH_EDITOR_SQUARE_ROOT,OnSquareRoot)
	ON_COMMAND(ID_MATH_EDITOR_SQUARE_ROOT,OnRoot)
END_MESSAGE_MAP()


// CMathDrawDlg message handlers

void CMathDrawDlg::OnExponent()
{
	
}

void CMathDrawDlg::OnSubText()
{

}

void CMathDrawDlg::OnFraction()
{

}

void CMathDrawDlg::OnSquareRoot()
{

}

void CMathDrawDlg::OnRoot()
{

}

void CMathDrawDlg::OnEnChangeEdit()
{
	CString str;
	GetDlgItem(IDC_EDIT)->GetWindowText(str);
	if (bmp!=NULL) delete bmp;
	Font font(L"Times New Roman",12);
	bmp=CMathDraw::DrawExpression(str,Color(0,0,0),&font);
	OnPaint();
}

void CMathDrawDlg::OnPaint()
{
	Graphics gr(GetDlgItem(IDC_STATIC_MATH)->m_hWnd);

	CRect rc;
	GetDlgItem(IDC_STATIC_MATH)->GetClientRect(rc);
	Bitmap drawBmp(rc.right,rc.bottom);
	Graphics graph(&drawBmp);
	
	graph.Clear(Color(255,255,255));
	if (bmp!=NULL) graph.DrawImage(bmp,5,5);
	Pen pen(Color(192,192,192));
	graph.DrawRectangle(&pen,0,0,rc.Width()-1,rc.Height()-1);
	
	gr.DrawImage(&drawBmp,0,0);
	CDialog::OnPaint();
}

BOOL CMathDrawDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	WINDOWPLACEMENT wpl;
	CSize sizeToolbar;
	CRect mrect;
	mrect.SetRectEmpty();
	m_ToolBar.Create(this); // attach command routing to dialog window
	m_ToolBar.LoadToolBar(IDR_TOOLBAR_MATH_EDITOR);
	m_ToolBar.SetBarStyle(CBRS_ALIGN_TOP | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_ToolBar.ShowWindow(SW_SHOW);
	// Caltulate size of toolbar and adjust size of static control to fit size
	sizeToolbar = m_ToolBar.CalcFixedLayout(false,true);
	m_staticTBar.GetWindowPlacement(&wpl);
	wpl.rcNormalPosition.bottom = wpl.rcNormalPosition.top  + sizeToolbar.cy + 4;
	wpl.rcNormalPosition.right  = wpl.rcNormalPosition.left + sizeToolbar.cx + 4;
	// Position static control and toolbar
	m_staticTBar.SetWindowPlacement(&wpl);
	m_ToolBar.SetWindowPlacement(&wpl);
	// Adjust buttons into static control
	m_staticTBar.RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	m_staticTBar.ShowWindow(SW_HIDE);

	return TRUE;
}
