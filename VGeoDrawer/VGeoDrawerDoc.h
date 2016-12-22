// VGeoDrawerDoc.h : interface of the CVGeoDrawerDoc class
//


#pragma once

#include "CommandsOrganizeDlg.h"
#include "VGGrid.h"
#include "AxisInfo.h"
#include "VGObjContainer.h"
#include "VGeoDrawerView.h"
#include "PropertiesBar.h"
#include "CommandCtrlBar.h"
#include "GeoObjTree.h"
#include "ConstructionStepsBar.h"
#include "ObjToolBar.h"
#include "ObjListBar.h"
#include "PageListBox.h"
#include "WatchBar.h"

#define WM_NEW_DOCUMENT WM_USER+1
#define DOCUMENT_MODE_GEO 1
#define DOCUMENT_MODE_PRESENTATION 2
#define DOCUMENT_MODE_TEXT 3

#define ID_SELECT_PAGE 42456

#define ID_CMD_PAGE_FIRST 32454
#define ID_CMD_PAGE_LAST ID_CMD_PAGE_FIRST+32

class CPropertiesBar;
class CDrawingPadDlg;
class CObjToolBar;
class CPageListBox;

class CVGeoDrawerDoc : public CDocument
{
protected: // create from serialization only
	CVGeoDrawerDoc();
	DECLARE_DYNCREATE(CVGeoDrawerDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	CArray<CVGObjContainer*> m_ObjContainerArr;
	int m_nCurrentContainer;

	CVGeoDrawerView* pView;

	CPropertiesBar* m_wndProperties;
	CCommandCtrlBar* m_wndCommand;
	CConstructionStepsBar* m_wndConstructionSteps;
	CObjToolBar* m_wndObjToolBar;
	CObjListBar* m_wndList;
	CPageListBox* m_wndPageList;
	CWatchBar* m_wndWatchBar;
	CComboBox* m_cbPage;
	CToolBar* m_wndMotionController;

	CString m_currentToolName;
	BOOL m_bHasPadSize;
	int m_Height, m_Width;
	int m_Mode;
	CScriptObject m_ScriptObject;
	bool m_bFitScreen;
	CCommandArray m_cmdArray;

	CStringArray m_crCommandName;
	CArray<CCommandArray::SubCommand*> m_crSubCommand;
	CArray<CVGObject*> m_crObj;
	
	CStatusBar* m_StatusBar;

	Bitmap* m_TraceBitmap;

	int m_bInit;

	bool m_presWhenStart;
	bool m_askWhenClose;

	bool m_bDesignMode;

	virtual ~CVGeoDrawerDoc();

public:
	CAxisInfo m_defaultAxisInfo;
	CVGGrid m_defaultGraphAxis;

	CVGDefaultValue m_defaultValue;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	void SetToolMode(CString strToolName);
	BOOL IsObjTypeAvailable(int nType, BOOL* bIsFinal=NULL);
	void AddCrObj(CVGObject* obj, BOOL bTest=FALSE);
	BOOL SaveModified();
	void SaveDefault();
	CVGObjContainer* GetObjCont();

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnOptionsCommandsOrganize();
	afx_msg void OnViewAxis();
	afx_msg void OnUpdateViewAxis(CCmdUI *pCmdUI);
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI *pCmdUI);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	afx_msg void OnViewStandardView();
	afx_msg void OnObjectTraceobject();
	afx_msg void OnUpdateObjectTraceobject(CCmdUI *pCmdUI);
	afx_msg void OnUpdateObjectAnimateobject(CCmdUI *pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnExportImage();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
public:
	afx_msg void OnEditDelete();
	afx_msg void OnEditDeleteTrace();
	void LoadDefaultSettings();
public:
	afx_msg void OnViewShowAllObjects();
public:
	afx_msg void OnEditRedo();
public:
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
public:
	afx_msg void OnEditUndo();
public:
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
public:
	afx_msg void OnEditHideselection();
	CVGeoDrawerView* GetView();
	
public:
	afx_msg void OnToolScript();
	void InitScriptObject();
public:
	afx_msg void OnToolsOptions();
	void SerializeSettings(CArchive& ar);
public:
	afx_msg void OnUpdateZoom(CCmdUI *pCmdUI);
public:
	afx_msg void OnZoom();
	afx_msg void OnZoom100();
	afx_msg void OnZoom200();
	afx_msg void OnZoom50();
	afx_msg void OnZoom75();
	afx_msg void OnZoomFitScreen();
public:
	void AddObjContainer(int pos=-1);
	void SetObjContainer(int nIndex);
public:
	afx_msg void OnPageNext();
	afx_msg void OnUpdatePageNext(CCmdUI *pCmdUI);
	afx_msg void OnPagePrevious();
	afx_msg void OnUpdatePagePrevious(CCmdUI *pCmdUI);
	afx_msg void OnPageNewPage();
	afx_msg void OnPageDeletePage();
	void DeleteAllObjCont();
public:
	afx_msg void OnToolsEvent();
	afx_msg void OnObjectProperties();
public:
	afx_msg void OnWatchwndAddwatch();
	afx_msg void OnObjectAnimateobject();
	void AddExpression();
	void ResetSelection();
	void EndSelectObject();
public:
	afx_msg void OnToolPresentMode();
public:
	afx_msg void OnUpdatePageDeletePage(CCmdUI *pCmdUI);
public:
	afx_msg void OnViewDesignmode();
public:
	afx_msg void OnUpdateViewDesignmode(CCmdUI *pCmdUI);
};