// FS.cpp: implementation of the CFS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OS.h"
#include "OSDlg.h"
#include "FS.h"
#include "DirCreatDlg.h"
#include "FileCreatDlg.h"
#include "FileType.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFS::CFS()
{
	enabledir=1;
	strcpy(curdir.name,"cch");
	strcpy(curdir.ext,"||");
	curdir.first=2;
	curdir.length=1;
	curdir.attribute=0;//'0'表示目录
	for(int i=0;i<8;i++)
	{
		strcpy(subdirname[i],"|||");
	}
	for(i=0;i<128;i++)
		fat[i]='0';
	fat[0]='@';
	fat[1]='@';
	fat[2]='@';

}

CFS::~CFS()
{

}

void CFS::CreatDir()
{
	CDirCreatDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		if(dlg.m_edit1.GetLength()!=3)
		{
			AfxMessageBox("目录名不为空");
			return ;
		}
		
		char name[4];
		char temp[2]={'\0','\0'};
		name[0]=dlg.m_edit1.GetAt(0);
		name[1]=dlg.m_edit1.GetAt(1);
		name[2]=dlg.m_edit1.GetAt(2);
		name[3]='\0';
		
		CFile file;
		if(file.Open("mydisk.txt",
			CFile::modeReadWrite|CFile::shareExclusive)!=0)
		{
			//position,目录项号
			int position;
			//sonfirst，起始盘块号
			int sonfirst;
			for(int i=0;i<8;i++)
			{
				if(strcmp(subdirname[i],name)==0)
				{
					AfxMessageBox("重名错误");
					return;
				}
			}
			for(i=0;i<8;i++)
			{
				if(strcmp(subdirname[i],"|||")==0)
					break;
			}
			if(i==8)
			{
				AfxMessageBox("不能再创建文件或目录");
				return;
			}
			//position,目录项号
			position=i;
			for(i=3;i<128;i++)
			{
				if(fat[i]=='0')
					break;
			}
			if(i==128)
			{
				AfxMessageBox("磁盘满");
				return;
			}
			//sonfirst，起始盘块号
			sonfirst=i;
			//
			strcpy(subdirname[position],name);
			//写FAT数组及磁盘
			fat[sonfirst]='&';
			file.Seek(i,CFile::begin);
			temp[0]=fat[i];
			file.Write(temp,1);
			
			//写目录项
			file.Seek(curdir.first*64+position*8,CFile::begin);
			file.Write(name,3);
			file.Write("||",2);
			temp[0]='0';
			file.Write(temp,1);
			temp[0]=sonfirst+'0';
			file.Write(temp,1);
			temp[0]=1+'0';
			file.Write(temp,1);
			
			//向子目录第一项写入父目录信息
			file.Seek(sonfirst*64,CFile::begin);
			file.Write(curdir.name,3);
			file.Write(curdir.ext,2);
			temp[0]='0';
			file.Write(temp,1);
			temp[0]=curdir.first+'0';
			file.Write(temp,1);
			temp[0]=curdir.length+'0';
			file.Write(temp,1);
			//
			file.Close();
			
			//画扇区
			int radius=30;
			radius=30+int(sonfirst/8)*8;
			int begin,end;
			begin=sonfirst%8;
			end=sonfirst%8+1;
			DrawCircle(radius,begin,end,1);
			
			//向目录树添加项目
			HTREEITEM hItem,hItem0;
			hItem=((COSDlg*)AfxGetMainWnd())->m_tree1.GetSelectedItem();
			TVINSERTSTRUCT tvItem;
			tvItem.hParent=hItem;
			tvItem.hInsertAfter=TVI_LAST;
			tvItem.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
			tvItem.item.iImage=tvItem.item.iSelectedImage=1;
			char str1[4];
			str1[0]=dlg.m_edit1.GetAt(0);
			str1[1]=dlg.m_edit1.GetAt(1);
			str1[2]=dlg.m_edit1.GetAt(2);
			str1[3]='\0';
			tvItem.item.pszText=str1;
			hItem0=((COSDlg*)AfxGetMainWnd())->m_tree1.InsertItem(&tvItem);
			
			((COSDlg*)AfxGetMainWnd())->m_tree1.SetItemData(hItem0,curdir.first);
			
			((COSDlg*)AfxGetMainWnd())->m_tree1.Expand(hItem,TVE_EXPAND);
		}
	}

}

