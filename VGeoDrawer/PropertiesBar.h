#pragma once
#include "sizecbar.h"
#include "VGObject.h"
#include "VGeoDrawerDoc.h"
#include "PropertyGrid.h"
#include "PropertyTextItem.h"
#include "CustomItem.h"
#include "PropertyButtonCmd.h"
#include "PropertyGradient.h"

#define IDC_TAB 100

class CVGeoDrawerDoc;
class CPropertiesAxisGrid;
class CPropertiesCommon;

class CPropertiesBar :
	public CSizingControlBar
{
public:
	CPropertiesBar(void);

	CPropertyGrid m_Grid;

	CFont m_Font;
	CArray<CVGObject*> m_Selection;
public:
	~CPropertiesBar(void);
public:
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	void RefreshProperties();
	afx_msg LRESULT OnItemChanged(WPARAM, LPARAM);
	bool CheckSelection(ObjType nType1=OBJ_NONE, ObjType nType2=OBJ_NONE, ObjType nType3=OBJ_NONE, ObjType nType4=OBJ_NONE, ObjType nType5=OBJ_NONE);
	bool CheckNoBoundObjSelection();
	bool CheckGeoSelection();
	bool CheckLineSelection();
	bool CheckTextSelection();
public:
	CVGeoDrawerDoc* pDoc;
	CPropertyTextItem m_propertyTextItem;
	CPropertyButtonCmdItem m_propertyButtonCmd;
	CPropertyGradientPanel m_propertyGradient;
private:
	HSECTION secInfo,secEvent,secValue,secStyle,secAnimateTrace,secObjWin,secOther,secAxis,secGrid;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
