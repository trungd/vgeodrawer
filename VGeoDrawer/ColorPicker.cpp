// ColorPalette.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "ColorPicker.h"


// CColorPalette

IMPLEMENT_DYNAMIC(CColorPicker, CWnd)

BOOL CColorPicker::RegisterWndClass()
{
	WNDCLASS windowclass;
	HINSTANCE hInst = AfxGetInstanceHandle();

	//Check weather the class is registerd already

	if (!(::GetClassInfo(hInst, L"ColorPicker", &windowclass)))
	{
		//If not then we have to register the new class

		windowclass.style = CS_DBLCLKS;// | CS_HREDRAW | CS_VREDRAW;

		windowclass.lpfnWndProc = ::DefWindowProc;
		windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
		windowclass.hInstance = hInst;
		windowclass.hIcon = NULL;
		windowclass.hCursor = LoadCursor(hInst,MAKEINTRESOURCE(IDC_IBEAM));//LoadCursor(hInst,MAKEINTRESOURCE(IDC_CURSOR_PEN));
		windowclass.hbrBackground = ::GetSysColorBrush(COLOR_3DFACE);
		windowclass.lpszMenuName = NULL;
		windowclass.lpszClassName = L"ColorPicker";

		if (!AfxRegisterClass(&windowclass))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}

CColorPicker::CColorPicker()
{
	RegisterWndClass();
}

CColorPicker::~CColorPicker()
{
}


BEGIN_MESSAGE_MAP(CColorPicker, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

void CColorPicker::DrawColor()
{
	int r=-1;//Row
	int c;//Column
	Graphics gr(this->m_hWnd);
	int left=0;
	if (showChosenColor)
	{
		left=(COLOR_DISTANCE+COLOR_SIZE)*2;
		int size=2*COLOR_SIZE+COLOR_DISTANCE;
		Rect rect(0,0,size,size);
		SolidBrush br(Color(250,250,250));
		gr.FillRectangle(&br,rect);
		Pen pen(Color(128,128,128));
		gr.DrawRectangle(&pen,rect);

		if (m_bOneColor)
		{
			int p2=size/4;
			DrawColorItem(p2,p2,m_leftClr,&gr);
		}
		else
		{
			int p2=size/2-COLOR_SIZE/4;
			DrawColorItem(p2,p2,m_rightClr,&gr);
			int p1=(size-3*COLOR_SIZE/2)/2;
			DrawColorItem(p1,p1,m_leftClr,&gr);
		}
	}

	c=0;
	for (int i=0;i<m_Colors.size();i++)
	{
		if (c==0) r+=1;
		DrawColorItem((COLOR_DISTANCE+COLOR_SIZE)*c+ (r<2 ? left : 0),
			(COLOR_DISTANCE+COLOR_SIZE)*r,
			m_Colors[i],&gr);
		c++;
		if (c==(r<2 ? m_Column-2 : m_Column)) c=0;
	}
}

void CColorPicker::DrawColorItem(int x, int y, Color clr, Graphics* gr)
{
	Pen pen(Color(128,128,128));
	Rect rect(x,y,COLOR_SIZE,COLOR_SIZE);
	SolidBrush br(clr);
	gr->FillRectangle(&br,rect);
	gr->DrawRectangle(&pen,rect);
}


void CColorPicker::OnPaint()
{
	CWnd::OnPaint();
	DrawColor();
}

int CColorPicker::GetColorIndex(CPoint pt)
{
	int r=-1;//Row
	int c;//Column
	Graphics gr(this->m_hWnd);
	int left=0;
	if (showChosenColor)
	{
		left=(COLOR_DISTANCE+COLOR_SIZE)*2;
	}
	c=0;
	for (int i=0;i<m_Colors.size();i++)
	{
		if (c==0) r+=1;
		if (pt.x>((COLOR_DISTANCE+COLOR_SIZE)*c+ (r<2 ? left : 0)) && 
			pt.x<((COLOR_DISTANCE+COLOR_SIZE)*c+ (r<2 ? left : 0))+COLOR_SIZE &&
			pt.y>(COLOR_DISTANCE+COLOR_SIZE)*r && 
			pt.y<(COLOR_DISTANCE+COLOR_SIZE)*r+COLOR_SIZE)
			return i;
		c++;
		if (c==(r<2 ? m_Column-2 : m_Column)) c=0;
	}
	return -1;
}

void CColorPicker::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	int i=GetColorIndex(point);
	if (i!=-1)
	{
		CColorDialog dlg(m_Colors[i].ToCOLORREF(),0,this);
		if (dlg.DoModal()==IDOK)
		{
			m_Colors[i].SetFromCOLORREF(dlg.m_cc.rgbResult);
			m_leftClr.SetFromCOLORREF(dlg.m_cc.rgbResult);
			DrawColor();
		}
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}

void CColorPicker::OnLButtonDown(UINT nFlags, CPoint point)
{
	int i=GetColorIndex(point);
	if (i!=-1) 
	{
		m_leftClr=m_Colors[i];
		GetParent()->SendMessage(WM_COLORCHANGED);
	}
	DrawColor();

	CWnd::OnLButtonDown(nFlags, point);
}

void CColorPicker::OnRButtonDown(UINT nFlags, CPoint point)
{
	int i=GetColorIndex(point);
	if (i!=-1) m_rightClr=m_Colors[i];
	DrawColor();

	CWnd::OnRButtonDown(nFlags, point);
}
