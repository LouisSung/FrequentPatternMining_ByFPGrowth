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
#include "handleDataBase.hpp"
#include "handleFPtree.hpp"
#include "handleFrequentPatterns.hpp"
using std::cout ;
using std::endl ;
using std::vector ;
using std::pair ;
using std::round ;

int main(int argc, const char * argv[]){
	vector<vector<int>> originalDB ;			//讀檔建oDB
	createOriginalDB(&originalDB) ;
	printDB(&originalDB) ;
	
	double minSupportRatio = 0.1f ;
	int transactionCount = (int)originalDB.size() ;
	int minSupportCount = round(transactionCount*minSupportRatio) ;			//計算所需的support數
	cout << "\n* minSupport: " << minSupportCount << "" << endl ;
	vector<pair<int, int>> fList ;			//讀oDB建frequent list
	getFrequentListFromDB(&fList, minSupportCount, &originalDB) ;
	printFlist(&fList) ;
	
	transformOriginalDBIntoFListDBByFlist(&originalDB, &fList) ;			//oDB改按flist排序為fDB
	vector<vector<int>> &fListDB = originalDB ;			//建立別名
	printDB(&fListDB) ;
	
	FPtree fpTree(&fList, minSupportCount, 0) ;			//fDB建FPtree
	fpTree.buildFPtreeByFlistDB(&fListDB) ;
	fpTree.printFPtree() ;
	fpTree.mineFPtree() ;
	writeFrequentPatternsTo("sample.out", transactionCount) ;
}

