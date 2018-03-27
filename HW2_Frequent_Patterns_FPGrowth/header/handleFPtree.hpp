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

class FPtree ;
void buildFPtreeByFlistDB(FPtree *fpTree, vector<vector<int>> *fListDB) ;

struct TreeNode{
	int _item, _itemCount ;
	int _childrenCount ;
	
	TreeNode *_parrent ;
	TreeNode *_nextSameItem ;
	vector<TreeNode> _children;
	
	TreeNode(int item, TreeNode *parrent) ;
};

class FPtree{
	TreeNode root ;
public:
	FPtree() ;
	void insertNodeFromListAt(vector<int> *itemList, TreeNode *currentNode) ;
	void printFPtree(TreeNode *currentNode) ;
	TreeNode* getRoot() ;
};
#endif /* handleFPtree_hpp */
