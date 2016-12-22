#include "stdafx.h"
#include "VGObject.h"

int CVGObject::GetValueType(CString strValueType)
{
	if (strValueType==L"Name") return 0;
	else if (strValueType==L"Select") return 1;
	else if (strValueType==L"Description") return 2;
	else if (strValueType==L"Definition") return 3;
	else if (strValueType==L"Visible") return 4;
	else if (strValueType==L"Fix") return 5;
	else if (strValueType==L"ShowName") return 6;
	else return -1;
}

CValue* CVGObject::GetObjValue(int nType) 
{
	switch (nType)
	{
	case 0: return new CValueString(m_Name);
	case 1: return new CValueBool(m_Select);
	case 2: return new CValueString(m_Description);
	case 3: return new CValueString(m_Definition);
	case 4: return new CValueBool(m_bVisible);
	case 5: return new CValueBool(m_bFixed);
	case 6: return new CValueBool(m_bShowName);
	default: return NULL;
	}
}

bool CVGObject::SetValue(CString strValue, CVGExpression* vl, CArray<CVGObject*>* m_Array) 
{
	if (strValue==L"Name") { m_Name=((CValueString*)vl->m_Exp.m_Value)->m_Value; return false; }
	else if (strValue==L"Select") { m_Select=((CValueBool*)vl->m_Exp.m_Value)->m_Value; return false; }
	else if (strValue==L"Description") { m_Description=((CValueString*)vl->m_Exp.m_Value)->m_Value; return false; }
	else if (strValue==L"Definition") { m_Definition=((CValueString*)vl->m_Exp.m_Value)->m_Value; return false; }
	else if (strValue==L"Visible") { m_bVisible=((CValueBool*)vl->m_Exp.m_Value)->m_Value; return false; }
	else if (strValue==L"Fix") { m_bFixed=((CValueBool*)vl->m_Exp.m_Value)->m_Value; return false; }
	else if (strValue==L"ShowName") { m_bShowName=((CValueBool*)vl->m_Exp.m_Value)->m_Value; return false; }
	else if (strValue==L"Condition") { m_strCondition=vl->m_Exp.m_strExp; RefreshCondition(m_Array); return false; }
	else return false;
}

//////////////////////////////////////////////////////////////////////////

int CVGGeoObject::GetValueType(CString strValueType)
{
// 	if (strValueType==L"Select") return 0;
// 	else if (strValueType==L"Description") return 1;
// 	else if (strValueType==L"Definition") return 2;
// 	else if (strValueType==L"Visible") return 3;
// 	else if (strValueType==L"Fix") return 4;
// 	else if (strValueType==L"ShowName") return 5;
// 	else
	 return CVGObject::GetValueType(strValueType);
}

CValue* CVGGeoObject::GetObjValue(int nType) 
{
	switch (nType)
	{
// 	case 0: return new CValueBool(m_Select);
// 	case 1: return new CValueString(m_Description);
// 	case 2: return new CValueString(m_Definition);
// 	case 3: return new CValueBool(m_bVisible);
// 	case 4: return new CValueBool(m_bFixed);
// 	case 5: return new CValueBool(m_bShowName);
	default: return CVGObject::GetObjValue(nType);
	}
}

bool CVGGeoObject::SetValue(CString strValue, CVGExpression* vl, CArray<CVGObject*>* m_Array) 
{
	/*
	if (strValue==L"Select") m_Select=((CValueBool*)vl)->m_Value; 
		else if (strValue==L"Description") m_Description=((CValueString*)vl)->m_Value;
		else if (strValue==L"Definition") m_Definition=((CValueString*)vl)->m_Value;
		else if (strValue==L"Visible") m_bVisible=((CValueBool*)vl)->m_Value; 
		else if (strValue==L"Fix") m_bFixed=((CValueBool*)vl)->m_Value; 
		else if (strValue==L"ShowName") m_bShowName=((CValueBool*)vl)->m_Value; 
		else*/
	 return CVGObject::SetValue(strValue, vl, m_Array);
}

//////////////////////////////////////////////////////////////////////////

int CVGPoint::GetValueType(CString strValueType) 
{ 
	if (strValueType==L"") return 10; 
	else if (strValueType==L"x") return 11; 
	else if (strValueType==L"y") return 12;
	else return CVGGeoObject::GetValueType(strValueType);
}

CValue* CVGPoint::GetObjValue(int nType) 
{
	if (nType==10) return new CValueVector(m_x,m_y); 
	else if (nType==11) return new CValueDouble(m_x); 
	else if (nType==12) return new CValueDouble(m_y);
	else return CVGGeoObject::GetObjValue(nType);
}

