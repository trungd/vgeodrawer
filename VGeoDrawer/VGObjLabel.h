#pragma once
#include "AxisInfo.h"
#include "VGObject.h"
#include "MathDraw.h"

#define LABEL_DISTANCE_POINT 40

class CVGObject;

class CVGObjLabel
{
public:
	CVGObjLabel(void);
	CVGObject* m_Object;
	CString* m_Text;

	void SetObject(CVGObject* obj);
	void SetLabel(CString strText);
	void Draw(Graphics* gr, CAxisInfo* m_AxisInfo);
	bool CheckMouseOver(Point point, CAxisInfo* m_AxisInfo);
	void MoveTo(int x, int y, CAxisInfo* m_AxisInfo);

	int p1,p2;
	int h,w;
	Font* m_Font;
public:
	~CVGObjLabel(void);
	Point GetPos(CAxisInfo* m_AxisInfo);
	void Serialize(CArchive& ar);
	void Clone(CVGObjLabel* obj);
};
