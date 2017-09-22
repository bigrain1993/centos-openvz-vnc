// FileType.cpp : implementation file
//

#include "stdafx.h"
#include "OS.h"
#include "FileType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileType dialog


CFileType::CFileType(CWnd* pParent /*=NULL*/)
	: CDialog(CFileType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileType)
	m_edit1 = _T("");
	//}}AFX_DATA_INIT
}


void CFileType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileType)
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileType, CDialog)
	//{{AFX_MSG_MAP(CFileType)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileType message handlers
