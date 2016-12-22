#include "stdafx.h"
#include "VGObject.h"

CVGSegment::CVGSegment()
{
	m_DashStyle=0;
	m_PenWidth=1;
}

CVGSegment::~CVGSegment()
{

}

void CVGSegment::Draw(Graphics *gr, CAxisInfo* m_AxisInfo, bool bTrace)
{
	if (!m_bVisible || !m_bAvailable || m_bTemp) return;
	Point pt1;	Point pt2;

	CVGPoint* m_Point1=(CVGPoint*)m_Param[0];
	CVGPoint* m_Point2=(CVGPoint*)m_Param[1];
	pt1=m_AxisInfo->ToClientPoint(m_Point1->m_x,m_Point1->m_y);
	pt2=m_AxisInfo->ToClientPoint(m_Point2->m_x,m_Point2->m_y);

	Pen pen(m_Color,(REAL)m_PenWidth);
	GetPen(m_DashStyle,&pen);

	if ((m_Select || m_HighLight) && (!bTrace))
	{
		Pen pen2(Color(100,m_Color.GetRed(),m_Color.GetGreen(),m_Color.GetBlue()),m_PenWidth+2);
		gr->DrawLine(&pen2,pt1,pt2);
	}
	gr->DrawLine(&pen,pt1,pt2);

	/*DrawLine(pt1,pt2,gr,bTrace);*/
}

bool CVGSegment::CheckMouseOver(Point point, CAxisInfo* m_AxisInfo)
{
	if (!m_bVisible) return FALSE;
	if (m_Mode==LINE_MODE_THROUGH_TWO_POINTS)
	{
		Point pt1=m_AxisInfo->ToClientPoint(((CVGPoint*)m_Param[0])->m_x,((CVGPoint*)m_Param[0])->m_y);
		Point pt2=m_AxisInfo->ToClientPoint(((CVGPoint*)m_Param[1])->m_x,((CVGPoint*)m_Param[1])->m_y);
		if (point.X>=min(pt1.X,pt2.X)-6 && point.X<=max(pt1.X,pt2.X)+6 && 
			point.Y>=min(pt1.Y,pt2.Y)-6 && point.Y<=max(pt1.Y,pt2.Y)+6)
		{
			pt1.Y=-pt1.Y; pt2.Y=-pt2.Y;
			Point newPt=Point(point.X,-point.Y);
			double a,b,c;
			Math::LineThroughTwoPoints(pt1.X,pt1.Y,pt2.X,pt2.Y,a,b,c);
			if (Math::GetDistance(newPt.X,newPt.Y,a,b,c)<6) return TRUE;
		}
	}
	return FALSE;
}

void CVGSegment::Move(int x,int y, CPoint startPt, CAxisInfo* m_AxisInfo)
{
	if (m_bFixed) return;
	if (m_Mode==LINE_MODE_THROUGH_TWO_POINTS)
	{
		CVGPoint* m_Point1=(CVGPoint*)m_Param[0];
		CVGPoint* m_Point2=(CVGPoint*)m_Param[1];
		m_Point1->Move(x,y,startPt,m_AxisInfo);
		m_Point2->Move(x,y,startPt,m_AxisInfo);
	}
}

void CVGSegment::GetABC(double& A, double& B, double& C)
{
	CVGPoint* pt1=(CVGPoint*)m_Param[0];
	CVGPoint* pt2=(CVGPoint*)m_Param[1];
	Math::LineThroughTwoPoints(pt1->m_x,pt1->m_y,pt2->m_x,pt2->m_y,A,B,C);
}

bool CVGSegment::CheckPtIn(double x, double y)
{
	CVGPoint* pt1=(CVGPoint*)m_Param[0];
	CVGPoint* pt2=(CVGPoint*)m_Param[1];
	if (Math::Equal(pt1->m_x,pt2->m_x))
	{
		if ((y<pt1->m_y && y>pt2->m_y) || (y>pt1->m_y && y<pt2->m_y)) return TRUE;
		else return FALSE;
	}
	if ((x<pt1->m_x && x>pt2->m_x) || (x>pt1->m_x && x<pt2->m_x))
		return TRUE;
	else return FALSE;
}

void CVGSegment::GetScreenStartEndPoint( Point& pt1, Point& pt2, CAxisInfo* m_AxisInfo )
{
	pt1=m_AxisInfo->ToClientPoint(((CVGPoint*)m_Param[0])->m_x, ((CVGPoint*)m_Param[0])->m_y);
	pt2=m_AxisInfo->ToClientPoint(((CVGPoint*)m_Param[1])->m_x, ((CVGPoint*)m_Param[1])->m_y);
}

void CVGSegment::Serialize( CArchive& ar, CArray<CVGObject*>* objArr )
{
	CVGLineBase::Serialize(ar,objArr);

}

bool CVGSegment::CheckObjInRect(Rect rect, CAxisInfo* m_AxisInfo)
{
	return ((CVGPoint*)m_Param[0])->CheckObjInRect(rect,m_AxisInfo) && 
		((CVGPoint*)m_Param[1])->CheckObjInRect(rect,m_AxisInfo);
}

CString CVGSegment::GetValue(bool bName)
{
	CString str;
	if (bName) str=m_Name+L" = ";
	str=str+Math::DoubleToString(Math::GetDistance(((CVGPoint*)m_Param[0])->m_x,((CVGPoint*)m_Param[0])->m_y
		,((CVGPoint*)m_Param[1])->m_x,((CVGPoint*)m_Param[1])->m_y));
	return str;
}

// void CVGSegment::Calc(CAxisInfo* m_AxisInfo)
//{
//	if (m_bCalc || !CanCalc()) return;
//	CheckAvailable();
//	m_bCalc=TRUE;
//}