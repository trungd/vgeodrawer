#pragma once
#include "gdi+.h"

#define PIXEL_SIZE 8

#define MODE_PEN 0
#define MODE_LINE 1
#define MODE_RECTANGLE 2
#define MODE_ELLIPSE 3
#define MODE_POINT 4
#define MODE_COLORSEL 5
#define MODE_COLOR 6

#define WM_ICONCHANGE WM_USER+1
#define WM_REDRAWCOLORPICKER WM_USER+2
#define ID_TIMER 1

// CIconEditor

class CIconEditor : public CWnd
{
	DECLARE_DYNAMIC(CIconEditor)

public:
	CIconEditor();
	virtual ~CIconEditor();
	Bitmap* m_bmp;
	Bitmap* m_tmpBitmap;
	void SetPixel(int x, int y, Graphics* gr, Color color);
	CToolBar m_ToolBar;
	int m_Mode;
	Color* m_leftClr;
	Color* m_rightClr;
	void SetBitmap(Bitmap* bmp);
	BOOL m_bAntiAlias;
private:
	Point m_prevPoint;
	void CopyBmpToTemp();
	void CopyTempToBmp();
	Rect RectFromTwoPoints(Point pt1, Point pt2);
	BOOL m_bMouseMove;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	BOOL RegisterWndClass();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	Point GetPixel(CPoint pt);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void ClearIcon();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
