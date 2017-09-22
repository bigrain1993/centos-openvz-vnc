// FileCreatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OS.h"
#include "FileCreatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileCreatDlg dialog


CFileCreatDlg::CFileCreatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileCreatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileCreatDlg)
	m_edit1 = _T("");
	m_edit2 = _T("");
	m_edit3 = _T("");
	//}}AFX_DATA_INIT
}


void CFileCreatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileCreatDlg)
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDV_MaxChars(pDX, m_edit1, 3);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDV_MaxChars(pDX, m_edit2, 2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDV_MaxChars(pDX, m_edit3, 191);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileCreatDlg, CDialog)
	//{{AFX_MSG_MAP(CFileCreatDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileCreatDlg message handlers
