#include "StdAfx.h"
#include "VGObjLabel.h"
#include <math.h>

CVGObjLabel::CVGObjLabel(void)
{

}

CVGObjLabel::~CVGObjLabel(void)
{
}

void CVGObjLabel::Clone(CVGObjLabel* obj)
{
	p1=obj->p1;
	p2=obj->p2;
	//m_Object=obj->m_Object;
	//m_Text=obj->m_Text;
}

void CVGObjLabel::Draw(Graphics* gr, CAxisInfo* m_AxisInfo)
{
// 	FontFamily fontFamily(L"Tahoma");
// 	Font font1(&fontFamily,10);
// 	Font font2(&fontFamily,7);
// 	SolidBrush br(Color(0,0,0));
// 	gr->DrawString(m_Text,-1,&font1,PointF((REAL)m_Pos.X,(REAL)m_Pos.Y),NULL,&br);
// 	RectF rectF;
// 	gr->MeasureString(m_Text,-1,&font1,PointF((REAL)m_Pos.X,(REAL)m_Pos.Y),&rectF);
// 	gr->DrawString(m_SubText,-1,&font2,PointF((REAL)(m_Pos.X+rectF.Width-3),(REAL)(m_Pos.Y+7)),NULL,&br);
// 	gr->DrawString(m_SuperText,-1,&font2,PointF((REAL)(m_Pos.X+rectF.Width-3),(REAL)(m_Pos.Y-3)),NULL,&br);
// 	m_Width=rectF.Width;
// 	m_Height=rectF.Height;
// 	Pen pen(Color(0,0,0));
// 	gr->DrawRectangle(&pen,Rect(m_Pos,Size(m_Width,m_Height)));
	//if (*m_Text!=m_prevText) SetLabel(*m_Text);
	Point pos=GetPos(m_AxisInfo);
	if (nZoom!=100)
	{
		Font* f=GetResizeFont(m_Font,m_Font->GetSize()*nZoom/100);
		Bitmap* bmp=CMathDraw::DrawObjectName(*m_Text,f);
		h=bmp->GetHeight(); w=bmp->GetWidth();
		gr->DrawImage(bmp,pos.X,pos.Y,bmp->GetWidth(),bmp->GetHeight());
		delete bmp;
		delete f;
	}
	else
	{
		Bitmap* bmp=CMathDraw::DrawObjectName(*m_Text,m_Font);
		h=bmp->GetHeight(); w=bmp->GetWidth();
		gr->DrawImage(bmp,pos.X,pos.Y,bmp->GetWidth(),bmp->GetHeight());
		delete bmp;
	}
	
	//if (m_bmpText!=NULL) 
	//{
	//	gr->DrawImage(m_bmpText,pos.X,pos.Y,m_bmpText->GetWidth(),m_bmpText->GetHeight());
	//	Pen pen(Color(0,0,0));
		//gr->DrawRectangle(&pen,Rect(m_Pos.X,m_Pos.Y,m_bmpText->GetWidth(),m_bmpText->GetHeight()));
	//}
}

Point CVGObjLabel::GetPos(CAxisInfo* m_AxisInfo)
{
	Point pos;
	switch (m_Object->m_Type)
	{
	case OBJ_POINT:
		{
			Point pt=m_AxisInfo->ToClientPoint(((CVGPoint*)m_Object)->m_x,((CVGPoint*)m_Object)->m_y);
			pos.X=pt.X+p1*nZoom/100;
			pos.Y=pt.Y+p2*nZoom/100;
			break;
		}
	}
	return pos;
}

bool CVGObjLabel::CheckMouseOver(Point point, CAxisInfo* m_AxisInfo)
{
	//if (m_bmpText==NULL) return FALSE;
	Point pos=GetPos(m_AxisInfo);
	if (PtInRect(CRect(pos.X,pos.Y,pos.X+w,pos.Y+h),CPoint(point.X,point.Y)))
		return TRUE;
	return FALSE;
}

void CVGObjLabel::MoveTo(int x, int y, CAxisInfo* m_AxisInfo)
{
// 	if (m_Object->m_Type=OBJ_POINT)
// 	{
// 		CVGPoint* pt=(CVGPoint*)m_Object;
// 		Point pt1(m_Pos.X+x,m_Pos.Y+y);
// 		Point pt2=m_AxisInfo->ToClientPoint(pt->m_x,pt->m_y);
// 		double dis=sqrt(pow((double)(pt1.X-pt2.X),2)+pow((double)(pt1.Y-pt2.Y),2));
// 		if (dis<=LABEL_DISTANCE_POINT) m_Pos=pt1;
// 		else
// 		{
// 			if (pt1.X==pt2.X)
// 			{
// 
// 			}
// 			else
// 			{
// 				double k=(pt2.Y-pt1.Y)/(pt2.X-pt1.X);
// 				double x=sqrt(LABEL_DISTANCE_POINT*LABEL_DISTANCE_POINT/(k*k+1));
// 				double y=k*x;
// 				m_Pos=Point((int)x+pt2.X,(int)y+pt2.Y);
// 			}
// 		}
// 	}
// 	else 
	switch (m_Object->m_Type)
	{
	case OBJ_POINT:
		{
			p1+=x;
			p2+=y;
			break;
		}
	}
	//m_Pos=Point(m_Pos.X+x,m_Pos.Y+y);
}

void CVGObjLabel::SetObject(CVGObject* obj)
{
	m_Object=obj;
	if (obj->m_Type==OBJ_POINT)
	{
		p1=3;p2=3;
	}
}

void CVGObjLabel::SetLabel(CString strText)
{
	*m_Text=strText;
	//m_prevText=strText;
	//if (m_bmpText!=NULL) delete m_bmpText;
	//m_bmpText=CMathDraw::DrawObjectName(strText,m_Font);
}

void CVGObjLabel::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << p1;
		ar << p2;
	}
	else 
	{
		ar >> p1;
		ar >> p2;
	}
}
