#include "stdafx.h"
#include "VGObject.h"

CVGCheckBox::CVGCheckBox()
{
	m_Type=OBJ_CHECKBOX;

	m_Font.lfCharSet=DEFAULT_CHARSET;
	m_Font.lfStrikeOut=FALSE;
	m_Font.lfItalic=FALSE;
	m_Font.lfUnderline=FALSE;
	m_Font.lfWeight=FW_NORMAL;
	wcsncpy(m_Font.lfFaceName, _T("Tahoma"), LF_FACESIZE);
	m_Font.lfHeight=-12;

	//m_Color=Color::White;
	//m_ColorMouseOver=Color::LightGray;
	//m_ColorMouseDown=Color::Gray;
	//m_BorderColor=Color::Black;
}

CVGCheckBox::~CVGCheckBox()
{
	
}

void CVGCheckBox::Draw( Graphics* gr, CAxisInfo* m_AxisInfo, bool bTrace )
{
	if (!IsVisible()) return;
	
	CVGBound::Draw(gr,m_AxisInfo,bTrace);

	Font font(AfxGetMainWnd()->GetDC()->m_hDC,&m_Font);
	
	m_boxSize=font.GetSize();
	Rect rect(m_Left*nZoom/100,(m_Top+(m_Height-m_boxSize)/2)*nZoom/100,m_boxSize*nZoom/100,m_boxSize*nZoom/100);

	Brush* brush=GetBrush(m_bButtonMouseDown ? m_ColorMouseDown : (m_bButtonMouseOver ? m_ColorMouseOver : m_ColorNormal),rect);
	gr->FillRectangle(brush,rect);
	delete brush;
	
	Pen pen(m_BorderColor);
	gr->DrawRectangle(&pen,rect);

	if (m_bState)
	{
		gr->DrawLine(&pen,Point(rect.GetLeft()+2,rect.GetTop()+rect.Height/2),
			Point(rect.GetLeft()+rect.Width/2,rect.GetTop()+rect.Height-2));
		gr->DrawLine(&pen,Point(rect.GetLeft()+rect.Width/2,rect.GetTop()+rect.Height-2),
			Point(rect.GetLeft()+rect.Width-2,rect.GetTop()+2));
	}

	SolidBrush textBr(Color::Black);
	StringFormat strFormat;
	//strFormat.SetAlignment(StringAlignmentCenter);
	strFormat.SetLineAlignment(StringAlignmentCenter);

	RectF rectF(rect.GetLeft()+(m_boxSize+CHECK_BOX_DISTANCE)*nZoom/100,m_Top*nZoom/100,(m_Width-CHECK_BOX_DISTANCE-m_boxSize)*nZoom/100,m_Height*nZoom/100);
	//gr->DrawRectangle(&pen,rectF);
	Font* f=GetResizeFont(&font,font.GetSize()*nZoom/100);
	gr->DrawString(m_Text,-1,f,rectF,&strFormat,&textBr);
	delete f;
}

bool CVGCheckBox::CheckMouseOverButton(Point pt)
{
	Rect rect(m_Left,m_Top+(m_Height-m_boxSize)/2,m_boxSize,m_boxSize);
	return rect.Contains(pt);
}