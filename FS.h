// FS.h: interface for the CFS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FS_H__4428FB18_2146_4097_82AA_2D531999D7D2__INCLUDED_)
#define AFX_FS_H__4428FB18_2146_4097_82AA_2D531999D7D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct {
	char name[4];
	char ext[3];
	int attribute;
	int first;
	int length;
} dirstruct;

class CFS  
{
public:
	char fat[128];
	int enabledir;
	dirstruct curdir;
	char subdirname[8][4];
	CImageList m_ImageList;
	CRect rect;
public:
	bool ReadCommandFile(CString &name, CString **command, int &num);
	void TypeFile();
	void DeleteFile();
	void CreatFile();
	void DeleteDir();
	void DirItemChanged();
	void InitReadDigu(HTREEITEM hItem, int position, int isroot);
	void InitReadDisk();
	void DrawCircle(int radius, int begin, int end, int color);
	void InitDraw();
	void InitTree();
	void InitDisk();
	void CreatDir();
	CFS();
	virtual ~CFS();

};

#endif // !defined(AFX_FS_H__4428FB18_2146_4097_82AA_2D531999D7D2__INCLUDED_)
