// OSDlg.h : header file
//

#if !defined(AFX_OSDLG_H__C2BBFDD5_1AF7_4307_A201_310C94CD25C0__INCLUDED_)
#define AFX_OSDLG_H__C2BBFDD5_1AF7_4307_A201_310C94CD25C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CPU.h"
#include "FS.h"

/////////////////////////////////////////////////////////////////////////////
// COSDlg dialog

class COSDlg : public CDialog
{
//USER

// Construction
public:
	CFont m_font;
	long systotaltime;
	CFS fs;
	CCPU cpu;
	COSDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(COSDlg)
	enum { IDD = IDD_OS_DIALOG };
	CStatic	m_static10;
	CStatic	m_static9;
	CStatic	m_static11;
	CStatic	m_disk;
	CTreeCtrl	m_tree1;
	CStatic	m_static8;
	CListBox	m_list3;
	CProgressCtrl	m_progress1;
	CStatic	m_static7;
	CSliderCtrl	m_slider1;
	CStatic	m_static6;
	CStatic	m_static5;
	CStatic	m_static4;
	CStatic	m_static3;
	CStatic	m_static2;
	CStatic	m_static1;
	CListBox	m_list2;
	CListBox	m_list1;
	CString	m_edit1;
	CString	m_edit2;
	CString	m_edit3;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(COSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRunthread();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEndthread();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRestart();
	afx_msg void OnMenuMakedir();
	afx_msg void OnMenuDeldir();
	afx_msg void OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuType();
	afx_msg void OnMenuDelete();
	afx_msg void OnMenuCreat();
	afx_msg void OnFormat();
	afx_msg void OnMenuAddthr();
	afx_msg void OnMyhelp();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSDLG_H__C2BBFDD5_1AF7_4307_A201_310C94CD25C0__INCLUDED_)
