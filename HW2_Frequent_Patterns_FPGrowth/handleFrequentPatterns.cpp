//
//  handleFrequentPatterns.cpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/3/31.
//  Copyright © 2018年 LS. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include "handleFrequentPatterns.hpp"
using std::cout ;
using std::endl ;
using std::ofstream ;
using std::string ;
using std::sort ;
using std::round ;
using std::fixed ;
using std::setprecision ;

FrequentPatternTable frequentPatterns ;

static void sortFrequentPatternsByLength() ;
static void printFrequentPatternTable(int transactionCount) ;
static void writeFrequentPatternTableToFile(string fileName, int transactionCount) ;

//==========
void writeFrequentPatternsTo(string fileName, int transactionCount){
	sortFrequentPatternsByLength() ;
	
	cout << "\n*FP總數: " << frequentPatterns.size() << "\n" ;
	printFrequentPatternTable(transactionCount) ;
	
	cout << "寫檔...\n" ;
	writeFrequentPatternTableToFile(fileName, transactionCount) ;
	cout << "完成" << endl ;
}

//==========
static void sortFrequentPatternsByLength(){
	auto greaterBySizeThenValue = [](SingleFrequentPattern const &a, SingleFrequentPattern const &b){			//magic!!!!!
		if(a.frequentPattern.size() != b.frequentPattern.size()){
			return a.frequentPattern.size() < b.frequentPattern.size() ;}
		else{
			for(int i=0; i<a.frequentPattern.size(); ++i){
				if(a.frequentPattern[i] < b.frequentPattern[i]){
					return true ;}
				else if(a.frequentPattern[i] > b.frequentPattern[i]){
					return false ;}
			}
			return false ;
		}} ;			//自訂比較器, 先用vector長度排, 長度相同則比較每一元素
	sort(frequentPatterns.begin(), frequentPatterns.end(), greaterBySizeThenValue) ;
}

static void printFrequentPatternTable(int transactionCount){
	if(printOrNot.frequentPatternTable == true){
		for(auto i=frequentPatterns.begin(); i!=frequentPatterns.end(); ++i){
			auto j=i->frequentPattern.begin() ;
			for(; j!=i->frequentPattern.end()-1; ++j){
				cout << *j << "," ;}
			cout << *j << ":" << fixed << setprecision(4) << (double)i->frequentPatternCount/transactionCount << "\n" ;
		}}
}

static void writeFrequentPatternTableToFile(string fileName, int transactionCount){
	ofstream fout(fileName) ;
	for(auto i=frequentPatterns.begin(); i!=frequentPatterns.end(); ++i){
		auto j=i->frequentPattern.begin() ;
		for(; j!=i->frequentPattern.end()-1; ++j){
			fout << *j << "," ;}
		fout << *j << ":" << fixed << setprecision(4) << (double)i->frequentPatternCount/transactionCount << "\n" ;
	}
	fout.close() ;
}
