Data Structure Assignment 8
===
###### tags:`Data Structure`
[TOC]

# Single source shortest paths
## 基本介紹
因為weitht > 0，所以使用了Dijkstra’s Algorithm

在演算法中，將會使用到==Min-Priority Queue==，包含三個基本操作(operation)
- ExtractMin()
- DecreaseKey()
- BuildMinHeap()


## Min-Priority Queue
### HeapNode
Binary Heap中的每個資料(node)之Dictionary將以struct實現：
```cpp=
struct HeapNode{
    int element, key;
    HeapNode():element(0),key(0){};
    HeapNode(int node, int key):element(node), key(key){};
};
```
### class BinaryHeap之定義
```cpp=
class BinaryHeap{
private:
    std::vector<HeapNode> heap;        // 存放HeapNode資料的矩陣
    void swap(struct HeapNode &p1, struct HeapNode &p2);
    int FindPosition(int node);
    int GetParentNode(int node){return std::floor(node/2);};

public:
    BinaryHeap(){               // default constructor會把heap[0]給預留 
        heap.resize(1);         // 之後若新增HeapNode, 會從heap[1]開始新增
    }
    BinaryHeap(int n){
        heap.resize(n + 1);
    }
    bool IsHeapEmpty(){return (heap.size()<1);};

    // Min-Priority Queue
    void MinHeapify(int node, int length);
    void BuildMinHeap(std::vector<int> array);
    void DecreaseKey(int node, int newKey);
    int Minimum();                  // 回傳vertex的位置index
    int ExtractMin();               // 回傳vertex的位置index
};

```
### 函式：MinHeapify
MinHeapify()是一種「==由上至下==」(由root往leaf)，按照Min Heap之規則逐一調整subtree的方法，步驟如下：

- 選定某個index(i)之node(i)，視為subtree之root；
- 比較root的Key與兩個child(node(2i)與node(2i+1))之Key；
	- 找出三者最小的放root
	- 會需要一個迴圈對「所有具有child的node」進行檢查(利用MinHeapify()檢查)，這就是下一個函式BuildMinHeap()的任務
	
### 函式：BuildMinHeap
BuildMinHeap()的任務很簡單，把==每一個「具有child」的node都進行過一次MinHeapify()==，如此便能保證Binary Heap中的所有subtree皆滿足Min Heap規則，便能==將一個由任意矩陣代表的Binary Heap轉換成Min Heap==

- input：給定一個任意矩陣array[]。
- heap[]初始化：先把array[]的資料放進heap[]，並將heap[0]閒置。

- 接著對index(⌊N/2⌋)到index(1)進行MinHeapify()

### 函式：ExtractMin
ExtractMin()的目的是「==回傳==具有最小Key的node之index」，並且將其從Heap中==移除==

### 函式：DecreaseKey
DecreaseKey()的目的是==調整Min Heap中的node之Key值==，因為Key值改變，極有可能違反Min Heap規則，因此也需要對Heap進行調整

## Dijkstra’s Algorithm
```cpp=
class Graph_SP{             // SP serves as Shortest Path
private:
    int num_vertex;
    std::vector<std::list<std::pair<int,int> > > AdjList;
    std::vector<int> predecessor, distance;
    std::vector<bool> visited;
    std::stack<int> ans;
public:
    Graph_SP():num_vertex(0){};
    Graph_SP(int n):num_vertex(n){
        AdjList.resize(num_vertex);
    }
    void AddEdge(int from, int to, int weight);
    void PrintDataArray(std::vector<int> array);
    void PrintPath();

    void InitializeSingleSource(int Start);     // 以Start作為起點
    void Relax(int X, int Y, int weight);       // edge方向：from X to Y

    void Dijkstra(int Start = 0);        // 需要Min-Priority Queue
    friend class BinaryHeap;             // 以Binary Heap實現Min-Priority Queue
};
```
- num_vertex 有幾個vertex
- predecessor 紀錄上一個
- distance 紀錄path上的total weight
- ans 利用predecessor回朔，得到拜訪的path
- void AddEdge(int from, int to, int weight);
使用std::vector<std::list<std::pair<int,int> > > 紀錄adjacency list
	- 將from以std::vector的index表示；
	- 將to放在std::pair<int,int>的第一個int資料項；
	- 將weight放在std::pair<int,int>的第二個int資料項
	
- void InitializeSingleSource(int Start) 進行初始化
	- predecessor：將所有vertex之predecessor設為−1
	- distance 都設成 Max_Distance;
	- ==distance[Start] = 0==;
	
### Relaxation觀念	
現從vertex(S)作為起點，欲尋找抵達vertex(X)與vertex(Y)之最短路徑。

