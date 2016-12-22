#include "stdafx.h"
#include "VGObject.h"

CVGBound::CVGBound()
{
	m_minWidth=20;
	m_minHeight=20;
	ResetBoundMark();
	m_ParentPanel=NULL;
}

CVGBound::~CVGBound()
{

}

void CVGBound::ResetBoundMark(bool bValue)
{
	for (int i=0;i<8;i++) m_bBoundMark[i]=bValue;
}

int CVGBound::CheckMouseOverState(Point point, CAxisInfo* m_AxisInfo, int &x, int &y)
{
	if (!m_Select) return false;

	Rect rc=GetDrawRect();

	int top=rc.Y-BOUND_BORDER_SIZE;
	int left=rc.X-BOUND_BORDER_SIZE;
	int height=rc.Height+2*BOUND_BORDER_SIZE;
	int width=rc.Width+2*BOUND_BORDER_SIZE;

	if (m_bBoundMark[0]) if (CheckMouseOverPt(point,Point(left,top),x,y)) return BOUND_STATE_TOPLEFT;
	if (m_bBoundMark[1]) if (CheckMouseOverPt(point,Point(left+width/2,top),x,y)) return BOUND_STATE_TOP;
	if (m_bBoundMark[2]) if (CheckMouseOverPt(point,Point(left+width,top),x,y)) return BOUND_STATE_TOPRIGHT;
	if (m_bBoundMark[3]) if (CheckMouseOverPt(point,Point(left,top+height/2),x,y)) return BOUND_STATE_LEFT;
	if (m_bBoundMark[4]) if (CheckMouseOverPt(point,Point(left+width,top+height/2),x,y)) return BOUND_STATE_RIGHT;
	if (m_bBoundMark[5]) if (CheckMouseOverPt(point,Point(left,top+height),x,y)) return BOUND_STATE_BOTTOMLEFT;
	if (m_bBoundMark[6]) if (CheckMouseOverPt(point,Point(left+width/2,top+height),x,y)) return BOUND_STATE_BOTTOM;
	if (m_bBoundMark[7]) if (CheckMouseOverPt(point,Point(left+width,top+height),x,y)) return BOUND_STATE_BOTTOMRIGHT;

	return 0;
}

LPWSTR CVGBound::GetCursor(int state)
{
	switch (state)
	{
	case BOUND_STATE_TOPLEFT: 
	case BOUND_STATE_BOTTOMRIGHT:
		return IDC_SIZENWSE;
	case BOUND_STATE_TOPRIGHT:
	case BOUND_STATE_BOTTOMLEFT:
		return IDC_SIZENESW;
	case BOUND_STATE_LEFT:
	case BOUND_STATE_RIGHT:
		return IDC_SIZEWE;
	case BOUND_STATE_BOTTOM:
	case BOUND_STATE_TOP:
		return IDC_SIZENS;
	}
	return IDC_ARROW;
}

void CVGBound::Resize(int state,int X,int Y)
{
	int x=X;
	int y=Y;
	int top=m_Top; int left=m_Left;
	int right=left+m_Width;
	int bottom=top+m_Height;
	if (state==BOUND_STATE_TOP || state==BOUND_STATE_TOPLEFT || state==BOUND_STATE_TOPRIGHT)
	{
		top=min(y-m_ResizeY,bottom-m_minHeight);
	}
	if (state==BOUND_STATE_BOTTOM || state==BOUND_STATE_BOTTOMLEFT || state==BOUND_STATE_BOTTOMRIGHT)
	{
		bottom=max(y-m_ResizeY,top+m_minHeight);
	}
	if (state==BOUND_STATE_LEFT || state==BOUND_STATE_BOTTOMLEFT || state==BOUND_STATE_TOPLEFT)
	{
		left=min(x-m_ResizeX,right-m_minWidth);
	}
	if (state==BOUND_STATE_RIGHT || state==BOUND_STATE_BOTTOMRIGHT || state==BOUND_STATE_TOPRIGHT)
	{
		right=max(x-m_ResizeX,left+m_minWidth);
	}
	m_Top=top; m_Left=left; m_Width=right-left; m_Height=bottom-top;
}

bool CVGBound::CheckMouseOverPt(Point mouse, Point pt, int& x, int& y)
{
	x=mouse.X-pt.X;
	y=mouse.Y-pt.Y;
	return (x>-BOUND_PT_SIZE && x<BOUND_PT_SIZE && 
		y>-BOUND_PT_SIZE && y<BOUND_PT_SIZE);
}

