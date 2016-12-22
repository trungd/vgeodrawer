#pragma once
#include <afx.h> 
#include <stack>
#include <queue>
#include <vector>
#include <math.h>
#include "AxisInfo.h"

using namespace std;
const double pi=3.141592653589;

class CValueFractionEx;

enum ValueType
{
	VALUE_NONE=0,
	VALUE_BOOL,
	VALUE_DOUBLE,
	VALUE_VECTOR,
	VALUE_STRING,
	VALUE_FRACTION_EX,
	VALUE_VECTOR_EX
};

class Math
{
public:

	static int SolveQuadricFunction(double a, double b, double c, double& x1, double& x2);
	static int SolveQuadricFunctionFr(CValueFractionEx& a, CValueFractionEx& b, CValueFractionEx& c, CValueFractionEx& x1, CValueFractionEx& x2);
	static BOOL GetIntersectionLineLine(double a1, double b1, double c1, double a2, double b2, double c2, double& x, double& y);
	static BOOL GetIntersectionLineLineFr(CValueFractionEx& a1, CValueFractionEx& b1, CValueFractionEx& c1, CValueFractionEx& a2, CValueFractionEx& b2, CValueFractionEx& c2, CValueFractionEx& x, CValueFractionEx& y);
	static double GetDistance(double x1, double y1, double x2, double y2);
	static CValueFractionEx GetDistanceFr(CValueFractionEx& x1, CValueFractionEx& y1, CValueFractionEx& x2, CValueFractionEx& y2);
	static double GetDistance(double x, double y, double A, double B, double C);
	static CValueFractionEx GetDistanceFr(CValueFractionEx& x, CValueFractionEx& y, CValueFractionEx& A, CValueFractionEx& B, CValueFractionEx& C);
	static void GetPointByRatio(double x1, double y1, double x2, double y2, double k, double& x, double& y);
	static CString DoubleToString(double d);
	static CString IntToString(int i);
	static int GetIntersectionLineCircle(double centerX, double centerY, double r, double A, double B, double C, double& x1, double & y1, double& x2, double& y2);
	static int GetIntersectionLineCircleFr(CValueFractionEx& centerX, CValueFractionEx& centerY, CValueFractionEx& r, CValueFractionEx& A, CValueFractionEx& B, CValueFractionEx& C, CValueFractionEx& x1, CValueFractionEx& y1, CValueFractionEx& x2, CValueFractionEx& y2);
	static int GetIntersectionCircleCircle(double centerX1, double centerY1, double r1,double centerX2, double centerY2, double r2, double &x1, double &y1, double &x2, double& y2);
	static int GetIntersectionCircleCircleFr(CValueFractionEx& centerX1, CValueFractionEx& centerY1, CValueFractionEx& r1,CValueFractionEx& centerX2, CValueFractionEx& centerY2, CValueFractionEx& r2, CValueFractionEx &x1, CValueFractionEx& y1, CValueFractionEx& x2, CValueFractionEx& y2);
	static int GetIntersectionLineConic(double a, double b, double c, double d, double e, double f, double la,double lb, double lc, double& x1, double &y1, double &x2, double &y2);
	static int GetIntersectionLineConicFr(CValueFractionEx& a, CValueFractionEx& b, CValueFractionEx& c, CValueFractionEx& d, CValueFractionEx& e, CValueFractionEx& f, CValueFractionEx& la,CValueFractionEx& lb, CValueFractionEx& lc, CValueFractionEx& x1, CValueFractionEx& y1, CValueFractionEx& x2, CValueFractionEx& y2);
	static double GetDistanceDS( double x1, double y1, double x2, double y2 );
	static void PointOnLineDS(double x0, double y0, double a, double b, double c, double length, double& x, double& y);
	static void PointOnLineDSFr(CValueFractionEx& x0, CValueFractionEx& y0, CValueFractionEx& a, CValueFractionEx& b, CValueFractionEx& c, CValueFractionEx& length, CValueFractionEx& x, CValueFractionEx& y);
	static void PointOnLine(double x0, double y0, double a, double b, double c, double length, double& x1, double& y1, double& x2, double& y2);
	static void PointOnLineFr(CValueFractionEx& x0, CValueFractionEx& y0, CValueFractionEx& a, CValueFractionEx& b, CValueFractionEx& c, CValueFractionEx& length, CValueFractionEx& x1, CValueFractionEx& y1, CValueFractionEx& x2, CValueFractionEx& y2);
	static void LineThroughTwoPoints(double x1, double y1, double x2, double y2, double& a, double& b, double& c);
	static void LineThroughTwoPointsFr(CValueFractionEx x1, CValueFractionEx y1, CValueFractionEx x2, CValueFractionEx y2, CValueFractionEx& a, CValueFractionEx& b, CValueFractionEx& c);
	static BOOL Equal(double i1, double i2);
	static void AngleBisector(double a1, double b1, double c1, double a2, double b2, double c2, double& a3, double& b3, double& c3, double& a4, double& b4, double& c4);
	static void AngleBisectorFr(CValueFractionEx& a1, CValueFractionEx& b1, CValueFractionEx& c1, CValueFractionEx& a2, CValueFractionEx& b2, CValueFractionEx& c2, CValueFractionEx& a3, CValueFractionEx& b3, CValueFractionEx& c3, CValueFractionEx& a4, CValueFractionEx& b4, CValueFractionEx& c4);
	static BOOL IsPerpendicular(double a1, double b1, double c1, double a2, double b2, double c2);
	static BOOL IsParallel( double a1, double b1, double c1, double a2, double b2, double c2 );
	static void GetReflectLine(double a1, double b1, double c1, double a2, double b2, double c2, double& a, double& b, double& c);
	static void GetReflectLine(double a1, double b1, double c1, double x, double y, double& a, double& b, double& c);
	static void GetReflectPoint(double x,double y,double a,double b,double c,double& x1,double& y1);
	static void GetReflectPoint(double x1, double y1, double x2, double y2, double& x, double& y);
	static void GetDilatePoint(double x1, double y1, double x2, double y2, double k, double& x, double& y);
	static void GetDilateLine(double a1, double b1, double c1, double x, double y, double k, double& a, double& b, double& c);
	static void GetRotatePoint(double x1, double y1, double x2, double y2, double k, double& x, double& y);
	static void GetTwoPointsOnLine(double a, double b, double c, double& x1, double& y1, double& x2, double& y2);
	static void GetRotateLine(double a1, double b1, double c1, double x, double y, double k, double& a, double& b, double& c);
	static void GetRotateLineFr(CValueFractionEx& a1, CValueFractionEx& b1, CValueFractionEx& c1, CValueFractionEx& x, CValueFractionEx& y, CValueFractionEx& k, CValueFractionEx& a, CValueFractionEx& b, CValueFractionEx& c);
	static double ConvertFromRadianToAngleUnit(double sd);
	static double ConvertToRadian(double sd);
	static BOOL IsCollinear(double x1, double y1, double x2, double y2, double x3, double y3);
	static BOOL IsConcurrent(double a1, double b1, double c1, double a2, double b2, double c2, double a3, double b3, double c3);
	static bool IsInside(const Point &point, const std::vector<Point> &points_list);
	static int Round(double d);
	static double Area(PointD* pts, int count);
	static double Angle(double a1, double b1, double c1, double a2, double b2, double c2);
	static double Angle(double x1, double y1, double x2, double y2);
	static bool IsTangent(double a1, double b1, double c1, double centerX, double centerY, double R);
	static void GetParallelLine(double x, double y, double a0, double b0, double c0, double& a, double& b, double& c);
	static void GetParallelLineFr(CValueFractionEx& x, CValueFractionEx& y, CValueFractionEx& a0, CValueFractionEx& b0, CValueFractionEx& c0, CValueFractionEx& a, CValueFractionEx& b, CValueFractionEx& c);
	static void GetPerpendicularLine(double x, double y, double a0, double b0, double c0, double& a, double& b, double& c);
	static void GetPerpendicularLineFr(CValueFractionEx& x, CValueFractionEx& y, CValueFractionEx& a0, CValueFractionEx& b0, CValueFractionEx& c0, CValueFractionEx& a, CValueFractionEx& b, CValueFractionEx& c);
	static bool IsPtInSegment(double x, double y, double x1, double y1, double x2, double y2);
	static bool IsInt(double d);
	static int gcd(int a, int b);
	static int lcm(int a, int b);
	static int TangentLine(double x,double y,double a,double b,double c,double d,double e,double f,double& la1,double& lb1,double& lc1,double& la2,double& lb2,double& lc2);
	static int TangentLineFr(CValueFractionEx& x,CValueFractionEx& y,CValueFractionEx& a,CValueFractionEx& b,CValueFractionEx& c,CValueFractionEx& d,CValueFractionEx& e,CValueFractionEx& f,CValueFractionEx& la1,CValueFractionEx& lb1,CValueFractionEx& lc1,CValueFractionEx& la2,CValueFractionEx& lb2,CValueFractionEx& lc2);
	static void GetReflectPointFr(CValueFractionEx& x1, CValueFractionEx& y1, CValueFractionEx& x2, CValueFractionEx& y2, CValueFractionEx& x, CValueFractionEx& y);
	static void GetReflectPointFr( CValueFractionEx& x,CValueFractionEx& y,CValueFractionEx& a,CValueFractionEx& b,CValueFractionEx& c,CValueFractionEx& x1,CValueFractionEx& y1 );
	static void GetReflectLineFr(CValueFractionEx& a1, CValueFractionEx& b1, CValueFractionEx& c1, CValueFractionEx& x, CValueFractionEx& y, CValueFractionEx& a, CValueFractionEx& b, CValueFractionEx& c);
	static void GetReflectLineFr( CValueFractionEx& a1, CValueFractionEx& b1, CValueFractionEx& c1, CValueFractionEx& a2, CValueFractionEx& b2, CValueFractionEx& c2, CValueFractionEx& a, CValueFractionEx& b, CValueFractionEx& c );
	static void GetDilatePointFr(CValueFractionEx& x1, CValueFractionEx& y1, CValueFractionEx& x2, CValueFractionEx& y2, CValueFractionEx& k, CValueFractionEx& x, CValueFractionEx& y);
	static void GetDilateLineFr(CValueFractionEx& a1, CValueFractionEx& b1, CValueFractionEx& c1, CValueFractionEx& x, CValueFractionEx& y, CValueFractionEx& k, CValueFractionEx& a, CValueFractionEx& b, CValueFractionEx& c );
	static void GetRotatePointFr(CValueFractionEx& x1, CValueFractionEx& y1, CValueFractionEx& x2, CValueFractionEx& y2, CValueFractionEx& k, CValueFractionEx& x, CValueFractionEx& y);
	static void GetTwoPointsOnLineFr(CValueFractionEx& a, CValueFractionEx& b, CValueFractionEx& c, CValueFractionEx& x1, CValueFractionEx& y1, CValueFractionEx& x2, CValueFractionEx& y2);
	static CValueFractionEx AreaFr(CArray<CValueFractionEx*>& ptsx, CArray<CValueFractionEx*>& ptsy);
	static CValueFractionEx GetDistanceDSFr( CValueFractionEx& x1, CValueFractionEx& y1, CValueFractionEx& x2, CValueFractionEx& y2 );
private:
	static inline int IsLeft(const Point &p0, const Point &p1, const Point &point);
};

