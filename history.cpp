/*=============================================================================
*
*										ヒストリ
*
===============================================================================
/ Copyright (C) 1997-2007 Sota. All rights reserved.
/
/ Redistribution and use in source and binary forms, with or without 
/ modification, are permitted provided that the following conditions 
/ are met:
/
/  1. Redistributions of source code must retain the above copyright 
/     notice, this list of conditions and the following disclaimer.
/  2. Redistributions in binary form must reproduce the above copyright 
/     notice, this list of conditions and the following disclaimer in the 
/     documentation and/or other materials provided with the distribution.
/
/ THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR 
/ IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
/ OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
/ IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, 
/ INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
/ BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF 
/ USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
/ ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
/ (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
/ THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/============================================================================*/

#include "common.h"

static void CopyHostToHistory(HOSTDATA *Host, HISTORYDATA *New);

extern int FileHist;
extern int PassToHist;

static std::list<HISTORYDATA> HistoryBase;

/* ヒストリのメニュー項目のID */
static int MenuHistId[HISTORY_MAX] = {
	MENU_HIST_1,  MENU_HIST_2,  MENU_HIST_3,  MENU_HIST_4,  MENU_HIST_5,
	MENU_HIST_6,  MENU_HIST_7,  MENU_HIST_8,  MENU_HIST_9,  MENU_HIST_10,
	MENU_HIST_11, MENU_HIST_12, MENU_HIST_13, MENU_HIST_14, MENU_HIST_15,
	MENU_HIST_16, MENU_HIST_17, MENU_HIST_18, MENU_HIST_19, MENU_HIST_20
};


/*----- ホスト情報をヒストリリストの先頭に追加する ----------------------------
*
*	Parameter
*		HOSTDATA *Host : ホストデータ
*		int TrMode : 転送モード
*
*	Return Value
*		なし
*----------------------------------------------------------------------------*/

void AddHostToHistory(HOSTDATA *Host, int TrMode)
{
	HISTORYDATA New;

	CopyHostToHistory(Host, &New);
	New.Type = TrMode;
	AddHistoryToHistory(&New);
	return;
}


// ヒストリをヒストリリストの先頭に追加する
void AddHistoryToHistory(HISTORYDATA *Hist) {
	CheckHistoryNum(1);
	if (FileHist > size_as<int>(HistoryBase))
		HistoryBase.push_front(*Hist);
}


// ヒストリの数を返す
int AskHistoryNum() {
	return size_as<int>(HistoryBase);
}


// ヒストリの数をチェックし多すぎたら削除
void CheckHistoryNum(int Space) {
	if (size_as<int>(HistoryBase) > FileHist - Space)
		HistoryBase.resize(FileHist - Space);
}


/*----- ホスト情報をヒストリにセット ------------------------------------------
*
*	Parameter
*		HOSTDATA *Host : ホストデータ
*		HISTORYDATA *New : ヒストリをセットするワーク
*
*	Return Value
*		なし
*----------------------------------------------------------------------------*/

static void CopyHostToHistory(HOSTDATA *Host, HISTORYDATA *New)
{
	strcpy(New->HostAdrs, Host->HostAdrs);
	strcpy(New->UserName, Host->UserName);
	if(PassToHist == YES)
		strcpy(New->PassWord, Host->PassWord);
	else
		strcpy(New->PassWord, "");
	strcpy(New->Account, Host->Account);
	strcpy(New->LocalInitDir, Host->LocalInitDir);
	strcpy(New->RemoteInitDir, Host->RemoteInitDir);
	strcpy(New->ChmodCmd, Host->ChmodCmd);
	strcpy(New->LsName, Host->LsName);
	strcpy(New->InitCmd, Host->InitCmd);
	New->Port = Host->Port;
	New->KanjiCode = Host->KanjiCode;
	New->KanaCnv = Host->KanaCnv;
	New->NameKanjiCode = Host->NameKanjiCode;
	New->NameKanaCnv = Host->NameKanaCnv;
	New->Pasv = Host->Pasv;
	New->FireWall = Host->FireWall;
	New->ListCmdOnly = Host->ListCmdOnly;
	New->UseNLST_R = Host->UseNLST_R;
	New->TimeZone = Host->TimeZone;
	New->HostType = Host->HostType;
	New->SyncMove = Host->SyncMove;
	New->NoFullPath = Host->NoFullPath;
	New->Sort = Host->Sort;
	New->Security = Host->Security;
	New->Dialup = Host->Dialup;
	New->DialupAlways = Host->DialupAlways;
	New->DialupNotify = Host->DialupNotify;
	strcpy(New->DialEntry, Host->DialEntry);
	// 暗号化通信対応
	New->UseNoEncryption = Host->UseNoEncryption;
	New->UseFTPES = Host->UseFTPES;
	New->UseFTPIS = Host->UseFTPIS;
	New->UseSFTP = Host->UseSFTP;
	strcpy(New->PrivateKey, Host->PrivateKey);
	// 同時接続対応
	New->MaxThreadCount = Host->MaxThreadCount;
	New->ReuseCmdSkt = Host->ReuseCmdSkt;
	// MLSD対応
	New->UseMLSD = Host->UseMLSD;
	// 自動切断対策
	New->NoopInterval = Host->NoopInterval;
	// 再転送対応
	New->TransferErrorMode = Host->TransferErrorMode;
	New->TransferErrorNotify = Host->TransferErrorNotify;
	// セッションあたりの転送量制限対策
	New->TransferErrorReconnect = Host->TransferErrorReconnect;
	// ホスト側の設定ミス対策
	New->NoPasvAdrs = Host->NoPasvAdrs;
	return;
}