void CFS::InitDisk()
{
	char str[9]="00000000";
	CFile file;
	if(file.Open("mydisk.txt",
		CFile::modeReadWrite|CFile::shareExclusive)!=0)
	{
		//文件初始化
		for(int i=0;i<16;i++)
			file.Write(str,8);
		strcpy(str,"||||||||");
		for(i=16;i<8*128;i++)
			file.Write(str,8);
		file.Seek(0,CFile::begin);
		file.Write("@@@",3);
		file.Close();
		return ;
	}else
	{
		AfxMessageBox("打开文件失败 0");
		return ;
	}

}

void CFS::InitTree()
{
			//初始化树控件
	m_ImageList.Create(16,16,FALSE,3,0);
	m_ImageList.Add(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_DISK)));
    m_ImageList.Add(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_FLODER)));
    m_ImageList.Add(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_FILE)));

	((COSDlg*)AfxGetMainWnd())->m_tree1.SetImageList(&m_ImageList,LVSIL_NORMAL);

	HTREEITEM hItem0;
	TVINSERTSTRUCT tvItem;
	tvItem.hParent=NULL;
	tvItem.hInsertAfter=TVI_LAST;
	tvItem.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
    tvItem.item.pszText="disk";
	tvItem.item.iImage=tvItem.item.iSelectedImage=0;
	hItem0=((COSDlg*)AfxGetMainWnd())->m_tree1.InsertItem(&tvItem);

	((COSDlg*)AfxGetMainWnd())->m_tree1.SetItemData(hItem0,-1);

    ((COSDlg*)AfxGetMainWnd())->m_tree1.Expand(hItem0,TVE_EXPAND);
}

void CFS::InitDraw()
{
		//磁盘图形初始化
	CRect rect;
	(((COSDlg*)AfxGetMainWnd())->GetDlgItem(IDC_DISK))->GetClientRect(rect);
	CClientDC dc(((COSDlg*)AfxGetMainWnd())->GetDlgItem(IDC_DISK));
	CBrush brush(RGB(255,255,255));
	dc.FillRect(rect,&brush);
	
	int radius;
	int begin;
	int end;
	int color;
	for(int i=3;i<128;i++)
	{
		radius=int(i/8)*8+30;
		begin=i%8;
		end=i%8+1;
		if(fat[i]!='0')
			color=1;
		else
			color=0;
		DrawCircle(radius,begin,end,color);
	}
	DrawCircle(30,0,3,2);
	
	//每条磁道分成八块
	dc.SetViewportOrg(rect.Width()/2,rect.Height()/2);
	CPen pen(PS_SOLID,1,RGB(255,255,0));
	dc.SelectObject(&pen);
	dc.MoveTo(-150,150);
	dc.LineTo(150,-150);
	dc.MoveTo(-150,-150);
	dc.LineTo(150,150);
	dc.MoveTo(0,150);
	dc.LineTo(0,-150);
	dc.MoveTo(150,0);
	dc.LineTo(-150,0);
	dc.TextOut(130,100,"0");
	dc.TextOut(100,130,"1");
	dc.TextOut(-100,130,"2");
	dc.TextOut(-140,100,"3");
	dc.TextOut(-140,-100,"4");
	dc.TextOut(-100,-140,"5");
	dc.TextOut(100,-140,"6");
	dc.TextOut(130,-100,"7");

}