class CValue { 
public: virtual ValueType GetType() { return VALUE_NONE; } 
		virtual CValue* Clone() { return NULL; } 
		virtual CString ToString() { return NULL; }
		virtual double ToDouble() { return 0; }
		virtual bool operator=(CValue& vl) { return false; }
};
class CValueBool : public CValue { 
public: CValueBool(bool vl) { m_Value=vl; } 
		bool m_Value; 
		ValueType GetType() { return VALUE_BOOL; } 
		CValue* Clone() { return new CValueBool(m_Value); } 
		CString ToString() { return m_Value ? L"true" : L"false"; }
		double ToDouble() { return m_Value; }
		bool operator=(CValue& vl) { m_Value=((CValueBool*)&vl)->m_Value; return true; }
};
class CValueDouble : public CValue { 
public: CValueDouble(double vl) { m_Value=vl; } 
		double m_Value; 
		ValueType GetType() { return VALUE_DOUBLE; } 
		CValue* Clone() { return new CValueDouble(m_Value); } 
		CString ToString() { return Math::DoubleToString(m_Value); }
		double ToDouble() { return m_Value; }
		bool operator=(CValue& vl) { m_Value=((CValueDouble*)&vl)->m_Value; return true; }
};

class CValueFractionEx : public CValue { // (x+y*sqrt(z))/t
public: CValueFractionEx();
		CValueFractionEx(CValueFractionEx &copy);
		CValueFractionEx(double d);
		int ms;
		bool bIsDouble; double dValue;
		CArray<int> a;
		CArray<int> b;
		ValueType GetType() { return VALUE_FRACTION_EX; }
		//CValue* Clone();
		void AddSqrt(int na, int nb);
		bool operator=(CValueFractionEx& f);
		bool operator=(int i);
		CValueFractionEx operator+(CValueFractionEx& f);
		CValueFractionEx operator+(double d) { CValueFractionEx fd; fd.FromNumber(d); return (*this)+fd; }
		CValueFractionEx operator-(CValueFractionEx& f);
		CValueFractionEx operator-(double d) { CValueFractionEx fd; fd.FromNumber(d); return (*this)-fd; }
		CValueFractionEx operator-();
		CValueFractionEx operator*(CValueFractionEx& f);
		CValueFractionEx operator*(double d) { CValueFractionEx fd; fd.FromNumber(d); return (*this)*fd; }
		CValueFractionEx operator/(CValueFractionEx& f);
		CValueFractionEx operator/(double d) { CValueFractionEx fd; fd.FromNumber(d); return (*this)/fd; }
		void Simplify();

