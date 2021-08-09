/////////////////////////////////////////////////////////////////
//             By Eugene Khodakovsky                           //
//                  April,2002                                 //
//            Last Update: July, 2011                          //
/////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JSCall.h"
#include "NavigateBar.h"
#include "JSCallDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNavigateBar dialog


CNavigateBar::CNavigateBar(CWnd* pParent /*=NULL*/):
	m_pDoc(NULL)
{
	//{{AFX_DATA_INIT(CNavigateBar)
	m_strURL = _T("http://www.cpplab.net/Articles/JSCalls/TestPage/JSCallTestPage.htm");
	//}}AFX_DATA_INIT
}

void CNavigateBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNavigateBar)
	DDX_Text(pDX, IDC_EDIT_URL, m_strURL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNavigateBar, CDialogBar)
	//{{AFX_MSG_MAP(CNavigateBar)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNavigateBar message handlers

void CNavigateBar::SetDocument(CJSCallDoc* pDoc)
{
	m_pDoc = pDoc;
}

BOOL CNavigateBar::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
{
	if(!CDialogBar::Create(pParentWnd,nIDTemplate,nStyle,nID))
		return false;
	UpdateData(FALSE);
	return true;
}

BOOL CNavigateBar::PreTranslateMessage(MSG* pMsg) 
{
	bool bProcess = false;
	if(pMsg->message == WM_KEYDOWN)
	{
		UINT nChar = pMsg->wParam;
		LONG lKeyData = pMsg->lParam;
		switch(nChar)
		{
		case VK_ESCAPE:
		default:
			break;
		case VK_RETURN:
			{
				UpdateData();
				if(m_pDoc)
				{
					m_pDoc->DoNavigate(m_strURL);
				}
				bProcess = true;
			}
			break;
		}
	}
	if(bProcess)
		return TRUE;
	return CDialogBar::PreTranslateMessage(pMsg);
}
