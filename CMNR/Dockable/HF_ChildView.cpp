﻿#include "pch.h"
#include "CMNR.h"
#include "HF_ChildView.h"
#include "HF_MainFrm.h"
#include "afxdockablepane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HF_ChildView::HF_ChildView()
{
}

HF_ChildView::~HF_ChildView()
{

}

BEGIN_MESSAGE_MAP(HF_ChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDC_BUTTON_VIEW_LEFT, &HF_ChildView::OnButtonViewLeft)
	ON_COMMAND(IDC_BUTTON_VIEW_RIGHT, &HF_ChildView::OnButtonViewRight)
	ON_COMMAND(IDC_BUTTON_VIEW_UP, &HF_ChildView::OnButtonViewUp)
	ON_COMMAND(IDC_BUTTON_VIEW_FRONT, &HF_ChildView::OnButtonViewFront)
	ON_COMMAND(IDC_BUTTON_VIEW_DOWN, &HF_ChildView::OnButtonViewDown)
	ON_COMMAND(IDC_BUTTON_VIEW_BACK, &HF_ChildView::OnButtonViewBack)

	ON_COMMAND_RANGE(IDM_SHAPE_CIRCLE, IDM_SHAPE_SQUARE, &HF_ChildView::OnShape)
	ON_COMMAND_RANGE(IDM_SHAPE_RED, IDM_SHAPE_BLUE, &HF_ChildView::OnColor)

	ON_UPDATE_COMMAND_UI_RANGE(IDM_SHAPE_CIRCLE, IDM_SHAPE_SQUARE, &HF_ChildView::OnShapeUI)
	ON_UPDATE_COMMAND_UI_RANGE(IDM_SHAPE_RED, IDM_SHAPE_BLUE, &HF_ChildView::OnColorUI)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

BOOL HF_ChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), (HBRUSH)GetStockObject(BLACK_BRUSH), nullptr);
	return TRUE;
}

void HF_ChildView::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);

	constexpr int WIDTH = 180;
	constexpr int BTN_WIDTH = 40;
	constexpr int GAP = 10;
	int nCenterX = rect.right - WIDTH / 2;
	int nCenterY = rect.bottom - WIDTH / 2;

	CRect recLeft(
		nCenterX - BTN_WIDTH / 2 - BTN_WIDTH,	// left
		nCenterY - BTN_WIDTH / 2,				// top
		nCenterX - BTN_WIDTH / 2,				// right
		nCenterY - BTN_WIDTH / 2 + BTN_WIDTH	// bootm
	);

	CRect recRight(
		nCenterX + BTN_WIDTH / 2,				// left
		nCenterY - BTN_WIDTH / 2,				// top
		nCenterX + BTN_WIDTH / 2 + BTN_WIDTH,	// right
		nCenterY - BTN_WIDTH / 2 + BTN_WIDTH	// bootm
	);

	CRect recFront(
		nCenterX - BTN_WIDTH / 2,				// left
		nCenterY - BTN_WIDTH / 2 - BTN_WIDTH,	// top
		nCenterX - BTN_WIDTH / 2 + BTN_WIDTH,	// right
		nCenterY - BTN_WIDTH / 2				// bootm
	);

	CRect recBack(
		nCenterX - BTN_WIDTH / 2,				// left
		nCenterY + BTN_WIDTH / 2,				// top
		nCenterX - BTN_WIDTH / 2 + BTN_WIDTH,	// right
		nCenterY + BTN_WIDTH / 2 + BTN_WIDTH	// bootm
	);

	CRect recUp(
		nCenterX - BTN_WIDTH * 2,				// left
		nCenterY - BTN_WIDTH * 2,				// top
		nCenterX - BTN_WIDTH,					// right
		nCenterY - BTN_WIDTH					// bootm
	);

	CRect recDown(
		nCenterX + BTN_WIDTH,					// left
		nCenterY - BTN_WIDTH * 2,				// top
		nCenterX + BTN_WIDTH * 2,				// right
		nCenterY - BTN_WIDTH					// bootm
	);

	CRect recCenter(
		nCenterX - 16,				// left
		nCenterY - 16,				// top
		nCenterX + 16,				// right
		nCenterY + 16				// bootm
	);

	if (m_BtnLeft.m_hWnd == NULL)
	{
		m_BtnLeft.Create(_T(""), WS_CHILD | WS_VISIBLE, recLeft, this, IDC_BUTTON_VIEW_LEFT);
		m_BtnLeft.SetImage(IDB_PNG_LEFT);

		m_BtnRight.Create(_T(""), WS_CHILD | WS_VISIBLE, recRight, this, IDC_BUTTON_VIEW_RIGHT);
		m_BtnRight.SetImage(IDB_PNG_RIGHT);

		m_BtnFront.Create(_T(""), WS_CHILD | WS_VISIBLE, recFront, this, IDC_BUTTON_VIEW_FRONT);
		m_BtnFront.SetImage(IDB_PNG_FRONT);

		m_BtnBack.Create(_T(""), WS_CHILD | WS_VISIBLE, recBack, this, IDC_BUTTON_VIEW_BACK);
		m_BtnBack.SetImage(IDB_PNG_BACK);

		m_BtnUp.Create(_T(""), WS_CHILD | WS_VISIBLE, recUp, this, IDC_BUTTON_VIEW_UP);
		m_BtnUp.SetImage(IDB_PNG_UP);

		m_BtnDown.Create(_T(""), WS_CHILD | WS_VISIBLE, recDown, this, IDC_BUTTON_VIEW_DOWN);
		m_BtnDown.SetImage(IDB_PNG_DOWN);

		m_BtnCenter.Create(_T(""), WS_CHILD | WS_VISIBLE, recCenter, this, IDC_BUTTON_VIEW_DOWN);
		m_BtnCenter.SetImage(IDB_PNG_CENTER);
	}
	else
	{
		m_BtnLeft.MoveWindow(recLeft);
		m_BtnRight.MoveWindow(recRight);
		m_BtnFront.MoveWindow(recFront);
		m_BtnBack.MoveWindow(recBack);
		m_BtnUp.MoveWindow(recUp);
		m_BtnDown.MoveWindow(recDown);
		m_BtnCenter.MoveWindow(recCenter);
	}

	CPoint points[3];

	CRect rcClient;
	GetClientRect(&rcClient);
	int cx = rcClient.Width() / 2;
	int cy = rcClient.Height() / 2;

	CRect rcShape(cx - SZ, cy - SZ, cx + SZ, cy + SZ);
	CBrush brush(m_clrColors[m_nColor]);
	CBrush* pOldBrush = dc.SelectObject(&brush);
	switch (m_nShape) {
	case 0: // Circle 
		dc.Ellipse(rcShape);
		break;
	case 1: // Triangle 
		points[0].x = cx - SZ;
		points[0].y = cy + SZ;
		points[1].x = cx;
		points[1].y = cy - SZ;
		points[2].x = cx + SZ;
		points[2].y = cy + SZ;
		dc.Polygon(points, 3);
		break;
	case 2: // Square 
		dc.Rectangle(rcShape);
		break;
	}
	dc.SelectObject(pOldBrush);
}

