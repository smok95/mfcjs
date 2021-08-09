#if !defined(AFX_NAVIGATEBAR_H__BB4A1B5A_AB7E_4AEE_A8EE_69B08024A858__INCLUDED_)
#define AFX_NAVIGATEBAR_H__BB4A1B5A_AB7E_4AEE_A8EE_69B08024A858__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NavigateBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNavigateBar dialog
class CJSCallDoc;

class CNavigateBar : public CDialogBar
{
// Construction
public:
	CNavigateBar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNavigateBar)
	enum { IDD = CG_IDD_NAVIGATEBAR };
	CString	m_strURL;
	//}}AFX_DATA

	BOOL Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);

	void SetDocument(CJSCallDoc* pDoc);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavigateBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNavigateBar)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CJSCallDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVIGATEBAR_H__BB4A1B5A_AB7E_4AEE_A8EE_69B08024A858__INCLUDED_)
