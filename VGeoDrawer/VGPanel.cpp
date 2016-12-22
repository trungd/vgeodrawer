#include "stdafx.h"
#include "VGObject.h"

CVGPanel::CVGPanel()
{
	m_Type=OBJ_PANEL;
	m_Color=Color::LightGray;
	m_Dock=PANEL_DOCK_NONE;
	m_dHeight=150;
	m_dWidth=150;
	m_BorderColor=Color::Gray;

	m_gradientStyle.m_Color1=Color(255,255,255);
	m_gradientStyle.m_Color2=Color(212,212,212);
	m_gradientStyle.m_Mode=LinearGradientModeVertical;
	m_gradientTitleStyle.m_Color1=Color(255,255,255);
	m_gradientTitleStyle.m_Color2=Color(234,234,234);
	m_gradientTitleStyle.m_Mode=LinearGradientModeVertical;
	m_BorderColor=Color(128,128,128);

	m_Font.lfCharSet=DEFAULT_CHARSET;
	m_Font.lfStrikeOut=FALSE;
	m_Font.lfItalic=FALSE;
	m_Font.lfUnderline=FALSE;
	m_Font.lfWeight=FW_BOLD;
	wcsncpy(m_Font.lfFaceName, _T("Tahoma"), LF_FACESIZE);
	m_Font.lfHeight=-12;

	m_Color=Color(100,100,100);

	m_Text=L"Panel";
	m_nTitleHeight=25;
	m_bTitle=true;

	m_minHeight=80;
	m_minWidth=80;

	m_nOpacity=100;
}

CVGPanel::~CVGPanel()
{

}

void CVGPanel::SetOpacity()
{
	m_nOpacity=m_nOpacity>=0 ? (m_nOpacity<=100 ? m_nOpacity : 100) : 0;

	SetAlpha(m_gradientStyle.m_Color1,m_nOpacity*255/100);
	SetAlpha(m_gradientStyle.m_Color2,m_nOpacity*255/100);
	SetAlpha(m_gradientTitleStyle.m_Color1,m_nOpacity*255/100);
	SetAlpha(m_gradientTitleStyle.m_Color2,m_nOpacity*255/100);
}

void CVGPanel::Draw(Graphics* gr, CAxisInfo* m_AxisInfo, bool bTrace)
{
	CVGBound::Draw(gr,m_AxisInfo,bTrace);

	Rect rect=GetDrawRect();
	Brush* br=GetBrush(m_gradientStyle,rect);
	//LinearGradientBrush br(rect,m_Color,Color::White,LinearGradientModeVertical);
	gr->FillRectangle(br,rect);

	Pen pen(m_BorderColor);
	gr->DrawRectangle(&pen,rect);

	if (m_bTitle)
	{
		Rect rectTitle=Rect(rect.X,rect.Y,rect.Width,m_nTitleHeight);
		Brush* brTitle=GetBrush(m_gradientTitleStyle,rectTitle);
		gr->FillRectangle(brTitle,rectTitle);
		gr->DrawRectangle(&pen,rectTitle);

		Font font(AfxGetMainWnd()->GetDC()->m_hDC,&m_Font);
		SolidBrush textBr(m_Color);
		RectF rcf=RectF(5+rectTitle.X,rectTitle.Y,rectTitle.Width,rectTitle.Height);
		StringFormat stringFormat;
		stringFormat.SetLineAlignment(StringAlignmentCenter);
		gr->DrawString(m_Text,-1,&font, rcf, &stringFormat, &textBr);
	}

	delete br;
}

