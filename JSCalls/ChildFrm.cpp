/////////////////////////////////////////////////////////////////
//             By Eugene Khodakovsky                           //
//                  April,2002                                 //
//            Last Update: April, 2002                         //
/////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JSCall.h"

#include "ChildFrm.h"
#include "LeftView.h"
#include "JSCallDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_WM_CREATE()
	ON_COMMAND_EX(CG_ID_VIEW_NAVIGATEBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_NAVIGATEBAR, OnUpdateControlBarMenu)
	//{{AFX_MSG_MAP(CChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame():
	m_bInit(false)
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

CJSCallDoc* CChildFrame::GetDocument()
{
	CDocument* pDoc = GetActiveDocument();
	if(pDoc->IsKindOf(RUNTIME_CLASS(CJSCallDoc)))
		return (CJSCallDoc*)pDoc;
	ASSERT(0);
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::ActivateFrame(int nCmdShow) 
{
	if(!m_bInit)
	{
		CJSCallDoc* pDoc = GetDocument();
		m_wndNavigateBar.SetDocument(pDoc);
		pDoc->DoNavigate(m_wndNavigateBar.m_strURL);
		m_bInit = true;
	}
	nCmdShow = SW_SHOWMAXIMIZED;
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if(!m_wndSplitter.CreateStatic(this, 1, 2)) 
		return false;
	if(!m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CLeftView), CSize(200,350), pContext)) 
		return false;
	if(!m_wndSplitter.CreateView(0,1, pContext->m_pNewViewClass, CSize(750,320), pContext)) 
		return false;
	return TRUE;
}

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "NavigateBar":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CChildFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_NAVIGATEBAR
	//   5. Assign the item a Caption: NavigateBar

	// TODO: Change the value of CG_ID_VIEW_NAVIGATEBAR to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndNavigateBar
		if (!m_wndNavigateBar.Create(this, CG_IDD_NAVIGATEBAR,
			CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
			CG_ID_VIEW_NAVIGATEBAR))
		{
			TRACE0("Failed to create dialog bar m_wndNavigateBar\n");
			return -1;		// fail to create
		}

		m_wndNavigateBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndNavigateBar);

	}

	return 0;
}
