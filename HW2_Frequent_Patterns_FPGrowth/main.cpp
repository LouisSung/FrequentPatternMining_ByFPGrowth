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

vector<vector<int>> originalDB ;
vector<pair<int, int>> fList ;

int main(int argc, const char * argv[]){
	createOriginalDB(&originalDB) ;
	printDB(&originalDB) ;
	
	getFrequentListFromDB(&fList, &originalDB) ;
	printFlist(&fList) ;
	
	transformOriginalDBIntoFListDBByFlist(&originalDB, &fList) ;
	vector<vector<int>> &fListDB = originalDB ;			//建立別名
	printDB(&fListDB) ;
	
	buildFPtree(&fListDB) ;
}

