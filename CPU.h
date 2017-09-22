// CPU.h: interface for the CCPU class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPU_H__97889265_1962_4506_98CA_91ACED5CFA25__INCLUDED_)
#define AFX_CPU_H__97889265_1962_4506_98CA_91ACED5CFA25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


enum event_source {null,timeout,waiting,processing};
enum event_type {a,b,c};

class PCB
{
public:
	CString pcb_name;// 进程名
	int pcb_no;//进程号
	CString *command;//进程文件
	int linesnum;//进程文件指令数
	int current;//当前指针
	int result;//计算结果
	enum event_source event;//事件 
	enum event_type eventtype;//阻塞事件请求的资源
	int event_time;//使用资源时间
	PCB *link;
};

class QUEUE
{
	PCB *first,*last;
	int count;
public:
    QUEUE() {first=NULL;last=NULL;count=0;}
	void add(PCB * a)
	{
		if(first==NULL)
		{
			first=a;
			last=a;
		}else
		{
			last->link=a;
			last=a;

		}
		count++;
	}
	void gethead(PCB **a) 
	{
		*a=first;
		//摘到的结点link域不一定为空
	}
	int getcount() {return count;}
	void takeoffhead()
	{
		if(first!=NULL)
			first=first->link;
		count--;
	}
		
};


class CCPU  
{
public:
	CCPU();
	virtual ~CCPU();
public:
    //时间片辅助控制
	int timepieces;
	//时间片长度
	int timelength;
	//当前处理进程进程块
	PCB * currPCB;
	//设备状态标志
	int useA;
	int useB;
	int useC;
	//进程个数
    int pcbnum;
	//运行过进程总个数
	int totalnum;
	//就绪队列
	QUEUE ready;
	//使用设备阻塞队列,
	QUEUE block_0;
	//得不到设备A，B，C阻塞队列
	QUEUE block_1,block_2,block_3;
public:
	//一个时钟周期操作
	void Process();
	//进程创建操作,并加入就绪队列
	void Creat(CString name,CString *command,int number);
	//撤消进程操作
	void Destroy(PCB *pcb);
	//阻塞队列操作
	void Block(PCB *pcb);
	//唤醒操作
	void Wake();
	//进程调度操作
	void scheduling(); 

	void InitCpu(PCB *pcb);
	int GetCpuStatus();

};

#endif // !defined(AFX_CPU_H__97889265_1962_4506_98CA_91ACED5CFA25__INCLUDED_)
