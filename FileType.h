#if !defined(AFX_FILETYPE_H__19702690_304C_4381_9A5A_CC6F0696AC79__INCLUDED_)
#define AFX_FILETYPE_H__19702690_304C_4381_9A5A_CC6F0696AC79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileType dialog

class CFileType : public CDialog
{
// Construction
public:
	//À¦°óµ½¶Ô»°¿òIDD_FILETYPE
	CFileType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileType)
	enum { IDD = IDD_FILETYPE };
	CString	m_edit1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileType)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileType)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETYPE_H__19702690_304C_4381_9A5A_CC6F0696AC79__INCLUDED_)