void CVGBound::Draw( Graphics* gr, CAxisInfo* m_AxisInfo, bool bTrace/* =FALSE */ )
{
	Rect rc=GetDrawRect();
	
	int top=rc.Y-BOUND_BORDER_SIZE;
	int left=rc.X-BOUND_BORDER_SIZE;
	int height=rc.Height+2*BOUND_BORDER_SIZE;
	int width=rc.Width+2*BOUND_BORDER_SIZE;

	if (m_Select)
	{
		Pen pen(Color::Black); float f[2]={1,4}; pen.SetDashPattern(f,2);
		gr->DrawRectangle(&pen,left,top,width,height);

		if (m_bBoundMark[0]) DrawPoint(gr,Point(left,top));
		if (m_bBoundMark[1]) DrawPoint(gr,Point(left+width/2,top));
		if (m_bBoundMark[2]) DrawPoint(gr,Point(left+width,top));
		if (m_bBoundMark[3]) DrawPoint(gr,Point(left,top+height/2));
		if (m_bBoundMark[4]) DrawPoint(gr,Point(left+width,top+height/2));
		if (m_bBoundMark[5]) DrawPoint(gr,Point(left,top+height));
		if (m_bBoundMark[6]) DrawPoint(gr,Point(left+width/2,top+height));
		if (m_bBoundMark[7]) DrawPoint(gr,Point(left+width,top+height));
	}
}

void CVGBound::DrawPoint(Graphics* gr, Point pt)
{
	SolidBrush br(Color(255,255,255));
	gr->FillRectangle(&br,pt.X-BOUND_PT_SIZE,pt.Y-BOUND_PT_SIZE,2*BOUND_PT_SIZE,2*BOUND_PT_SIZE);
	Pen pen(Color(0,0,0));
	gr->DrawRectangle(&pen,pt.X-BOUND_PT_SIZE,pt.Y-BOUND_PT_SIZE,2*BOUND_PT_SIZE,2*BOUND_PT_SIZE);
}

bool CVGBound::CheckMouseOver(Point point, CAxisInfo* m_AxisInfo)
{
	Rect rc=GetVisibleRect();

	Rect rect(rc.X-BOUND_BORDER_SIZE,rc.Y-BOUND_BORDER_SIZE,rc.Width+2*BOUND_BORDER_SIZE,rc.Height+2*BOUND_BORDER_SIZE);
	return rect.Contains(point);
}

void CVGBound::Serialize(CArchive& ar , CArray<CVGObject*>* objArr)
{
	CVGObject::Serialize(ar,objArr);
	
	if (ar.IsStoring())
	{
		ar << m_Top;
		ar << m_Left;
		ar << m_Height;
		ar << m_Width;
		ar << m_minWidth;
		ar << m_minHeight;
		for (int i=0;i<8;i++) ar << m_bBoundMark[i];
		if (m_ParentPanel==NULL) ar << -1;
		for (int i=0;i<objArr->GetSize();i++) if (objArr->GetAt(i)==m_ParentPanel) ar << i;
	}
	else
	{
		ar >> m_Top;
		ar >> m_Left;
		ar >> m_Height;
		ar >> m_Width;
		ar >> m_minWidth;
		ar >> m_minHeight;
		for (int i=0;i<8;i++) ar >> m_bBoundMark[i];
		int index;
		ar >> index;
		m_ParentPanel=(CVGPanel*)index;
	}
}

void CVGBound::Clone(CVGObject* obj)
{
	CVGObject::Clone(obj);

	CVGBound* Obj=(CVGBound*)obj;
	m_Top=Obj->m_Top;
	m_Left=Obj->m_Left;
	m_Height=Obj->m_Height;
	m_Width=Obj->m_Width;
	m_minHeight=Obj->m_minHeight;
	m_minWidth=Obj->m_minWidth;
	m_ParentPanel=Obj->m_ParentPanel;
	for (int i=0;i<8;i++) m_bBoundMark[i]=Obj->m_bBoundMark[i];
}

void CVGBound::Move(int x,int y, CPoint startPt, CAxisInfo* m_AxisInfo)
{
	m_Top+=y;
	m_Left+=x;
}

bool CVGBound::CheckObjInRect( Rect rect, CAxisInfo* m_AxisInfo )
{
	return rect.Contains(GetVisibleRect());
}

void CVGBound::SetRect(Rect rect)
{
	m_Top=rect.GetTop();
	m_Left=rect.GetLeft();
	m_Height=max(rect.Height,m_minHeight);
	m_Width=max(rect.Width,m_minWidth);
}

Rect CVGBound::GetRect()
{
	return Rect(m_Left,m_Top,m_Width,m_Height);
}

Rect CVGBound::GetDrawRect()
{
	return Rect(m_Left*nZoom/100,
		m_Top*nZoom/100,
		m_Width*nZoom/100,
		m_Height*nZoom/100);
}

Rect CVGBound::GetVisibleRect()
{
	if (m_ParentPanel==NULL)
		return GetDrawRect();
	else
	{
		Rect rectParent=m_ParentPanel->GetVisibleRect();
		Rect rectOut;
		Rect::Intersect(rectOut, rectParent, GetDrawRect());
		return rectOut;
	}
}

bool CVGBound::IsVisible()
{
	return (CVGObject::IsVisible() && (m_ParentPanel==NULL || m_ParentPanel->IsVisible()));
}