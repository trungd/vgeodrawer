#include "stdafx.h"
#include "VGObject.h"

CVGRay::CVGRay()
{

}

CVGRay::~CVGRay()
{

}

void CVGRay::Draw(Graphics *gr, CAxisInfo* m_AxisInfo, bool bTrace)
{
	if (!m_bVisible) return;
	Point pt1;	Point pt2;

	double x,y;
	bool bflag=FALSE;
	Point pt;
	x=m_AxisInfo->GetMinX(); y=(-m_c-m_a*x)/m_b;
	pt=m_AxisInfo->ToClientPoint(x,y);
	if (pt.Y>0 && pt.Y<=drPadSize.Height)
	{ pt1=pt ;bflag=TRUE;	}

	y=m_AxisInfo->GetMaxY();
	pt=m_AxisInfo->ToClientPoint((-m_c-m_b*y)/m_a,y);
	if (pt.X>0 && pt.X<=drPadSize.Width)
	{
		if (!bflag) { pt1=pt; bflag=TRUE; }
		else { pt2=pt; }
	}

	x=m_AxisInfo->GetMaxX();
	y=(-m_c-m_a*x)/m_b;
	pt=m_AxisInfo->ToClientPoint(x,y);
	if (pt.Y>0 && pt.Y<=drPadSize.Height)
	{
		if (!bflag) { pt1=pt; bflag=TRUE; }
		else { pt2=pt; }
	}

	y=m_AxisInfo->GetMinY();
	pt=m_AxisInfo->ToClientPoint((-m_c-m_b*y)/m_a,y);
	if (pt.X>0 && pt.X<=drPadSize.Width)
	{
		if (!bflag) { pt1=pt; bflag=TRUE; }
		else { pt2=pt; }
	}
	
	CVGPoint* m_Point1=(CVGPoint*)m_Param[0];
	CVGPoint* m_Point2=(CVGPoint*)m_Param[1];
	Point p1=m_AxisInfo->ToClientPoint(m_Point1->m_x,m_Point1->m_y);
	Point p2=m_AxisInfo->ToClientPoint(m_Point2->m_x,m_Point2->m_y);
	if ((pt1.X-p1.X)*(p2.X-p1.X)>0 || (pt1.Y-p1.Y)*(p2.Y-p1.Y)>0)
		DrawLine(pt1,p1,gr,bTrace);
	else
		DrawLine(pt2,p1,gr,bTrace);
}

bool CVGRay::CheckMouseOver(Point point, CAxisInfo* m_AxisInfo)
{
	if (!m_bVisible) return FALSE;
	PointD pt=m_AxisInfo->ToAxisPoint(point); // Toa do chuot tren truc
	double y=(-m_c-m_a*pt.X)/m_b;
	double x=(-m_c-m_b*pt.Y)/m_a;
	Point pt1=m_AxisInfo->ToClientPoint(x,pt.Y);
	Point pt2=m_AxisInfo->ToClientPoint(pt.X,y);
	if ((point.X>pt1.X-8 && point.X<pt1.X+8)||(point.Y>pt2.Y-8 && point.Y<pt2.Y+8)) 
	{
		Point p1=m_AxisInfo->ToClientPoint(((CVGPoint*)m_Param[0])->m_x,((CVGPoint*)m_Param[0])->m_y);
		Point p2=m_AxisInfo->ToClientPoint(((CVGPoint*)m_Param[1])->m_x,((CVGPoint*)m_Param[1])->m_y);
			
		if ((p2.Y-p1.Y)*(pt1.Y-p1.Y)>0 || (p2.Y-p1.Y)*(pt2.Y-p1.Y)>0) return TRUE;
	}
	return FALSE;
}

bool CVGRay::CheckPtIn(double x, double y)
{
	CVGPoint* m_Point1=(CVGPoint*)m_Param[0];
	CVGPoint* m_Point2=(CVGPoint*)m_Param[1];
	bool x1=m_Point2->m_x>m_Point1->m_x;
	bool y1=m_Point2->m_y>m_Point1->m_y;
	bool x2=x>m_Point1->m_x;
	bool y2=y>m_Point1->m_y;
	if (x1==x2 && y1==y2) return TRUE;
	else return FALSE;
}

void CVGRay::Serialize( CArchive& ar, CArray<CVGObject*>* objArr )
{
	CVGLine::Serialize(ar,objArr);

}