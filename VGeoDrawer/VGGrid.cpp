#include "StdAfx.h"
#include "VGGrid.h"
#include "math.h"
#include "appfunc.h"

CVGGrid::CVGGrid(void)
{
	m_GridDashStyle=0;
}

CVGGrid::~CVGGrid(void)
{
}

void CVGGrid::DrawAxis( Graphics* gr,int x,int y,CAxisInfo* m_AxisInfo )
{
	int tl=(m_AxisInfo->Pixel)*nZoom/100;
	if (tl==0) return;
	int nlen=3*nZoom/100;

	Point origintPt(m_AxisInfo->m_originPoint.X*nZoom/100,m_AxisInfo->m_originPoint.Y*nZoom/100);
	
	double k=m_AxisInfo->Unit;
	int znum=0;;
	if (k<1)
	{
		while (k<1)
		{
			znum--;
			k*=10;
		}
	}
	if (k>1)
	{
		while (k>=10)
		{
			znum++;
			k/=10;
		}
	}
	int num=(int)k;

	// Draw

	Pen pen(Color(255,0,0,0)); //Black
	SolidBrush  solidBrush(Color(255, 0, 0, 0));


	if (m_bOy) gr->DrawLine(&pen,origintPt.X,0,origintPt.X,y);
	if (m_bOx) gr->DrawLine(&pen,0,origintPt.Y,x,origintPt.Y);

	FontFamily fontFamily(L"Tahoma");
	Font font(&fontFamily, (float)7*nZoom/100);

	int i;
	int nStart,nEnd;

	int distance=5*nZoom/100;

	//Draw Oy
	if (m_bOy)
	{
		nStart=-(origintPt.Y/tl)-1;
		nEnd=((y-origintPt.Y)/tl)+1;
		for (i=nStart*tl;i<nEnd*tl;i=i+tl)
		{
			if (i!=0)	
			{
				//Draw Text
				if (m_bShowNumber) gr->DrawString(GetString(-num*i/tl,znum),-1,&font,PointF((REAL)(origintPt.X+5),REAL(origintPt.Y+i-distance)),&solidBrush);
			}
			gr->DrawLine(&pen,origintPt.X-nlen,origintPt.Y+i,
				origintPt.X+nlen,origintPt.Y+i);
		}
	}
	//Draw Ox
	if (m_bOx)
	{
		nStart=-(origintPt.X/tl)-1;
		nEnd=((x-origintPt.X)/tl)+1;
		for (i=nStart*tl;i<nEnd*tl;i=i+tl)
		{
			if (i!=0)	
			{
				//Draw Text
				if (m_bShowNumber) gr->DrawString(GetString(num*i/tl,znum),-1,&font,PointF((REAL)(origintPt.X+i-5),(REAL)(origintPt.Y+distance)),&solidBrush);
			}
			gr->DrawLine(&pen,origintPt.X+i,origintPt.Y-nlen,
				origintPt.X+i,origintPt.Y+nlen);
		}
	}

	if ((m_bOx||m_bOy) && m_bShowNumber) gr->DrawString(L"0",-1,&font,PointF((REAL)(origintPt.X+distance),(REAL)(origintPt.Y+distance)),&solidBrush);
}

CString CVGGrid::GetString(int Num, int zeroNum)
{
	char c[10];
	_itoa_s(Num > 0 ? Num : -Num ,c,10);
	CString str(c);
	if (zeroNum > 0)
	{
		for (int i=0;i<zeroNum;i++)
			str+=L"0";
	}
	if (zeroNum < 0)
	{
		int k=0;
		while (k<zeroNum && str.GetAt(str.GetLength()-1)=='0') { str.Delete(str.GetLength()-1); k++; }
		if (str.GetLength()>-zeroNum-k)
		{
			str.Insert(str.GetLength()+zeroNum+k,'.');
		}
		else
		{
			CString str2=L"0.";
			for (int i=0;i<-zeroNum-k-str.GetLength();i++) str2+=L"0";
			str=str2+str;
		}
// 		CString str2=L"0.";
// 		int pos=str.GetLength()-1;
// 		for (int i=0;i<-zeroNum;i++)
// 		{
// 			if (pos==str.GetLength()-1 && str[pos]=='0') { str.Delete(pos,1); pos--; }
// 			else if (pos<0) str=L"0"+str;
// 		}
// 		str2+=str;
// 		return str2;
	}
	if (Num<0) str=L"-"+str;
	return str;
}

void CVGGrid::DrawGrid( Graphics* gr,int x,int y,CAxisInfo* m_AxisInfo )
{
	if (!m_bShowGrid) return;
	double tl=m_AxisInfo->Pixel*nZoom/100;
	Pen pen(Color(255,192,192,192)); //Gray
	GetPen(m_GridDashStyle,&pen);

	Point origintPt(m_AxisInfo->m_originPoint.X*nZoom/100,m_AxisInfo->m_originPoint.Y*nZoom/100);

	int i;
	int start,end;
	//Draw Oy
	start=-(int)ceil(origintPt.Y/tl)-1;
	end=(int)ceil((y-origintPt.Y)/tl)+1;
	for (i=start*(int)tl;i<end*(int)tl;i=i+(int)tl)
	{
		gr->DrawLine(&pen,0,origintPt.Y+i, x,origintPt.Y+i);
	}
	//Draw Ox
	start=-(int)ceil(origintPt.X/tl)-1;
	end=(int)ceil((x-origintPt.X)/tl)+1;
	for (i=start*(int)tl;i<end*(int)tl;i=i+(int)tl)
	{
		gr->DrawLine(&pen,origintPt.X+i,0, origintPt.X+i,y);
	}
}

void CVGGrid::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_bOx;
		ar << m_bOy;
		ar << m_bShowGrid;
		ar << m_bShowNumber;
	}
	else 
	{
		ar >> m_bOx;
		ar >> m_bOy;
		ar >> m_bShowGrid;
		ar >> m_bShowNumber;
	}
}