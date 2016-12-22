// TextEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "TextEditorDlg.h"
#include "MathDraw.h"
#include "VGMath.h"
#include "appfunc.h"


// CTextEditorDlg dialog

IMPLEMENT_DYNAMIC(CTextEditorDlg, CDialog)

CTextEditorDlg::CTextEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTextEditorDlg::IDD, pParent)
	, m_bPreview(FALSE)
	, m_Text(_T(""))
{
	bmp=NULL;
	m_Font=new Font(L"Times New Roman",12);
	m_bPreview=TRUE;
}

CTextEditorDlg::~CTextEditorDlg()
{
	delete m_Font;
}

void CTextEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_PREVIEW, m_bPreview);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_Text);
}


BEGIN_MESSAGE_MAP(CTextEditorDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_PREVIEW, &CTextEditorDlg::OnBnClickedBtnPreview)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT_TEXT, &CTextEditorDlg::OnEnChangeEditText)
	ON_BN_CLICKED(IDOK, &CTextEditorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTextEditorDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_FONT, &CTextEditorDlg::OnBnClickedFont)
END_MESSAGE_MAP()


// CTextEditorDlg message handlers

void CTextEditorDlg::OnOK()
{
	
}

void CTextEditorDlg::OnBnClickedBtnPreview()
{
	UpdateData(TRUE);
	if (bmp!=NULL) delete bmp;
	bmp=CMathDraw::DrawText(m_Text,Color(0,0,0),m_Font);
	OnPaint();
}

void CTextEditorDlg::OnPaint()
{
	Graphics gr(GetDlgItem(IDC_STATIC_PREVIEW)->m_hWnd);

	CRect rc;
	GetDlgItem(IDC_STATIC_PREVIEW)->GetClientRect(rc);
	Bitmap drawBmp(rc.right,rc.bottom);
	Graphics graph(&drawBmp);

	graph.Clear(Color::White);
	if (bmp!=NULL) graph.DrawImage(bmp,5,5);
	Pen pen(Color(192,192,192));
	graph.DrawRectangle(&pen,0,0,rc.Width()-1,rc.Height()-1);

	gr.DrawImage(&drawBmp,0,0);
	CDialog::OnPaint();
}

void CTextEditorDlg::OnEnChangeEditText()
{
	UpdateData(TRUE);
	if (m_bPreview) OnBnClickedBtnPreview();
}

void CTextEditorDlg::OnBnClickedOk()
{
	CDialog::OnOK();
}

void CTextEditorDlg::OnBnClickedCancel()
{
	CDialog::OnCancel();
}

void CTextEditorDlg::OnBnClickedFont()
{
	LOGFONT lf;
	Graphics g(this->m_hWnd);
	m_Font->GetLogFontW(&g,&lf);
	CFontDialog dlg(&lf,CF_EFFECTS|CF_SCREENFONTS, NULL, this);
	//memcpy(&dlg.m_lf,&lf,sizeof(LOGFONT));
	if (dlg.DoModal()==IDOK)
	{
		LOGFONT lgFont;
		dlg.GetCurrentFont(&lgFont);
		Font* font=LOGFONT_To_Font(&lgFont);
		delete m_Font;
		m_Font=font;
		GetDlgItem(IDC_STATIC_FONT)->SetWindowText(dlg.GetFaceName()+L", "+Math::IntToString(dlg.GetSize()/10)+L"pt");
		OnBnClickedBtnPreview();
	}
}

BOOL CTextEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_FONT)->SetWindowText(L"Times New Roman, 12pt");

	return TRUE;
}