void CFS::DrawCircle(int radius, int begin, int end, int color)
{
		end=end*64/8;
	begin=begin*64/8;

	CRect rect;
	(((COSDlg*)AfxGetMainWnd())->GetDlgItem(IDC_DISK))->GetClientRect(rect);
	CClientDC dc(((COSDlg*)AfxGetMainWnd())->GetDlgItem(IDC_DISK));
    dc.SetViewportOrg(rect.Width()/2,rect.Height()/2);
	COLORREF penColor;
	if(color==0)
		penColor=RGB(0,255,0);
	else if(color==1)
		penColor=RGB(255,0,0);
	else if(color==2)
		penColor=RGB(220,120,180);
	else AfxMessageBox("color choice wrong!");
	CPen pen(PS_SOLID,1,penColor);
	dc.SelectObject(&pen);
	for(int n=begin;n<end;n++)
	{
		dc.MoveTo(int(radius*cos((n*3.1415926/32))),int(radius*sin(n*3.1415926/32)));
		dc.LineTo(int(radius*cos((n+1)*3.1415926/32)),int(radius*sin((n+1)*3.1415926/32)));
	}

}

void CFS::InitReadDisk()
{
	CFileFind filefind;
	if(filefind.FindFile("mydisk.txt")==0)
	{
		CFile file;
		if(file.Open("mydisk.txt",CFile::modeCreate)!=0)
		{
			file.Close();
			InitDisk();
			
		}else
		{
			AfxMessageBox("创建文件失败");
		}
		return ;
	}
	HTREEITEM hItem;
	hItem=((COSDlg*)AfxGetMainWnd())->m_tree1.GetRootItem();
	InitReadDigu(hItem,2,1);

}

void CFS::InitReadDigu(HTREEITEM hItem, int position, int isroot)
{
	HTREEITEM hItem0;
	CFile file;
	if(file.Open("mydisk.txt",
		CFile::shareDenyNone)!=0)
	{
		char str[9];
		int i;
		if(isroot==1)
			i=0;
		else 
			i=1;
		for(;i<8;i++)
		{
			file.Seek(position*64+i*8,CFile::begin);
			file.Read(str,8);
			str[8]='\0';
			if(strcmp(str,"||||||||")!=0)
			{
				int attribut=str[5]-'0';
				if(attribut==0)
				{
					//dir
					int subfirst=str[6]-'0';
					//写FAT数组
					fat[subfirst]='&';
					//画扇区
					int radius=30;
					radius=30+int(subfirst/8)*8;
					int begin,end;
					begin=subfirst%8;
					end=subfirst%8+1;
					DrawCircle(radius,begin,end,1);
					
					//向目录树添加项目
					TVINSERTSTRUCT tvItem;
					tvItem.hParent=hItem;
					tvItem.hInsertAfter=TVI_LAST;
					tvItem.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
					tvItem.item.iImage=tvItem.item.iSelectedImage=1;
					char str1[4];
					str1[0]=str[0];
					str1[1]=str[1];
					str1[2]=str[2];
					str1[3]='\0';
					tvItem.item.pszText=str1;
					hItem0=((COSDlg*)AfxGetMainWnd())->m_tree1.InsertItem(&tvItem);
					
					((COSDlg*)AfxGetMainWnd())->m_tree1.SetItemData(hItem0,position);
					
					((COSDlg*)AfxGetMainWnd())->m_tree1.Expand(hItem,TVE_EXPAND);
					
					InitReadDigu(hItem0,subfirst,0);
				}else
				{
					//文件
					int subfirst=str[6]-'0';
					int blocks[4];
					int blocklength=str[7]-'0';
					if(blocklength!=0)
					{	
						//写FAT数组
						int i=0;
						blocks[0]=subfirst;
						char temp[2]={'\0','\0'};
						file.Seek(blocks[0],CFile::begin);
						file.Read(temp,1);
						fat[subfirst]=temp[0];
						while(fat[blocks[i]]!='*')
						{
							i++;
							blocks[i]=fat[blocks[i-1]]-'0';
							file.Seek(blocks[i],CFile::begin);
							file.Read(temp,1);
							fat[blocks[i]]=temp[0];
						}	
						//画扇区
						int radius=30;
						int begin,end;
						i=0;
						for(i=0;i<blocklength;i++)
						{
							radius=30+int(blocks[i]/8)*8;
							begin=blocks[i]%8;
							end=blocks[i]%8+1;
							DrawCircle(radius,begin,end,1);
							i++;
						}
					}
					//向目录树添加项目
					TVINSERTSTRUCT tvItem;
					tvItem.hParent=hItem;
					tvItem.hInsertAfter=TVI_LAST;
					tvItem.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
					tvItem.item.iImage=tvItem.item.iSelectedImage=2;
					char str1[7];
					str1[0]=str[0];
					str1[1]=str[1];
					str1[2]=str[2];
					str1[3]='.';
					str1[4]=str[3];
					str1[5]=str[4];
					str1[6]='\0';
					tvItem.item.pszText=str1;
					hItem0=((COSDlg*)AfxGetMainWnd())->m_tree1.InsertItem(&tvItem);
					
					((COSDlg*)AfxGetMainWnd())->m_tree1.SetItemData(hItem0,position);
					
					((COSDlg*)AfxGetMainWnd())->m_tree1.Expand(hItem,TVE_EXPAND);

				}
			
			}
		}
		file.Close();
	}else
	{
		AfxMessageBox("打开文件失败 5");
		return;
	}


}

