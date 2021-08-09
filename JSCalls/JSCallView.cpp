/////////////////////////////////////////////////////////////////
//             By Eugene Khodakovsky                           //
//                  April,2002                                 //
//            Last Update: April, 2002                         //
/////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JSCall.h"

#include "JSCallDoc.h"
#include "JSCallView.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJSCallView

IMPLEMENT_DYNCREATE(CJSCallView, CHtmlView)

BEGIN_MESSAGE_MAP(CJSCallView, CHtmlView)
	//{{AFX_MSG_MAP(CJSCallView)
	ON_COMMAND(ID_IE_GO_BACK, OnIeGoBack)
	ON_UPDATE_COMMAND_UI(ID_IE_GO_BACK, OnUpdateIeGoBack)
	ON_COMMAND(ID_IE_GO_FORWARD, OnIeGoForward)
	ON_UPDATE_COMMAND_UI(ID_IE_GO_FORWARD, OnUpdateIeGoForward)
	ON_COMMAND(ID_IE_STOP, OnIeStop)
	ON_UPDATE_COMMAND_UI(ID_IE_STOP, OnUpdateIeStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CJSCallView, CHtmlView)
	DISP_FUNCTION(CJSCallView, "CppFunc", CppFunc, VT_EMPTY, VTS_BSTR)
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJSCallView construction/destruction

CJSCallView::CJSCallView()
{
	// TODO: add construction code here
	EnableAutomation();
}

CJSCallView::~CJSCallView()
{
}

BOOL CJSCallView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CJSCallView drawing

void CJSCallView::OnDraw(CDC* pDC)
{
	CJSCallDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CJSCallView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
}

/////////////////////////////////////////////////////////////////////////////
// CJSCallView diagnostics

#ifdef _DEBUG
void CJSCallView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CJSCallView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CJSCallDoc* CJSCallView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJSCallDoc)));
	return (CJSCallDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJSCallView message handlers

void CJSCallView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	switch (lHint)
	{
	default:
		break;
	case HINT_UPDATE_WINDOW:    // redraw entire window
		Invalidate(FALSE);
		break;
	case HINT_ON_DOCUMENT_COMPLETE:
		{
			Invalidate(FALSE);
		}
		break;
	case HINT_ON_DO_NAVIGATE:
		{
			DWORD dwFlag = navNoReadFromCache;
			Navigate2(GetDocument()->m_strURL,dwFlag,NULL);
		}
	case HINT_ON_BEFORE_NAVIGATE:
	case HINT_ON_NAVIGATE_COMPLETE:
		{
			CFrameWnd* pFrame = GetParentFrame();
			ASSERT_KINDOF(CChildFrame,pFrame);
			((CChildFrame*)pFrame)->SetupURL(GetDocument()->m_strURL);
		}
		break;
	}
}

void CJSCallView::OnNavigateComplete2(LPCTSTR strURL)
{
	GetDocument()->OnNavigateComplete(strURL);
}

void CJSCallView::OnDocumentComplete(LPCTSTR strURL)
{
	LPDISPATCH pDisp = GetHtmlDocument();
	GetDocument()->OnDocumentComplete(strURL,pDisp);
}

void CJSCallView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags,
									LPCTSTR lpszTargetFrameName, 
									CByteArray& baPostedData,
									LPCTSTR lpszHeaders, BOOL* pbCancel)
{
	GetDocument()->OnBeforeNavigate(lpszURL);
}

void CJSCallView::OnIeGoBack() 
{
	GoBack();	
}

void CJSCallView::OnUpdateIeGoBack(CCmdUI* pCmdUI) 
{
}

void CJSCallView::OnIeGoForward() 
{
	GoForward();
}

void CJSCallView::OnUpdateIeGoForward(CCmdUI* pCmdUI) 
{

}

void CJSCallView::OnIeStop() 
{
	Stop();	
}

void CJSCallView::OnUpdateIeStop(CCmdUI* pCmdUI) 
{
	
}

HRESULT CJSCallView::OnGetExternal(LPDISPATCH *lppDispatch) {
	*lppDispatch = GetIDispatch(TRUE);
	return S_OK;
}

void CJSCallView::CppFunc(LPCTSTR bStr) {
	CString s = bStr;
	MessageBox(s);
}