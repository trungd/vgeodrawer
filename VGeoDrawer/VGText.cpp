#include "stdafx.h"
#include "VGObject.h"
#include "appfunc.h"

CVGText::CVGText()
{
	m_bmpText=NULL;
	m_bModeMath=FALSE;
 	m_Font.lfCharSet=DEFAULT_CHARSET;
 	m_Font.lfStrikeOut=FALSE;
 	m_Font.lfItalic=FALSE;
	m_Font.lfUnderline=FALSE;
	m_Font.lfWeight=FW_NORMAL;
	wcsncpy(m_Font.lfFaceName, _T("Tahoma"), LF_FACESIZE);
 	m_Font.lfHeight=-12;
	//m_Font=new Font(L"Times New Roman",12);

	m_Height=0;
	m_Width=0;
}

CVGText::~CVGText()
{
	for (int i=0;i<m_ExpArr.GetSize();i++)
		delete m_ExpArr[i];
}

void CVGText::DrawText()
{
	//if (AfxGetApp()->GetMainWnd()==NULL) return; // Khi open file b?ng cách nh?p chu?t tr?c ti?p thì ph?n này l?i
	Font* font=LOGFONT_To_Font(&m_Font);

	if (m_bmpText!=NULL) delete m_bmpText;
	
	CString strText;
	int addToLength=0;
	if (m_ExpArr.GetSize()!=0)
	{
		strText=m_TextDraw;
		CString s;
		for (int i=0;i<m_ExpArr.GetSize();i++)
		{
			s=m_ExpArr[i]->GetStringValue();
			strText.Insert(m_ExpArrPos[i]+addToLength,s);
			addToLength+=s.GetLength();
		}
	}
	else
		strText=m_Text;

	if (m_bModeMath) m_bmpText=CMathDraw::DrawExpression(strText,m_bAvailable ? m_Color : Color::Red,font);
	else m_bmpText=CMathDraw::DrawText(strText,m_bAvailable ? m_Color : Color::Red,font);

	delete font;
	//m_Height=m_bmpText->GetHeight();
	//m_Width=m_bmpText->GetWidth();
}

bool CVGText::CanCalc()
{
	for (int i=0;i<m_ExpArr.GetSize();i++)
		if (!m_ExpArr[i]->CanCalc()) return FALSE;
	return TRUE;
}

void CVGText::Calc(CAxisInfo* m_AxisInfo)
{
	if (m_bCalc || !CanCalc()) return;
	
	m_bCalc=TRUE;
	for (int i=0;i<m_ExpArr.GetSize();i++)
		m_ExpArr[i]->Calc();
	DrawText();
}

void CVGText::Draw(Graphics* gr, CAxisInfo* m_AxisInfo, bool bTrace)
{
	if (!m_bVisible || m_bTemp) return;
	
	if (m_bmpText==NULL) DrawText();

	CVGBound::Draw(gr,m_AxisInfo,bTrace);

	Rect rect=GetDrawRect();
	gr->DrawImage(m_bmpText,rect.X,rect.Y,0,0,min(m_bmpText->GetWidth(),rect.Width),min(m_bmpText->GetHeight(),rect.Height),UnitPixel);
}

void CVGText::SetText(CString strText, CArray<CVGObject*>* m_Array, CScriptObject* scriptObj, CStringArray* m_strReplacedNameArr)
{
	for (int j=0;j<m_ExpArr.GetSize();j++) delete m_ExpArr[j];
	m_ExpArr.RemoveAll();
	m_ExpArrPos.RemoveAll();

	m_Text=strText;
	int i;
	i=0;
	CString strTextDraw;
	while (i<m_Text.GetLength())
	{
		int pos=m_Text.Find('#',i);
		if (pos==-1) pos=m_Text.GetLength();
		strTextDraw+=m_Text.Mid(i,pos-i);
		i=pos+1;
		if (i!=m_Text.GetLength()+1)
		{
			pos=m_Text.Find('#',i);
			if (pos==-1) pos=m_Text.GetLength();
			CString str=m_Text.Mid(i,pos-i);

			CGeoExp* e=new CGeoExp();
			e->m_ScriptObject=scriptObj;
			e->SetExpression(str,m_Array,false,m_strReplacedNameArr);
			m_ExpArr.Add(e);
			m_ExpArrPos.Add(strTextDraw.GetLength());
			i=pos+1;
		}
	}

	if (m_ExpArr.GetSize()!=0)
		m_TextDraw=strTextDraw;

	DrawText();
}

void CVGText::Serialize(CArchive& ar , CArray<CVGObject*>* objArr)
{
	CVGBound::Serialize(ar,objArr);

	if (ar.IsStoring())
	{
		ar << m_Text;
	}
	else
	{
		ar >> m_Text;
	}
	SerializeFont(m_Font,ar);
}

CString CVGText::GetText()
{
	return m_Text;
}

void CVGText::Clone( CVGObject* obj )
{
	CVGBound::Clone(obj);
	
	CVGText* t=(CVGText*)obj;
	m_Text=t->m_Text;
	m_bModeMath=t->m_bModeMath;
	memcpy(&m_Font,&t->m_Font,sizeof(LOGFONT));
}

bool CVGText::IsRelated(CVGObject* obj)
{
	for (int i=0;i<m_ExpArr.GetSize();i++)
		if (m_ExpArr[i]->IsRelated(obj)) return true;
	return false;
}