void CFS::DirItemChanged()
{
	HTREEITEM hItem;
	hItem=((COSDlg*)AfxGetMainWnd())->m_tree1.GetSelectedItem();
	int n=((COSDlg*)AfxGetMainWnd())->m_tree1.GetItemData(hItem);
	char name[4];
	CString tempname;
	tempname=((COSDlg*)AfxGetMainWnd())->m_tree1.GetItemText(hItem);
	name[0]=tempname.GetAt(0);
	name[1]=tempname.GetAt(1);
	name[2]=tempname.GetAt(2);
	name[3]='\0';
	if(n!=-1)
	{
		CFile file;
		if(file.Open("mydisk.txt",
			CFile::modeReadWrite|CFile::shareExclusive)!=0)
		{
			
			int tempfirst;
			tempfirst=n;
			char str[9];
			file.Seek(tempfirst*64,CFile::begin);
			for(int i=0;i<8;i++)
			{
				file.Read(str,8);
				char str1[4];
				str1[0]=str[0];
				str1[1]=str[1];
				str1[2]=str[2];
				str1[3]='\0';
				if(strcmp(str1,name)==0)
					break;
			}
			int position=i;
			curdir.name[0]=str[0];
			curdir.name[1]=str[1];
			curdir.name[2]=str[2];
			curdir.name[3]='\0';
			curdir.ext[0]=str[3];
			curdir.ext[1]=str[4];
			curdir.ext[2]='\0';
			curdir.attribute=str[5]-'0';
			curdir.first=str[6]-'0';
			curdir.length=str[7]-'0';
			if(curdir.attribute==0)
				enabledir=1;
			else 
				enabledir=0;
			file.Seek(curdir.first*64,CFile::begin);
			for(i=0;i<8;i++)
			{
				file.Read(str,8);
				subdirname[i][0]=str[0];
				subdirname[i][1]=str[1];
				subdirname[i][2]=str[2];
				subdirname[i][3]='\0';
			}
		}
	}else
	{
		enabledir=1;
		strcpy(curdir.name,"cch");
		strcpy(curdir.ext,"||");
		curdir.first=2;
		curdir.length=1;
		curdir.attribute=0;
		CFile file;
		if(file.Open("mydisk.txt",
			CFile::modeReadWrite|CFile::shareExclusive)!=0)
		{
			char str[9];
			file.Seek(curdir.first*64,CFile::begin);
			for(int i=0;i<8;i++)
			{
				file.Read(str,8);
				subdirname[i][0]=str[0];
				subdirname[i][1]=str[1];
				subdirname[i][2]=str[2];
				subdirname[i][3]='\0';
			}
		}
		else
		{
			AfxMessageBox("打开文件失败 1");
			return;
		}

	}

}

