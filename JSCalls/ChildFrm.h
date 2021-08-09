// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__E79D63D5_A9AB_4174_B013_65A34C4C356D__INCLUDED_)
#define AFX_CHILDFRM_H__E79D63D5_A9AB_4174_B013_65A34C4C356D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NavigateBar.h"

class CJSCallDoc;

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:
	CJSCallDoc* GetDocument();
	
	void SetupURL(const CString strURL);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	CNavigateBar	m_wndNavigateBar;
	CSplitterWnd	m_wndSplitter;
	bool			m_bInit;

	//{{AFX_MSG(CChildFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

inline
void CChildFrame::SetupURL(const CString strURL)
{
	m_wndNavigateBar.m_strURL = strURL;
	if(::IsWindow(m_wndNavigateBar.GetSafeHwnd()))
		m_wndNavigateBar.UpdateData(FALSE);
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__E79D63D5_A9AB_4174_B013_65A34C4C356D__INCLUDED_)
