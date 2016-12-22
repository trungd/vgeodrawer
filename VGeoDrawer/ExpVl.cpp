#include "stdafx.h"
#include "ExpVl.h"

CExpVl::CExpVl()
{

}

CExpVl::~CExpVl()
{
	for (int i=0;i<a.GetSize();i++) delete a[i];
}

CString CExpVl::ToString()
{
	CString s;
	for (int i=0;i<a.GetSize();i++)
	{
		if (s!=L"") s+=L"+";
		s+=a[i]->ToString();
	}
}

bool CExpVl::operator=(CExpVl& f)
{
	for (int i=0;i<a.GetSize();i++) delete a[i];
	a.RemoveAll();
	for (int i=0;i<f.a.GetSize();i++)
		a.Add(f.a[i]->Clone());
}

CExpVl CExpVl::operator+(CExpVl& f)
{
	CExpVl vl=*this;
	for (int i=0;i<f.a.GetSize();i++)
		a.Add(f.a[i]->Clone());
}

CExpVl CExpVl::operator-()
{
	
}

CExpVl CExpVl::operator-(CExpVl& f)
{
	return (*this)+(-f);
}

CExpVl CExpVl::operator*(CExpVl& f)
{
	CExpVl vl;
	for (int i=0;i<this->a.GetSize();i++)
	{
		for (int j=0;j<f.a.GetSize();j++)
		{
			if (this->a[i].Type()==ELE_MUL && f.a[j].Type()==ELE_MUL)
			{
				CElementMul* m=this->a[i]->Clone();
				for (int k=0;k<((CElementMul*)f.a[j])->vl.GetSize();k++) m->vl.Add(((CElementMul*)f.a[j])->vl[k]->Clone());
			}
			else if (this->a[i].Type()==ELE_MUL)
			{
				CElementMul* m=this->a[i]->Clone();
				m->vl.Add(f.a[j]->Clone());
			}
			else if (f.a[j].Type()==ELE_MUL)
			{
				CElementMul* m=f.a[j]->Clone();
				m->vl.Add(this->a[i]->Clone());
			}
			else
			{
				CElementMul* m;
				m->vl.Add(f.a[j]->Clone());
				m->vl.Add(this->a[i]->Clone());
			}
		}
	}
}

CExpVl CExpVl::operator/(CExpVl& f)
{
	CElementFr* fr=new CElementFr();
	fr->ts=*this;
	fr->ms=f;
}

CExpVl CExpVl::Sqrt( CValueFractionEx& f )
{
	CExpVl vl;
	CElementSqrt* s=new CElementSqrt();
	s->coff=1;
	s->vl=f;
	vl.a.Add(s);
}

CString CElementSqrt::ToString()
{
	return L"sqrt("+vl.ToString()+L")";
}