//
//  handleFPtree.hpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/3/26.
//  Copyright © 2018年 LS. All rights reserved.
//

#ifndef handleFPtree_hpp
#define handleFPtree_hpp

#include "handleTypesAndParameters.hpp"

class FPtree{
public:
	FPtree(FList *fList, int minSupportCount, int conditionCount) ;
	void buildFPtreeByFlistDB(Database *fListDB) ;
	void mineFPtree() ;
	void printFPtree() ;
	TreeNode* getRoot() ;
	
private:
	TreeNode _root ;
	int _minSupportCount ;
	FList _fList ;
	HeaderTable _headerTable ;
	ConditionalPatternBases _conditionalPatternBases ;
	vector<int> _condition ;
	
	void insertNodeFromListAt(Transaction *itemList, TreeNode *currentNode) ;
	void treeTraversal(TreeNode *currentNode) ;
	
	void createConditionalPatternBases() ;
	vector<FPtree*> createConditionalFPtree() ;
	void getFrequentPatterns() ;
	void printConditionalPatternBases() ;
};
#endif /* handleFPtree_hpp */
