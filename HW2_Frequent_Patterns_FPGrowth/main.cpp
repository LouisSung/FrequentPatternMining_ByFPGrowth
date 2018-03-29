//
//  main.cpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/3/26.
//  Copyright © 2018年 LS. All rights reserved.
//

#include <iostream>
#include <vector>
#include "handleDataBase.hpp"
#include "handleFPtree.hpp"
using std::cout ;
using std::endl ;
using std::vector ;
using std::pair ;

int main(int argc, const char * argv[]){
	vector<vector<int>> originalDB ;			//讀檔建oDB
	createOriginalDB(&originalDB) ;
	printDB(&originalDB) ;

	vector<pair<int, int>> fList ;			//讀oDB建frequent list
	getFrequentListFromDB(&fList, &originalDB) ;
	printFlist(&fList) ;
	
	transformOriginalDBIntoFListDBByFlist(&originalDB, &fList) ;			//oDB改按flist排序為fDB
	vector<vector<int>> &fListDB = originalDB ;			//建立別名
	printDB(&fListDB) ;
	
	FPtree fpTree(&fList) ;			//fDB建FPtree
	fpTree.buildFPtreeByFlistDB(&fListDB) ;
	fpTree.printFPtree(fpTree.getRoot()) ;
}

