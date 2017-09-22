// CPU.cpp: implementation of the CCPU class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OS.h"
#include "CPU.h"
#include "OSDlg.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCPU::CCPU()
{
	currPCB=NULL;
	timepieces=1;
	timelength=2+1;
	useA=0;
	useB=0;
	useC=0;
	pcbnum=0;
	totalnum=0;

}

CCPU::~CCPU()
{

}

int CCPU::GetCpuStatus()
{
	if(currPCB==NULL)
		return 0;
	else return 1;

}

void CCPU::InitCpu(PCB *pcb)
{
	currPCB=pcb;
	timepieces=1;

}

void CCPU::scheduling()
{  
	Wake();
	if(GetCpuStatus()!=0)
	{
		Process();
	}else if(ready.getcount()!=0)
	{
		
		((COSDlg*)AfxGetMainWnd())->m_list1.DeleteString(0);
        PCB *a;
		ready.gethead(&a);
		ready.takeoffhead();
		a->link=NULL;
		InitCpu(a);
		Process();
	}
}

void CCPU::Creat(CString name, CString *command, int number)
{
	PCB *pcb;
	pcb=new PCB;
	pcb->pcb_name.Format("%d.%s",totalnum,name);
	pcb->result=0;
	pcb->command=command;
	pcb->linesnum=number;
	pcb->pcb_no=totalnum++;
	pcb->current=0;
	pcb->event=null;
	pcb->event_time=-1;
	pcb->link=NULL;
	pcbnum++;
    	
	ready.add(pcb);
	((COSDlg*)AfxGetMainWnd())->m_list1.AddString(pcb->pcb_name);
	
}

void CCPU::Destroy(PCB *pcb)
{
	//释放进程块
	delete [](pcb->command);

	//释放进程程序
	delete pcb;
    pcbnum--;
}

void CCPU::Block(PCB *pcb)
{
	int time;
	//请求设备A
	if(pcb->command[pcb->current].GetAt(1)=='a')
	{
		time=pcb->command[pcb->current].GetAt(2)-'0';
		pcb->eventtype=a;
        pcb->event_time=time;
		if(useA==0)
		{
			useA=1;
		    block_0.add(pcb);
			HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_SCRE2));
			((COSDlg*)AfxGetMainWnd())->m_static1.SetIcon(hIcon);
			CString sss;
			sss.Format("%s\nusing:%d",pcb->pcb_name,pcb->event_time);
			((COSDlg*)AfxGetMainWnd())->m_static2.SetWindowText(sss);//"使用中");
			((COSDlg*)AfxGetMainWnd())->m_edit2=pcb->command[pcb->current];
			((COSDlg*)AfxGetMainWnd())->m_edit3.Format("请求%c设备",pcb->command[pcb->current].GetAt(0));
			pcb->current++;
			
        }else
		{
			block_1.add(pcb);
			((COSDlg*)AfxGetMainWnd())->m_edit2=pcb->command[pcb->current];
			((COSDlg*)AfxGetMainWnd())->m_edit3.Format("请求%c设备",pcb->command[pcb->current].GetAt(0));
		}
	}else   //请求设备B 
		if(pcb->command[pcb->current].GetAt(1)=='b')
	{
		time=pcb->command[pcb->current].GetAt(2)-'0';
		pcb->eventtype=b;
        pcb->event_time=time;
		if(useB==0)
		{
			useB=1;
		    block_0.add(pcb);
			HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_CD2));
			((COSDlg*)AfxGetMainWnd())->m_static3.SetIcon(hIcon);
			CString sss;
			sss.Format("%s\nusing:%d",pcb->pcb_name,pcb->event_time);
			((COSDlg*)AfxGetMainWnd())->m_static4.SetWindowText(sss);///"使用中");
			((COSDlg*)AfxGetMainWnd())->m_edit2=pcb->command[pcb->current];
			((COSDlg*)AfxGetMainWnd())->m_edit3.Format("请求%c设备",pcb->command[pcb->current].GetAt(0));
			pcb->current++;
		}else
		{
			block_2.add(pcb);
			((COSDlg*)AfxGetMainWnd())->m_edit2=pcb->command[pcb->current];
			((COSDlg*)AfxGetMainWnd())->m_edit3.Format("请求%c设备",pcb->command[pcb->current].GetAt(0));
		}
	}else //请求设备C
		if(pcb->command[pcb->current].GetAt(1)=='c')
	{
		time=pcb->command[pcb->current].GetAt(2)-'0';
		pcb->eventtype=c;
        pcb->event_time=time;
		if(useC==0)
		{
			useC=1;
		    block_0.add(pcb);
			HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_BOAR2));
			((COSDlg*)AfxGetMainWnd())->m_static5.SetIcon(hIcon);
			CString sss;
			sss.Format("%s\nusing:%d",pcb->pcb_name,pcb->event_time);
			((COSDlg*)AfxGetMainWnd())->m_static6.SetWindowText(sss);
			((COSDlg*)AfxGetMainWnd())->m_edit2=pcb->command[pcb->current];
			((COSDlg*)AfxGetMainWnd())->m_edit3.Format("请求%c设备",pcb->command[pcb->current].GetAt(0));
			pcb->current++;
		}else
		{
			block_3.add(pcb);
			((COSDlg*)AfxGetMainWnd())->m_edit2=pcb->command[pcb->current];
			((COSDlg*)AfxGetMainWnd())->m_edit3.Format("请求%c设备",pcb->command[pcb->current].GetAt(0));
		}
	}
	
	((COSDlg*)AfxGetMainWnd())->m_edit1=_T(""); 
	((COSDlg*)AfxGetMainWnd())->UpdateData(FALSE);
	((COSDlg*)AfxGetMainWnd())->m_list2.AddString(pcb->pcb_name);
}

