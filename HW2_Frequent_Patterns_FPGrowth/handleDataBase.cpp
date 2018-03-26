//
//  createOriginalDB.cpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/3/26.
//  Copyright © 2018年 LS. All rights reserved.
//

#include <sstream>
#include "handleDataBase.hpp"
using std::cin ;
using std::cout ;
using std::endl ;
using std::string ;
using std::istringstream ;
using std::stoi ;

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

