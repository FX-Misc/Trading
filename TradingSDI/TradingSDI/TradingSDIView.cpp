
#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "TradingSDI.h"
#endif
#include "TradingSDIDoc.h"
#include "TradingSDIView.h"
#include "resource.h"
#include "symbol_grp.h"
#include "define_margin.h"
#include "ClientCreate.h"
#include "OrderForm.h"
#include "NetPosForm.h"
#include "CommentChangeForm.h"
#include "DealingForm.h"
#include "Group2WiseNetPosForm.h"
#include "GroupWiseNetPosForm.h"
#include "AuditForm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CTradingSDIView, CTabView)
	
BEGIN_MESSAGE_MAP(CTradingSDIView, CTabView)
	// Standard printing commands
	ON_WM_CREATE()		
	ON_COMMAND(ID_FILE_SYMBOLGROUPMAPPING, &CTradingSDIView::OnFileSymbolgroupmapping)
	ON_COMMAND(ID_FILE_DEFINESYMBOLMARGIN, &CTradingSDIView::OnFileDefinesymbolmargin)
	ON_COMMAND(ID_FILE_CREATECLIENT, &CTradingSDIView::OnFileCreateclient)
END_MESSAGE_MAP()
CTradingSDIView::CTradingSDIView()
{
	// TODO: add construction code here

}
CTradingSDIView::~CTradingSDIView()
{
}
BOOL CTradingSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CTabView::PreCreateWindow(cs);
}

// CTradingSDIView drawing

void CTradingSDIView::OnDraw(CDC* pDC)
{
	
	/*const CString str("Hello");
    pDC->TextOut(0, 0, str);	 */

}

int CTradingSDIView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
		CMFCTabCtrl m_tab;
		CRect m_rect;
		m_rect.SetRectEmpty();
		m_tab.DestroyWindow();
		m_tab.Create(CMFCTabCtrl::STYLE_3D_VS2005,m_rect,this,1,CMFCTabCtrl::LOCATION_TOP);
		m_tab.EnableTabSwap(false);
		AddView(RUNTIME_CLASS(COrderForm),_T("Order"),0);
		AddView(RUNTIME_CLASS(CNetPosForm),_T("NetPosition"),1);
		AddView(RUNTIME_CLASS(CCommentChangeForm),_T("CommentChange"),2);
		AddView(RUNTIME_CLASS(CDealingForm),_T("Dealing"),3);
		AddView(RUNTIME_CLASS(CGroup2WiseNetPosForm),_T("Group2WiseNetPos"),4);
		AddView(RUNTIME_CLASS(CGroupWiseNetPosForm),_T("GroupWiseNetPos"),5);
		AddView(RUNTIME_CLASS(CAuditForm),_T("Audit"),6);
	return 0;
}

// CTradingSDIView diagnostics

#ifdef _DEBUG


CTradingSDIDoc* CTradingSDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTradingSDIDoc)));
	return (CTradingSDIDoc*)m_pDocument;
}
#endif 

void CTradingSDIView::OnFileSymbolgroupmapping()
{
	symbol_grp smbl_dlg;	
	 smbl_dlg.DoModal();	 
}


void CTradingSDIView::OnFileDefinesymbolmargin()
{
	define_margin dlg;
	dlg.DoModal();
}


void CTradingSDIView::OnFileCreateclient()
{
	ClientCreate dlg;
	dlg.DoModal();
	// TODO: Add your command handler code here
}
