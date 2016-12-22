#include "stdafx.h"
#include "VGObject.h"

CVGAngle::CVGAngle()
{
	m_Size=3;
	m_ArcCount=0;
}

CVGAngle::~CVGAngle()
{

}

void CVGAngle::Draw( Graphics* gr, CAxisInfo* m_AxisInfo, bool bTrace/*=FALSE*/ )
{
	if (!m_bVisible || !m_bAvailable || m_bTemp) return;
	if (m_Mode==ANGLE_MODE_POINT_POINT_POINT)
	{
		CVGPoint* pt2=(CVGPoint*)m_Param[1];
		Point p2=m_AxisInfo->ToClientPoint(pt2->m_x,pt2->m_y);
		Pen pen(m_Color,(m_HighLight || m_Select) ? 2 : 1);
		int size=5+4*m_Size;
		size*=nZoom/100;
		for (int i=0;i<m_ArcCount+1;i++)
		{
			gr->DrawArc(&pen,Rect(p2.X-size,p2.Y-size,2*size,2*size),start/pi*180,sweep/pi*180);
			size+=4*nZoom/100;
		}
	}
// 	else if (m_Mode==ANGLE_MODE_LINE_LINE)
// 	{
// 		CVGLine* l1=(CVGLine*)m_Param[0];
// 		CVGLine* l2=(CVGLine*)m_Param[1];
// 		double x,y;
// 		Math::GetIntersectionLineLine(l1->m_a,l1->m_b,l1->m_c,l2->m_a,l2->m_b,l2->m_c,x,y);
// 		Point pt=m_AxisInfo->ToClientPoint(x,y);
// 
// 		double ang1=0;
// 		double ang2=(Math::Equal(l1->m_a,0) ? 0 : atan(-l1->m_b/l1->m_a));
// 		double angle1=ang1-ang2;
// 
// 		ang1=(Math::Equal(l1->m_a,0) ? 0 : atan(-l1->m_b/l1->m_a));
// 		ang2=(Math::Equal(l2->m_a,0) ? 0 : atan(-l2->m_b/l2->m_a));
// 		double angle2=ang1-ang2;
// 
// 		Pen pen(m_Color,(m_HighLight || m_Select) ? 2 : 1);
// 		int size=5+4*m_Size;
// 		gr->DrawArc(&pen,Rect(pt.X-size,pt.Y-size,2*size,2*size),angle1/pi*180,angle2/pi*180);
// 		//gr->DrawArc(&pen,Rect(pt.X-size,pt.Y-size,2*size,2*size),-10,angle2/pi*180);
// 	}
}

bool CVGAngle::CheckMouseOver(Point point, CAxisInfo* m_AxisInfo)
{
	if (m_Mode==ANGLE_MODE_POINT_POINT_POINT)
	{
		CVGPoint* pt1=(CVGPoint*)m_Param[0];
		CVGPoint* pt2=(CVGPoint*)m_Param[1];
		CVGPoint* pt3=(CVGPoint*)m_Param[2];
		Point p2=m_AxisInfo->ToClientPoint(pt2->m_x,pt2->m_y);

		int size=5+4*m_Size+(m_ArcCount-1)*4;
		double x3=point.X-p2.X;
		double y3=point.Y-p2.Y;
		if (pow(x3,(int)2)+pow(y3,(int)2)>pow((double)size,(int)2)) return FALSE;

		double angTmp=-(y3>0 ? -1 : 1)*Math::Angle(x3,y3,1,0);
		double swp=angTmp-start;//Math::Angle(x2,y2,x1,y1);
		if (swp>pi) swp=-2*pi+swp;
		if (swp<-pi) swp=2*pi+swp;
		return ((swp>0 && swp<sweep) || (swp<0 && swp>sweep));
	}
	return false;
}

void CVGAngle::Calc(CAxisInfo* m_AxisInfo)
{
	if (m_bCalc || !CanCalc()) return;
	CheckAvailable();
	if (!m_bAvailable) { m_bCalc=TRUE; return; }

	m_bCalc=TRUE;
	if (m_Mode==ANGLE_MODE_POINT_POINT_POINT)
	{
		CVGPoint* pt1=(CVGPoint*)m_Param[0];
		CVGPoint* pt2=(CVGPoint*)m_Param[1];
		CVGPoint* pt3=(CVGPoint*)m_Param[2];
		Point p2=m_AxisInfo->ToClientPoint(pt2->m_x,pt2->m_y);

		double x1=pt1->m_x-pt2->m_x;
		double y1=pt1->m_y-pt2->m_y;
		double x2=pt3->m_x-pt2->m_x;
		double y2=pt3->m_y-pt2->m_y;
		start=(y1>0 ? -1 : 1)*Math::Angle(x1,y1,1,0);
		double angTmp=(y2>0 ? -1 : 1)*Math::Angle(x2,y2,1,0);
		sweep=angTmp-start;//Math::Angle(x2,y2,x1,y1);
		if (sweep>pi) sweep=-2*pi+sweep;
		if (sweep<-pi) sweep=2*pi+sweep;
	}
}

void CVGAngle::Serialize(CArchive& ar , CArray<CVGObject*>* objArr)
{
	CVGObject::Serialize(ar,objArr);

	if (ar.IsStoring())
	{
		ar << m_Size;
		ar << m_ArcCount;
	}
	else
	{
		ar >> m_Size;
		ar >> m_ArcCount;
	}
}