//
//  handleFrequentPatterns.cpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/3/31.
//  Copyright © 2018年 LS. All rights reserved.
//

#include "handleFrequentPatterns.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using std::cout ;
using std::endl ;
using std::string ;
using std::vector ;
using std::sort ;
using std::pair ;
using std::make_pair ;
using std::round ;
using std::setprecision ;
using std::fixed ;

extern bool printFrequentPatternsOrNot ;
vector<pair<vector<int>, int>> frequentPatterns ;
static bool readyToWriteFile = false ;

static void sortFrequentPatternsByLength() ;
static void printFrequentPatterns(int transactionCount) ;

void writeFrequentPatternsTo(string fileName, int transactionCount){
	sortFrequentPatternsByLength() ;
	
	cout << "\n*FP總數: " << frequentPatterns.size() << endl ;
	printFrequentPatterns(transactionCount) ;
	
	cout << "寫檔..." << endl ;
	freopen(fileName.c_str(), "w", stdout) ;			//重新導向stdout
	readyToWriteFile = true ;
	printFrequentPatterns(transactionCount) ;
}

static void sortFrequentPatternsByLength(){
	auto greaterBySizeThenValue = [](pair<vector<int>, int> const & a, pair<vector<int>, int> const & b){			//magic!!!!!
		if(a.first.size() != b.first.size()){
			return a.first.size() < b.first.size() ;}
		else{
			for(int i=0; i<a.first.size(); ++i){
				if(a.first[i] < b.first[i]){
					return true ;}
				else if(a.first[i] > b.first[i]){
					return false ;}
			}
			return false ;
		}} ;			//自訂比較器, 先用vector長度排, 長度相同則比較每一元素
	sort(frequentPatterns.begin(), frequentPatterns.end(), greaterBySizeThenValue) ;
}

static void printFrequentPatterns(int transactionCount){
	if(printFrequentPatternsOrNot == true or readyToWriteFile == true){
		for(auto i=frequentPatterns.begin(); i!=frequentPatterns.end(); ++i){
			auto j=i->first.begin() ;
			for(; j!=i->first.end()-1; ++j){
				cout << *j << "," ;}
			cout << *j << ":" << fixed << setprecision(4) << (double)i->second/transactionCount << endl ;
		}}
}

