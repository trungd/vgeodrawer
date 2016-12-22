// PresSetting.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "PresSetting.h"


// CPresSetting dialog

IMPLEMENT_DYNAMIC(CPresSetting, CDialog)

CPresSetting::CPresSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CPresSetting::IDD, pParent)
{

}

CPresSetting::~CPresSetting()
{
}

void CPresSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK2, m_chkPresWhenStart);
	DDX_Check(pDX, IDC_CHECK3, m_chkAskWhenClose);
}


BEGIN_MESSAGE_MAP(CPresSetting, CDialog)
	ON_BN_CLICKED(IDOK, &CPresSetting::OnBnClickedOk)
END_MESSAGE_MAP()


// CPresSetting message handlers

void CPresSetting::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
