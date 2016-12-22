#include "StdAfx.h"
#include "VGObject.h"

CVGLineBase::CVGLineBase()
{
	m_DashStyle=0;
}

CVGLineBase::~CVGLineBase()
{

}

void CVGLineBase::SetThroughTwoPoints(CVGPoint *pt1, CVGPoint *pt2)
{
	m_Mode=LINE_MODE_THROUGH_TWO_POINTS;
	m_Param.RemoveAll();
	m_Param.Add(pt1);
	m_Param.Add(pt2);
}

void CVGLineBase::DrawLine(Point pt1, Point pt2, Graphics* gr, bool bTrace)
{
	Pen pen(m_Color,(REAL)m_PenWidth+1);
	GetPen(m_DashStyle,&pen);
	
	if ((m_Select || m_HighLight) && (!bTrace))
	{
		Pen pen2(Color(100,m_Color.GetRed(),m_Color.GetGreen(),m_Color.GetBlue()),m_PenWidth+1+2);
		gr->DrawLine(&pen2,pt1,pt2);
	}
	gr->DrawLine(&pen,pt1,pt2);
}

void CVGLineBase::GetScreenStartEndPoint(Point& pt1, Point& pt2, CAxisInfo* m_AxisInfo)
{

}

bool CVGLineBase::CheckPtIn( double x, double y )
{
	return TRUE;
}

void CVGLineBase::Serialize( CArchive& ar, CArray<CVGObject*>* objArr )
{
	CVGGeoObject::Serialize(ar,objArr);

	if (ar.IsStoring())
	{
		ar << m_PenWidth;
		ar << m_DashStyle;
	}
	else
	{
		ar >> m_PenWidth;
		ar >> m_DashStyle;
	}
}

void CVGLineBase::Clone(CVGObject* obj)
{
	CVGGeoObject::Clone(obj);
	CVGLineBase* l=(CVGLineBase*)obj;
	m_PenWidth=l->m_PenWidth;
	m_DashStyle=l->m_DashStyle;
}