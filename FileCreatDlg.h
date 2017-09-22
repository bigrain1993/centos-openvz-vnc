#if !defined(AFX_FILECREATDLG_H__0E1AA452_68CE_4321_9286_D594EC0C6594__INCLUDED_)
#define AFX_FILECREATDLG_H__0E1AA452_68CE_4321_9286_D594EC0C6594__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileCreatDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileCreatDlg dialog

class CFileCreatDlg : public CDialog
{
// Construction
public:
	CFileCreatDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileCreatDlg)
	enum { IDD = IDD_FILECREAT };
	CString	m_edit1;
	CString	m_edit2;
	CString	m_edit3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileCreatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileCreatDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILECREATDLG_H__0E1AA452_68CE_4321_9286_D594EC0C6594__INCLUDED_)
