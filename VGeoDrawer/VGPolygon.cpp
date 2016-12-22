#include "stdafx.h"
#include "VGObject.h"

CVGPolygon::CVGPolygon( void )
{
	m_Opacity=50;
	m_Color=Color(81,168,255);
	m_bBorder=true;
}


CVGPolygon::~CVGPolygon( void )
{

}

void CVGPolygon::Draw(Graphics* gr, CAxisInfo* m_AxisInfo, bool bTrace/*=FALSE*/)
{
	if (!m_bVisible || !m_bAvailable || m_bTemp) return;

	//Pen pen(m_Color,(REAL)m_PenWidth);
	//GetPen(m_DashStyle,&pen);
	
	Point* pts=new Point[m_Param.GetSize()];
	for (int i=0;i<m_Param.GetSize();i++)
	{
		pts[i]=m_AxisInfo->ToClientPoint(((CVGPoint*)m_Param[i])->m_x,((CVGPoint*)m_Param[i])->m_y);
	}
	
	if ((m_Select || m_HighLight) && !bTrace)
	{
		//SolidBrush br(Color(150,m_Color.GetRed(),m_Color.GetGreen(),m_Color.GetBlue()));
		HatchBrush br(HatchStyleDiagonalCross,
			Color((m_Opacity>20 ? m_Opacity-20 : 0)*255/100,m_Color.GetRed(),m_Color.GetGreen(),m_Color.GetBlue()),
			Color(m_Opacity*255/100,m_Color.GetRed(),m_Color.GetGreen(),m_Color.GetBlue()));
		gr->FillPolygon(&br,pts,m_Param.GetSize(),FillModeWinding);
	}
	else
	{
		//SolidBrush br(m_Color);
		SolidBrush br(Color(m_Opacity*255/100,m_Color.GetRed(),m_Color.GetGreen(),m_Color.GetBlue()));
        gr->FillPolygon(&br,pts,m_Param.GetSize(),FillModeWinding);
	}
	
	Pen pen(m_Color);
	if (m_bBorder) gr->DrawPolygon(&pen,pts,m_Param.GetSize());

	delete[] pts;
}

bool CVGPolygon::CheckMouseOver(Point point, CAxisInfo* m_AxisInfo)
{
	std::vector<Point> pts;
	for (int i=0;i<m_Param.GetSize();i++)
	{
		pts.push_back(m_AxisInfo->ToClientPoint(((CVGPoint*)m_Param[i])->m_x,((CVGPoint*)m_Param[i])->m_y));
	}
	pts.push_back(m_AxisInfo->ToClientPoint(((CVGPoint*)m_Param[0])->m_x,((CVGPoint*)m_Param[0])->m_y));
	return Math::IsInside(point,pts);
}

bool CVGPolygon::CheckObjInRect(Rect rect, CAxisInfo* m_AxisInfo)
{
	for (int i=0;i<m_Param.GetSize();i++)
	{
		if (!((CVGPoint*)m_Param[i])->CheckObjInRect(rect,m_AxisInfo)) return false;
	}
	return true;
}

void CVGPolygon::Serialize( CArchive& ar, CArray<CVGObject*>* objArr )
{
	CVGGeoObject::Serialize(ar, objArr);

	if (ar.IsStoring())
	{
		ar << m_Opacity;
	}
	else
	{
		ar >> m_Opacity;
	}
}

double CVGPolygon::GetArea()
{
	PointD* pts=new PointD[m_Param.GetSize()];
	for (int i=0;i<m_Param.GetSize();i++)
		pts[i]=PointD(((CVGPoint*)m_Param[i])->m_x,((CVGPoint*)m_Param[i])->m_y);

	double s=Math::Area(pts,m_Param.GetSize());
	delete[] pts;
	return s;
}

CValueFractionEx CVGPolygon::GetAreaFr()
{
	CArray<CValueFractionEx*> ptsx,ptsy;
	CValueFractionEx* x; CValueFractionEx* y;
	for (int i=0;i<m_Param.GetSize();i++)
	{
		x=new CValueFractionEx();
		y=new CValueFractionEx();
		((CVGPoint*)m_Param[i])->CaclFr(*x,*y);
		ptsx.Add(x); ptsy.Add(y);
	}

	CValueFractionEx f=Math::AreaFr(ptsx,ptsy);

	for (int i=0;i<m_Param.GetSize();i++)
	{
		delete ptsx[i];
		delete ptsy[i];
	}

	return f;
}

void CVGPolygon::Move(int x,int y, CPoint startPt, CAxisInfo* m_AxisInfo)
{
	for (int i=0;i<m_Param.GetSize();i++)
		if (((CVGPoint*)m_Param[i])->m_Mode!=POINT_MODE_NUM_NUM) return;
	
	for (int i=0;i<m_Param.GetSize();i++)
		((CVGPoint*)m_Param[i])->Move(x,y,startPt,m_AxisInfo);
}