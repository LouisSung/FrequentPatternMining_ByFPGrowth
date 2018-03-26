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

using std::cout ;
using std::endl ;
using std::vector ;
using std::pair ;

int transactionCount = 0 ;
vector<vector<int>> originalDB ;
vector<pair<int, int>> fList ;

int main(int argc, const char * argv[]) {
	createOriginalDB(&originalDB) ;
	transactionCount = (int)originalDB.size() ;
	printDB(&originalDB) ;
	getFrequentListFromDB(&fList, &originalDB) ;
	cout << "a" ;
}

