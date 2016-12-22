// IconEditor.cpp : implementation file

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "IconEditor.h"
#include "resource.h"

#include "appfunc.h"


// CIconEditor

IMPLEMENT_DYNAMIC(CIconEditor, CWnd)

CIconEditor::CIconEditor()
{
	RegisterWndClass();
	m_bmp=new Bitmap(32,32,PixelFormat32bppRGB);
	m_tmpBitmap=new Bitmap(32,32,PixelFormat32bppRGB);
	ClearIcon();
	m_bMouseMove=FALSE;
}

CIconEditor::~CIconEditor()
{
	delete m_bmp;
	delete m_tmpBitmap;
}

BOOL CIconEditor::RegisterWndClass()
{
	WNDCLASS windowclass;
	HINSTANCE hInst = AfxGetInstanceHandle();

	//Check weather the class is registerd already

	if (!(::GetClassInfo(hInst, L"IconEditor", &windowclass)))
	{
		//If not then we have to register the new class

		windowclass.style = CS_DBLCLKS;// | CS_HREDRAW | CS_VREDRAW;

		windowclass.lpfnWndProc = ::DefWindowProc;
		windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
		windowclass.hInstance = hInst;
		windowclass.hIcon = NULL;
		windowclass.hCursor = LoadCursor(hInst,MAKEINTRESOURCE(IDC_IBEAM));
		windowclass.hbrBackground = ::GetSysColorBrush(COLOR_3DFACE);
		windowclass.lpszMenuName = NULL;
		windowclass.lpszClassName = L"IconEditor";

		if (!AfxRegisterClass(&windowclass))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}


BEGIN_MESSAGE_MAP(CIconEditor, CWnd)
	ON_WM_PAINT()
	ON_WM_DRAWITEM()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CIconEditor message handlers



void CIconEditor::OnPaint()
{
	CWnd::OnPaint();
	Graphics graphic(this->m_hWnd);
	
	CRect rect;
	GetClientRect(&rect);
	Bitmap memBmp(rect.Width(),rect.Height(),PixelFormat32bppARGB);
	Graphics gr(&memBmp);
	
	//SolidBrush br(Color(200,200,200));
	HatchBrush br(HatchStyleLargeCheckerBoard,Color::White,Color(230,230,230));
	

	gr.FillRectangle(&br,0,0,PIXEL_SIZE*32,PIXEL_SIZE*32);
	Color clr;
	for (int i=0;i<=31;i++)
		for (int j=0;j<=31;j++)
		{
			m_tmpBitmap->GetPixel(i,j,&clr);
			SetPixel(i,j,&gr,clr);
		}

	Pen pen(Color(192,192,192));
	for (int i=0;i<=32;i++)
	{
		gr.DrawLine(&pen,Point(i*PIXEL_SIZE,0),Point(i*PIXEL_SIZE,32*PIXEL_SIZE));
		gr.DrawLine(&pen,Point(0,i*PIXEL_SIZE),Point(32*PIXEL_SIZE,i*PIXEL_SIZE));
	}

	graphic.DrawImage(&memBmp,0,0,memBmp.GetWidth(),memBmp.GetHeight());
	GetParent()->SendMessage(WM_ICONCHANGE);
}

void CIconEditor::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

int CIconEditor::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CIconEditor::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	Point pt=GetPixel(point);
	m_prevPoint=pt;
	if (m_Mode==MODE_PEN)
	{
		m_bmp->SetPixel(pt.X,pt.Y,*m_leftClr);
	}
	else if (m_Mode==MODE_LINE)
	{
		
	}
	else if (m_Mode==MODE_RECTANGLE)
	{
	}
	else if (m_Mode==MODE_COLORSEL)
	{
		m_bmp->GetPixel(pt.X,pt.Y,m_leftClr);
		GetParent()->SendMessage(WM_REDRAWCOLORPICKER);
	}
	else if (m_Mode==MODE_COLOR)
	{
		FloodFill(m_bmp,pt.X,pt.Y,*m_leftClr);
	}
	OnPaint();

	CWnd::OnLButtonDown(nFlags, point);
}

void CIconEditor::SetPixel(int x, int y, Graphics* gr, Color color)
{
	SolidBrush br(color);
	
	gr->FillRectangle(&br,x*PIXEL_SIZE,y*PIXEL_SIZE,PIXEL_SIZE,PIXEL_SIZE);
}

Point CIconEditor::GetPixel(CPoint pt)
{
	return Point(pt.x/PIXEL_SIZE,pt.y/PIXEL_SIZE);
}

