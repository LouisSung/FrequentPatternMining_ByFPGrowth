//
//  main.cpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/3/26.
//  Copyright © 2018年 LS. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include "handleDataBase.hpp"
#include "handleFPtree.hpp"
#include "handleFrequentPatterns.hpp"
using std::cout ;
using std::cerr ;
using std::endl ;
using std::string ;
using std::vector ;
using std::pair ;
using std::round ;

extern const bool			//印出結果用的flags
	printAllOrNot = true,
	printDataBaseOrNot = true and printAllOrNot,
	printMinSupportCountOrNot = true and printAllOrNot,
	printFlistOrNot = true and printAllOrNot,
	printFPtreeOrNot = true and printAllOrNot,
	printConditionalPatternBasesOrNot = true and printAllOrNot,
	printFrequentPatternsOrNot = true and printAllOrNot ;

int main(int argc, const char * argv[]){
	double minSupportRatio = 0.15f ;
	string readFileName = "sample.in" ;
	string writeFileName = "sample.out" ;
	
//開始計時
	clock_t start = clock() ;
	
//建orginalDB
	vector<vector<int>> originalDB ;			//讀檔建oDB
	createOriginalDB(readFileName, &originalDB) ;
	printDB(&originalDB) ;

//計算總交易數、minmumSupportCount
	int transactionCount = (int)originalDB.size() ;
	int minSupportCount = round(transactionCount*minSupportRatio) ;			//計算所需的support數
	if(printMinSupportCountOrNot == true){
		cout << "\n* minSupportCount: " << minSupportCount << "" << endl ;}

//建frequentList
	vector<pair<int, int>> fList ;			//讀oDB建frequent list
	getFrequentListFromDB(&fList, minSupportCount, &originalDB) ;
	printFlist(&fList) ;

//根據fList把orginalDB改成fListDB
	transformOriginalDBIntoFListDBByFlist(&originalDB, &fList) ;			//oDB改按flist排序為fDB
	vector<vector<int>> &fListDB = originalDB ;			//建立別名
	printDB(&fListDB) ;

//利用fListDB建FPtree
	FPtree fpTree(&fList, minSupportCount, 0) ;			//fDB建FPtree
	fpTree.buildFPtreeByFlistDB(&fListDB) ;
	fpTree.printFPtree() ;
	fpTree.mineFPtree() ;

//mining完成, 寫檔
	writeFrequentPatternsTo(writeFileName, transactionCount) ;

//停止計時, stdout已被導向寫檔, 改用stderr
	clock_t stop = clock() ;
	cout << "共" << (double)(stop-start)/CLOCKS_PER_SEC << "秒" << endl ;
}
