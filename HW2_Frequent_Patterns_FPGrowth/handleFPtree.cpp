//
//  handleFPtree.cpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/3/26.
//  Copyright © 2018年 LS. All rights reserved.
//

#include "handleFPtree.hpp"

void buildFPtree(vector<vector<int>> *fListDB){
	FPtree fpTree ;
	for(auto i=fListDB->begin(); i!=fListDB->end(); ++i){
		fpTree.insertNodeFromListAt(&(*i), fpTree.getRootPointer()) ;}
}

//==========
TreeNode::TreeNode(int item, TreeNode *parrent){
	_item = item ;
	_itemCount = 1 ;			//出現一次
	_childrenCount = 0 ;
	_parrent = parrent ;			//紀錄parrent
	_nextSameItem = NULL ;
	_children = vector<TreeNode>() ;
}

//==========
FPtree::FPtree(): root(TreeNode(-1, NULL)){			//constructor預設建立一個item=-1, parrent=NULL的TreeNode作為root
}

void FPtree::insertNodeFromListAt(vector<int> *itemList, TreeNode *parrent){
	if(itemList->size() > 0){			//還有item
		int currentItem = (*itemList)[0] ;
		itemList->erase(itemList->begin()) ;			//取出第一個item編號, 並從itemList移除
		
		bool noDuplicatePath = true ;
		if(parrent->_childrenCount !=0){			//有child
			for(auto i=parrent->_children.begin(); i!=parrent->_children.end(); ++i){			//遍歷每個child
				if(currentItem == i->_item){			//現在item和child item重複, 表示這個path已經建立過
					++i->_itemCount ;			//child的item計數+1
					insertNodeFromListAt(itemList, &(*i)) ;			//從child item繼續做(往下一層)
					noDuplicatePath = false ;			//有重複路徑
					break ;			//一次處理一個item, 若有找到一個重複, 則後面不可能再重複, 不需繼續遍歷
				}}}
		
		if(noDuplicatePath){			//沒有重複路徑: 沒有child(不會有重複問題)或child沒有重複的item
			TreeNode *newChild = new TreeNode(currentItem, parrent) ;			//建立新節點
			parrent->_children.push_back(*newChild) ;
			++parrent->_childrenCount ;
			insertNodeFromListAt(itemList, &(parrent->_children.back())) ;			//此處不能用newChild而要用parrent, 因為push_back是拷貝值而不是位址
		}
	}
}

TreeNode* FPtree::getRootPointer(){
	return &root ;
}
