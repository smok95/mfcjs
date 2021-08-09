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
// CJSCallDoc

IMPLEMENT_DYNCREATE(CJSCallDoc, CDocument)

BEGIN_MESSAGE_MAP(CJSCallDoc, CDocument)
	//{{AFX_MSG_MAP(CJSCallDoc)
	ON_COMMAND(ID_CALL_JSCRIPT, OnCallJscript)
	ON_UPDATE_COMMAND_UI(ID_CALL_JSCRIPT, OnUpdateCallJscript)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJSCallDoc construction/destruction

CJSCallDoc::CJSCallDoc():
	m_selNodeType(TreeNode_None),
	m_bDocumentComplete(false)
{
	// TODO: add one-time construction code here

}

CJSCallDoc::~CJSCallDoc()
{
}

BOOL CJSCallDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CJSCallDoc serialization

void CJSCallDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CJSCallDoc diagnostics

#ifdef _DEBUG
void CJSCallDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CJSCallDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void CJSCallDoc::DoNavigate(const CString strURL)
{
	m_strURL = strURL;
	UpdateAllViews(NULL,HINT_ON_DO_NAVIGATE);
}

void CJSCallDoc::DoJSCall(const CString strJSFunc)
{
	m_strJSFunc = strJSFunc;
	m_webPage.CallJScript(m_strJSFunc);
	UpdateAllViews(NULL,HINT_ON_DO_JSCALL);
}

/////////////////////////////////////////////////////////////////////////////
// CJSCallDoc commands

void CJSCallDoc::OnBeforeNavigate(LPCTSTR strURL)
{
	m_bDocumentComplete = false;
	m_selNodeType = TreeNode_None;
	m_strSelNodeName.Empty();
	m_strJSFunc.Empty();
	m_strURL = strURL;
	SetTitle("Loading...");
	UpdateAllViews(NULL,HINT_ON_BEFORE_NAVIGATE);
}

void CJSCallDoc::OnNavigateComplete(LPCTSTR strURL)
{
	m_strURL = strURL;
	UpdateAllViews(NULL,HINT_ON_NAVIGATE_COMPLETE);
}

void CJSCallDoc::OnDocumentComplete(LPCTSTR strURL,LPDISPATCH pDisp)
{
	m_strURL = strURL;
	SetTitle(m_strURL);
	m_bDocumentComplete = true;
	m_webPage.SetDocument(pDisp);
	UpdateAllViews(NULL,HINT_ON_DOCUMENT_COMPLETE);
}

void CJSCallDoc::OnNodeSelected(TreeNodeType node, const CString strNodeName,CStringArray& args)
{
	m_selNodeType		= node;
	m_strSelNodeName	= strNodeName;

	m_args.RemoveAll();
	m_args.Copy(args);
	if(m_selNodeType == TreeNode_JScriptFunc)
		m_strJSFunc = strNodeName;
	else
		m_strJSFunc.Empty();
	
	UpdateAllViews(NULL,HINT_ON_NODE_SELECTED);
}

void CJSCallDoc::OnNodeDblClick()
{
	bool bEn = m_bDocumentComplete && m_selNodeType == TreeNode_JScriptFunc;
	if(!bEn)
	{
		return;
	}

	CCallJScriptDlg dlg(this);
	dlg.DoModal();
}

void CJSCallDoc::OnCallJscript() 
{
	if(m_args.GetSize())
	{
		CCallJScriptDlg dlg(this);
		dlg.DoModal();
	}
	else
	{
		if(!m_webPage.CallJScript(m_strJSFunc))
		{
			AfxGetMainWnd()->MessageBox(m_webPage.GetLastError(),"JScripCall error");
		}
	}
}

void CJSCallDoc::OnUpdateCallJscript(CCmdUI* pCmdUI) 
{
	bool bEn = m_bDocumentComplete && m_selNodeType == TreeNode_JScriptFunc;
	pCmdUI->Enable(bEn);
}
