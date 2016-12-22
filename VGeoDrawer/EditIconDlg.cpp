// EditIconDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "EditIconDlg.h"


// CEditIconDlg dialog

IMPLEMENT_DYNAMIC(CEditIconDlg, CDialog)

CEditIconDlg::CEditIconDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditIconDlg::IDD, pParent)
{

}

CEditIconDlg::~CEditIconDlg()
{
}

void CEditIconDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ICON_EDITOR, m_IconEditor);
	DDX_Control(pDX, IDC_CUSTOM2, m_ColorPicker);
	DDX_Control(pDX, IDC_STATIC_TOOLBAR, m_staticTBar);
	DDX_Control(pDX, IDC_CHECK_ANTIALIAS, m_chkAntiAlias);
	DDX_Control(pDX, IDC_STATIC_PREVIEW, m_staticPreview);
}


BEGIN_MESSAGE_MAP(CEditIconDlg, CDialog)
	ON_BN_CLICKED(ID_ICON_BTN, &CEditIconDlg::OnBnClickedIconBtn)
	
// 	ON_UPDATE_COMMAND_UI(ID_ICON_PEN, OnUpdateIconPen)
// 	ON_UPDATE_COMMAND_UI(ID_ICON, OnUpdateEditCut)
// 	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
// 	ON_UPDATE_COMMAND_UI(ID_FORMAT_BOLD, OnUpdateFormatBold)
// 	ON_UPDATE_COMMAND_UI(ID_FORMAT_DURCHSTRICH, OnUpdateFormatDurchstrich)
// 	ON_UPDATE_COMMAND_UI(ID_FORMAT_KURSIV, OnUpdateFormatKursiv)
// 	ON_UPDATE_COMMAND_UI(ID_FORMAT_UNTERSTRICH, OnUpdateFormatUnterstrich)
	ON_COMMAND(ID_ICON_PEN, OnIconPen)
	ON_COMMAND(ID_ICON_RECTANGLE, OnIconRect)
	ON_COMMAND(ID_ICON_ELIP, OnIconEllipse)
	ON_COMMAND(ID_ICON_LINE, OnIconLine)
 	ON_COMMAND(ID_ICON_POINT, OnIconPoint)
 	ON_COMMAND(ID_ICON_COLOR_SEL, OnIconClrSel)
	ON_COMMAND(ID_ICON_FILL, OnIconFill)
// 	ON_COMMAND(ID_FORMAT_KURSIV, OnFormatKursiv)
// 	ON_COMMAND(ID_FORMAT_UNTERSTRICH, OnFormatUnterstrich)
ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CEditIconDlg::OnBnClickedButtonClear)
//ON_BN_CLICKED(IDC_CHECK1, &CEditIconDlg::OnBnClickedCheck1)
ON_BN_CLICKED(IDC_CHECK_ANTIALIAS, &CEditIconDlg::OnBnClickedCheckAntialias)
ON_BN_CLICKED(IDOK, &CEditIconDlg::OnBnClickedOk)
//ON_STN_CLICKED(IDC_STATIC_PREVIEW, &CEditIconDlg::OnStnClickedStaticPreview)
END_MESSAGE_MAP()


// CEditIconDlg message handlers

void CEditIconDlg::OnBnClickedIconBtn()
{
	CFileDialog dlgFile(TRUE, NULL , NULL, 
		OFN_PATHMUSTEXIST,
		L"Bitmap (*.bmp)|*.bmp|All Files (*.*)|*.*||", this, 0);
	if (dlgFile.DoModal()==IDOK)
	{
		CString path=dlgFile.GetOFN().lpstrFile;
		Bitmap* bmp;
		bmp=Bitmap::FromFile(path);
		m_IconEditor.SetBitmap(bmp);
		m_IconEditor.OnPaint();
		delete bmp;
	}
}