bool CVGPoint::SetValue(CString strValue, CVGExpression* vl, CArray<CVGObject*>* m_Array) 
{
	if (strValue==L"x") 
	{
		if (vl->IsConstant())
		{
			double d=vl->GetDoubleValue();
			m_x=d;
			if (m_Mode==POINT_MODE_EXP_EXP)
			{
				m_Mode=POINT_MODE_NUM_EXP; m_Param.RemoveAt(0);
			}
			else if (m_Mode==POINT_MODE_EXP_NUM)
			{
				m_Mode=POINT_MODE_NUM_NUM; m_Param.RemoveAt(0);
			}
			return false;
		}
		else
		{
			if (m_Mode==POINT_MODE_NUM_NUM)
			{
				m_Mode=POINT_MODE_EXP_NUM; m_Param.Add(vl); return true;
			}
			else if (m_Mode==POINT_MODE_NUM_EXP)
			{
				m_Mode=POINT_MODE_EXP_EXP; m_Param.Add(vl); return true;
			}
			else if (m_Mode==POINT_MODE_EXP_EXP || m_Mode==POINT_MODE_EXP_NUM)
			{
				m_Param[0]=vl; return true;
			}
		}
	}
	else if (strValue==L"y") 
	{
		if (vl->IsConstant())
		{
			double d=vl->GetDoubleValue();
			m_y=d;
			if (m_Mode==POINT_MODE_EXP_EXP)
			{
				m_Mode=POINT_MODE_EXP_NUM; m_Param.RemoveAt(1);
			}
			else if (m_Mode==POINT_MODE_NUM_EXP)
			{
				m_Mode=POINT_MODE_NUM_NUM; m_Param.RemoveAt(0);
			}
			return false;
		}
		else
		{
			if (m_Mode==POINT_MODE_NUM_NUM)
			{
				m_Mode=POINT_MODE_NUM_EXP; m_Param.Add(vl); return true;
			}
			else if (m_Mode==POINT_MODE_EXP_NUM)
			{
				m_Mode=POINT_MODE_EXP_EXP; m_Param.Add(vl); return true;
			}
			else if (m_Mode==POINT_MODE_NUM_EXP)
			{
				m_Param[0]=vl; return true;
			}
			else if (m_Mode==POINT_MODE_EXP_EXP)
			{
				m_Param[1]=vl; return true;
			}
		}
	}
	else if (strValue==L"") { 
		m_x=((CValueVector*)vl->m_Exp.m_Value)->x; 
		m_y=((CValueVector*)vl->m_Exp.m_Value)->y; 
		return false; }
	else return CVGGeoObject::SetValue(strValue, vl, m_Array);
}

//////////////////////////////////////////////////////////////////////////

int CVGLineBase::GetValueType(CString strValueType) 
{ 
	if (strValueType==L"Width") return 11; 
	else if (strValueType==L"Style") return 12;
	else return CVGGeoObject::GetValueType(strValueType);
}

CValue* CVGLineBase::GetObjValue(int nType) 
{
	if (nType==11) return new CValueDouble(m_PenWidth+1); 
	else if (nType==12) return new CValueDouble(m_DashStyle+1); 
	else return CVGGeoObject::GetObjValue(nType);
}

bool CVGLineBase::SetValue(CString strValue, CVGExpression* vl, CArray<CVGObject*>* m_Array) 
{
	if (strValue==L"Width") m_PenWidth=(int)vl->GetDoubleValue()-1;
	else if (strValue==L"Style") m_DashStyle=(int)vl->GetDoubleValue()-1;
	else return CVGGeoObject::SetValue(strValue, vl, m_Array);
}

//////////////////////////////////////////////////////////////////////////


int CVGLine::GetValueType( CString strValueType )
{
	return CVGLineBase::GetValueType(strValueType);
}

CValue* CVGLine::GetObjValue( int nType )
{
	return CVGLineBase::GetObjValue(nType);
}

bool CVGLine::SetValue( CString strValue, CVGExpression* vl, CArray<CVGObject*>* m_Array )
{
	return CVGLineBase::SetValue(strValue,vl,m_Array);
}

//////////////////////////////////////////////////////////////////////////

int CVGCircle::GetValueType(CString strValueType) 
{ 
	if (strValueType==L"R") return 10; 
	else if (strValueType==L"CenterX") return 11; 
	else if (strValueType==L"CenterY") return 12;
	else return CVGGeoObject::GetValueType(strValueType);
}

CValue* CVGCircle::GetObjValue(int nType) 
{
	if (nType==10) return new CValueDouble(m_Radius); 
	else if (nType==11) return new CValueDouble(m_CenterX); 
	else if (nType==12) return new CValueDouble(m_CenterY);
	else return CVGGeoObject::GetObjValue(nType);
}

//////////////////////////////////////////////////////////////////////////

int CVGVector::GetValueType(CString strValueType) 
{ 
	if (strValueType==L"") return 20; 
	else return CVGLineBase::GetValueType(strValueType);
}

CValue* CVGVector::GetObjValue(int nType) 
{
	if (nType==20) return new CValueVector(x,y); 
	else return CVGGeoObject::GetObjValue(nType);
}

//////////////////////////////////////////////////////////////////////////

int CVGExpression::GetValueType(CString strValueType) 
{ 
	if (strValueType==L"") return 10; 
	else return CVGObject::GetValueType(strValueType);
}

CValue* CVGExpression::GetObjValue(int nType) 
{
	if (nType==10) return m_Exp.m_Value!=NULL ? m_Exp.m_Value->Clone() : NULL;
	else return CVGObject::GetObjValue(nType);
}

//////////////////////////////////////////////////////////////////////////

int CVGButtonBase::GetValueType(CString strValueType)
{
	if (strValueType==L"Text") return 20;
	//else if (strValueType==L"Select") return 1;
	else return CVGBound::GetValueType(strValueType);
}

CValue* CVGButtonBase::GetObjValue(int nType) 
{
	switch (nType)
	{
	case 20: return new CValueString(m_Text);
	default: return CVGBound::GetObjValue(nType);
	}
}

bool CVGButtonBase::SetValue(CString strValue, CVGExpression* vl, CArray<CVGObject*>* m_Array) 
{
	if (strValue==L"Text") { m_Text=((CValueString*)vl->m_Exp.m_Value)->m_Value; return false; }
	//else if (strValue==L"Select") { m_Select=((CValueBool*)vl->m_Exp.m_Value)->m_Value; return false; }
	else return CVGBound::SetValue(strValue,vl,m_Array);
}