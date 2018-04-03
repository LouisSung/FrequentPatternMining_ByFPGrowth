//
//  createOriginalDB.cpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/3/26.
//  Copyright © 2018年 LS. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "handleDataBase.hpp"
using std::cin ;
using std::cout ;
using std::endl ;
using std::string ;
using std::ifstream ;
using std::istringstream ;
using std::stoi ;
using std::sort ;
using std::find ;

//==========
void createOriginalDB(string fileName, Database *originalDB){
	ifstream fin(fileName) ;
	string singleLine ;
	Transaction singleTransaction ;
	singleTransaction.reserve(100) ;			//每行(交易)最多100個item
	originalDB->reserve(128) ;			//為push_back預留128的空間
	
	while(getline(fin, singleLine)){			//讀取一行
		singleTransaction.clear() ;
		istringstream ssline(singleLine) ;
		string singleItem ;			//取得該交易個別的item
		while(getline(ssline, singleItem, ',')){
			singleTransaction.push_back(stoi(singleItem)) ;}			//將個別item放入該交易
		originalDB->push_back(singleTransaction) ;			//將該交易存入資料庫
	}
	fin.close() ;
}

//==========
void getFrequentListFromDB(FList *fList, int minSupportCount, Database *originalDB){
	for(auto i=originalDB->begin(); i!=originalDB->end(); ++i){
		for(auto j=i->begin(); j!=i->end(); ++j){			//每筆交易的個別item
			auto k=fList->begin() ;			//iterator, 紀錄frequentOneItem目前位置
			for(; k!=fList->end(); ++k){
				if(k->itemName == *j){			//找到同樣的item, 表示已記錄過, break
					break ;}}
			if(k == fList->end()){			//沒找到
				fList->push_back(Item(*j, 1)) ;}			//第一次出現, 紀錄item出現次數為1
			else{
				++(k->itemCount) ;}			//第n次出現, 累加出現的次數
		}
	}
	
	for(auto i=fList->begin(); i!=fList->end(); ++i){
		if(i->itemCount < minSupportCount){			//移除小於minSupportCount的item
			fList->erase(i) ;
			--i ;			//調整指標
		}}
	auto greaterByValue = [](Item const & a, Item const & b){			//magic!!!!!
		return a.itemCount != b.itemCount?  a.itemCount > b.itemCount : a.itemName < b.itemName ;} ;			//自訂比較器, 兩數不同用value排, 否則用key排
	sort(fList->begin(), fList->end(), greaterByValue) ;			//依照出現次數排序
}

//==========
void transformOriginalDBIntoFListDBByFlist(Database *originalDB, FList *fList){
	Transaction sortedTransaction ;
	for(auto i=originalDB->begin(); i!=originalDB->end(); ++i){			//取得orginalDB每筆交易
		sortedTransaction.clear() ;
		for(auto j=fList->begin(); j!=fList->end(); ++j){			//取得fList內容、順序
			if(find(i->begin(), i->end(), j->itemName) != i->end()){			//判斷fList內的item是否在orginalDB出現
				sortedTransaction.push_back(j->itemName) ;}}
		
		if(sortedTransaction.size() == 0){			//該筆交易沒有任何item數量超過minSupportCount
			originalDB->erase(i) ;			//從originalDB移除
			--i ;			//調整iterator回被移除的位置
		}
		else{
			i->swap(sortedTransaction) ;}			//直接修改orginalDB
	}
}

//==========
void printDB(Database *dataBase){			//印出database
	if(printOrNot.database == true){
		cout << "資料庫大小: " << dataBase->size() << "\n" ;
		int count = 0 ;
		for(auto i=dataBase->begin(); i!=dataBase->end(); ++i){
			cout << ++count <<":\t  " ;
			auto j=i->begin() ;
			for(; j!=i->end()-1; ++j){
				cout << *j << ", " ;}
			cout << *j << "\n" ;
		}
		cout << endl ;
	}
}

//==========
void printFlist(FList *fList){			//印出flist
	if(printOrNot.fList == true){
		if(fList->size() > 0){
			cout << "* flist: " ;
			auto i=fList->begin() ;
			for(; i!=fList->end()-1; ++i){
				cout << "<" << i->itemName << ", " << i->itemCount << ">, " ;}
			cout  << "<" << i->itemName << ", " << i->itemCount << ">" << endl ;
		}
		else{
			cout << "fList為空" << endl ;}
	}
}