void CCPU::Wake()
{
	if(block_0.getcount()!=0)
	{
		PCB *block_pcb;
	    block_0.gethead(&block_pcb);
	    while(block_pcb!=NULL)
		{
		    block_pcb->event_time--;
			CString sss;
			sss.Format("%s\nusing:%d",block_pcb->pcb_name,block_pcb->event_time);
			switch(block_pcb->eventtype)
			{
			case a :
				((COSDlg*)AfxGetMainWnd())->m_static2.SetWindowText(sss);
				break;
			case b :
				((COSDlg*)AfxGetMainWnd())->m_static4.SetWindowText(sss);
				break;
			case c :
				((COSDlg*)AfxGetMainWnd())->m_static6.SetWindowText(sss);
				break;
			}

		    block_pcb=block_pcb->link;
		}
		
		int j=block_0.getcount();
		//检测是否有设备使用完而空闲，是则唤醒相应请求响映设备的进程
		for(int i=0;i<j;i++)
		{
			block_0.gethead(&block_pcb);
			block_0.takeoffhead();
			block_pcb->link=NULL;
			if(block_pcb->event_time<=0)
			{
				//使用完设备进程如就绪队列
				ready.add(block_pcb);
			    ((COSDlg*)AfxGetMainWnd())->m_list1.AddString(block_pcb->pcb_name);
			    ((COSDlg*)AfxGetMainWnd())->m_list2.DeleteString(((COSDlg*)AfxGetMainWnd())->m_list2.FindString(0,block_pcb->pcb_name));
				//唤醒相映其他进程
				if(block_pcb->eventtype==a)
				{
					HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_SCRE1));
					((COSDlg*)AfxGetMainWnd())->m_static1.SetIcon(hIcon);
					((COSDlg*)AfxGetMainWnd())->m_static2.SetWindowText("空闲");
					useA=0;
					PCB *a;
					if(block_1.getcount()!=0)
					{
						block_1.gethead(&a);
						block_1.takeoffhead();
						((COSDlg*)AfxGetMainWnd())->m_list2.DeleteString(((COSDlg*)AfxGetMainWnd())->m_list2.FindString(0,a->pcb_name));
						a->link=NULL;
						((COSDlg*)AfxGetMainWnd())->m_list1.AddString(a->pcb_name);
						ready.add(a);
					}
				}else if(block_pcb->eventtype==b)
				{
					
					HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_CD1));
					((COSDlg*)AfxGetMainWnd())->m_static3.SetIcon(hIcon);
					((COSDlg*)AfxGetMainWnd())->m_static4.SetWindowText("空闲");
					useB=0;
					PCB *a;
					if(block_2.getcount()!=0)
					{
						block_2.gethead(&a);
						block_2.takeoffhead();
						((COSDlg*)AfxGetMainWnd())->m_list2.DeleteString(((COSDlg*)AfxGetMainWnd())->m_list2.FindString(0,a->pcb_name));
						a->link=NULL;
						((COSDlg*)AfxGetMainWnd())->m_list1.AddString(a->pcb_name);
						ready.add(a);
					}
				}else if(block_pcb->eventtype==c)
				{
					HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_BOAR1));
					((COSDlg*)AfxGetMainWnd())->m_static5.SetIcon(hIcon);
					((COSDlg*)AfxGetMainWnd())->m_static6.SetWindowText("空闲");
					useC=0;
					PCB *a;
					if(block_3.getcount()!=0)
					{
						block_3.gethead(&a);
						block_3.takeoffhead();
						((COSDlg*)AfxGetMainWnd())->m_list2.DeleteString(((COSDlg*)AfxGetMainWnd())->m_list2.FindString(0,a->pcb_name));
						a->link=NULL;
						((COSDlg*)AfxGetMainWnd())->m_list1.AddString(a->pcb_name);
						ready.add(a);
					}
				}
			}else
			{
				block_0.add(block_pcb);
			}
		}
	}

}

