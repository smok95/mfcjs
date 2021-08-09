// JSCallDoc.h : interface of the CJSCallDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_JSCALLDOC_H__25ECAFD3_7ABA_4B10_9ECB_B97CD452EA48__INCLUDED_)
#define AFX_JSCALLDOC_H__25ECAFD3_7ABA_4B10_9ECB_B97CD452EA48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WebPage.h"

enum UpdateHints
{
	HINT_UPDATE_WINDOW,
	HINT_ON_BEFORE_NAVIGATE,
	HINT_ON_NAVIGATE_COMPLETE,
	HINT_ON_DOCUMENT_COMPLETE,
	HINT_ON_NODE_SELECTED,
	HINT_ON_DO_NAVIGATE,
	HINT_ON_DO_JSCALL,
};

typedef enum TreeNodeType
{
	TreeNode_None,
	TreeNode_Root,
	TreeNode_JScriptFunc,
	TreeNode_ArgRoot,
	TreeNode_Arg,
};


class CJSCallDoc : public CDocument
{
protected: // create from serialization only
	CJSCallDoc();
	DECLARE_DYNCREATE(CJSCallDoc)

// Attributes
public:

	CWebPage		m_webPage;
	CString			m_strURL;
	bool			m_bDocumentComplete;

	TreeNodeType	m_selNodeType;
	CString			m_strSelNodeName;

	CString			m_strJSFunc;
	CStringArray	m_args;


// Operations
public:
	void DoNavigate(const CString strURL);
	void DoJSCall(const CString strJSFunc);
	
	//HTML
	void OnBeforeNavigate(LPCTSTR lpszURL);
	void OnNavigateComplete(LPCTSTR strURL);
	void OnDocumentComplete(LPCTSTR lpszURL,LPDISPATCH pDisp);

	//Tree
	void OnNodeSelected(TreeNodeType node, const CString strNodeName,CStringArray& args);
	void OnNodeDblClick();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJSCallDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CJSCallDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CJSCallDoc)
	afx_msg void OnCallJscript();
	afx_msg void OnUpdateCallJscript(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JSCALLDOC_H__25ECAFD3_7ABA_4B10_9ECB_B97CD452EA48__INCLUDED_)
