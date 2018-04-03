//
//  createOriginalDB.hpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/3/26.
//  Copyright © 2018年 LS. All rights reserved.
//

#ifndef createOriginalDB_hpp
#define createOriginalDB_hpp

#include "handleTypesAndParameters.hpp"
using std::string ;

void createOriginalDB(string fileName, Database *originalDB) ;
void getFrequentListFromDB(FList *fList, int minSupportCount, Database *originalDB) ;
void transformOriginalDBIntoFListDBByFlist(Database *originalDB, FList *fList) ;

void printDB(Database *dataBase) ;
void printFlist(FList *fList) ;
#endif /* createOriginalDB_hpp */
