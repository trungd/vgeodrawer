#include "StdAfx.h"
#include "VGObject.h"


CVGExpression::CVGExpression()
{
	m_Type=OBJ_EXPRESSION;
}

void CVGExpression::Calc( CAxisInfo* m_AxisInfo )
{
	if (!CheckCanCalc()) return; 
	m_bCalc=true; m_Exp.Calc();
}

bool CVGExpression::SetExp( CString strExp, CArray<CVGObject*> *m_Array, CStringArray* m_strReplacedNameArr )
{
	m_strExp=strExp;
	bool b=m_Exp.SetExpression(strExp,m_Array,false,m_strReplacedNameArr);
	m_Exp.Calc();
	return b;
}

void CVGExpression::Serialize( CArchive& ar , CArray<CVGObject*>* objArr )
{
	CVGObject::Serialize(ar,objArr);
	if (ar.IsStoring()) ar << m_strExp;
	else 
	{
		ar >> m_strExp;
		m_Exp.SetExpression(m_strExp,objArr);
	}
}

CString CVGExpression::GetValue( bool bName/*=false*/ )
{
	return bName ? m_Name+L"="+m_strExp : m_strExp;
}