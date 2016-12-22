#pragma once
#include <vector>

using namespace std;

class CCommandArray
{
public:
	struct SubCommand
	{
		CString m_Command;
		CString m_Description;
		CString m_Input;
		CString m_Output;
		CString m_ToolName;
		int m_ImageIndex;
	};

	class CCmd
	{
	public:
 		CString m_CommandName;
		CArray<SubCommand> m_SubCmdArray;
		void Serialize(CArchive& ar);
		int GetIndexByInput(CString input);
		int GetSize();
		SubCommand* operator [](int nIndex);
	};

	class CStdCmd
	{
	public:
		CString strName;
		CString strDescription;
		CString strInput;
	};

	class CExpCmd
	{
	public:
		CString strName;
		CString strDescription;
		CString strInput;
		CString strOutput;
	};

	CCommandArray(void);
	~CCommandArray(void);

	CImageList m_ImageList;
	CArray<CCmd*> m_CmdArray;
	CArray<CStdCmd> m_CmdStdArray;
	CArray<CExpCmd> m_CmdExpArray;
	CCmd* operator [](int nIndex);
	CCmd* operator [](CString str);

	void Serialize( CArchive& ar );
	void AddCommand(CString m_Name,CString m_Des,CString m_Cmd,CString m_In,CString m_Out,CString m_ToolName,int m_imgIndex);
	void Delete(CString strName, CString strInput);
	static CString GetParam(CString strIn);
	int GetSize();
	SubCommand* GetSubCommandByToolName(CString strToolName);
	int GetToolImageIndex(CString toolName);
	void GetCommandByDeclaration(CString strCmd, CCmd** cmd, SubCommand** subCmd);
	CCommandArray::CCmd* GetCommandByString(CString str);
	static void GetParamType(CString strParam, CArray<int>* m_TypeArray);
	static int GetParamCount(CString strParam);
	void LoadCommands();
	void SaveCommands();
	void AddStdCommand(CString strName,CString strDes,CString strIn);
	int GetStdIndex(CString strName);
	void AddExpCommand(CString strName,CString strDes,CString strIn,CString strOut);
	int GetExpIndex(CString strName);
	void GetParamText(CString strParam, vector<CString>& m_strArray);
};
