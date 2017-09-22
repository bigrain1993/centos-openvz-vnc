; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COSDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "OS.h"

ClassCount=7
Class1=COSApp
Class2=COSDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_FILETYPE
Resource2=IDR_MAINFRAME
Class4=CEndInfoDlg
Resource3=IDD_DIRCREAT
Resource4=IDD_OS_DIALOG
Class5=CDirCreatDlg
Resource5=IDD_FILECREAT
Class6=CFileCreatDlg
Resource6=IDD_ABOUTBOX
Class7=CFileType
Resource7=IDR_MENU1

[CLS:COSApp]
Type=0
HeaderFile=OS.h
ImplementationFile=OS.cpp
Filter=N

[CLS:COSDlg]
Type=0
HeaderFile=OSDlg.h
ImplementationFile=OSDlg.cpp
Filter=D
LastObject=ID_MENU_ADDTHR
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=OSDlg.h
ImplementationFile=OSDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_OS_DIALOG]
Type=1
Class=COSDlg
ControlCount=57
Control1=IDOK,button,1342242817
Control2=IDC_MYHELP,button,1342242816
Control3=IDC_RUNTHREAD,button,1342242816
Control4=IDC_ENDTHREAD,button,1342242816
Control5=IDC_RESTART,button,1342242816
Control6=IDC_LIST1,listbox,1352728833
Control7=IDC_LIST2,listbox,1352728833
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT1,edit,1350631552
Control14=IDC_EDIT2,edit,1350631552
Control15=IDC_EDIT3,edit,1350631552
Control16=IDC_SLIDER1,msctls_trackbar32,1342242821
Control17=IDC_STATIC,static,1342308865
Control18=IDC_STATIC1,static,1342177283
Control19=IDC_STATIC3,static,1342177283
Control20=IDC_STATIC5,static,1342177283
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC2,static,1342308352
Control28=IDC_STATIC4,static,1342308352
Control29=IDC_STATIC6,static,1342308352
Control30=IDC_STATIC7,static,1342177793
Control31=IDC_PROGRESS1,msctls_progress32,1342177281
Control32=IDC_STATIC,static,1342177289
Control33=IDC_LIST3,listbox,1353777408
Control34=IDC_STATIC,static,1342177289
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,static,1342308864
Control38=IDC_STATIC8,static,1342181889
Control39=IDC_DISK,static,1342177287
Control40=IDC_STATIC9,static,1342308352
Control41=IDC_STATIC,static,1342177296
Control42=IDC_STATIC,static,1342177297
Control43=IDC_STATIC,static,1342177296
Control44=IDC_TREE1,SysTreeView32,1350631431
Control45=IDC_STATIC,static,1342308352
Control46=IDC_STATIC,static,1342308352
Control47=IDC_FORMAT,button,1342242816
Control48=IDC_STATIC,static,1342308352
Control49=IDC_STATIC11,static,1342308352
Control50=IDC_STATIC10,static,1342308352
Control51=IDC_STATIC,static,1342177289
Control52=IDC_STATIC,static,1342177289
Control53=IDC_STATIC,static,1342177297
Control54=IDC_STATIC,static,1342177296
Control55=IDC_STATIC,static,1342177289
Control56=IDC_STATIC,static,1342177289
Control57=IDC_STATIC,static,1342177283

[CLS:CEndInfoDlg]
Type=0
HeaderFile=EndInfoDlg.h
ImplementationFile=EndInfoDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_STATIC1

[MNU:IDR_MENU1]
Type=1
Class=COSDlg
Command1=ID_MENU_MAKEDIR
Command2=ID_MENU_DELDIR
Command3=ID_MENU_CREAT
Command4=ID_MENU_DELETE
Command5=ID_MENU_TYPE
Command6=ID_MENU_ADDTHR
CommandCount=6

[DLG:IDD_DIRCREAT]
Type=1
Class=CDirCreatDlg
ControlCount=5
Control1=IDC_EDIT1,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287

[CLS:CDirCreatDlg]
Type=0
HeaderFile=DirCreatDlg.h
ImplementationFile=DirCreatDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDirCreatDlg

[DLG:IDD_FILECREAT]
Type=1
Class=CFileCreatDlg
ControlCount=9
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_EDIT3,edit,1352728580
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,button,1342177287

[CLS:CFileCreatDlg]
Type=0
HeaderFile=FileCreatDlg.h
ImplementationFile=FileCreatDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_FILETYPE]
Type=1
Class=CFileType
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_EDIT1,edit,1352730628

[CLS:CFileType]
Type=0
HeaderFile=FileType.h
ImplementationFile=FileType.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