void CFS::DeleteDir()
{
	HTREEITEM hItem,hItem0;
	hItem=((COSDlg*)AfxGetMainWnd())->m_tree1.GetSelectedItem();
	hItem0=((COSDlg*)AfxGetMainWnd())->m_tree1.GetRootItem();
	if(hItem==hItem0)
	{
		AfxMessageBox("根目录不能删除");
		return;
	}
	for(int i=1;i<8;i++)
	{
		if(strcmp(subdirname[i],"|||")!=0)
			break;
	}
	if(i<8)
	{
		AfxMessageBox("目录非空，删除失败!");
		return;
	}

	CFile file;
	if(file.Open("mydisk.txt",
		CFile::modeReadWrite|CFile::shareExclusive)!=0)
	{
		
		int n=((COSDlg*)AfxGetMainWnd())->m_tree1.GetItemData(hItem);
		char name[4];
		CString tempname;
		tempname=((COSDlg*)AfxGetMainWnd())->m_tree1.GetItemText(hItem);
		name[0]=tempname.GetAt(0);
		name[1]=tempname.GetAt(1);
		name[2]=tempname.GetAt(2);
		name[3]='\0';
		file.Seek(n*64,CFile::begin);
		char str[9];
		for(int i=0;i<8;i++)
		{
			file.Read(str,8);
			char str1[4];
			str1[0]=str[0];
			str1[1]=str[1];
			str1[2]=str[2];
			str1[3]='\0';
			if(strcmp(str1,name)==0)
				break;
		}
		int position=i;
		fat[curdir.first]='0';
		file.Seek(curdir.first,CFile::begin);
		file.Write("0",1);
		file.Seek(n*64+position*8,CFile::begin);
		file.Write("||||||||",8);
		file.Seek(curdir.first*64,CFile::begin);
		file.Write("||||||||",8);
		file.Close();

		//画扇区
		int radius=30;
		radius=30+int(curdir.first/8)*8;
		int begin,end;
		begin=curdir.first%8;
		end=curdir.first%8+1;
		DrawCircle(radius,begin,end,0);

    	((COSDlg*)AfxGetMainWnd())->m_tree1.DeleteItem(hItem);

	}else
	{
		AfxMessageBox("打开文件失败 2");
		return ;
	}


}

