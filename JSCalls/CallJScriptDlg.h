#if !defined(AFX_CALLJSCRIPTDLG_H__F8563467_24CD_45D8_B9D4_0BD6E4FEA143__INCLUDED_)
#define AFX_CALLJSCRIPTDLG_H__F8563467_24CD_45D8_B9D4_0BD6E4FEA143__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CallJScriptDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCallJScriptDlg dialog
class CJSCallDoc;

class CCallJScriptDlg : public CDialog
{
// Construction
public:
	CCallJScriptDlg(CJSCallDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCallJScriptDlg)
	enum { IDD = IDD_DIALOG_CALL_JSCRIPT };
	CString	m_strFunctionName;
	CString	m_strArguments;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCallJScriptDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	CJSCallDoc*	m_pDoc;

	// Generated message map functions
	//{{AFX_MSG(CCallJScriptDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonRun();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALLJSCRIPTDLG_H__F8563467_24CD_45D8_B9D4_0BD6E4FEA143__INCLUDED_)
