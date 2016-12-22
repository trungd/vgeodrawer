#include "stdafx.h"
#include "appfunc.h"

CString GetAppDirectory()
{
	CString strFilePath;
	CString strFolderPath;

	//Get program file path
	TCHAR lpFileName[MAX_PATH+1];
	GetModuleFileName(NULL, lpFileName, MAX_PATH);
	strFilePath = lpFileName;

	//Get program folder
	int nLastIndex = strFilePath.ReverseFind('\\');
	if (nLastIndex!=-1) {
		strFolderPath = strFilePath.Left(nLastIndex);
	} else {
		strFolderPath = _T("\\");
	}

	return strFolderPath;
}

CString LoadAppString(UINT uID)
{
	CComBSTR bstrTemp;

	bstrTemp.LoadString(uID);

	return CW2CT(bstrTemp);

}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;  // number of image encoders

	UINT  size = 0; // size of the image encoder array in bytes


	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if(size == 0)
		return -1;  // Failure


	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1;  // Failure


	GetImageEncoders(num, size, pImageCodecInfo);

	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success

		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure

}

void GetPen(int nStyle, Pen* pen)
{
	switch (nStyle)
	{
	case 0:{break;}
	case 1:{float f[2]={1,2}; pen->SetDashPattern(f,2); break;}
	case 2:{float f[2]={1,4}; pen->SetDashPattern(f,2); break;}
	case 3:{float f[2]={3,3}; pen->SetDashPattern(f,2); break;}
	case 4:{float f[2]={7,5}; pen->SetDashPattern(f,2); break;}
	case 5:{float f[4]={1,3,7,3}; pen->SetDashPattern(f,4); break;}
	}
}

void SplitString(CString str, char chSplit, CStringArray& strArray, BOOL bTrimLeftRight)
{
	strArray.RemoveAll();
	int i=0;
	while (i<str.GetLength())
	{
		int pos=str.Find(chSplit,i);
		if (pos==-1) pos=str.GetLength();
		CString strTemp=str.Mid(i,pos-i);
		strArray.Add(str.Mid(i,pos-i));
		i=pos+1;
	}
}

void RectFromTwoPoints(Point pt1, Point pt2, Rect& rect)
{
	rect.X=min(pt1.X,pt2.X);
	rect.Y=min(pt1.Y,pt2.Y);
	rect.Width=abs(pt1.X-pt2.X);
	rect.Height=abs(pt1.Y-pt2.Y);
}

Font* LOGFONT_To_Font(LOGFONT* lgFont)
{
	int size=-MulDiv(lgFont->lfHeight, 72, AfxGetMainWnd()->GetDC()->GetDeviceCaps(LOGPIXELSY));
	int style=FontStyleRegular;
	if (lgFont->lfItalic) style=style | FontStyleItalic;
	if (lgFont->lfWeight==FW_BOLD) style=style | FontStyleBold;
	if (lgFont->lfStrikeOut) style=style | FontStyleStrikeout;
	if (lgFont->lfUnderline) style=style | FontStyleUnderline;
	Font* font=new Font((CString)lgFont->lfFaceName,size,style);
	return font;
}

Font* GetResizeFont(Font* font, int newSize)
{
	FontFamily ff; font->GetFamily(&ff);
	Font* f=new Font(&ff,newSize,font->GetStyle(),font->GetUnit());
	return f;
}

void SerializeFont(LOGFONT& lgFont,CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar.Write(&lgFont,sizeof(LOGFONT));
	}
	else
	{
		ar.Read(&lgFont,sizeof(LOGFONT));
	}
}

void SerializeColor(Color& clr, CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << clr.GetValue();
	}
	else
	{
		int argb;
		ar >> argb;
		clr.SetValue(argb);
	}
}

void SerializeRect(Rect& rect,CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << rect.X;
		ar << rect.Y;
		ar << rect.Width;
		ar << rect.Height;
	}
	else
	{
		ar >> rect.X;
		ar >> rect.Y;
		ar >> rect.Width;
		ar >> rect.Height;
	}
}

double GetNumberValue(CVGObject* obj)
{
	//if (obj->m_Type==OBJ_NUMBER) return ((CVGNumber*)obj)->m_Value;
	//else if (obj->m_Type==OBJ_EXPRESSION) return ((CVGExpression*)obj)->m_Value;
	return 0;
}

Brush* GetBrush( CVGGradientStyle& style, Rect rect )
{
	if (style.m_Color1.GetValue()==style.m_Color2.GetValue())
		return new SolidBrush(style.m_Color1);
	else
		return new LinearGradientBrush(rect,style.m_Color1,style.m_Color2,style.m_Mode);
}

void SelectColor(Color& clr)
{
	CColorDialog dlg(clr.ToCOLORREF());
	if (dlg.DoModal()==IDOK)
	{
		clr.SetFromCOLORREF(dlg.GetColor());
	}
}

Color GetDarkerColor(Color clr)
{
	const int add=-50;
	return Color(clr.GetAlpha(),clr.GetR()+add,clr.GetG()+add,clr.GetB()+add);
}

void FloodFill(Bitmap* bmp,int x, int y, Color clr)
{
	// Get the old and new colors.    
	Color old_color;
	bmp->GetPixel(x,y,&old_color);   
	if (clr.GetValue()==old_color.GetValue()) return;   
	// Start with the original point in the stack.    
	stack<Point> pts;
	pts.push(Point(x, y));   
	bmp->SetPixel(x, y, clr);   

	// While the stack is not empty, process a point.    
	while (pts.size() > 0)   
	{   
		Point pt = (Point)pts.top(); pts.pop();
		if (pt.X > 0) CheckPoint(bmp, pts, pt.X - 1, pt.Y, old_color, clr);   
		if (pt.Y > 0) CheckPoint(bmp, pts, pt.X, pt.Y - 1, old_color, clr);   
		if (pt.X < bmp->GetWidth() - 1) CheckPoint(bmp, pts, pt.X + 1, pt.Y, old_color, clr);   
		if (pt.Y < bmp->GetHeight() - 1) CheckPoint(bmp, pts, pt.X, pt.Y + 1, old_color, clr);   
	}   
}

void CheckPoint(Bitmap* bmp, stack<Point>& pts, int x, int y, Color oldClr, Color clr)
{
	Color clr2;
	bmp->GetPixel(x, y, &clr2);   
	if (clr2.GetValue()==oldClr.GetValue())   
	{   
		pts.push(Point(x, y));   
		bmp->SetPixel(x, y, clr);   
	}   

}

void SetAlpha(Color& clr, int alpha)
{
	clr=Color(alpha,clr.GetR(),clr.GetG(),clr.GetB());
}