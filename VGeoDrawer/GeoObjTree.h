#include "VGObject.h"
#include "VGObjContainer.h"
//#include "VGObject.h"

#pragma once

#define GROUP_BY_TYPE 0
#define GROUP_BY_SHOW_HIDE 1
#define GROUP_BY_FREE_DEPENDENDENT 2

#define ROOT_POS_POINT 0
#define ROOT_POS_LINE 1

#define ROOT_COUNT OBJ_COUNT

// CGeoObjListBox
class CVGObjContainer;

class CGeoObjTree : public CTreeCtrl
{
	DECLARE_DYNAMIC(CGeoObjTree)

public:
	CGeoObjTree();
	virtual ~CGeoObjTree();
	void AddObj(CVGObject* obj);
	int m_GroupBy;
	CArray<CVGObject*>* m_Array;
	CImageList m_imgList;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	void FillList();
	void OnRButtonUp(UINT nFlags, CPoint point);
	void Refresh();
public:
	CVGObjContainer* pArray;
	void Reset();
private:
	HTREEITEM root[OBJ_COUNT];
	bool bRoot[OBJ_COUNT];
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	int GetIconIndex(ObjType type);
};


