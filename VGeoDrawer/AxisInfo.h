#pragma once

#include "gdi+.h"

class PointD
{
public:
	PointD()
	{
		X = Y = 0;
	}

	PointD(const PointD &point)
	{
		X = point.X;
		Y = point.Y;
	}

	PointD(double x, double y)
	{
		X = x;
		Y = y;
	}

	PointD operator+(const PointD& point) const
	{
		return PointD(X + point.X,
			Y + point.Y);
	}

	PointD operator-(IN const PointD& point) const
	{
		return PointD(X - point.X,
			Y - point.Y);
	}

	BOOL Equals(IN const PointD& point)
	{
		return (X == point.X) && (Y == point.Y);
	}

public:

	double X;
	double Y;
};


class CAxisInfo
{
public:
	CAxisInfo(void);

	double GetMaxY();
	double GetMinY();
	double GetMaxX();
	double GetMinX();
	double GetTL();
	
	PointD ToAxisPoint(Point point);
	Point ToClientPoint(double x, double y);
	
	Size m_Size;
	int Pixel;
	double Unit;
	Point m_originPoint;
public:
	~CAxisInfo(void);
	double ToClientLength(double d);
	void IncZoom(BOOL bInc, CPoint pt);
	double GetUnit(BOOL bNext);
	double ToAxisLength(int d);
	void Serialize(CArchive& ar);
	void Clone(CAxisInfo* axisInfo);
	double ToAxisX(int x);
	int ToClientY(double y);
	double ToAxisY(int y);
	int ToClientX(double x);
};
