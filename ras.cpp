/*=============================================================================
*
*									ＲＡＳ関係
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
#include <Ras.h>
#include <RasDlg.h>
#include <RasError.h>
// これらはリンクオプションで遅延ロードに設定する
#pragma comment(lib, "Rasapi32.lib")
#pragma comment(lib, "Rasdlg.lib")


template<class T, class Fn>
static inline auto Get(Fn&& fn) {
	std::vector<T> items{ { sizeof(T) } };
	for (DWORD size = sizeof(T), count = 0;;) {
		auto result = fn(data(items), &size, &count);
		if (result == ERROR_BUFFER_TOO_SMALL || result == ERROR_NOT_ENOUGH_MEMORY) {
			items.resize(size / sizeof(T));
			continue;
		}
		if (result == ERROR_SUCCESS)
			items.resize(count);
		else
			items.clear();
		return std::move(items);
	}
}


static inline auto GetConnections() {
	return Get<RASCONNW>(RasEnumConnectionsW);
}


// 現在のRASコネクションを切断する
static void DisconnectAll(std::vector<RASCONNW> const& connections) {
	if (!empty(connections)) {
		SetTaskMsg(MSGJPN220);
		for (auto const& connection : connections) {
			// 切断し、完了するまで待つ
			RasHangUpW(connection.hrasconn);
			RASCONNSTATUSW status{ sizeof(RASCONNSTATUSW) };
			while (RasGetConnectStatusW(connection.hrasconn, &status) != ERROR_INVALID_HANDLE)
				std::this_thread::sleep_for(10ms);
		}
	}
}


// RASを切断する
void DisconnectRas(int Notify) {
	if (auto const connections = GetConnections(); !empty(connections) && (Notify == NO || Dialog(GetFtpInst(), rasnotify_dlg, GetMainHwnd())))
		DisconnectAll(connections);
}


/*----- RASのエントリ一覧をコンボボックスにセットする -------------------------
*
*	Parameter
*		HWND hDlg : ダイアログボックスのハンドル
*		int Item : コンボボックスのリソース番号
*		char *CurName : 初期値
*
*	Return Value
*		int エントリ数
*----------------------------------------------------------------------------*/

int SetRasEntryToComboBox(HWND hDlg, int Item, char* CurName) {
	auto const entries = Get<RASENTRYNAMEW>([](auto... args) { return RasEnumEntriesW(nullptr, nullptr, args...); });
	if (!empty(entries)) {
		for (auto const& entry : entries)
			SendDlgItemMessageW(hDlg, Item, CB_ADDSTRING, 0, (LPARAM)entry.szEntryName);
		SendDlgItemMessageW(hDlg, Item, CB_SELECTSTRING, -1, (LPARAM)u8(CurName).c_str());
	}
	return size_as<int>(entries);
}


/*----- RASの接続を行う -------------------------------------------------------
*
*	Parameter
*		int Dialup : ダイアルアップするかどうか (YES/NO)
*		int UseThis : 必ずこのエントリに接続するかどうか (YES/NO)
*		int Notify : 再接続前に確認するかどうか (YES/NO)
*		char *Name : 接続先
*
*	Return Value
*		int ステータス (FFFTP_SUCCESS/FFFTP_FAIL)
*----------------------------------------------------------------------------*/

int ConnectRas(int Dialup, int UseThis, int Notify, char* Name) {
	if (Dialup != YES)
		return FFFTP_SUCCESS;
	auto wName = u8(Name);

	/* 現在の接続を確認 */
	if (auto const connections = GetConnections(); !empty(connections)) {
		if (UseThis != YES)
			return FFFTP_SUCCESS;
		for (auto const& connection : connections)
			if (wName == connection.szEntryName)
				return FFFTP_SUCCESS;
		if (Notify != NO && !Dialog(GetFtpInst(), rasreconnect_dlg, GetMainHwnd()))
			return FFFTP_SUCCESS;
		DisconnectAll(connections);
	}

	/* 接続する */
	SetTaskMsg(MSGJPN221);
	RASDIALDLG dlg{ sizeof(RASDIALDLG), GetMainHwnd() };
	return RasDialDlgW(nullptr, data(wName), nullptr, &dlg) ? FFFTP_SUCCESS : FFFTP_FAIL;
}
