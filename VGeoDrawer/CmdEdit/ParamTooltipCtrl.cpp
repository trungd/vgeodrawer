//// ParamTooltipCtrl.cpp: archivo de implementación
//

#include "stdafx.h"
#include "ParamToolTipCtrl.h"


// CParamTooltipCtrl

IMPLEMENT_DYNAMIC(CParamTooltipCtrl, CWnd)

BEGIN_MESSAGE_MAP(CParamTooltipCtrl, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()


CParamTooltipCtrl::CParamTooltipCtrl()
	: m_cBackground(::GetSysColor(COLOR_INFOBK))
	, m_cText(::GetSysColor(COLOR_INFOTEXT))
{
}

CParamTooltipCtrl::CParamTooltipCtrl(COLORREF cBackground, COLORREF cText)
	: m_cBackground(cBackground)
	, m_cText(cText)
{
}

BOOL CParamTooltipCtrl::Create(CWnd* pParentWnd)
{
	m_pParentWnd=pParentWnd;
	CString sClass = AfxRegisterWndClass(CS_DBLCLKS/*CS_CLASSDC|CS_HREDRAW|CS_SAVEBITS|CS_VREDRAW*/, NULL, NULL, NULL);

	if( !CWnd::CreateEx(WS_EX_TOPMOST, sClass, L"ParamTooltip", WS_POPUP|WS_BORDER, CRect(0,0,0,0), pParentWnd, 0) ) {
		TRACE("Failed to create ParamTooltip Window");
		return FALSE;
	}

	return TRUE;
}

void CParamTooltipCtrl::AddMethod( const CString& sMethod, const vector<CString>& setParams, const CString& desc )
{
	m_setMethods.push_back(METHOD(sMethod, setParams, desc));
	m_nCurParam = 0;
}
void CParamTooltipCtrl::FlushMethods()
{
	m_setMethods.resize(0);
}

void CParamTooltipCtrl::SetCurMethod(UINT nCurMethod)
{
	m_nCurMethod = nCurMethod;
}

void CParamTooltipCtrl::SetCurParam(UINT nCurParam)
{
	m_nCurParam = nCurParam;
}

void CParamTooltipCtrl::ShowTooltip(const CPoint& ptClient)
{
	m_ptOldClient = ptClient;
	CPoint ptScreen(ptClient);

	//MapWindowPoints(AfxGetMainWnd(),&ptScreen,1);
	//this->GetParent()->ClientToScreen(&ptScreen);
	CWnd* cwnd=this->GetParent();
	m_pParentWnd->ClientToScreen(&ptScreen);

	CClientDC dc(this);
	CSize size = Draw(dc, true);

	this->MoveWindow(ptScreen.x, ptScreen.y, size.cx, size.cy);
	ShowWindow(SW_SHOWNOACTIVATE);
}

void CParamTooltipCtrl::ShowPrevMethod()
{
	ShowWindow(SW_HIDE);
	m_nCurMethod--;
	if( m_nCurMethod < 0 )
		m_nCurMethod = (int)(m_setMethods.size())-1;
	m_nCurParam = 0;

	ShowTooltip(m_ptOldClient);
}

void CParamTooltipCtrl::ShowNextMethod()
{
	ShowWindow(SW_HIDE);

	m_nCurMethod++;
	if( m_nCurMethod == m_setMethods.size() )
		m_nCurMethod = 0;
	m_nCurParam = 0;

	ShowTooltip(m_ptOldClient);
}

void CParamTooltipCtrl::ShowPrevParam()
{
	if( 0 == m_nCurParam )
		return;

	ShowWindow(SW_HIDE);
	m_nCurParam--;
	ShowTooltip(m_ptOldClient);
}

void CParamTooltipCtrl::ShowNextParam()
{
	if( m_nCurParam == m_setMethods[m_nCurMethod].m_setParams.size()-1 )
		return;

	ShowWindow(SW_HIDE);
	m_nCurParam++;
	ShowTooltip(m_ptOldClient);
}

void CParamTooltipCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(&rect, m_cBackground);

	Draw(dc, true);
}

CSize CParamTooltipCtrl::Draw( CDC& dc, bool bDraw )
{
	CString& sMethod = m_setMethods[m_nCurMethod].m_sName;
	vector<CString>& setParams = m_setMethods[m_nCurMethod].m_setParams;
	CString strDes = m_setMethods[m_nCurMethod].m_Description;

	CFont fontNormal;
	VERIFY(fontNormal.CreateFont(
		-12,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		L"Tahoma"));                 // lpszFacename

	CFont fontBold;
	VERIFY(fontBold.CreateFont(
		-12,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_BOLD,	               // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		L"Tahoma"));                 // lpszFacename

	CFont* pOldFont = dc.SelectObject(&fontNormal);

	int cx = 0;

	if( m_setMethods.size() > 1 ) {
		// I we need arrows, first we create the bitmaps in memory. 
		// Because we won't use resources, we will create it in memory. 

		CString sString;
		sString.Format(L" [%d of %d] ", 1 + m_nCurMethod, m_setMethods.size() );

		dc.SelectObject(&fontBold);
		if( bDraw ) dc.TextOut(cx,0,sString); 
		cx += 1 + dc.GetTextExtent(sString).cx;
		dc.SelectObject(&fontNormal);
	}

	if( bDraw ) dc.TextOut(cx,0, L" "+sMethod); 
	cx += 1 + dc.GetTextExtent(L" "+sMethod).cx;
	
	if( bDraw )dc.TextOut(cx,0, L"("); 
	cx += 1 + dc.GetTextExtent(CString(L"(")).cx;

	for( size_t i=0; i<setParams.size(); i++ ) {
		if( i != m_nCurParam ) {
			if( bDraw ) dc.TextOut(cx,0,setParams[i]); 
			cx += 1 + dc.GetTextExtent(setParams[i]).cx;
		} else {
			dc.SelectObject(&fontBold);
			if( bDraw) dc.TextOut(cx,0,setParams[i]); 
			cx += 1 + dc.GetTextExtent(setParams[i]).cx;
			dc.SelectObject(&fontNormal);
		}

		if( i < setParams.size()-1 ) {
			if( bDraw ) dc.TextOut(cx,0, CString(", ")); 
			cx += 1 + dc.GetTextExtent(CString(", ")).cx;
		}
	}

	if( bDraw ) dc.TextOut(cx,0, CString(")")); 
	cx += 1 + dc.GetTextExtent(CString(")")).cx;

	int h = 2 + dc.GetTextExtent(CString(")")).cy;
	dc.TextOut(5,h,strDes);
	CSize s = dc.GetTextExtent(strDes);

	return CSize(max(s.cx + 8, 2 + cx), h + s.cy + 5);
}