void CFS::CreatFile()
{
	CFileCreatDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		if(dlg.m_edit1.GetLength()!=3)
		{
			AfxMessageBox("文件名为三个字符");
			return ;
		}
		if(dlg.m_edit2.GetLength()!=2)
		{
			AfxMessageBox("扩展名为两个字符");
			return ;
		}
		
		char fname[4],fext[3];
		int filelength;
		int charlength;
		char temp[2]={'\0','\0'};
		fname[0]=dlg.m_edit1.GetAt(0);
		fname[1]=dlg.m_edit1.GetAt(1);
		fname[2]=dlg.m_edit1.GetAt(2);
		fname[3]='\0';
		fext[0]=dlg.m_edit2.GetAt(0);
		fext[1]=dlg.m_edit2.GetAt(1);
		fext[3]='\0';
		
		charlength=dlg.m_edit3.GetLength();
		filelength=int(ceil(dlg.m_edit3.GetLength()/64.000000));
		
		CFile file;
		if(file.Open("mydisk.txt",
			CFile::modeReadWrite|CFile::shareExclusive)!=0)
		{
			//position,目录项号
			int position;
			//sonfirst，起始盘块号
			int subfirst;
			for(int i=0;i<8;i++)
			{
				if(strcmp(subdirname[i],fname)==0)
				{
					AfxMessageBox("重名错误");
					return;
				}
			}
			for(i=0;i<8;i++)
			{
				if(strcmp(subdirname[i],"|||")==0)
					break;
			}
			if(i==8)
			{
				AfxMessageBox("不能再创建文件或目录");
				return;
			}
			//position,目录项号
			position=i;
			strcpy(subdirname[i],fname);
			if(filelength!=0)
			{
				int blocknum;
				blocknum=filelength;
				int blocks[4];
				int j=0;
				for(i=3;i<128;i++)
				{
					if(fat[i]=='0')
					{
						blocks[j]=i;	
						j++;
					}
					if(j==blocknum)
						break;
				}
				if(j!=blocknum)
				{
					AfxMessageBox("磁盘满");
					return;
				}
				subfirst=blocks[0];
				
				//写FAT数组及磁盘
				for(i=0;i<blocknum-1;i++)
				{
					fat[blocks[i]]='0'+blocks[i+1];
				}
				fat[blocks[blocknum-1]]='*';
				for(i=0;i<blocknum;i++)
				{
					file.Seek(blocks[i],CFile::begin);
					temp[0]=fat[blocks[i]];
					file.Write(temp,1);
				}
				
				//写目录项
				
				file.Seek(curdir.first*64+position*8,CFile::begin);
				file.Write(fname,3);
				file.Write(fext,2);
				temp[0]='1';
				file.Write(temp,1);
				temp[0]=subfirst+'0';
				file.Write(temp,1);
				temp[0]=filelength+'0';
				file.Write(temp,1);
				
				//画扇区
				int radius=30;
				for(i=0;i<blocknum;i++)
				{
					radius=30+int(blocks[i]/8)*8;
					int begin,end;
					begin=blocks[i]%8;
					end=blocks[i]%8+1;
					DrawCircle(radius,begin,end,1);
				}
				
				
				//写文件内容
				char buf[65];
				for(i=0;i<blocknum-1;i++)
				{
					for(int j=0;j<64;j++)
						buf[j]=dlg.m_edit3.GetAt(i*64+j);
					buf[64]='\0';
					file.Seek(64*blocks[i],CFile::begin);
					file.Write(buf,64);
				}
				int len=charlength%64; 
				for(i=0;i<len;i++)
					buf[i]=dlg.m_edit3.GetAt((blocknum-1)*64+i);
				buf[len]='*';
				buf[len+1]='\0';
				file.Seek(64*blocks[blocknum-1],CFile::begin);
				file.Write(buf,len+1);
				file.Close();
			}else
			{
				//写目录项
				file.Seek(curdir.first*64+position*8,CFile::begin);
				file.Write(fname,3);
				file.Write(fext,2);
				temp[0]='1';
				file.Write(temp,1);
				temp[0]=0+'0';
				file.Write(temp,1);
				temp[0]=filelength+'0';
				file.Write(temp,1);
				file.Close();
			}
			
			//向目录树添加项目
			HTREEITEM hItem,hItem0;
			hItem=((COSDlg*)AfxGetMainWnd())->m_tree1.GetSelectedItem();
			TVINSERTSTRUCT tvItem;
			tvItem.hParent=hItem;
			tvItem.hInsertAfter=TVI_LAST;
			tvItem.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
			tvItem.item.iImage=tvItem.item.iSelectedImage=2;
			char str1[7];
			strcpy(str1,fname);
			strcat(str1,".");
			strcat(str1,fext);
			str1[6]='\0';
			tvItem.item.pszText=str1;
			hItem0=((COSDlg*)AfxGetMainWnd())->m_tree1.InsertItem(&tvItem);
			
			((COSDlg*)AfxGetMainWnd())->m_tree1.SetItemData(hItem0,curdir.first);
			
			((COSDlg*)AfxGetMainWnd())->m_tree1.Expand(hItem,TVE_EXPAND);
		}else
		{
			AfxMessageBox("打开文件失败 3");
			return;
		}
	}

}

