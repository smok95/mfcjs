// JSCallView.h : interface of the CJSCallView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_JSCALLVIEW_H__B77E6876_47A1_4F7A_AD9A_716B2C33C983__INCLUDED_)
#define AFX_JSCALLVIEW_H__B77E6876_47A1_4F7A_AD9A_716B2C33C983__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CJSCallView : public CHtmlView
{
protected: // create from serialization only
	CJSCallView();
	DECLARE_DYNCREATE(CJSCallView)

// Attributes
public:
	CJSCallDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJSCallView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CJSCallView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags,
		LPCTSTR lpszTargetFrameName, CByteArray& baPostedData,
		LPCTSTR lpszHeaders, BOOL* pbCancel);
	virtual void OnNavigateComplete2(LPCTSTR strURL);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);

	HRESULT OnGetExternal(LPDISPATCH *lppDispatch) override;

	void CppFunc(LPCTSTR bStr);
// Generated message map functions
protected:
	//{{AFX_MSG(CJSCallView)
	afx_msg void OnIeGoBack();
	afx_msg void OnUpdateIeGoBack(CCmdUI* pCmdUI);
	afx_msg void OnIeGoForward();
	afx_msg void OnUpdateIeGoForward(CCmdUI* pCmdUI);
	afx_msg void OnIeStop();
	afx_msg void OnUpdateIeStop(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
};

#ifndef _DEBUG  // debug version in JSCallView.cpp
inline CJSCallDoc* CJSCallView::GetDocument()
   { return (CJSCallDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JSCALLVIEW_H__B77E6876_47A1_4F7A_AD9A_716B2C33C983__INCLUDED_)
