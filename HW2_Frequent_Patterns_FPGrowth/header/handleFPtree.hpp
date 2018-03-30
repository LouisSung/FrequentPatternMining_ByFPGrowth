//
//  handleFPtree.hpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/3/26.
//  Copyright © 2018年 LS. All rights reserved.
//

#ifndef handleFPtree_hpp
#define handleFPtree_hpp

#include <stdio.h>
#include <vector>
using std::vector ;
using std::pair ;

class FPtree;

struct TreeNode{
	int _item, _itemCount ;
	int _childrenCount ;
	
	TreeNode *_parrent ;
	TreeNode *_nextSameItem ;
	vector<TreeNode*> _children;
	
	TreeNode(int item, TreeNode *parrent) ;
};

class FPtree{
public:
	FPtree(vector<pair<int, int>> *fList, int minSupportCount, int conditionCount) ;
	void buildFPtreeByFlistDB(vector<vector<int>> *fListDB) ;
	void mineFPtree() ;
	void printFPtree() ;
	TreeNode* getRoot() ;
	
private:
	TreeNode _root ;
	int _minSupportCount ;
	vector<pair<int, int>> _fList ;
	vector<pair<pair<int, int>, TreeNode*>> _headerTable ;
	vector<pair<int, vector<pair<vector<int>, int>>>> _conditionalPatternBases ;
	vector<int> _condition ;
	
	void insertNodeFromListAt(vector<int> *itemList, TreeNode *currentNode) ;
	void treeTraversal(TreeNode *currentNode) ;
	
	void createConditionalPatternBases() ;
	vector<FPtree*> createConditionalFPtree() ;
	void printConditionalPatternBases() ;
	
};
#endif /* handleFPtree_hpp */
