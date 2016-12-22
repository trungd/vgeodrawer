#include "stdafx.h"
#include "VGObject.h"

CVGButtonBase::CVGButtonBase()
{
	m_Color=Color::LightGray;
	m_bButtonMouseDown=false;
	m_bButtonMouseOver=false;
	m_Height=100;
	m_Width=100;

	m_Font.lfCharSet=DEFAULT_CHARSET;
	m_Font.lfStrikeOut=FALSE;
	m_Font.lfItalic=FALSE;
	m_Font.lfUnderline=FALSE;
	m_Font.lfWeight=FW_NORMAL;
	wcsncpy(m_Font.lfFaceName, _T("Tahoma"), LF_FACESIZE);
	m_Font.lfHeight=-12;

	m_ColorMouseDown.m_Color1=Color::LightGray;
	m_ColorMouseDown.m_Color2=Color::White;
	m_ColorMouseDown.m_Mode=LinearGradientModeVertical;

	m_ColorMouseOver.m_Color1=Color::WhiteSmoke;
	m_ColorMouseOver.m_Color2=Color::White;
	m_ColorMouseOver.m_Mode=LinearGradientModeVertical;

	m_ColorNormal.m_Color1=Color::White;
	m_ColorNormal.m_Color2=Color::WhiteSmoke;
	m_ColorNormal.m_Mode=LinearGradientModeVertical;
}

CVGButtonBase::~CVGButtonBase()
{

}

bool CVGButtonBase::CheckMouseOver(Point point, CAxisInfo* m_AxisInfo)
{
	if (!IsVisible()) return false;

	return (CVGBound::CheckMouseOver(point,m_AxisInfo) && !CheckMouseOverButton(point));
}

void CVGButtonBase::OnClick()
{

}

void CVGButtonBase::Serialize(CArchive& ar , CArray<CVGObject*>* objArr)
{
	CVGBound::Serialize(ar,objArr);

	if (ar.IsStoring())
	{
		SerializeColor(m_BorderColor, ar);
		ar << m_Text;
		ar << m_Command;
		ar << m_bButtonMouseOver;
		ar << m_bButtonMouseDown;
	}
	else
	{
		SerializeColor(m_BorderColor, ar);
		ar >> m_Text;
		ar >> m_Command;
		ar >> m_bButtonMouseOver;
		ar >> m_bButtonMouseDown;
	}
}

void CVGButtonBase::Clone(CVGObject* obj)
{
	CVGBound::Clone(obj);

	CVGButtonBase* btn=(CVGButtonBase*)obj;
	m_bButtonMouseDown=btn->m_bButtonMouseDown;
	m_bButtonMouseOver=btn->m_bButtonMouseOver;
	m_ColorMouseDown=btn->m_ColorMouseDown;
	m_ColorMouseOver=btn->m_ColorMouseOver;
	m_Text=btn->m_Text;
	m_Command=btn->m_Command;
}