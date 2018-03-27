//
//  createOriginalDB.hpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/3/26.
//  Copyright © 2018年 LS. All rights reserved.
//

#ifndef createOriginalDB_hpp
#define createOriginalDB_hpp

#include <iostream>
#include <vector>
using std::vector ;
using std::pair ;

void createOriginalDB(vector<vector<int>> *originalDB) ;
void getFrequentListFromDB(vector<pair<int, int>> *fList, vector<vector<int>> *originalDB) ;
void transformOriginalDBIntoFListDBByFlist(vector<vector<int>> *originalDB, vector<pair<int, int>> *fList) ;

void printDB(vector<vector<int>> *dataBase) ;
void printFlist(vector<pair<int, int>> *fList) ;
#endif /* createOriginalDB_hpp */
