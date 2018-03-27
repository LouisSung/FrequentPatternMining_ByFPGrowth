//
//  createOriginalDB.cpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/3/26.
//  Copyright © 2018年 LS. All rights reserved.
//

#include <sstream>
#include <map>
#include "handleDataBase.hpp"
using std::cin ;
using std::cout ;
using std::endl ;
using std::string ;
using std::istringstream ;
using std::stoi ;
using std::map ;
using std::make_pair ;
using std::pair ;
using std::sort ;
using std::find ;

void createOriginalDB(vector<vector<int>> *originalDB){
	freopen("sample.in", "r", stdin) ;			//重新導向
	string singleLine ;
	vector<int> singleTransaction ;
	singleTransaction.reserve(100) ;			//每行(交易)最多100個item
	
	while(!(getline(cin, singleLine).eof())){			//讀取一行
		singleTransaction.clear() ;
		istringstream ssline(singleLine) ;
		string singleItem ;			//取得該交易個別的item
		while(getline(ssline, singleItem, ',')){
			singleTransaction.push_back(stoi(singleItem)) ;}			//將個別item放入該交易
		originalDB->push_back(singleTransaction) ;			//將該交易存入資料庫
	}
}

//==========
void getFrequentListFromDB(vector<pair<int, int>> *fList, vector<vector<int>> *originalDB){
	for(auto i=originalDB->begin(); i!=originalDB->end(); ++i){
		for(auto j=i->begin(); j!=i->end(); ++j){			//每筆交易的個別item
			auto k=fList->begin() ;			//iterator, 紀錄frequentOneItem目前位置
			for(; k!=fList->end(); ++k){
				if(k->first == *j){			//找到同樣的item, 表示已記錄過, break
					break ;}}
			if(k == fList->end()){			//沒找到
				fList->push_back(make_pair(*j, 1)) ;}			//第一次出現, 新增pair, 紀錄次數為1
			else{
				++(k->second) ;}			//第n次出現, 累加出現的次數
		}}
	
	auto greaterByValue = [](pair<int,int> const & a, pair<int,int> const & b){			//magic!!!!!
		return a.second != b.second?  a.second > b.second : a.first > b.first ;} ;			//自訂比較器, 兩數不同用value排, 否則用key排
	sort(fList->begin(), fList->end(), greaterByValue);			//依照出現次數排序
}

//==========
void createFListDBfromOriginalDB(vector<vector<int>> *fListDB, vector<vector<int>> *originalDB, vector<pair<int, int>> *fList){
	vector<int> sortedTransaction ;
	for(auto i=originalDB->begin(); i!=originalDB->end(); ++i){			//取得orginalDB每筆交易
		sortedTransaction.clear() ;
		for(auto j=fList->begin(); j!=fList->end(); ++j){			//取得fList內容、順序
			if(find(i->begin(), i->end(), j->first) != i->end()){			//判斷fList內的item是否在orginalDB出現
				sortedTransaction.push_back(j->first) ;}}
		fListDB->push_back(sortedTransaction) ;			//放回排序後內容
//		i->swap(sortedTransaction) ;			//直接修改orginalDB
	}
}

//==========
void printDB(vector<vector<int>> *dataBase){
	cout << "資料庫大小: " << dataBase->size() << endl ;
	
	int number = 0 ;
	for(auto i=dataBase->begin(); i!=dataBase->end(); ++i){
		cout << ++number <<":\t  " ;
		for(auto j=i->begin(); j!=i->end()-1; ++j){
			cout << *j << ", " ;}
		cout << *(i->end()-1) << endl ;
	}
}

