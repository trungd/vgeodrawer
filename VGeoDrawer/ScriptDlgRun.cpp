// ScriptDlgRun.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "ScriptDlgRun.h"
#include "Script\SafeArrayHelper.h"
#include "appfunc.h"


// CScriptDlgRun dialog

IMPLEMENT_DYNAMIC(CScriptDlgRun, CDialog)

CScriptDlgRun::CScriptDlgRun(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptDlgRun::IDD, pParent)
	, m_strParam(_T(""))
{

}

CScriptDlgRun::~CScriptDlgRun()
{
}

void CScriptDlgRun::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FUNCTION, m_FuncList);
	DDX_Text(pDX, IDC_EDIT_PARAM, m_strParam);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
}


BEGIN_MESSAGE_MAP(CScriptDlgRun, CDialog)
	ON_BN_CLICKED(IDC_RUN, &CScriptDlgRun::OnBnClickedRun)
END_MESSAGE_MAP()


// CScriptDlgRun message handlers

BOOL CScriptDlgRun::OnInitDialog()
{
	CDialog::OnInitDialog();

	int nCount = m_ScriptObj->GetMethodsCount();
	for(int i=0;i<nCount;i++)
	{
		CString strFunc = m_ScriptObj->GetNameAt(i);
		m_FuncList.AddString(strFunc);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CScriptDlgRun::OnBnClickedRun()
{
	UpdateData();
	CString strProc;
	m_FuncList.GetWindowText(strProc);

	CSafeArrayHelper sfHelper;
	try{
		CStringArray arrParam;
		SplitString(m_strParam,',',arrParam,TRUE);
		
		if (strProc.IsEmpty())
			sfHelper.Create(VT_VARIANT, 1, 0, 0);
		else
		{
			sfHelper.Create(VT_VARIANT, 1, 0, arrParam.GetCount());
		}

		_variant_t var;
		for (int i=0;i<arrParam.GetSize();i++)
		{
			var = _variant_t(arrParam[i]);
			sfHelper.PutElement(i, (void*)&var);
		}
		
		LPSAFEARRAY sa =  sfHelper.GetArray();
		_variant_t varRet;
		if (m_ScriptObj->RunProcedure(strProc, &sa, &varRet))
		{
			m_strResult=(LPCTSTR)(_bstr_t(varRet));
		}
		else
		{
			int line;
			CString strError = m_ScriptObj->GetErrorString(line);
			m_strResult=strError;
		}
	}
	catch(...)
	{
		int line;
		CString strError = m_ScriptObj->GetErrorString(line);
		m_strResult=strError;
	}

	UpdateData(FALSE);
}