其中，到vertex(X)之最短路徑只有一種可能，δ(S,X)=w(S,X)。
而到vertex(Y)可以從vertex(S)或者vertex(X)抵達，因此最短路徑δ(S,Y)有兩種可能：
- δ(S,Y)=w(S,Y)：vertex(Y)經由vertex(S)直接抵達。
- δ(S,Y)=w(S,X)+w(X,Y)：vertex(S)先經過vertex(X)，再到vertex(Y)。


找到最短路徑的方法很直觀，只要比較這兩條路徑的weight，挑weight小的path即可。

### Dijkstra 主要觀念
1. ExtractMin()：從Min-Priority Queue，也就是Q中，選出distance最小的vertex，並將其從Q中移除。
2. ==Relax()以及DecreaseKey()==：對選出的vertex所連結的edge進行Relax()，更新distance與predecessor，並同步更新Q。


# All pair shortest paths

使用Floyd-Warshall Algorithm

引入==中繼點(intermediate vertex)==

每次多加入一個「中繼點(intermediate vertex)」，考慮從vertex(X)走向vertex(Y)的最短路徑，==是否因為經過了該中繼點vertex(Z)而降低成本==，形成新的最短路徑。

Floyd-Warshall Algorithm的奧義就是「==以較小段的最短路徑(subpath)，連結出最終的最短路徑==」

換句話說，==由較小段的最短路徑(subpath)接起來的路徑必定仍然是最短路徑==。

## Graph_SP_AllPairs class
```cpp=
class Graph_SP_AllPairs{
private:
    int num_vertex;
    std::vector< std::vector<int> > AdjMatrix, Distance, Predecessor;
    std::stack<int> ans;
public:
    Graph_SP_AllPairs():num_vertex(0){};
    Graph_SP_AllPairs(int n);
    void AddEdge(int from, int to, int weight);
    void PrintData(std::vector< std::vector<int> > array);
    void InitializeData();
    void FloydWarshall();
    void PrintPath();
};
```
### 基本參數
由於是All Pairs，每個vertex都將視為起點，尋找以該vertex走到其他vertex之最短路徑，可以想見，在Single-Source Shortest Path中使用的一維矩陣distance[]與predecessor[]，需要再增加一個維度成==二維矩陣==，以Distance[][]與Predecessor[][]表示

連帶地，在建立Graph時，也將==使用Adjacency Matrix==，並以其陣列元素值代表edge之weight。

- 基本的資料項目：AdjList、Distance、Predecessor
    - 以std::vector\<std::vector\<int>>實現。
    
### InitializeData()
```cpp=
void Graph_SP_AllPairs::InitializeData(){

    Distance.resize(num_vertex);
    Predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; i++) {
        Distance[i].resize(num_vertex);
        Predecessor[i].resize(num_vertex, -1);
        for (int j = 0; j < num_vertex; j++) {
            Distance[i][j] = AdjMatrix[i][j];
            if (Distance[i][j] != 0 && Distance[i][j] != MaxDistance) {
                Predecessor[i][j] = i;
            }
        }
    }
}
```
用來對Distance與Predecessor進行初始化

- Distance
因為實際上的程式碼不存在無限大(∞)，所以定義const int MaxDistance = 1000;
只要Distance[i][j]的ij之間沒有edge就初始化為MaxDistance，反之就是ij之間的weight

- Predecessor
Distance[i][j]
初始狀態時，因為當只有edge(i,j)存在時，才存在一條路徑從vertex(i)走到vertex(j)，因此，Distance[i][j]的初始狀態為，存在edge就為j不存在就為-1


### FloydWarshall
```cpp=
void Graph_SP_AllPairs::FloydWarshall(){

    InitializeData();

    for (int k = 0; k < num_vertex; k++) {
        for (int i = 0; i < num_vertex; i++) {
            for (int j = 0; j < num_vertex; j++) {
                if ((Distance[i][j] > Distance[i][k]+Distance[k][j]) 
                     && (Distance[i][k] != MaxDistance)) {
                    Distance[i][j] = Distance[i][k]+Distance[k][j];
                    Predecessor[i][j] = Predecessor[k][j];
                }
            }
        }

    }
}
```
- FloydWarshall()利用==三層迴圈==，進行Floyd-Warshall Algorithm
    - 在第三層迴圈的if判斷式內，多了一個條件(Distance[i][k] != MaxDistance)，是因為實際上的程式碼不存在「無限大(∞)」，以下面提供的程式碼為例，令無限大的距離為int MaxDistance = 1000，可以想像的是，若不加上上述條件，程式會以為Distance=1000是「有edge相連」
    
最外層for的k代表每次加入的中繼點
若加入的中繼點形成的distance會比較小，就更新Distance[i][j]和Predecessor[i][j]