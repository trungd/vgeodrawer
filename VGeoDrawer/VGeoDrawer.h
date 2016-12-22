// VGeoDrawer.h : main header file for the VGeoDrawer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "gdi+.h"


// CVGeoDrawerApp:
// See VGeoDrawer.cpp for the implementation of this class
//

class CVGeoDrawerApp : public CWinApp
{
public:
	CVGeoDrawerApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	virtual int Run();
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
};

extern CVGeoDrawerApp theApp;