void CVGPanel::RefreshDocking(CAxisInfo* m_AxisInfo)
{
	if (m_Dock==PANEL_DOCK_NONE)
	{
		m_Top=m_rcPos.GetTop();
		m_Left=m_rcPos.GetLeft();
		m_Height=m_rcPos.Height;
		m_Width=m_rcPos.Width;
		ResetBoundMark(true);
	}
	if (m_Dock==PANEL_DOCK_TOP)
	{
		m_Top=0; m_Left=0; 
		m_Width=drPadSize.Width;
		m_Height=m_dHeight;
		ResetBoundMark(false);
		m_bBoundMark[6]=true;
	}
	if (m_Dock==PANEL_DOCK_BOTTOM)
	{
		m_Top=drPadSize.Height-m_dHeight; m_Left=0;
		m_Width=drPadSize.Width;
		m_Height=m_dHeight;
		ResetBoundMark(false);
		m_bBoundMark[1]=true;
	}
	if (m_Dock==PANEL_DOCK_LEFT)
	{
		m_Top=0; m_Left=0;
		m_Width=m_dWidth;
		m_Height=drPadSize.Height;
		ResetBoundMark(false);
		m_bBoundMark[4]=true;
	}
	if (m_Dock==PANEL_DOCK_RIGHT)
	{
		m_Top=0; m_Left=drPadSize.Width-m_dWidth;
		m_Width=m_dWidth;
		m_Height=drPadSize.Height;
		ResetBoundMark(false);
		m_bBoundMark[3]=true;
	}
}

void CVGPanel::Resize(int state,int X,int Y)
{
	int top=m_Top; int left=m_Left;
	CVGBound::Resize(state,X,Y);
	for (int i=0;i<m_objChild.GetSize();i++)
		if (m_objChild[i]!=NULL) m_objChild[i]->Move(m_Left-left,m_Top-top,CPoint(0,0),NULL);
	if (m_Dock==PANEL_DOCK_TOP  || m_Dock==PANEL_DOCK_BOTTOM) m_dHeight=m_Height;
	if (m_Dock==PANEL_DOCK_LEFT || m_Dock==PANEL_DOCK_RIGHT) m_dWidth=m_Width;
	if (m_Dock==PANEL_DOCK_NONE) 
		m_rcPos=Rect(m_Left,m_Top,m_Width,m_Height);
}

void CVGPanel::Move(int x,int y, CPoint startPt, CAxisInfo* m_AxisInfo)
{
	if (m_Dock==PANEL_DOCK_NONE) 
	{
		CVGBound::Move(x,y,startPt,m_AxisInfo);
		m_rcPos=Rect(m_Left,m_Top,m_Width,m_Height);
		for (int i=0;i<m_objChild.GetSize();i++)
			m_objChild[i]->Move(x,y,startPt,m_AxisInfo);
	}
}

void CVGPanel::Clone(CVGObject* obj)
{
	CVGBound::Clone(obj);

	CVGPanel* Obj=(CVGPanel*)obj;
	m_Dock=Obj->m_Dock;
	m_dWidth=Obj->m_dWidth;
	m_dHeight=Obj->m_dHeight;
	m_nOpacity=Obj->m_nOpacity;
	m_bTitle=Obj->m_bTitle;
	m_Text=Obj->m_Text;
	m_nTitleHeight=Obj->m_nTitleHeight;

	m_objChild.RemoveAll();
	for (int i=0;i<Obj->m_objChild.GetSize();i++)
		m_objChild.Add(Obj->m_objChild[i]);
}

void CVGPanel::Serialize(CArchive& ar , CArray<CVGObject*>* objArr)
{
	CVGBound::Serialize(ar,objArr);

	m_gradientStyle.Serialize(ar);
	m_gradientTitleStyle.Serialize(ar);
	SerializeColor(m_BorderColor,ar);
	SerializeRect(m_rcPos,ar);
	SerializeFont(m_Font,ar);

	if (ar.IsStoring())
	{
		ar << m_Dock;
		ar << m_dWidth;
		ar << m_dHeight;
		ar << m_nOpacity;
		ar << m_bTitle;
		ar << m_Text;
		ar << m_nTitleHeight;

		ar << m_objChild.GetSize();
		for (int i=0;i<m_objChild.GetSize();i++)
		{
			for (int j=0;j<objArr->GetSize();j++) 
				if (objArr->GetAt(j)==m_objChild[i]) ar << j;
		}
	}
	else
	{
		ar >> m_Dock;
		ar >> m_dWidth;
		ar >> m_dHeight;
		ar >> m_nOpacity;
		ar >> m_bTitle;
		ar >> m_Text;
		ar >> m_nTitleHeight;

		int count;
		ar >> count;
		for (int i=0;i<count;i++)
		{
			int index;
			ar >> index;
			m_objChild.Add((CVGBound*)index);
		}
	}
}