/*----- ヒストリ情報をホスト情報にセット --------------------------------------
*
*	Parameter
*		HISTORYDATA *Hist : ヒストリ
*		HOSTDATA *Host : ホストデータをセットするワーク
*
*	Return Value
*		なし
*----------------------------------------------------------------------------*/

void CopyHistoryToHost(HISTORYDATA *Hist, HOSTDATA *Host)
{
	CopyDefaultHost(Host);

	strcpy(Host->HostAdrs, Hist->HostAdrs);
	strcpy(Host->UserName, Hist->UserName);
	if(PassToHist == YES)
		strcpy(Host->PassWord, Hist->PassWord);
	else
		strcpy(Host->PassWord, "");
	strcpy(Host->Account, Hist->Account);
	strcpy(Host->LocalInitDir, Hist->LocalInitDir);
	strcpy(Host->RemoteInitDir, Hist->RemoteInitDir);
	strcpy(Host->ChmodCmd, Hist->ChmodCmd);
	strcpy(Host->LsName, Hist->LsName);
	strcpy(Host->InitCmd, Hist->InitCmd);
	Host->Port = Hist->Port;
	Host->KanjiCode = Hist->KanjiCode;
	Host->KanaCnv = Hist->KanaCnv;
	Host->NameKanjiCode = Hist->NameKanjiCode;
	Host->NameKanaCnv = Hist->NameKanaCnv;
	Host->Pasv = Hist->Pasv;
	Host->FireWall = Hist->FireWall;
	Host->ListCmdOnly = Hist->ListCmdOnly;
	Host->UseNLST_R = Hist->UseNLST_R;
	Host->TimeZone = Hist->TimeZone;
	Host->HostType = Hist->HostType;
	Host->SyncMove = Hist->SyncMove;
	Host->NoFullPath = Hist->NoFullPath;
	Host->Sort = Hist->Sort;
	Host->Security = Hist->Security;
	Host->Dialup = Hist->Dialup;
	Host->DialupAlways = Hist->DialupAlways;
	Host->DialupNotify = Hist->DialupNotify;
	strcpy(Host->DialEntry, Hist->DialEntry);
	// 暗号化通信対応
	Host->UseNoEncryption = Hist->UseNoEncryption;
	Host->UseFTPES = Hist->UseFTPES;
	Host->UseFTPIS = Hist->UseFTPIS;
	Host->UseSFTP = Hist->UseSFTP;
	strcpy(Host->PrivateKey, Hist->PrivateKey);
	// 同時接続対応
	Host->MaxThreadCount = Hist->MaxThreadCount;
	Host->ReuseCmdSkt = Hist->ReuseCmdSkt;
	// MLSD対応
	Host->UseMLSD = Hist->UseMLSD;
	// 自動切断対策
	Host->NoopInterval = Hist->NoopInterval;
	// 再転送対応
	Host->TransferErrorMode = Hist->TransferErrorMode;
	Host->TransferErrorNotify = Hist->TransferErrorNotify;
	// セッションあたりの転送量制限対策
	Host->TransferErrorReconnect = Hist->TransferErrorReconnect;
	// ホスト側の設定ミス対策
	Host->NoPasvAdrs = Hist->NoPasvAdrs;
	return;
}


/*----- ヒストリ情報の初期値を取得 --------------------------------------------
*
*	Parameter
*		HISTORYDATA *Set : ヒストリをセットするワーク
*
*	Return Value
*		なし
*----------------------------------------------------------------------------*/

void CopyDefaultHistory(HISTORYDATA *Set)
{
	HOSTDATA Host;

	// ホスト共通設定機能
//	CopyDefaultHost(&Host);
	CopyDefaultDefaultHost(&Host);
	CopyHostToHistory(&Host, Set);
	return;
}


// 全ヒストリをメニューにセット
void SetAllHistoryToMenu() {
	auto menu = GetSubMenu(GetMenu(GetMainHwnd()), 0);
	for (int i = DEF_FMENU_ITEMS, count = GetMenuItemCount(menu); i < count; i++)
		DeleteMenu(menu, DEF_FMENU_ITEMS, MF_BYPOSITION);
	if (empty(HistoryBase))
		return;
	AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
	int i = 0;
	for (auto const& h : HistoryBase) {
		char buffer[HOST_ADRS_LEN + USER_NAME_LEN + INIT_DIR_LEN + 7 + 1];
		if (i < 9)
			sprintf(buffer, "&%d %s (%s) %s", i + 1, h.HostAdrs, h.UserName, h.RemoteInitDir);
		else if (i == 9)
			sprintf(buffer, "&0 %s (%s) %s", h.HostAdrs, h.UserName, h.RemoteInitDir);
		else
			sprintf(buffer, "&* %s (%s) %s", h.HostAdrs, h.UserName, h.RemoteInitDir);
		AppendMenu(menu, MF_STRING, MenuHistId[i++], buffer);
	}
}


// 指定メニューコマンドに対応するヒストリを返す
int GetHistoryByCmd(int MenuCmd, HISTORYDATA *Buf) {
	int i = 0;
	for (auto const& h : HistoryBase)
		if (MenuHistId[i++] == MenuCmd) {
			*Buf = h;
			return FFFTP_SUCCESS;
		}
	return FFFTP_FAIL;
}


/*----- 指定番号に対応するヒストリを返す --------------------------------------
*
*	Parameter
*		int Num : 番号(0～)
*		HISTORYDATA *Buf : ヒストリデータを返すバッファ
*
*	Return Value
*		int ステータス
*			FFFTP_SUCCESS/FFFTP_FAIL
*----------------------------------------------------------------------------*/

int GetHistoryByNum(int Num, HISTORYDATA *Buf)
{
	return(GetHistoryByCmd(MenuHistId[Num], Buf));
}


