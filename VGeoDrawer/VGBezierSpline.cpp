#include "StdAfx.h"
#include "VGObject.h"

CVGBezierSpline::CVGBezierSpline(void)
{
	m_Type=OBJ_BEZIER_SPLINE;
}

CVGBezierSpline::~CVGBezierSpline(void)
{

}

void CVGBezierSpline::Draw(Graphics* gr, CAxisInfo* m_AxisInfo, bool bTrace)
{
	if (!m_bVisible) return;
	Point* pt=new Point[4];
	for (int i=0;i<4;i++)
		pt[i]=m_AxisInfo->ToClientPoint(((CVGPoint*)m_Param[i])->m_x,((CVGPoint*)m_Param[i])->m_y);

	Pen pen(m_Color,(REAL)m_PenWidth);
	gr->DrawBezier(&pen,pt[0],pt[1],pt[2],pt[3]);
	delete[] pt;
}