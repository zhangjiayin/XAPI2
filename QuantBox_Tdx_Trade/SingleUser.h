#pragma once

#include "../include/Tdx/TdxApi.h"
#include "../include/ApiStruct.h"

#include <list>
#include <map>
#include <unordered_map>

using namespace std;

class CMsgQueue;

//////////////////////////////////////////////////////////////////////////
// 只是用来维护单账号的信息用
// 不支持在此类中主动调用API，而是交上层统一控制
class CSingleUser
{
public:
	CSingleUser();
	~CSingleUser();

	void UpdateQueryOrderTime(time_t t, double db, const char* szSource);
	void UpdateQueryTradeTime(time_t t, double db, const char* szSource);

private:
	void CompareTradeMapAndEmit(unordered_map<string, TradeField*> &oldMap, unordered_map<string, TradeField*> &newMap);
	void CompareTradeListAndEmit(list<TradeField*> &oldList, list<TradeField*> &newList);

private:
	//CTdxApi*					m_pApi;					//交易API
	//void*						m_pClient;

	CMsgQueue*					m_msgQueue;
	void*						m_pClass;

	list<TradeField*>			m_OldTradeList;
	list<TradeField*>			m_NewTradeList;
	unordered_map<string, TradeField*> m_NewTradeMap;
	unordered_map<string, TradeField*> m_OldTradeMap;


	list<OrderField*>			m_OldOrderList;
	list<OrderField*>			m_NewOrderList;

	time_t						m_QueryTradeTime;
	time_t						m_QueryOrderTime;
	int							m_OrderNotUpdateCount;
	bool						m_TradeListReverse;
	bool						m_LastIsMerge;

public:
	bool						m_bSendSuccess;
};

