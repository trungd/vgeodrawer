#include "stdafx.h"
#include "VGObject.h"

CVGSlider::CVGSlider()
{
	m_Type=OBJ_SLIDER;
	m_NumVariable=NULL;
	m_nStart=-5;
	m_nEnd=5;

	m_bBoundMark[0]=false;
	m_bBoundMark[1]=false;
	m_bBoundMark[2]=false;
	m_bBoundMark[3]=true;
	m_bBoundMark[4]=true;
	m_bBoundMark[5]=false;
	m_bBoundMark[6]=false;
	m_bBoundMark[7]=false;

	m_Height=15;
}

CVGSlider::~CVGSlider()
{

}

void CVGSlider::Draw(Graphics* gr, CAxisInfo* m_AxisInfo, bool bTrace/* =FALSE */)
{
	CVGBound::Draw(gr,m_AxisInfo,bTrace);

	Rect rect=GetDrawRect();
	Pen pen(m_Color);
	gr->DrawLine(&pen,rect.X,rect.Y+rect.Height/2,rect.GetRight(),rect.Y+rect.Height/2);
	
	if (m_NumVariable!=NULL)
	{
		int x=(m_NumVariable->GetDoubleValue()-m_nStart)/(m_nEnd-m_nStart)*rect.Width+rect.GetLeft();
		int y=rect.Y+rect.Height/2;
		if (x>=rect.GetLeft() && x<=rect.GetRight())
		{
			SolidBrush br(m_Color);
			if (m_bMouseOver) gr->FillEllipse(&br,x-4,y-4,8,8);
			else gr->FillEllipse(&br,x-3,y-3,6,6);
		}
	}
}

bool CVGSlider::CheckMouseOver(Point point, CAxisInfo* m_AxisInfo)
{
	return (CVGBound::CheckMouseOver(point,m_AxisInfo) && !CheckMouseOverSlider(point));
}

bool CVGSlider::CheckMouseOverSlider(Point pt)
{
	if (m_NumVariable==NULL) return false;
	Rect rect=GetDrawRect();
	int y=rect.Y+rect.Height/2;
	return (pt.X>rect.X && pt.X<rect.GetRight() && pt.Y>y-5 && pt.Y<y+5);
}

void CVGSlider::OnLButton(Point pt)
{
	if (m_NumVariable!=NULL && ((CVGExpression*)m_NumVariable)->IsConstant())
	{
		delete m_NumVariable->m_Exp.m_Value;
		Rect rect=GetDrawRect();
		double vl=m_nStart+(m_nEnd-m_nStart)*(pt.X-rect.X)/rect.Width;
		if (vl>m_nEnd) vl=m_nEnd;
		if (vl<m_nStart) vl=m_nStart;
		m_NumVariable->m_Exp.m_Value=new CValueDouble(vl);
	}
}

void CVGSlider::SetRect(Rect rect)
{
	m_Top=rect.GetTop();
	m_Left=rect.GetLeft();
	m_Height=15;
	m_Width=rect.Width;
}