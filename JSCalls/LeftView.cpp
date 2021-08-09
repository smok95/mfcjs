/////////////////////////////////////////////////////////////////
//             By Eugene Khodakovsky                           //
//                  April,2002                                 //
//            Last Update: April, 2002                         //
/////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JSCall.h"
#include "JSCallDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CFormView)

CLeftView::CLeftView()
	: CFormView(CLeftView::IDD),
	m_bLock(false)
{
	//{{AFX_DATA_INIT(CLeftView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CLeftView::~CLeftView()
{
}

void CLeftView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLeftView)
	DDX_Control(pDX, IDC_TREE_CTRL, m_treeCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLeftView, CFormView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CTRL, OnSelchangedTreeCtrl)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_CTRL, OnDblclkTreeCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

CJSCallDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJSCallDoc)));
	return (CJSCallDoc*)m_pDocument;
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	SetSize();
}

void CLeftView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	SetSize();
}

void CLeftView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	switch (lHint)
	{
	default:
		break;
	case HINT_UPDATE_WINDOW:    // redraw entire window
		Invalidate(FALSE);
		break;
	case HINT_ON_BEFORE_NAVIGATE:
		{
			m_bLock = true;
			LockWindowUpdate();
			m_treeCtrl.DeleteAllItems();
			HTREEITEM hRoot = m_treeCtrl.InsertItem("Loading ...");
			m_treeCtrl.SetItemData(hRoot,TreeNode_Root);
			UnlockWindowUpdate();
			m_bLock = false;
		}
		break;
	case HINT_ON_DOCUMENT_COMPLETE:
		{
			PopulateTree();
		}
		break;
	}
}

void CLeftView::SetSize()
{
	if(!::IsWindow(m_treeCtrl.GetSafeHwnd()))
		return;
	const int d = 5;
	CRect rcClient,rcTree;
	GetClientRect(rcClient);
	rcTree	= rcClient;
	rcTree.DeflateRect(d,d);
	m_treeCtrl.MoveWindow(rcTree);
}

void CLeftView::PopulateTree()
{
	m_bLock = true;
	LockWindowUpdate();
	m_treeCtrl.DeleteAllItems();
	
	CWebPage& web	= GetDocument()->m_webPage;
	
	HTREEITEM hRoot = m_treeCtrl.InsertItem("JScripts");
	m_treeCtrl.SetItemData(hRoot,TreeNode_Root);
	
	CComPtr<IHTMLElementCollection> spScripts;
	if(!web.GetJScripts(spScripts))
	{
		m_bLock = false;
		UnlockWindowUpdate();
		return;
	}

	long count = 0;
	HRESULT hr = spScripts->get_length(&count);
	ATLASSERT(SUCCEEDED(hr));
	
	long idx = -1;
	while(count--)
	{
		idx++;
		
		CComPtr<IDispatch> spDispatch;
		CComVariant name(idx),index(idx);
		hr = spScripts->item(name,index,(IDispatch**)&spDispatch);
		ATLASSERT(SUCCEEDED(hr));
		if(FAILED(hr))
			continue;


		CComPtr<IHTMLScriptElement> spScriptObj;
		hr = spDispatch->QueryInterface(IID_IHTMLScriptElement,(void**)&spScriptObj);
		ATLASSERT(SUCCEEDED(hr));
		if(FAILED(hr))
			continue;

		CComBSTR bstr;
		hr = spScriptObj->get_text(&bstr);
		ATLASSERT(SUCCEEDED(hr));

		CString strText(bstr),strFunc;
		CStringArray args;

		while( !(strFunc = web.ScanJScript(strText,args)).IsEmpty())
		{
			HTREEITEM hItemJScriptFunc = m_treeCtrl.InsertItem(strFunc,hRoot);
			m_treeCtrl.SetItemData(hItemJScriptFunc,TreeNode_JScriptFunc);
			if(args.GetSize())
			{
				HTREEITEM hItemArgsRoot = hItemJScriptFunc;
				for(int i = 0; i < args.GetSize(); i++)
				{
					HTREEITEM hItemArg = m_treeCtrl.InsertItem(args.GetAt(i),hItemArgsRoot);
					m_treeCtrl.SetItemData(hItemArg,TreeNode_Arg);
				}
			}
		}
	}

	m_treeCtrl.Expand(hRoot,TVE_EXPAND);
	UpdateWindow();
	UnlockWindowUpdate();
	m_bLock = false;
}


void CLeftView::OnSelchangedTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	if(m_bLock)
		return;

	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	TreeNodeType nodeType = TreeNode_None;
	CString strText;
	CStringArray args;

	if(hItem != NULL)
	{
		nodeType = (TreeNodeType)m_treeCtrl.GetItemData(hItem);
		strText = m_treeCtrl.GetItemText(hItem);
		if(nodeType == TreeNode_JScriptFunc)
		{
			UINT nCode = TVGN_CHILD;
			HTREEITEM hChildItem = hItem;
			while((hChildItem = m_treeCtrl.GetNextItem(hChildItem,nCode)) != NULL)
			{
				CString strChildName = m_treeCtrl.GetItemText(hChildItem);
				args.Add(strChildName);
				nCode = TVGN_NEXT;
			}
		}
	}

	GetDocument()->OnNodeSelected(nodeType,strText,args);
	
	*pResult = 0;
}

void CLeftView::OnDblclkTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_bLock)
		return;
	GetDocument()->OnNodeDblClick();
	*pResult = 0;
}
