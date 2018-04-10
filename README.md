# FrequentPatternMining_ByFPGrowth

---
### 106學年度(下)交大電機碩課程(NCTU-GEE9024)：資料科學(Data Science)  
#### HW2: Data Mining (Frequent Pattern Mining Using FP-Growth)  

---
0. 開發平台macOS_10.13.3、Xcode_9.1, 測試平台Windows10_1709、g++_5.4.0_i686-posix-dwarf-rev0
1. 編譯指令: g++ -std=c++11 main.cpp handleTypesAndParameters.cpp handleDataBase.cpp handleFPtree.cpp handleFrequentPatterns.cpp -o run.exe
2. 參數: (double)minSupport (string)inputFileName (string)outputFileName
3. 未輸入參數則預設 minSupport=0.1, imputFileName=sample.in, outputFileName=sample.out
4. 可輸入其他參數(需先輸入前三個)來印出運算過程(windows版實在印的太慢了... 所以預設是關閉的)
5. (windows版 main.cpp最後有system.("pause")是為了停在cmd用的 可以移除)  

=  

參數列表(比較重要的就all跟fpcount):  
all / -all :(開啟/關閉)所有除了fpcount以外的輸出  
fpcount / -fpcount :(開啟/關閉)輸出遞迴過程中的fp總數(避免傻傻等XD)  
database / -database  
minsupport / -minsupport  
flist / -flist  
fptree /-fptree  
cpb / -cpb  
fp / -fp  
(只是無聊加的功能 不知道有沒有bug 不要玩壞他拜託 ヽ(；▽；)ノ)  

```
執行範例:  
$ run.exe
$ run.exe 0.1 input.txt output.txt all fpcount  
$ run.exe 0.15 input.in output.out -all -fpcount  
```

---
#### 可使用./HW2_Frequent_Patterns_FPGrowth/dataGenerator 內的工具來產生測資(需用到Java、Jupyter)  
#### 詳情請自行閱讀該資料夾內的readme

---
#### 最新版本加入Smart Pointer可以大幅減少記憶體使用量  
#### Windows版請自行重新編譯 ( ´ ▽ ` )ﾉ，舊版仍可以使用 只是會memory leak而已QwQ

---
Input Format:

每一行為一筆交易(transaction), 交易中的item以逗號隔開(無空格), item順序由小到大排(0~999), 單行最多100個item(不重複), 最多500000行

範例:  
```
5,9,10
0,1,4,6,8,10
0,1,10
5
0,1,3,8,10
9
0,2,4,5,6,9
3
0,4,6,7,9,10
0,6,8,10
0,1,5,7,8,9
0,2,4,9
1,2,3,5,7,9,10
0,4,7,9
0,2,7
0,2,3,6,7,8,9
5,7,10
8
0,1,4,8,9,10
0,1,2,9,10
```

---
Output Format:

每一行為一組Frequent Pattern, FP內各item以逗號隔開(無空格), :後為supportRatio, 4捨5入至小數點後第四位

範例:  
```
0:0.6500
1:0.3500
2:0.3000
3:0.2000
4:0.3000
5:0.3000
6:0.2500
7:0.3500
8:0.3500
9:0.5500
10:0.5000
0,1:0.3000
0,2:0.2500
0,3:0.1000
0,4:0.3000
0,5:0.1000
0,6:0.2500
0,7:0.2500
0,8:0.3000
0,9:0.4000
0,10:0.3500
1,2:0.1000
1,3:0.1000
1,4:0.1000
1,5:0.1000
1,7:0.1000
1,8:0.2000
1,9:0.2000
1,10:0.3000
2,3:0.1000
2,4:0.1000
2,5:0.1000
2,6:0.1000
2,7:0.1500
2,9:0.2500
2,10:0.1000
3,7:0.1000
3,8:0.1000
3,9:0.1000
3,10:0.1000
4,6:0.1500
4,7:0.1000
4,8:0.1000
4,9:0.2500
4,10:0.1500
5,7:0.1500
5,9:0.2000
5,10:0.1500
6,7:0.1000
6,8:0.1500
6,9:0.1500
6,10:0.1500
7,8:0.1000
7,9:0.2500
7,10:0.1500
8,9:0.1500
8,10:0.2000
9,10:0.2500
0,1,4:0.1000
0,1,8:0.2000
0,1,9:0.1500
0,1,10:0.2500
0,2,4:0.1000
0,2,6:0.1000
0,2,7:0.1000
0,2,9:0.2000
0,3,8:0.1000
0,4,6:0.1500
0,4,7:0.1000
0,4,8:0.1000
0,4,9:0.2500
0,4,10:0.1500
0,5,9:0.1000
0,6,7:0.1000
0,6,8:0.1500
0,6,9:0.1500
0,6,10:0.1500
0,7,8:0.1000
0,7,9:0.2000
0,8,9:0.1500
0,8,10:0.2000
0,9,10:0.1500
1,2,9:0.1000
1,2,10:0.1000
1,3,10:0.1000
1,4,8:0.1000
1,4,10:0.1000
1,5,7:0.1000
1,5,9:0.1000
1,7,9:0.1000
1,8,9:0.1000
1,8,10:0.1500
1,9,10:0.1500
2,3,7:0.1000
2,3,9:0.1000
2,4,9:0.1000
2,5,9:0.1000
2,6,9:0.1000
2,7,9:0.1000
2,9,10:0.1000
3,7,9:0.1000
4,6,9:0.1000
4,6,10:0.1000
4,7,9:0.1000
4,8,10:0.1000
4,9,10:0.1000
5,7,9:0.1000
5,7,10:0.1000
5,9,10:0.1000
6,7,9:0.1000
6,8,10:0.1000
7,8,9:0.1000
7,9,10:0.1000
0,1,4,8:0.1000
0,1,4,10:0.1000
0,1,8,9:0.1000
0,1,8,10:0.1500
0,1,9,10:0.1000
0,2,4,9:0.1000
0,2,6,9:0.1000
0,4,6,9:0.1000
0,4,6,10:0.1000
0,4,7,9:0.1000
0,4,8,10:0.1000
0,4,9,10:0.1000
0,6,7,9:0.1000
0,6,8,10:0.1000
0,7,8,9:0.1000
1,2,9,10:0.1000
1,4,8,10:0.1000
1,5,7,9:0.1000
2,3,7,9:0.1000
0,1,4,8,10:0.1000
```
