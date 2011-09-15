// mbswrapper.h
// Copyright (C) 2011 Suguru Kawamoto
// マルチバイト文字ワイド文字APIラッパー

#ifndef __MBSWRAPPER_H__
#define __MBSWRAPPER_H__

#ifndef DO_NOT_REPLACE

#undef CreateFile
#define CreateFile CreateFileM
#undef MessageBox
#define MessageBox MessageBoxM
#undef FindFirstFile
#define FindFirstFile FindFirstFileM
#undef FindNextFile
#define FindNextFile FindNextFileM
#undef GetLogicalDriveStrings
#define GetLogicalDriveStrings GetLogicalDriveStringsM
#undef RegisterClassEx
#define RegisterClassEx RegisterClassExM
#undef CreateWindowEx
#define CreateWindowEx CreateWindowExM
#undef GetWindowLong
#define GetWindowLong GetWindowLongM
#undef SetWindowLong
#define SetWindowLong SetWindowLongM
#undef DefWindowProc
#define DefWindowProc DefWindowProcM
#undef CallWindowProc
#define CallWindowProc CallWindowProcM
#undef SendMessage
#define SendMessage SendMessageM
#undef SendDlgItemMessage
#define SendDlgItemMessage SendDlgItemMessageM
#undef SetWindowText
#define SetWindowText SetWindowTextM
#undef DragQueryFile
#define DragQueryFile DragQueryFileM
#undef GetCurrentDirectory
#define GetCurrentDirectory GetCurrentDirectoryM
#undef SetCurrentDirectory
#define SetCurrentDirectory SetCurrentDirectoryM
#undef SetDllDirectory
#define SetDllDirectory SetDllDirectoryM
#undef GetTempPath
#define GetTempPath GetTempPathM
#undef GetFileAttributes
#define GetFileAttributes GetFileAttributesM
#undef GetModuleFileName
#define GetModuleFileName GetModuleFileNameM
#undef RegOpenKeyEx
#define RegOpenKeyEx RegOpenKeyExM
#undef RegCreateKeyEx
#define RegCreateKeyEx RegCreateKeyExM
#undef RegDeleteValue
#define RegDeleteValue RegDeleteValueM
#undef RegQueryValueEx
#define RegQueryValueEx RegQueryValueExM
#undef RegSetValueEx
#define RegSetValueEx RegSetValueExM
#undef TextOut
#define TextOut TextOutM
#undef GetTextExtentPoint32
#define GetTextExtentPoint32 GetTextExtentPoint32M
#undef PropertySheet
#define PropertySheet PropertySheetM
#undef GetOpenFileName
#define GetOpenFileName GetOpenFileNameM
#undef GetSaveFileName
#define GetSaveFileName GetSaveFileNameM
#undef HtmlHelp
#define HtmlHelp HtmlHelpM
#undef CreateProcess
#define CreateProcess CreateProcessM
#undef FindExecutable
#define FindExecutable FindExecutableM
#undef ShellExecute
#define ShellExecute ShellExecuteM
#undef SHBrowseForFolder
#define SHBrowseForFolder SHBrowseForFolderM
#undef SHGetPathFromIDList
#define SHGetPathFromIDList SHGetPathFromIDListM
#undef SHFileOperation
#define SHFileOperation SHFileOperationM
#undef AppendMenu
#define AppendMenu AppendMenuM
#undef GetMenuItemInfo
#define GetMenuItemInfo GetMenuItemInfoM
#undef CreateFontIndirect
#define CreateFontIndirect CreateFontIndirectM
#undef ChooseFont
#define ChooseFont ChooseFontM
#undef DialogBoxParam
#define DialogBoxParam DialogBoxParamM
#undef CreateDialogParam
#define CreateDialogParam CreateDialogParamM
#undef mkdir
#define mkdir _mkdirM
#undef _mkdir
#define _mkdir _mkdirM
#undef rmdir
#define rmdir rmdirM
#undef _rmdir
#define _rmdir _rmdirM
#undef _mbslen
#define _mbslen _mbslenM
#undef _mbschr
#define _mbschr _mbschrM
#undef _mbsrchr
#define _mbsrchr _mbsrchrM
#undef _mbsstr
#define _mbsstr _mbsstrM
#undef _mbscmp
#define _mbscmp _mbscmpM
#undef _mbsicmp
#define _mbsicmp _mbsicmpM
#undef _mbsncmp
#define _mbsncmp _mbsncmpM
#undef _mbslwr
#define _mbslwr _mbslwrM
#undef _mbsupr
#define _mbsupr _mbsuprM
#undef _mbsninc
#define _mbsninc _mbsnincM

#undef CreateWindow
#define CreateWindow(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam) CreateWindowEx(0L, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)
#undef DialogBox
#define DialogBox(hInstance, lpTemplate, hWndParent, lpDialogFunc) DialogBoxParam(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0L)

#endif

int MtoW(LPWSTR pDst, int size, LPCSTR pSrc, int count);
int WtoM(LPSTR pDst, int size, LPCWSTR pSrc, int count);
int WtoA(LPSTR pDst, int size, LPCWSTR pSrc, int count);
int TerminateStringM(LPSTR lpString, int size);
int TerminateStringW(LPWSTR lpString, int size);
int TerminateStringA(LPWSTR lpString, int size);
size_t GetMultiStringLengthM(LPCSTR lpString);
size_t GetMultiStringLengthW(LPCWSTR lpString);
size_t GetMultiStringLengthA(LPCWSTR lpString);
int MtoWMultiString(LPWSTR pDst, int size, LPCSTR pSrc);
int WtoMMultiString(LPSTR pDst, int size, LPCWSTR pSrc);
int WtoAMultiString(LPSTR pDst, int size, LPCWSTR pSrc);
char* AllocateStringM(int size);
wchar_t* AllocateStringW(int size);
char* AllocateStringA(int size);
wchar_t* DuplicateMtoW(LPCSTR lpString, int c);
wchar_t* DuplicateMtoWBuffer(LPCSTR lpString, int c, int size);
wchar_t* DuplicateMtoWMultiString(LPCSTR lpString);
wchar_t* DuplicateMtoWMultiStringBuffer(LPCSTR lpString, int size);
char* DuplicateWtoM(LPCWSTR lpString, int c);
char* DuplicateWtoA(LPCWSTR lpString, int c);
void FreeDuplicatedString(void* p);

#endif