		static void SqrtTo_a_And_b_(int n, int& y, int& z);
		CValueFractionEx Sqrt();
		CValueFractionEx Abs();
		CValueFractionEx Inverse();
		CValueFractionEx Power(CValueFractionEx& k);
		void FromNumber(double d);
		CString ToString(bool bBracket=true);
		double ToDouble();
};

// class CValueDoubleEx : public CValue
// {
// public: CValueDoubleEx();
// 		~CValueDoubleEx();
// }

class CValueString : public CValue { 
public: CValueString(CString vl) { m_Value=vl; } 
		CString m_Value; 
		ValueType GetType() { return VALUE_STRING; } 
		CValue* Clone() { return new CValueString(m_Value); } 
		CString ToString() { return m_Value; }
		double ToDouble() { return _wtoi(m_Value); }
		bool operator=(CValue& vl) { m_Value=((CValueString*)&vl)->m_Value; return true; }
};

class CValueVector : public CValue { 
public: CValueVector(double vx, double vy) { x=vx; y=vy; } 
		double x,y; 
		CValue* Clone() { return new CValueVector(x,y); }
		ValueType GetType() { return VALUE_VECTOR; } 
		CString ToString() { return L"("+Math::DoubleToString(x)+L", "+Math::DoubleToString(y)+L")"; } 
		bool operator=(CValue& vl) { x=((CValueVector*)&vl)->x; y=((CValueVector*)&vl)->y; return true; }
};

class CValueVectorEx : public CValue {
public: CValueVectorEx(CValueFractionEx vx, CValueFractionEx vy) { x=vx; y=vy; } 
		CValueFractionEx x,y; 
		CValue* Clone() { return new CValueVectorEx(x,y); }
		ValueType GetType() { return VALUE_VECTOR_EX; } 
		CString ToString() { return L"("+x.ToString(false)+L", "+y.ToString(false)+L")"; } 
		bool operator=(CValue& vl) { x=((CValueVector*)&vl)->x; y=((CValueVector*)&vl)->y; return true; }
};