#include "stdafx.h"
#include "VGObject.h"

CVGVector::CVGVector()
{

}

CVGVector::~CVGVector()
{

}

void CVGVector::Draw(Graphics *gr, CAxisInfo* m_AxisInfo, bool bTrace)
{
	if (!m_bVisible || !m_bAvailable || m_bTemp) return;
	Point pt1;	Point pt2;

	CVGPoint* m_Point1=(CVGPoint*)m_Param[0];
	pt1=m_AxisInfo->ToClientPoint(m_Point1->m_x,m_Point1->m_y);
	pt2=m_AxisInfo->ToClientPoint(m_Point1->m_x+x,m_Point1->m_y+y);

	GraphicsPath strokePath;

	int s=5*nZoom/100;
	strokePath.AddLine(-s,-s,0,0);
	strokePath.AddLine(s,-s,0,0);

	CustomLineCap custCap(NULL, &strokePath);

	Pen pen(m_Color,(REAL)m_PenWidth);
	GetPen(m_DashStyle,&pen);

	if (m_Select || m_HighLight) 
	{
		GraphicsPath strokePath2;
		strokePath2.AddLine(-2,-2,0,0);
		strokePath2.AddLine(2,-2,0,0);

		CustomLineCap custCap2(NULL, &strokePath2);

		Pen pen2(Color(100,m_Color.GetRed(),m_Color.GetGreen(),m_Color.GetBlue()),m_PenWidth+2);
		pen2.SetCustomEndCap(&custCap2);
		gr->DrawLine(&pen2,pt1,pt2);
	}

	pen.SetCustomEndCap(&custCap);
	gr->DrawLine(&pen,pt1,pt2);
}

void CVGVector::Calc(CAxisInfo* m_AxisInfo)
{
	if (!CheckCanCalc()) return;

	switch (m_Mode)
	{
	case VECTOR_MODE_POINT_POINT:
		{
			CVGPoint* pt1=(CVGPoint*)m_Param[0];
			CVGPoint* pt2=(CVGPoint*)m_Param[1];
			x=pt2->m_x-pt1->m_x;
			y=pt2->m_y-pt1->m_y;
			break;
		}
	case VECTOR_MODE_POINT_EXP:
		{
			CVGPoint* pt=(CVGPoint*)m_Param[0];
			CVGExpression* exp=(CVGExpression*)m_Param[1];
			if (exp->GetExpValueType()!=VALUE_VECTOR) m_bAvailable=false;
			else
			{
				x=((CValueVector*)exp->m_Exp.m_Value)->x;
				y=((CValueVector*)exp->m_Exp.m_Value)->y;
			}
			break;
		}
	}
}

CString CVGVector::GetValue(bool bName)
{
	CString str;
	if (bName) str=m_Name+L" = ";
	str=str+L"("+Math::DoubleToString(x)+L", "+Math::DoubleToString(y)+L")";
	return str;
}

bool CVGVector::CheckMouseOver(Point point, CAxisInfo* m_AxisInfo)
{
	if (!m_bVisible) return FALSE;
	Point pt1;
	Point pt2;
	if (m_Mode==VECTOR_MODE_POINT_POINT)
	{
		pt1=m_AxisInfo->ToClientPoint(((CVGPoint*)m_Param[0])->m_x,((CVGPoint*)m_Param[0])->m_y);
		pt2=m_AxisInfo->ToClientPoint(((CVGPoint*)m_Param[1])->m_x,((CVGPoint*)m_Param[1])->m_y);
	}
	else if (m_Mode==VECTOR_MODE_POINT_EXP)
	{
		//CVGExpression* exp=(CVGExpression*)m_Param[1];
		
		pt1=m_AxisInfo->ToClientPoint(((CVGPoint*)m_Param[0])->m_x,((CVGPoint*)m_Param[0])->m_y);
		pt2=m_AxisInfo->ToClientPoint(((CVGPoint*)m_Param[0])->m_x+x,((CVGPoint*)m_Param[1])->m_y+y);
	}

	if (point.X>=min(pt1.X,pt2.X)-6 && point.X<=max(pt1.X,pt2.X)+6 && 
		point.Y>=min(pt1.Y,pt2.Y)-6 && point.Y<=max(pt1.Y,pt2.Y)+6)
	{
		pt1.Y=-pt1.Y; pt2.Y=-pt2.Y;
		Point newPt=Point(point.X,-point.Y);
		double a,b,c;
		Math::LineThroughTwoPoints(pt1.X,pt1.Y,pt2.X,pt2.Y,a,b,c);
		if (Math::GetDistance(newPt.X,newPt.Y,a,b,c)<6) return TRUE;
	}
	return FALSE;
}

void CVGVector::Serialize(CArchive& ar, CArray<CVGObject*>* objArr)
{
	CVGSegment::Serialize(ar,objArr);

	if (ar.IsStoring())
	{
		ar << x;
		ar << y;
	}
	else
	{
		ar >> x;
		ar >> y;
	}
}

void CVGVector::Clone(CVGObject* obj)
{
	CVGSegment::Clone(obj);

	x=((CVGVector*)obj)->x;
	y=((CVGVector*)obj)->y;
}