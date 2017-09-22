// OSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OS.h"
#include "OSDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COSDlg dialog

COSDlg::COSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COSDlg::IDD, pParent)
{

	//{{AFX_DATA_INIT(COSDlg)
	m_edit1 = _T("");
	m_edit2 = _T("");
	m_edit3 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	systotaltime=0;
}

void COSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COSDlg)
	DDX_Control(pDX, IDC_STATIC10, m_static10);
	DDX_Control(pDX, IDC_STATIC9, m_static9);
	DDX_Control(pDX, IDC_STATIC11, m_static11);
	DDX_Control(pDX, IDC_DISK, m_disk);
	DDX_Control(pDX, IDC_TREE1, m_tree1);
	DDX_Control(pDX, IDC_STATIC8, m_static8);
	DDX_Control(pDX, IDC_LIST3, m_list3);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress1);
	DDX_Control(pDX, IDC_STATIC7, m_static7);
	DDX_Control(pDX, IDC_SLIDER1, m_slider1);
	DDX_Control(pDX, IDC_STATIC6, m_static6);
	DDX_Control(pDX, IDC_STATIC5, m_static5);
	DDX_Control(pDX, IDC_STATIC4, m_static4);
	DDX_Control(pDX, IDC_STATIC3, m_static3);
	DDX_Control(pDX, IDC_STATIC2, m_static2);
	DDX_Control(pDX, IDC_STATIC1, m_static1);
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COSDlg, CDialog)
	//{{AFX_MSG_MAP(COSDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RUNTHREAD, OnRunthread)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ENDTHREAD, OnEndthread)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RESTART, OnRestart)
	ON_COMMAND(ID_MENU_MAKEDIR, OnMenuMakedir)
	ON_COMMAND(ID_MENU_DELDIR, OnMenuDeldir)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, OnRclickTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
	ON_COMMAND(ID_MENU_TYPE, OnMenuType)
	ON_COMMAND(ID_MENU_DELETE, OnMenuDelete)
	ON_COMMAND(ID_MENU_CREAT, OnMenuCreat)
	ON_BN_CLICKED(IDC_FORMAT, OnFormat)
	ON_COMMAND(ID_MENU_ADDTHR, OnMenuAddthr)
	ON_BN_CLICKED(IDC_MYHELP, OnMyhelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COSDlg message handlers

BOOL COSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_font.CreateFont(25,12,0,0,
		FW_HEAVY,TRUE,FALSE,
		FALSE,ANSI_CHARSET,
		OUT_DEVICE_PRECIS,
		CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY,FF_MODERN,
		"Arial");
	m_static9.SetFont(&m_font);
	m_static10.SetFont(&m_font);
	m_static11.SetFont(&m_font);
	m_slider1.SetRange(1,10);
	m_slider1.SetPos(cpu.timelength-1);
	m_progress1.SetRange(0,cpu.timelength-1);
	fs.InitTree();
	fs.InitReadDisk();
//	fs.InitDisk();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COSDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		fs.InitDraw();
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COSDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void COSDlg::OnRunthread() 
{
	// TODO: Add your control notification handler code here
	SetTimer(1,500,NULL);
}

void COSDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_progress1.SetPos(0);
	systotaltime++;
	CString s;
	s.Format("%ld",systotaltime);
	m_static8.SetWindowText(s);


	cpu.scheduling();
//	CDialog::OnTimer(nIDEvent);
}

void COSDlg::OnEndthread() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
	m_progress1.SetPos(0);
}


void COSDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if(nSBCode==SB_THUMBPOSITION)
	{
		CString s;
		s.Format("%ld",nPos);
		m_static7.SetWindowText(s);
		cpu.timelength=nPos+1;
		m_progress1.SetRange(0,cpu.timelength-1);
	}else
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

void COSDlg::OnRestart() 
{
	// TODO: Add your control notification handler code here
	if((cpu.block_0.getcount()==0)&&(cpu.block_1.getcount()==0)
		&&(cpu.block_2.getcount()==0)&&(cpu.block_3.getcount()==0)
		&&(cpu.GetCpuStatus()==0)&&(cpu.ready.getcount()==0))
	{
		KillTimer(1);
		systotaltime=0;
		cpu.totalnum=0;
		m_static8.SetWindowText("0");
		m_static7.SetWindowText("2");
		cpu.timelength=2+1;
		m_slider1.SetPos(cpu.timelength-1);
		m_progress1.SetRange(0,cpu.timelength-1);
		int n=m_list3.GetCount();
		while(n!=0)
		{
			m_list3.DeleteString(0);
			n--;
		}
	}
}

void COSDlg::OnMenuMakedir() 
{
	// TODO: Add your command handler code here
	fs.CreatDir();
}

void COSDlg::OnMenuDeldir() 
{
	// TODO: Add your command handler code here
	fs.DeleteDir();
}

void COSDlg::OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
		CMenu *pTopMenu,*pChildMenu;
	pTopMenu=new CMenu;
	pTopMenu->LoadMenu(IDR_MENU1);
    pChildMenu=pTopMenu->GetSubMenu(0);

	if(fs.enabledir==1)
	{
		pChildMenu->EnableMenuItem(ID_MENU_DELETE,MF_GRAYED);
		pChildMenu->EnableMenuItem(ID_MENU_TYPE,MF_GRAYED);
		pChildMenu->EnableMenuItem(ID_MENU_ADDTHR,MF_GRAYED);
	}else if(fs.enabledir==0)
	{
		pChildMenu->EnableMenuItem(ID_MENU_MAKEDIR,MF_GRAYED);
		pChildMenu->EnableMenuItem(ID_MENU_DELDIR,MF_GRAYED);
		pChildMenu->EnableMenuItem(ID_MENU_CREAT,MF_GRAYED);
	}

	CPoint point;
	GetCursorPos(&point);
	pChildMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);


	*pResult = 0;
}

void COSDlg::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	fs.DirItemChanged();
	*pResult = 0;
}

void COSDlg::OnMenuType() 
{
	// TODO: Add your command handler code here
	fs.TypeFile();
}

void COSDlg::OnMenuDelete() 
{
	// TODO: Add your command handler code here
	fs.DeleteFile();
}

void COSDlg::OnMenuCreat() 
{
	// TODO: Add your command handler code here
	fs.CreatFile();
}

void COSDlg::OnFormat() 
{
	// TODO: Add your control notification handler code here
	fs.enabledir=1;
	strcpy(fs.curdir.name,"cch");
	strcpy(fs.curdir.ext,"||");
	fs.curdir.first=2;
	fs.curdir.length=1;
	fs.curdir.attribute=0;//'0'表示目录
	for(int i=0;i<8;i++)
	{
		strcpy(fs.subdirname[i],"|||");
	}
	for(i=0;i<128;i++)
		fs.fat[i]='0';
	fs.fat[0]='@';
	fs.fat[1]='@';
	fs.fat[2]='@';

	fs.InitDraw();
	m_tree1.DeleteAllItems();
	fs.m_ImageList.DeleteImageList();
	fs.InitTree();
	fs.InitDisk();
}

void COSDlg::OnMenuAddthr() 
{
	// TODO: Add your command handler code here
	CString name,*command;
	int num;
	if(cpu.pcbnum<10)
	{
		if(fs.ReadCommandFile(name,&command,num)==1)
		{
			cpu.Creat(name,command,num);
		}
	}else
	{
		AfxMessageBox("PCB最大个数为10个!");
	}
}



void COSDlg::OnMyhelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnHelp();
}