void CFS::DeleteFile()
{
	HTREEITEM hItem;
	hItem=((COSDlg*)AfxGetMainWnd())->m_tree1.GetSelectedItem();
	CFile file;
	if(file.Open("mydisk.txt",
		CFile::modeReadWrite|CFile::shareExclusive)!=0)
	{
		
		int n=((COSDlg*)AfxGetMainWnd())->m_tree1.GetItemData(hItem);
		char name[4];
		CString tempname;
		tempname=((COSDlg*)AfxGetMainWnd())->m_tree1.GetItemText(hItem);
		name[0]=tempname.GetAt(0);
		name[1]=tempname.GetAt(1);
		name[2]=tempname.GetAt(2);
		name[3]='\0';
		file.Seek(n*64,CFile::begin);
		char str[9];
		for(int i=0;i<8;i++)
		{
			file.Read(str,8);
			char str1[4];
			str1[0]=str[0];
			str1[1]=str[1];
			str1[2]=str[2];
			str1[3]='\0';
			if(strcmp(str1,name)==0)
				break;
		}
		int position=i;
		if(curdir.length==0)
		{
			
			file.Seek(n*64+position*8,CFile::begin);
			file.Write("||||||||",8);
			file.Close();

			((COSDlg*)AfxGetMainWnd())->m_tree1.DeleteItem(hItem);
		}else
		{
			
			int blocks[4];
			char temp[2]={'\0','\0'};
			temp[0]=curdir.first+'0';
			int i=0;
			do
			{
				blocks[i]=temp[0]-'0';
				file.Seek(blocks[i],CFile::begin);
				file.Read(temp,1);
				i++;
			}while(temp[0]!='*');//也可使用curdir.length和for循环
			int blocknum=i;

			//覆盖目录项,该项要先做
			file.Seek(n*64+position*8,CFile::begin);
			file.Write("||||||||",8);
			

			//写FAT数组和FAT磁盘
			for(i=0;i<blocknum;i++)
			{
				fat[blocks[i]]='0';
				file.Seek(blocks[i],CFile::begin);
				file.Write("0",1);
			}

			//释放磁盘扇区
			char buf[65];
			for(i=0;i<64;i++)
				buf[i]='|';
			buf[64]='\0';
			for(i=0;i<blocknum;i++)
			{
				file.Seek(64*blocks[i],CFile::begin);
				file.Write(buf,64);
			}
			file.Close();

			
			//画扇区
			int radius=30;
			int begin,end;
			for(i=0;i<blocknum;i++)
			{
				radius=30+int(blocks[i]/8)*8;
				begin=blocks[i]%8;
				end=blocks[i]%8+1;
				DrawCircle(radius,begin,end,0);
			}

			((COSDlg*)AfxGetMainWnd())->m_tree1.DeleteItem(hItem);
			
		}
	}else
	{
		AfxMessageBox("打开文件失败 4");
		return ;
	}
}

void CFS::TypeFile()
{
	HTREEITEM hItem;
	hItem=((COSDlg*)AfxGetMainWnd())->m_tree1.GetSelectedItem();
	CFile file;
	if(file.Open("mydisk.txt",
		CFile::modeReadWrite|CFile::shareExclusive)!=0)
	{
		
		int n=((COSDlg*)AfxGetMainWnd())->m_tree1.GetItemData(hItem);
		char name[4];
		CString tempname;
		tempname=((COSDlg*)AfxGetMainWnd())->m_tree1.GetItemText(hItem);
		name[0]=tempname.GetAt(0);
		name[1]=tempname.GetAt(1);
		name[2]=tempname.GetAt(2);
		name[3]='\0';
		file.Seek(n*64,CFile::begin);
		char str[9];
		for(int i=0;i<8;i++)
		{
			file.Read(str,8);
			char str1[4];
			str1[0]=str[0];
			str1[1]=str[1];
			str1[2]=str[2];
			str1[3]='\0';
			if(strcmp(str1,name)==0)
				break;
		}
		int position=i;
		if(curdir.length==0)
		{
			AfxMessageBox("文件现在为空");
			return;
		}else
		{
			int blocks[4];
			char temp[2]={'\0','\0'};
			temp[0]=curdir.first+'0';
			int i=0;
			do
			{
				blocks[i]=temp[0]-'0';
				file.Seek(blocks[i],CFile::begin);
				file.Read(temp,1);
				i++;
			}while(temp[0]!='*');//也可使用curdir.length和for循环
			int blocknum=i;
			char buf[65];
			CString content,add;
			content="";
			for(i=0;i<blocknum-1;i++)
			{
				file.Seek(64*blocks[i],CFile::begin);
				file.Read(buf,64);
				buf[64]='\0';
				add.Empty();
				add.Format("%s",buf);
				content+=add;
			}
			file.Seek(64*blocks[blocknum-1],CFile::begin);
			for(i=0;i<64;i++)
			{
				file.Read(temp,1);
				if(temp[0]=='*')
					break;
			    buf[i]=temp[0];	
			}
			buf[i]='\0';
			add.Empty();
			add.Format("%s",buf);
			content+=add;
			CFileType dlg;
			dlg.m_edit1=content;
			dlg.DoModal();

			file.Close();
		}
	}

}

