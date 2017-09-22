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
	CString pcb_name;// ������
	int pcb_no;//���̺�
	CString *command;//�����ļ�
	int linesnum;//�����ļ�ָ����
	int current;//��ǰָ��
	int result;//������
	enum event_source event;//�¼� 
	enum event_type eventtype;//�����¼��������Դ
	int event_time;//ʹ����Դʱ��
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
		//ժ���Ľ��link��һ��Ϊ��
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
    //ʱ��Ƭ��������
	int timepieces;
	//ʱ��Ƭ����
	int timelength;
	//��ǰ������̽��̿�
	PCB * currPCB;
	//�豸״̬��־
	int useA;
	int useB;
	int useC;
	//���̸���
    int pcbnum;
	//���й������ܸ���
	int totalnum;
	//��������
	QUEUE ready;
	//ʹ���豸��������,
	QUEUE block_0;
	//�ò����豸A��B��C��������
	QUEUE block_1,block_2,block_3;
public:
	//һ��ʱ�����ڲ���
	void Process();
	//���̴�������,�������������
	void Creat(CString name,CString *command,int number);
	//�������̲���
	void Destroy(PCB *pcb);
	//�������в���
	void Block(PCB *pcb);
	//���Ѳ���
	void Wake();
	//���̵��Ȳ���
	void scheduling(); 

	void InitCpu(PCB *pcb);
	int GetCpuStatus();

};

#endif // !defined(AFX_CPU_H__97889265_1962_4506_98CA_91ACED5CFA25__INCLUDED_)