BOOL CEditIconDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ColorPicker.m_Colors.push_back(Color(0,0,0));
	m_ColorPicker.m_Colors.push_back(Color(128,128,128));
	m_ColorPicker.m_Colors.push_back(Color(128,0,0));
	m_ColorPicker.m_Colors.push_back(Color(128,128,0));
	m_ColorPicker.m_Colors.push_back(Color(0,128,0));
	m_ColorPicker.m_Colors.push_back(Color(0,128,128));
	m_ColorPicker.m_Colors.push_back(Color(0,0,128));
	m_ColorPicker.m_Colors.push_back(Color(128,0,128));
	m_ColorPicker.m_Colors.push_back(Color(128,128,64));
	m_ColorPicker.m_Colors.push_back(Color(0,64,64));
	m_ColorPicker.m_Colors.push_back(Color(0,128,255));
	m_ColorPicker.m_Colors.push_back(Color(0,64,128));
	m_ColorPicker.m_Colors.push_back(Color(128,0,255));
	m_ColorPicker.m_Colors.push_back(Color(128,64,0));


	m_ColorPicker.m_Colors.push_back(Color(255,255,255));
	m_ColorPicker.m_Colors.push_back(Color(192,192,192));
	m_ColorPicker.m_Colors.push_back(Color(255,0,0));
	m_ColorPicker.m_Colors.push_back(Color(255,255,0));
	m_ColorPicker.m_Colors.push_back(Color(0,255,0));
	m_ColorPicker.m_Colors.push_back(Color(0,255,255));
	m_ColorPicker.m_Colors.push_back(Color(0,0,255));
	m_ColorPicker.m_Colors.push_back(Color(255,0,255));
	m_ColorPicker.m_Colors.push_back(Color(255,255,128));
	m_ColorPicker.m_Colors.push_back(Color(0,255,128));
	m_ColorPicker.m_Colors.push_back(Color(128,255,255));
	m_ColorPicker.m_Colors.push_back(Color(128,128,255));
	m_ColorPicker.m_Colors.push_back(Color(255,0,128));
	m_ColorPicker.m_Colors.push_back(Color(255,128,64));

	m_ColorPicker.m_Column=16;
	m_ColorPicker.m_leftClr=Color(0,0,0);
	m_ColorPicker.m_rightClr=Color(255,255,255);

// 	POSITION pos=AfxGetApp()->GetFirstDocTemplatePosition();
// 	CDocTemplate* pDT=AfxGetApp()->GetNextDocTemplate(pos);
// 	pos=pDT->GetFirstDocPosition();
// 	CVGeoDrawerDoc* pDoc=(CVGeoDrawerDoc*)pDT->GetNextDoc(pos);
// 	BOOL bCheck;
	
// 	for (int i=0;i<pDoc->m_Array.m_aCommand.GetSize();i++)
// 	{
// 		CString cmd=pDoc->m_Array.m_aCommand.m_aCommandName[i];
// 		bCheck=FALSE;
// 		for (int j=0;j<i;j++)
// 			if (pDoc->m_Array.m_aCommand.m_aCommandName[j]==cmd) 
// 			{
// 				bCheck=TRUE;
// 				break;
// 			}
// 		if (!bCheck) m_cmdNameCombo.AddString(cmd);
// 	}

	WINDOWPLACEMENT wpl;
	CSize sizeToolbar;
	CRect mrect;
	mrect.SetRectEmpty();
	m_ToolBar.Create(this); // attach command routing to dialog window
	m_ToolBar.LoadToolBar(IDR_TOOLBAR_ICON);
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

	/*for (int i=0;i<m_ToolBar.GetCount();i++)
		m_ToolBar.SetButtonStyle(i,BTNS_CHECK);*/

	m_IconEditor.m_leftClr=&m_ColorPicker.m_leftClr;
	m_IconEditor.m_rightClr=&m_ColorPicker.m_rightClr;
	m_IconEditor.SetBitmap(bmp);

	m_chkAntiAlias.SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CEditIconDlg::OnOK()
{
	CDialog::OnOK();
}

void CEditIconDlg::OnIconPen()
{
	m_IconEditor.m_Mode=MODE_PEN;
}

void CEditIconDlg::OnIconRect()
{
	m_IconEditor.m_Mode=MODE_RECTANGLE;
}

void CEditIconDlg::OnIconEllipse()
{
	m_IconEditor.m_Mode=MODE_ELLIPSE;
}

void CEditIconDlg::OnIconLine()
{
	m_IconEditor.m_Mode=MODE_LINE;
}
LRESULT CEditIconDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message==WM_ICONCHANGE)
	{
		HBITMAP hbm;
		m_IconEditor.m_tmpBitmap->GetHBITMAP(Color(255,255,255),&hbm);
		m_staticPreview.SetBitmap(hbm);
		//Graphics gr(GetDlgItem(IDC_STATIC_PREVIEW)->m_hWnd);
		//gr.DrawImage(m_IconEditor.m_tmpBitmap,0,0,32,32);
	}
	else if (message==WM_REDRAWCOLORPICKER)
	{
		m_ColorPicker.OnPaint();
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

void CEditIconDlg::OnBnClickedButtonClear()
{
	m_IconEditor.ClearIcon();
	m_IconEditor.OnPaint();
}

void CEditIconDlg::OnBnClickedCheckAntialias()
{
	m_IconEditor.m_bAntiAlias=m_chkAntiAlias.GetCheck();	
}

void CEditIconDlg::OnIconPoint()
{
	m_IconEditor.m_Mode=MODE_POINT;
}

void CEditIconDlg::OnIconClrSel()
{
	m_IconEditor.m_Mode=MODE_COLORSEL;
}

void CEditIconDlg::OnIconFill()
{
	m_IconEditor.m_Mode=MODE_COLOR;
}

void CEditIconDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}