bool CFS::ReadCommandFile(CString &name, CString **command, int &num)
{
	HTREEITEM hItem;
	hItem=((COSDlg*)AfxGetMainWnd())->m_tree1.GetSelectedItem();
	CFile file;
	if(file.Open("mydisk.txt",
		CFile::modeReadWrite|CFile::shareExclusive)!=0)
	{
		
		int n=((COSDlg*)AfxGetMainWnd())->m_tree1.GetItemData(hItem);
		char fname[4];
		char fext[3];
		CString tempname;
		tempname=((COSDlg*)AfxGetMainWnd())->m_tree1.GetItemText(hItem);
		fname[0]=tempname.GetAt(0);
		fname[1]=tempname.GetAt(1);
		fname[2]=tempname.GetAt(2);
		fname[3]='\0';
		file.Seek(n*64,CFile::begin);
		char str[9];
		for(int i=0;i<8;i++)
		{
			file.Read(str,8);
			char str1[4];
			str1[0]=str[0];
			str1[1]=str[1];
			str1[2]=str[2];
			str1[3]='\0';
			if(strcmp(str1,fname)==0)
				break;
		}
		int position=i;
		fext[0]=str[3];
		fext[1]=str[4];
		fext[2]='\0';
		if(strcmp(fext,"ex")!=0&&strcmp(fext,"EX")!=0)
		{
			AfxMessageBox("请添加扩展名为\".ex\"的文件");
			return 0;
		}
		if(curdir.length==0)
		{
			AfxMessageBox("文件现在为空");
			return 0;
		}else
		{
			int blocks[4];
			char temp[2]={'\0','\0'};
			temp[0]=curdir.first+'0';
			int i=0;
			do
			{
				blocks[i]=temp[0]-'0';
				file.Seek(blocks[i],CFile::begin);
				file.Read(temp,1);
				i++;
			}while(temp[0]!='*');//也可使用curdir.length和for循环
			int blocknum=i;
			char buf[65];
			CString content,add;
			content="";
			for(i=0;i<blocknum-1;i++)
			{
				file.Seek(64*blocks[i],CFile::begin);
				file.Read(buf,64);
				buf[64]='\0';
				add.Empty();
				add.Format("%s",buf);
				content+=add;
			}
			file.Seek(64*blocks[blocknum-1],CFile::begin);
			for(i=0;i<64;i++)
			{
				file.Read(temp,1);
				if(temp[0]=='*')
					break;
			    buf[i]=temp[0];	
			}
			buf[i]='\0';
			add.Empty();
			add.Format("%s",buf);
			content+=add;

			file.Close();

			name.Format("%s",fname);
			*command=new CString[50];
			int charlength=content.GetLength();
			int j=-1;
			int flag=1;
		    do{
				j++;
				if(j*4+3>charlength)
				{
					flag=0;
					break;
				}
		    	(*command)[j].Format("%c%c%c%c",
					content.GetAt(j*4+0),content.GetAt(j*4+1),
					content.GetAt(j*4+2),content.GetAt(j*4+3));
		        (*command)[j].MakeLower();
				if((*command)[j].GetAt(3)!=';')
				{
					flag=0;
					break;
				}
			}while((*command)[j]!="end;");
			num=j;
			if((*command)[j]!="end;")
				flag=0;
			if(flag==0)
			{
			//	delete []command;
				AfxMessageBox("命令文件有误,请检查\n  或仔细阅读帮助");
				return 0;
			}
			if(j>0)
				return 1;
			else return 0;
		}
	}
	return 0;
}
