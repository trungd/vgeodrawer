#include "StdAfx.h"
#include "AxisInfo.h"
#include <math.h>

extern float nZoom;
extern Size drPadSize;

CAxisInfo::CAxisInfo(void)
{
}

CAxisInfo::~CAxisInfo(void)
{
}

void CAxisInfo::Clone(CAxisInfo* axisInfo)
{
	Pixel=axisInfo->Pixel;
	Unit=axisInfo->Unit;
	m_originPoint=axisInfo->m_originPoint;
}

Point CAxisInfo::ToClientPoint(double x, double y)
{
	Point point;
	double tl=GetTL();
	point.X=(m_originPoint.X+(int)(x*tl))*nZoom/100;
	point.Y=(m_originPoint.Y-(int)(y*tl))*nZoom/100;
	return point;
}

double CAxisInfo::GetTL()
{
	return Pixel/Unit;
}

PointD CAxisInfo::ToAxisPoint(Point point)
{
	PointD pt;
	double tl=GetTL();
	pt.X=(double)(point.X*100/nZoom-m_originPoint.X)/tl;
	pt.Y=(double)(-point.Y*100/nZoom+m_originPoint.Y)/tl;
	return pt;
}

double CAxisInfo::ToAxisX(int x)
{
	double tl=GetTL();
	return (double)(x-m_originPoint.X)/tl;
}

double CAxisInfo::ToAxisY(int y)
{
	double tl=GetTL();
	return (double)-(y-m_originPoint.Y)/tl;
}

int CAxisInfo::ToClientY(double y)
{
	double tl=GetTL();
	return (m_originPoint.Y-(int)(y*tl));
}

int CAxisInfo::ToClientX(double x)
{
	double tl=GetTL();
	return (m_originPoint.X+(int)(x*tl));
}

double CAxisInfo::GetMinX()
{
	return -m_originPoint.X/GetTL();
}

double CAxisInfo::GetMaxX()
{
	return (drPadSize.Width-m_originPoint.X)/GetTL();
}

double CAxisInfo::GetMinY()
{
	return (m_originPoint.Y-drPadSize.Height)/GetTL();
}

double CAxisInfo::GetMaxY()
{
	return m_originPoint.Y/GetTL();
}

double CAxisInfo::ToClientLength(double d)
{
	return d*GetTL()*nZoom/100;
}

double CAxisInfo::ToAxisLength(int d)
{
	return d/GetTL();
}

void CAxisInfo::IncZoom(int nInc, CPoint pt)
{
	if (Unit>=1000 && nInc<0) return;
	if (Unit<0.002 && nInc>0) return;
	Pixel+=nInc*2;
	if (Pixel>100)
	{
		double k=GetUnit(FALSE);
		Pixel=(int)((Pixel/Unit)*k);
		Unit=k;
	}
	if (Pixel<40)
	{
		double k=GetUnit(TRUE);
		Pixel=(int)((Pixel/Unit)*k);
		Unit=k;
	}
}

double CAxisInfo::GetUnit(BOOL bNext)
{
	double k=Unit;
	int num=0;;
	if (k<1)
	{
		while (k<1)
		{
			num--;
			k*=10;
		}
	}
	if (k>1)
	{
		while (k>=10)
		{
			num++;
			k/=10;
		}
	}
	switch ((int)k)
	{
	case 1: if (bNext) k=2; else { k=5;num--; } break;
	case 2: if (bNext) k=5; else { k=1; } break;
	case 5: if (bNext) { k=1;num++; } else { k=2; } break;
	}
	k*=pow((double)10,num);
	return k;
}

void CAxisInfo::Serialize( CArchive& ar )
{
	if (ar.IsStoring())
	{
		ar << m_originPoint.X;
		ar << m_originPoint.Y;
		ar << Pixel;
		ar << Unit;
	}
	else 
	{
		ar >> m_originPoint.X;
		ar >> m_originPoint.Y;
		ar >> Pixel;
		ar >> Unit;
	}
}