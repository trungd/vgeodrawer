#include "StdAfx.h"
#include "VGObject.h"

CVGCardinalSpline::CVGCardinalSpline(void)
{
	m_Type=OBJ_CARDINAL_SPLINE;
}

CVGCardinalSpline::~CVGCardinalSpline(void)
{

}

void CVGCardinalSpline::Draw(Graphics* gr, CAxisInfo* m_AxisInfo, bool bTrace)
{
	if (!m_bVisible) return;
	Point* pt=new Point[m_Param.GetSize()];
	for (int i=0;i<m_Param.GetSize();i++)
		pt[i]=m_AxisInfo->ToClientPoint(((CVGPoint*)m_Param[i])->m_x,((CVGPoint*)m_Param[i])->m_y);

	Pen pen(m_Color,(REAL)m_PenWidth);
	gr->DrawCurve(&pen,pt,m_Param.GetSize());
	delete[] pt;
}