int HF_ChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//CDockablePane::ShowPane(TRUE, FALSE, TRUE);
	return 0;
}

void HF_ChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd::OnMouseMove(nFlags, point);
}

void HF_ChildView::OnButtonViewLeft()
{
	HF_MainFrame* pMainWnd = (HF_MainFrame*)theApp.m_pMainWnd;
	pMainWnd->Log(LogType::ERR, _T("Move Left"));
}

void HF_ChildView::OnButtonViewRight()
{
	HF_MainFrame* pMainWnd = (HF_MainFrame*)theApp.m_pMainWnd;
	pMainWnd->Log(LogType::INFO, _T("Move Right"));
}

void HF_ChildView::OnButtonViewUp()
{
	HF_MainFrame* pMainWnd = (HF_MainFrame*)theApp.m_pMainWnd;
	pMainWnd->Log(LogType::WARN, _T("Move Up"));
}

void HF_ChildView::OnButtonViewFront()
{
	HF_MainFrame* pMainWnd = (HF_MainFrame*)theApp.m_pMainWnd;
	pMainWnd->Log(LogType::INFO, _T("Move Front"));
}

void HF_ChildView::OnButtonViewDown()
{
	HF_MainFrame* pMainWnd = (HF_MainFrame*)theApp.m_pMainWnd;
	pMainWnd->Log(LogType::ERR, _T("Move Down"));
}

void HF_ChildView::OnButtonViewBack()
{
	HF_MainFrame* pMainWnd = (HF_MainFrame*)theApp.m_pMainWnd;
	pMainWnd->Log(LogType::WARN, _T("Move Back"));
}

BOOL HF_ChildView::PreTranslateMessage(MSG* pMsg)
{
	return CWnd::PreTranslateMessage(pMsg);
}

void HF_ChildView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	int cx = rcClient.Width() / 2;
	int cy = rcClient.Height() / 2;
	CRect rcShape(cx - SZ, cy - SZ, cx + SZ, cy + SZ);

	CPoint pos = point;
	ScreenToClient(&pos);
	CPoint points[3];
	BOOL bShapeClicked = FALSE;
	int dx, dy;
	// 
	// Hit test the shape. 
	// 
	switch (1) {
	case 0: // Circle 
		dx = pos.x - cx;
		dy = pos.y - cy;
		if ((dx * dx) + (dy * dy) <= (SZ * SZ))
			bShapeClicked = TRUE;
		break;
	case 1: // Triangle 
		if (rcShape.PtInRect(pos)) {
			dx = min(pos.x - rcShape.left, rcShape.right - pos.x);
			if ((rcShape.bottom - pos.y) < (2 * dx))
				bShapeClicked = TRUE;
		}
		break;
	case 2: // Square 
		if (rcShape.PtInRect(pos))
			bShapeClicked = TRUE;
		break;
	}
	// 
	// Display a context menu if the shape was clicked. 
	// 
	if (bShapeClicked) {
		CMenu menu;
		menu.LoadMenu(IDR_CONTEXTMENU);
		CMenu* pContextMenu = menu.GetSubMenu(0);
		for (int i = 0; i < 5; i++)
			pContextMenu->ModifyMenu(IDM_COLOR_RED + i,
				MF_BYCOMMAND | MF_OWNERDRAW,
				IDM_COLOR_RED + i);
		pContextMenu->TrackPopupMenu(TPM_LEFTALIGN |
			TPM_LEFTBUTTON |
			TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
		return;
	}
	// 
	// Call the base class if the shape was not clicked. 
	// 
	CWnd::OnContextMenu(pWnd, point);
}

void HF_ChildView::OnShape(UINT id)
{
	m_nShape = id - IDM_SHAPE_CIRCLE;
	Invalidate();
}
void HF_ChildView::OnColor(UINT id)
{
	m_nColor = id - IDM_SHAPE_RED;
	Invalidate();
}

void HF_ChildView::OnShapeUI(CCmdUI* pCmd)
{
	pCmd->SetCheck(m_nShape == (pCmd->m_nID - IDM_SHAPE_CIRCLE));
}
void HF_ChildView::OnColorUI(CCmdUI* pCmd)
{
	pCmd->SetCheck(m_nColor == (pCmd->m_nID - IDM_SHAPE_RED));
}