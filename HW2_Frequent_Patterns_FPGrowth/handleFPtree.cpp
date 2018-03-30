//
//  handleFPtree.cpp
//  HW2_Frequent_Patterns_FPGrowth
//
//  Created by LouisSung on 2018/3/26.
//  Copyright © 2018年 LS. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include "handleFPtree.hpp"
using std::cout ;
using std::endl ;
using std::pair ;
using std::make_pair ;
using std::reverse ;

//==========
TreeNode::TreeNode(int item, TreeNode *parrent){
	_item = item ;
	_itemCount = 1 ;			//出現一次
	_childrenCount = 0 ;
	_parrent = parrent ;			//紀錄parrent
	_nextSameItem = (TreeNode*)NULL ;
	vector<TreeNode*> *children = new vector<TreeNode*> ;
	_children = *children ;
}

//==========
FPtree::FPtree(vector<pair<int, int>> *fList): root(TreeNode(-1000, (TreeNode*)NULL)){			//constructor預設建立一個item=-1000(item範圍0~999), parrent=NULL的TreeNode作為root
	headerTable.reserve(fList->size()) ;			//headerTable大小=fList長度
	
	for(auto i=fList->begin(); i!=fList->end(); ++i){
		TreeNode *headNode = new TreeNode(i->first, (TreeNode*)NULL) ;			//建立headNode, 用來指向該item在FPtree第一次出現的位置
		headerTable.push_back(make_pair(*i, headNode)) ;
	}
}

void FPtree::buildFPtreeByFlistDB(vector<vector<int>> *fListDB){
	for(auto i=fListDB->begin(); i!=fListDB->end(); ++i){			//將fListDB內的每筆交易用來建FPtree
		this->insertNodeFromListAt(&(*i), this->getRoot()) ;}
}

void FPtree::insertNodeFromListAt(vector<int> *itemList, TreeNode *currentNode){
	if(itemList->size() > 0){			//還有item
		int currentItem = (*itemList)[0] ;
		itemList->erase(itemList->begin()) ;			//取出第一個item編號, 並從itemList移除
		
		TreeNode **pointerToPreviousNode = (TreeNode**)NULL ;			//用以紀錄從header開始走到最後node的address(即新node的前一個)
		for(auto i=headerTable.begin(); i!=headerTable.end(); ++i){
			if(currentItem == i->first.first){			//從header table找到相符的item
				TreeNode *previousNode = i->second ;
				while(previousNode->_nextSameItem != (TreeNode*)NULL){			//一直往後找到該node沒有nextSameItem為止
					previousNode = previousNode->_nextSameItem ;}
				pointerToPreviousNode = &(previousNode) ;			//取得該node的address
				break ;			//item不會重複, 故可停止遍歷hearder table
			}}
		
		bool noDuplicatePath = true ;
		if(currentNode->_childrenCount !=0){			//有child
			for(auto i=currentNode->_children.begin(); i!=currentNode->_children.end(); ++i){			//遍歷每個child
				if(currentItem == (*i)->_item){			//現在item和child item重複, 表示這個path已經建立過
					++(*i)->_itemCount ;			//child的item計數+1
					insertNodeFromListAt(itemList, *i) ;			//從child item繼續做(往下一層)
					noDuplicatePath = false ;			//有重複路徑
					break ;			//一次處理一個item, 若有找到一個重複, 則後面不可能再重複, 不需繼續遍歷
				}}}
		
		if(noDuplicatePath){			//沒有重複路徑: 沒有child(不會有重複問題)或child沒有重複的item
			TreeNode *newChild = new TreeNode(currentItem, currentNode) ;			//建立新節點
			currentNode->_children.push_back(newChild) ;
			++currentNode->_childrenCount ;
			(*pointerToPreviousNode)->_nextSameItem = newChild ;			//將前一個node的nextSameItem設為目前node(建立新node時才做, 重複路徑的做過了)
			insertNodeFromListAt(itemList, newChild) ;
		}
	}
}

void FPtree::mineFPtree(){
	createConditionalPatternBases() ;
	printConditionalPatternBases() ;
}

