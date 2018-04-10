//
//  handleTypesAndParameters	.hpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/4/3.
//  Copyright © 2018年 LS. All rights reserved.
//

#ifndef handleTypeAndPrintflag_hpp
#define handleTypeAndPrintflag_hpp

#include <vector>
using std::vector ;
using std::shared_ptr ;
using std::weak_ptr ;

extern int minSupportCount, transactionCount ;

struct Item ;
struct TreeNode ;
struct SingleItemHeader ;
struct SinglePath ;
struct SingleConditionalPatternBase ;
struct SingleFrequentPattern ;

typedef vector<Item> FList ;
typedef vector<int> Transaction ;
typedef vector<int> FrequentPattern ;
typedef vector<Transaction> Database ;
typedef vector<SingleItemHeader> HeaderTable ;
typedef vector<SinglePath> AllConditionalPath ;
typedef vector<SingleConditionalPatternBase> ConditionalPatternBases ;
typedef vector<SingleFrequentPattern> FrequentPatternTable;

struct Item{
	int itemName ;
	int itemCount ;
	Item(int itemName, int itemCount) ;
};

struct TreeNode{
	int itemName ;
	int itemCount, childrenCount ;
	weak_ptr<TreeNode> parrent ;
	weak_ptr<TreeNode> nextSameItem ;
	vector<shared_ptr<TreeNode>> children;
	
	TreeNode(int itemName,shared_ptr<TreeNode> parrent) ;
};

struct SingleItemHeader{
	Item item ;
	shared_ptr<TreeNode> header ;
	
	SingleItemHeader(Item item, shared_ptr<TreeNode> header) ;
};

struct SinglePath{
	vector<int> pathRecord ;
	int pathCount ;
};

struct SingleConditionalPatternBase{
	int conditionalItemName ;
	vector<SinglePath> allConditionalPaths ;
	
	SingleConditionalPatternBase(int conditionalItemName, const AllConditionalPath &singlePath) ;
};

struct SingleFrequentPattern{
	FrequentPattern frequentPattern ;
	int frequentPatternCount ;
	
	SingleFrequentPattern(FrequentPattern frequentPattern, int frequentPatternCount) ;
};

struct PrintOrNot{
	bool all, fpCount, database, minSupportCount, fList, fpTree, conditionalPatternBases, frequentPatternTable ;
	bool *func[8] = {&all, &fpCount, &database, &minSupportCount, &fList, &fpTree, &conditionalPatternBases, &frequentPatternTable} ;
	
	void setPrintParameterByArgv(int argc, const char* parameter[]) ;
	void setPrintOrNot(bool all, bool fpCount=true, bool database=true, bool minSupportCount=true, bool fList=true, bool fpTree=true, bool conditionalPatternBases=true, bool frequentPatternTable=true) ;
	PrintOrNot(bool all) ;
}extern printOrNot ;
#endif /* handleTypeAndPrintflag_hpp */
