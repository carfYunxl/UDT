﻿#ifndef __HF_CHILD_VIEW_H__
#define __HF_CHILD_VIEW_H__

#include "HF_IcInfoDlg.h"

constexpr int SZ = 200;

class HF_ChildView : public CWnd
{
public:
	HF_ChildView();

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual			~HF_ChildView();
	virtual BOOL	PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg void	OnPaint();
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void	OnButtonViewLeft();
	afx_msg void	OnButtonViewRight();
	afx_msg void	OnButtonViewUp();
	afx_msg void	OnButtonViewFront();
	afx_msg void	OnButtonViewDown();
	afx_msg void	OnButtonViewBack();
	afx_msg void	OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void	OnShape(UINT id);
	afx_msg void	OnColor(UINT id);
	afx_msg void	OnShapeUI(CCmdUI* pCmd);
	afx_msg void	OnColorUI(CCmdUI* pCmd);
	DECLARE_MESSAGE_MAP()

private:
	CFont		m_Font;
	CMFCButton	m_BtnLeft;
	CMFCButton	m_BtnRight;
	CMFCButton	m_BtnFront;
	CMFCButton	m_BtnBack;
	CMFCButton	m_BtnUp;
	CMFCButton	m_BtnDown;
	CMFCButton	m_BtnCenter;
	CStatic		m_StaI2cClk;
	CEdit		m_EdtI2cClk;
	CStatic		m_StaI2cAddr;
	CComboBox	m_ComboI2cAddr;
	CStatic		m_StaBridge;
	CComboBox	m_ComboBridge;

	UINT		m_nColor{0};
	UINT		m_nShape{0};
public:
	inline static const COLORREF m_clrColors[5] = {
		RGB(255, 0, 0),
		RGB(255, 255, 0),
		RGB(0, 255, 0),
		RGB(0, 255, 255),
		RGB(0, 0, 255)
	};
};

#endif //__HF_CHILD_VIEW_H__
