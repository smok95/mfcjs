/////////////////////////////////////////////////////////////////
//             By Eugene Khodakovsky                           //
//                  April,2002                                 //
//            Last Update: April, 2002                         //
/////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JSCall.h"
#include "JSCallDoc.h"
#include "CallJScriptDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCallJScriptDlg dialog


CCallJScriptDlg::CCallJScriptDlg(CJSCallDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CCallJScriptDlg::IDD, pParent),
	m_pDoc(pDoc)
{
	//{{AFX_DATA_INIT(CCallJScriptDlg)
	m_strFunctionName = _T("");
	m_strArguments = _T("");
	//}}AFX_DATA_INIT

	if(m_pDoc)
		m_strFunctionName = m_pDoc->m_strJSFunc;
}


void CCallJScriptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCallJScriptDlg)
	DDX_Text(pDX, IDC_EDIT_FUNCTION_NAME, m_strFunctionName);
	DDX_Text(pDX, IDC_EDIT_ARGUMENTS, m_strArguments);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCallJScriptDlg, CDialog)
	//{{AFX_MSG_MAP(CCallJScriptDlg)
	ON_BN_CLICKED(IDC_BUTTON_RUN, OnButtonRun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCallJScriptDlg message handlers

BOOL CCallJScriptDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCallJScriptDlg::OnButtonRun() 
{
	UpdateData();
	ASSERT(m_pDoc != NULL);
	if(m_pDoc == NULL)
		return;

	CWebPage& web = m_pDoc->m_webPage;
	
	CStringArray args;
	CString strArgs(m_strArguments),strArg;
	while(!(strArg = GetNextToken(strArgs,",")).IsEmpty())
	{
		args.Add(strArg);
	}
	
	if(!web.CallJScript(m_strFunctionName,args))
	{
		MessageBox(web.GetLastError(),"JScripCall error");
	}
}
