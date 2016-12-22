#include "stdafx.h"
#include "VGObject.h"

CVGRadioButton::CVGRadioButton()
{
	m_Type=OBJ_RADIO_BUTTON;

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

CVGRadioButton::~CVGRadioButton()
{

}

void CVGRadioButton::Draw( Graphics* gr, CAxisInfo* m_AxisInfo, bool bTrace )
{
	CVGBound::Draw(gr,m_AxisInfo,bTrace);

	Font font(AfxGetMainWnd()->GetDC()->m_hDC,&m_Font);

	m_boxSize=font.GetSize()*nZoom/100;
	Rect rect(m_Left*nZoom/100,m_Top*nZoom/100+(m_Height*nZoom/100-m_boxSize)/2,m_boxSize,m_boxSize);

	Brush* brush=GetBrush(m_bButtonMouseDown ? m_ColorMouseDown : (m_bButtonMouseOver ? m_ColorMouseOver : m_ColorNormal),rect);
	gr->FillEllipse(brush,rect);
	delete brush;

	Pen pen(m_BorderColor);
	gr->DrawEllipse(&pen,rect);

	if (m_bState)
	{
		Rect r=rect;
		r.Inflate(-r.Height/4,-r.Height/4);
		SolidBrush br(m_BorderColor);
		gr->FillEllipse(&br,r);
	}

	SolidBrush textBr(Color::Black);
	StringFormat strFormat;
	//strFormat.SetAlignment(StringAlignmentCenter);
	strFormat.SetLineAlignment(StringAlignmentCenter);

	RectF rectF(rect.GetLeft()+m_boxSize+CHECK_BOX_DISTANCE*nZoom/100,m_Top*nZoom/100,(m_Width-CHECK_BOX_DISTANCE)*nZoom/100-m_boxSize,m_Height*nZoom/100);
	//gr->DrawRectangle(&pen,rectF);
	Font* f=GetResizeFont(&font,font.GetSize()*nZoom/100);
	gr->DrawString(m_Text,-1,f,rectF,&strFormat,&textBr);
	delete f;
}

bool CVGRadioButton::CheckMouseOverButton(Point pt)
{
	Rect rect(m_Left,m_Top+(m_Height-m_boxSize)/2,m_boxSize,m_boxSize);
	return rect.Contains(pt);
}