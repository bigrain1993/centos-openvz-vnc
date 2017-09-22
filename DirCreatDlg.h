#if !defined(AFX_DIRCREATDLG_H__C8EA8BF7_0F37_4338_A35C_B19DC68F7DCB__INCLUDED_)
#define AFX_DIRCREATDLG_H__C8EA8BF7_0F37_4338_A35C_B19DC68F7DCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirCreatDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirCreatDlg dialog

class CDirCreatDlg : public CDialog
{
// Construction
public:
	CDirCreatDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDirCreatDlg)
	enum { IDD = IDD_DIRCREAT };
	CString	m_edit1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirCreatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDirCreatDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRCREATDLG_H__C8EA8BF7_0F37_4338_A35C_B19DC68F7DCB__INCLUDED_)
