#pragma once
#include "AxisInfo.h"
#include "gdi+.h"

class CVGGrid
{
public:
	CVGGrid(void);
public:
	~CVGGrid(void);
	bool m_bShowNumber;
	bool m_bOx;
	bool m_bOy;
	bool m_bShowGrid;
	int m_GridDashStyle;
public:
	void DrawAxis(Graphics* gr,int x,int y,CAxisInfo* m_AxisInfo);
	void DrawGrid(Graphics* gr,int x,int y,CAxisInfo* m_AxisInfo);
	void Serialize(CArchive& ar);
private:
	CString GetString(int Num, int zeroNum);
};