void CCPU::Process()
{
	//调用此函数前保证currPCB指针非空
	if(timepieces%timelength==0)
	{
		((COSDlg*)AfxGetMainWnd())->m_edit1=_T("");
		((COSDlg*)AfxGetMainWnd())->m_edit2=_T("");
		((COSDlg*)AfxGetMainWnd())->m_edit3=_T("");
		((COSDlg*)AfxGetMainWnd())->UpdateData(FALSE);
		ready.add(currPCB);
		((COSDlg*)AfxGetMainWnd())->m_list1.AddString(currPCB->pcb_name);
		((COSDlg*)AfxGetMainWnd())->m_progress1.SetPos(0);
		currPCB=NULL;
	}else
	{   
		((COSDlg*)AfxGetMainWnd())->m_progress1.SetPos(timepieces);
		if((currPCB->current)<(currPCB->linesnum))
		{
			if(currPCB->command[currPCB->current].GetAt(0)=='x'||currPCB->command[currPCB->current].GetAt(0)=='y')
			{
				if(currPCB->command[currPCB->current].GetAt(1)=='=')
					currPCB->result=currPCB->command[currPCB->current].GetAt(2)-'0';
				else if(currPCB->command[currPCB->current].GetAt(1)=='+')
					currPCB->result++;
				else
					currPCB->result--;
				
				((COSDlg*)AfxGetMainWnd())->m_edit2=currPCB->command[currPCB->current];
				((COSDlg*)AfxGetMainWnd())->m_edit3.Format("%d",currPCB->result);
				((COSDlg*)AfxGetMainWnd())->m_edit1=currPCB->pcb_name; 
				((COSDlg*)AfxGetMainWnd())->UpdateData(FALSE);
				
				currPCB->current++;
				timepieces++;
				
			}else //处理使用资源的指令
			{
				Block(currPCB);
				currPCB=NULL;
				((COSDlg*)AfxGetMainWnd())->m_progress1.SetPos(0);
			}
			
		}else if((currPCB->current)>=(currPCB->linesnum))
		{
			CString sss;
			sss.Format("%s   re: %d",currPCB->pcb_name,currPCB->result);
			((COSDlg*)AfxGetMainWnd())->m_list3.AddString(sss);//currPCB->pcb_name);
			((COSDlg*)AfxGetMainWnd())->m_progress1.SetPos(0);
			
			((COSDlg*)AfxGetMainWnd())->m_edit1=_T("");
			((COSDlg*)AfxGetMainWnd())->m_edit2=_T("");
			((COSDlg*)AfxGetMainWnd())->m_edit3=_T("");
			((COSDlg*)AfxGetMainWnd())->UpdateData(FALSE);
			
			Destroy(currPCB);
			
			currPCB=NULL;
		}
	}
	
}
