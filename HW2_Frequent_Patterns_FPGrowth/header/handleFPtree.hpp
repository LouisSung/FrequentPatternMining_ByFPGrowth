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
using std::shared_ptr ;
class FPtree{
public:
	FPtree(FList *fList, int conditionCount) ;
	void buildFPtreeByFlistDB(Database *fListDB) ;
	void mineFPtree() ;
	void printFPtree() ;
	
private:
	shared_ptr<TreeNode> _root ;
	FList _fList ;
	HeaderTable _headerTable ;
	ConditionalPatternBases _conditionalPatternBases ;
	vector<int> _condition ;
	
	void insertNodeFromListAt(Transaction *itemList, shared_ptr<TreeNode> currentNode) ;
	void treeTraversal(shared_ptr<TreeNode> currentNode) ;
	
	void createConditionalPatternBases() ;
	vector<shared_ptr<FPtree>> createConditionalFPtree() ;
	void getFrequentPatterns() ;
	void printConditionalPatternBases() ;
};
#endif /* handleFPtree_hpp */
