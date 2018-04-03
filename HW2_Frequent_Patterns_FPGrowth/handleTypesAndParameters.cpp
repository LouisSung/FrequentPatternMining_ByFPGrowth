//
//  handleTypesAndParameters.cpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/4/3.
//  Copyright © 2018年 LS. All rights reserved.
//

#include <string>
#include "handleTypesAndParameters.hpp"
using std::string ;

PrintOrNot printOrNot(true) ;			//預設輸出所有內容
int minSupportCount = 0 ;
int transactionCount = 0 ;

//==========
Item::Item(int itemName, int itemCount){
	this->itemName = itemName ;
	this->itemCount = itemCount ;
}

//==========
TreeNode::TreeNode(int itemName, TreeNode *parrent):
itemName(itemName),
itemCount(1),			//出現一次
childrenCount(0),
parrent(parrent),
nextSameItem((TreeNode*) NULL){
}

//==========
SingleItemHeader::SingleItemHeader(Item item, TreeNode header):
item(item),
header(header){
}

//==========
SingleConditionalPatternBase::SingleConditionalPatternBase(int conditionalItemName, const AllConditionalPath &singlePath):
conditionalItemName(conditionalItemName),
allConditionalPaths(singlePath){
}

SingleFrequentPattern::SingleFrequentPattern(FrequentPattern frequentPattern, int frequentPatternCount):
frequentPattern(frequentPattern),
frequentPatternCount(frequentPatternCount){
}

//==========
PrintOrNot::PrintOrNot(bool all){
	setPrintOrNot(all, true) ;			//印出fpCount
}

void PrintOrNot::setPrintOrNot(bool all, bool fpCount, bool database, bool minSupportCount, bool fList, bool fpTree, bool conditionalPatternBases, bool frequentPatternTable){
	this->all = all ;
	this->fpCount = fpCount ;
	this->database = database and all;
	this->minSupportCount = minSupportCount and all ;
	this->fList = fList and all ;
	this->fpTree = fpTree and all ;
	this->conditionalPatternBases = conditionalPatternBases and all ;
	this->frequentPatternTable = frequentPatternTable and all ;
}

void PrintOrNot::setPrintParameterByArgv(int argc, const char* parameter[]){
	const string printFunc[8][2] = {{"all", "-all"}, {"fpcount", "-fpcount"}, {"database", "-database"}, {"minsupport", "-minsupport"}, {"flist", "-flist"}, {"fptree", "-fptree"}, {"cpb", "-cpb"}, {"fp", "-fp"}} ;
	bool allFlag = true ;
	for(int i=4; i<argc; ++i){
		string s = parameter[i] ;
		if(s == printFunc[0][0] or s == printFunc[0][1]){
			for(int j=2; j<8; ++j){			//不改fpCount
				if(s == printFunc[0][0]){
					*func[j] = true ;}
				else{
					*func[j] = false ;}
			}
			allFlag = false ;
		}
		for(int j=1; j<8; ++j){
			if(s == printFunc[j][0]){
				*func[j] = true and (allFlag or all) ;}
			else if(s == printFunc[j][1]){
				*func[j] = false ;}
		}
	}
}
