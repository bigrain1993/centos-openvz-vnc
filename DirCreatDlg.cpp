// DirCreatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OS.h"
#include "DirCreatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirCreatDlg dialog


CDirCreatDlg::CDirCreatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDirCreatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDirCreatDlg)
	m_edit1 = _T("");
	//}}AFX_DATA_INIT
}


void CDirCreatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirCreatDlg)
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDV_MaxChars(pDX, m_edit1, 3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDirCreatDlg, CDialog)
	//{{AFX_MSG_MAP(CDirCreatDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirCreatDlg message handlers
