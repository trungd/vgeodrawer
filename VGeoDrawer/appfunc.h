#include "stdafx.h"
#include "gdi+.h"
#include "VGObject.h"

class CVGObject;
class CVGGradientStyle;

CString GetAppDirectory();
CString LoadAppString(UINT uID);
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
void GetPen(int nStyle, Pen* pen);
void SplitString(CString str, char chSplit, CStringArray& strArray, BOOL bTrimLeftRight);
void RectFromTwoPoints(Point pt1, Point pt2, Rect& rect);
Font* LOGFONT_To_Font(LOGFONT* lgFont);
void SerializeFont(LOGFONT& lgFont,CArchive& ar);
void SerializeColor(Color& clr, CArchive& ar);
double GetNumberValue(CVGObject* obj);
Brush* GetBrush(CVGGradientStyle& style, Rect rect);
void SelectColor(Color& clr);
Color GetDarkerColor(Color clr);
void CheckPoint(Bitmap* bmp, stack<Point>& pts, int x, int y, Color oldClr, Color clr);
void FloodFill(Bitmap* bmp,int x, int y, Color clr);
void SetAlpha(Color& clr, int alpha);
void SerializeRect(Rect& rect,CArchive& ar);
Font* GetResizeFont(Font* font, int newSize);