void FPtree::createConditionalPatternBases(){
//	vector<pair<item編號, vector<pair<vector<單一路徑>, 路徑次數>>>> conditionalPatternBases
	TreeNode *sameItem, *currentItem ;
	vector<int> singlePath ;
	vector<pair<vector<int>, int>> allPaths ;
	int pathCount = 0;
	
	singlePath.reserve(512) ;
	allPaths.reserve(512) ;
	conditionalPatternBases.reserve(headerTable.size()) ;			//預留vector大小, cPatternBases數量和headerTable一樣
	
	for(auto i=headerTable.end()-1; i!=headerTable.begin()-1; --i){			//遍歷所有header table的item
		sameItem = i->second->_nextSameItem ;			//利用headerTable找到該編號在FPtree中第一次出現的位置
		
		while(sameItem != (TreeNode*)NULL){			//遍歷FPtree中與該item同編號的所有節點
			currentItem = sameItem->_parrent ;			//不紀錄葉節點, 從其parrent開始
			pathCount = sameItem->_itemCount ;			//紀錄葉節點的次數, 作為此path的出現次數
			
			while (currentItem->_parrent != (TreeNode*)NULL) {			//遍歷該節點的所有parrent
				singlePath.push_back(currentItem->_item) ;			//紀錄path
				currentItem = currentItem->_parrent ;			//指向parrent
			}
			
			if(singlePath.size() > 0){
				reverse(singlePath.begin(), singlePath.end()) ;			//葉to根--反轉-->根to葉
				allPaths.push_back(make_pair(singlePath, pathCount)) ;			//紀錄此item所有的path與出現次數
				singlePath.clear() ;			//清除以記錄下一條path
			}
			sameItem = sameItem->_nextSameItem ;			//指向下一個同編號的節點
		}
		
		if(allPaths.size() > 0){
			conditionalPatternBases.push_back(make_pair(i->first.first, allPaths)) ;
			allPaths.clear() ;			//清除以紀錄下一組paths
		}
	}
}

void FPtree::printFPtree(TreeNode *currentNode){
	static vector<pair<int, int>> pathFromRootToLeaf ;			//static, 遞迴過程中保留值
	
	pathFromRootToLeaf.push_back(make_pair(currentNode->_item, currentNode->_itemCount)) ;			//目前item放入vector
	if(currentNode->_nextSameItem == (TreeNode*)NULL){			//沒有nextSameItem的話輸出負數以做辨認
		(pathFromRootToLeaf.end()-1)->first *= -1 ;}
	
	if(currentNode->_childrenCount > 0){			//有child
		for(auto i=currentNode->_children.begin(); i!=currentNode->_children.end(); ++i){			//遞迴並遍歷所有child
			printFPtree(*i) ;}
		pathFromRootToLeaf.pop_back() ;			//pop目前item
	}
	else if(pathFromRootToLeaf.size() > 1){
		auto i=pathFromRootToLeaf.begin()+1 ;			//沒有child, 表示為葉節點, 準備印出root到leaf的path
		for(; i!=pathFromRootToLeaf.end()-1; ++i){
			cout << "<" << i->first << ": " << i->second << ">, " ;}
		cout << "<" << i->first << ": " << i->second << ">" << endl ;
		pathFromRootToLeaf.pop_back() ;			//pop目前節點
	}
	else if(pathFromRootToLeaf.size() == 1){			//只有root, 沒有item
		cout << "FPtree為空" << endl ;}
}

void FPtree::printConditionalPatternBases(){
	for(auto i=conditionalPatternBases.begin(); i!=conditionalPatternBases.end(); ++i){			//所有item
		int pathCounter = 0 ;
		cout << "\n* item: " << i->first << endl ;
		for(auto j=i->second.begin() ; j!=i->second.end(); ++j){			//所有path
			cout << "path " << ++pathCounter << ": <"  ;
			auto k=j->first.begin() ;
			for(; k!=j->first.end()-1; ++k){			//path內所有元素
				cout << *k << "," ;}
			cout << *k << "> 次數: " << j->second << endl ;
		}
	}
}

TreeNode* FPtree::getRoot(){
	return &root ;
}
