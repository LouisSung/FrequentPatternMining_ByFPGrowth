//
//  main.cpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/3/26.
//  Copyright © 2018年 LS. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <ctime>
#include "handleTypesAndParameters.hpp"
#include "handleDataBase.hpp"
#include "handleFPtree.hpp"
#include "handleFrequentPatterns.hpp"
using std::cout ;
using std::endl ;
using std::string ;
using std::round ;

int main(int argc, const char * argv[]){
	double minSupportRatio = 0.01f ;
	string readFileName = "sample2.in" ;
	string writeFileName = "sample.out" ;
	printOrNot.setPrintOrNot(false) ;			//關閉除了fpCount以外的輸出
	//printOrNot.setPrintOrNot(false, false) ;			//關閉所有輸出
	
	if(argc >=4 and argc <=4+8){
		minSupportRatio = atof(argv[1]) ;
		readFileName = (string)argv[2] ;
		writeFileName = (string)argv[3] ;
		if(argc >4){
			printOrNot.setPrintParameterByArgv(argc, argv) ;}
	}
	
//開始計時
	clock_t start = clock() ;
	
//建orginalDB
	Database originalDB ;			//讀檔建oDB
	createOriginalDB(readFileName, &originalDB) ;
	printDB(&originalDB) ;

//計算總交易數、minmumSupportCount
	transactionCount = (int)originalDB.size() ;			//最多50萬筆
	minSupportCount = round(transactionCount*minSupportRatio) ;			//計算所需的support數
	if(printOrNot.minSupportCount == true){
		cout << "\n* minSupportCount: " << minSupportCount << endl ;}

//建frequentList
	FList fList ;			//讀oDB建frequent list
	getFrequentListFromDB(&fList, minSupportCount, &originalDB) ;
	printFlist(&fList) ;

//根據fList把orginalDB改成fListDB
	transformOriginalDBIntoFListDBByFlist(&originalDB, &fList) ;			//oDB改按flist排序為fDB
	Database &fListDB = originalDB ;			//建立別名
	printDB(&fListDB) ;

//利用fListDB建FPtree
	FPtree fpTree(&fList, 0) ;			//fDB建FPtree
	fpTree.buildFPtreeByFlistDB(&fListDB) ;
	fpTree.printFPtree() ;
	cout << "開始mining...\n" ;
	fpTree.mineFPtree() ;

//mining完成, 寫檔
	writeFrequentPatternsTo(writeFileName, transactionCount) ;
	
//停止計時
	clock_t stop = clock() ;
	cout << "共" << (double)(stop-start)/CLOCKS_PER_SEC << "秒" << endl ;
}
