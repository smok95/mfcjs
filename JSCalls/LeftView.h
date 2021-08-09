#if !defined(AFX_LEFTVIEW_H__A05D3B05_CCD4_4E69_8627_F047645CFB61__INCLUDED_)
#define AFX_LEFTVIEW_H__A05D3B05_CCD4_4E69_8627_F047645CFB61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LeftView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLeftView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CJSCallDoc;

class CLeftView : public CFormView
{
protected:
	CLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLeftView)

// Form Data
public:
	//{{AFX_DATA(CLeftView)
	enum { IDD = IDD_FORM_LEFT_VIEW };
	CTreeCtrl	m_treeCtrl;
	//}}AFX_DATA

// Attributes
public:

	CJSCallDoc* GetDocument();

// Operations
public:
	void SetSize();
	void PopulateTree();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CLeftView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangedTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	bool	m_bLock;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__A05D3B05_CCD4_4E69_8627_F047645CFB61__INCLUDED_)