void CIconEditor::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bMouseMove)
	{
		m_bMouseMove=TRUE;
		SetTimer(ID_TIMER,100,NULL);
	}

	if ((nFlags & MK_LBUTTON)==MK_LBUTTON && GetCapture()==this)
	{
		Point pt=GetPixel(point);
		Pen pen(*m_leftClr);
		if (m_Mode==MODE_PEN)
		{
			Graphics gr(m_bmp);
			gr.DrawLine(&pen,m_prevPoint,pt);
			m_prevPoint=pt;
			CopyBmpToTemp();
			OnPaint();
			return;
		}

		CopyBmpToTemp();
		Graphics gr(m_tmpBitmap);
		if (m_bAntiAlias) gr.SetSmoothingMode(SmoothingModeAntiAlias);
		if (m_Mode==MODE_LINE)
		{
			gr.DrawLine(&pen,m_prevPoint,pt);
		}
		else if (m_Mode==MODE_RECTANGLE)
		{
			gr.DrawRectangle(&pen,RectFromTwoPoints(pt,m_prevPoint));
		}
		else if (m_Mode==MODE_ELLIPSE)
		{
			gr.DrawEllipse(&pen,RectFromTwoPoints(pt,m_prevPoint));
		}
		else return;

		OnPaint();
	}
	if (m_Mode==MODE_POINT)
	{
		Point pt=GetPixel(point);
		CopyBmpToTemp();
		Graphics gr(m_tmpBitmap);
		if (m_bAntiAlias) gr.SetSmoothingMode(SmoothingModeAntiAlias);
		SolidBrush br(*m_leftClr);
		gr.FillEllipse(&br,pt.X-2,pt.Y-2,4,4);
		OnPaint();
	}

	CWnd::OnMouseMove(nFlags, point);
}

BOOL CIconEditor::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	//return (HCURSOR)LoadCursor(NULL,MAKEINTRESOURCE(IDC_CURSOR_PEN));
	//HCURSOR lhCursor=LoadCursor(0,MAKEINTRESOURCE(IDC_CURSOR_PEN));
	//SetCursor(lhCursor);
	return TRUE;
	//return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CIconEditor::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (GetCapture()==this) 
	{
		ReleaseCapture();
		Point pt=GetPixel(point);
		Pen pen(*m_leftClr);
		Graphics gr(m_bmp);
		if (m_bAntiAlias) gr.SetSmoothingMode(SmoothingModeAntiAlias);
		if (m_Mode==MODE_LINE)
		{
			gr.DrawLine(&pen,m_prevPoint,pt);
		}
		else if (m_Mode==MODE_RECTANGLE)
		{
			gr.DrawRectangle(&pen,RectFromTwoPoints(m_prevPoint,pt));
		}
		else if (m_Mode==MODE_ELLIPSE)
		{
			gr.DrawEllipse(&pen,RectFromTwoPoints(m_prevPoint,pt));
		}
		else if (m_Mode==MODE_POINT)
		{
			SolidBrush br(*m_leftClr);
			gr.FillEllipse(&br,pt.X-2,pt.Y-2,4,4);
		}
		CopyBmpToTemp();
		OnPaint();
	}
	CWnd::OnLButtonUp(nFlags, point);
}

void CIconEditor::SetBitmap(Bitmap* bmp)
{
	if (m_bmp==NULL) 
	{
		m_bmp=new Bitmap(32,32,PixelFormat32bppARGB);
		m_tmpBitmap=new Bitmap(32,32,PixelFormat32bppARGB);
	}
	Graphics gr(m_bmp);
	gr.DrawImage(bmp,0,0,32,32);
	CopyBmpToTemp();
}

void CIconEditor::CopyBmpToTemp()
{
	Graphics gr(m_tmpBitmap);
	gr.Clear(Color::White);
	gr.DrawImage(m_bmp,0,0,32,32);
}

void CIconEditor::CopyTempToBmp()
{
	Graphics gr(m_bmp);
	gr.Clear(Color::White);
	gr.DrawImage(m_tmpBitmap,0,0,32,32);
}

Rect CIconEditor::RectFromTwoPoints(Point pt1, Point pt2)
{
	return Rect(min(pt1.X,pt2.X),min(pt1.Y,pt2.Y),
		abs(pt1.X-pt2.X),abs(pt1.Y-pt2.Y));
}

void CIconEditor::ClearIcon()
{
	Graphics gr1(m_tmpBitmap);
	gr1.Clear(Color::White);
	Graphics gr2(m_bmp);
	gr2.Clear(Color::White);
}
void CIconEditor::OnTimer(UINT_PTR nIDEvent)
{
	CPoint p(GetMessagePos());
	ScreenToClient(&p);

	CRect rect;
	GetClientRect(rect);

	if (!rect.PtInRect(p))
	{
		m_bMouseMove = FALSE;
		KillTimer(ID_TIMER);
		CopyBmpToTemp();
		OnPaint();
	}

	CWnd::OnTimer(nIDEvent);
}
