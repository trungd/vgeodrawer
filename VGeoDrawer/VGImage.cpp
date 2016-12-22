#include "stdafx.h"
#include "VGObject.h"

CVGImage::CVGImage()
{
	m_Top=0;
	m_Left=0;
	m_Bitmap=NULL;
}

CVGImage::~CVGImage()
{
	delete m_Bitmap;
}

void CVGImage::Draw(Graphics* gr, CAxisInfo* m_AxisInfo, bool bTrace/* =FALSE */)
{
	if (!m_bVisible  || m_bTemp || !m_bAvailable) return;
	gr->DrawImage(m_Bitmap,min(m_Left,m_Left+m_Width)*nZoom/100,min(m_Top,m_Top+m_Height)*nZoom/100,
		abs(m_Width)*nZoom/100,abs(m_Height)*nZoom/100);
	
	CVGBound::Draw(gr,m_AxisInfo,bTrace);
}

void CVGImage::SetBitmap(Bitmap* bmp)
{
	if (m_Bitmap!=NULL) delete m_Bitmap;
	m_Bitmap=bmp->Clone(0,0,bmp->GetWidth(),bmp->GetHeight(),PixelFormat32bppARGB);
	m_Width=m_Bitmap->GetWidth();
	m_Height=m_Bitmap->GetHeight();
}

void CVGImage::Serialize(CArchive& ar , CArray<CVGObject*>* objArr)
{
	CVGBound::Serialize(ar,objArr);

	if (ar.IsStoring())
	{
		Rect rect(0,0,m_Bitmap->GetWidth(),m_Bitmap->GetHeight());
		//m_Bitmap->
		//ar.Write(bmpData.Scan0,bmpData.Stride);
	}
	else
	{
	}
}