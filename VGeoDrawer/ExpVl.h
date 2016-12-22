#pragma once

class CElementVl;

class CExpVl
{
public:
	CExpVl();
	~CExpVl();
	CArray<CElementVl*> a;
	CExpVl operator+(CExpVl& f);
	CExpVl operator-(CExpVl& f);
	CExpVl operator-();
	CExpVl operator*(CValueFractionEx& f);
	CExpVl operator/(CValueFractionEx& f);
	CExpVl Sqrt(CValueFractionEx& f);
	bool operator=(CExpVl& f);

	CString ToString();
};

enum ElementType { ELE_NUM=0, ELE_VARI, ELE_MUL, ELE_FR, ELE_SQRT };

class CElementVl
{
public:
	virtual CString ToString() { return NULL; }
	virtual CElementVl* Clone();
	virtual void Type();
	virtual CExpVl operator-() { return }
};

class CElementNum : public CElementVl
{
public:
	ElementType Type() { return ELE_NUM; }
	double d;
	CString ToString() { return Math::DoubleToString(d); }
	CElementVl* Clone() { CElementNum* num=new CElementNum(); num->d=d; return num; }
	CExpVl operator-() { CElementNum num; num.d=-d; return num; }
};

class CElementVari : public CElementVl
{
public:
	ElementType Type() { return ELE_VARI; }
	CString vari;
};

class CElementMul : public CElementVl
{
public:
	ElementType Type() { return ELE_MUL; }
	~CElementMul { for (int i=0;i<vl.GetSize();i++) delete vl[i]; }
	CArray<CExpVl*> vl;
};

class CElementFr : public CElementVl
{
public:
	ElementType Type() { return ELE_FR; }
	CExpVl ts;
	CExpVl ms;
};

class CElementSqrt : public CElementVl
{
public:
	ElementType Type() { return ELE_SQRT; }
	CExpVl vl;
	double coff;
	CString ToString();
};