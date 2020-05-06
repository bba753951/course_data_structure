Data Structure Assignment 9-1
===
###### tags:`Data Structure`
[TOC]

# Activity On Edge (AOE) Network
大致作法
1. 把原本求shortest path改成尋找最長的，因此求出的distance[i]就是ee[i]
2. 接下來利用反向建立的revAdjList，反向搜尋路徑，並使用最短路徑紀錄，得到的ledistance[i]，就是le[i]
3. 利用activity的first得到e[i]的i(index)，再帶入distance[i]得到e[i]的值
4. 利用activity的second得到l[i]的i(index)，再帶入ledistance[i]，再減去wt[i]得到l[i]
5. l[i]-e[i]得到slack
6. slack等於0為critical

## Graph_SP class
```cpp=
class Graph_SP{             // SP serves as Shortest Path
private:
    int num_vertex;
	int ct;
    std::vector<std::list<std::pair<int,int> > > AdjList;
    std::vector<std::list<std::pair<int,int> > > revAdjList;
    std::vector<std::pair<int,int> > activity;
    std::vector<int> wt;
    std::vector<int> predecessor, distance,ledistance;
public:
    Graph_SP():num_vertex(0){};
    Graph_SP(int n):num_vertex(n){
        AdjList.resize(num_vertex);
        revAdjList.resize(num_vertex);
        activity.resize(num_vertex);
        wt.resize(num_vertex);
		ct=0;
    }
    void AddEdge(int from, int to, int weight);
    void PrintDataArray(std::vector<int> array);
    void PrintIntArray(int *array);
    void PrintResult();

    void InitializeSingleSource(int Start);     // 以Start作為起點
    void Relax(int X, int Y, int weight);       // 對edge(X,Y)進行Relax
    void leRelax(int X, int Y, int weight);       // 對edge(X,Y)進行Relax

    void DAG_SP(int Start = 0);                     // 需要 DFS, 加一個額外的Linked list
    void GetTopologicalSort(int *array, int Start);
    void DFSVisit_TS(int *array, int *color, int *discover, 
                     int *finish, int vertex, int &time, int &count);

};
```
- AdjList用來建立adjcency list
- revAdjList 用來建立inverse 反向，用於求le[i](ledistance)
- activity 紀錄activity
- wt紀錄activity的weight
- predecessor 被誰找到
- distance 最長路徑(ee[i])
- ledistance 反向求le[i]

## DAG_SP()
- DAG_SP()：尋找Shortest-Path Tree的主要函式
- 呼叫InitializeSingleSource初始化
- 第一個for進行Relax尋找最長路徑
- 第二個for進行反向的relax，尋找最小的le
- 在第二個for開始之前要先把最後一個vertex(topologicalsort的最後一個，相當於最早結束DFS的vertex)設ledistance
```cpp=
void Graph_SP::DAG_SP(int Start){

    InitializeSingleSource(Start);      // distance[],predecessor[]的initialization

    int topologicalsort[num_vertex];

    GetTopologicalSort(topologicalsort, Start);

    for (int i = 0; i < num_vertex; i++) {
        int v = topologicalsort[i];
        for (std::list<std::pair<int, int> >::iterator itr = AdjList[v].begin();
             itr != AdjList[v].end(); itr++) {
            Relax(v, (*itr).first, (*itr).second);
        }
    }
	ledistance[topologicalsort[num_vertex-1]]=distance[topologicalsort[num_vertex-1]];

    for (int i = num_vertex-1; i >= 0; i--) {
        int v = topologicalsort[i];
        for (std::list<std::pair<int, int> >::iterator itr = revAdjList[v].begin();
             itr != revAdjList[v].end(); itr++) {
            leRelax(v, (*itr).first, (*itr).second);
        };
    };

}
```


## GetTopologicalSort()
- GetTopologicalSort()：可以視為==DFS()的變形==，主要功能是==建立color[]、discover[]、finish[]等資料項目==，並把從DAG_SP()接收來的資料項目topologicalsort[]傳進DFSVisit_TS()。

```cpp=
void Graph_SP::GetTopologicalSort(int *array, int Start){

    int color[num_vertex], discover[num_vertex], finish[num_vertex];

    for (int i = 0; i < num_vertex; i++) {
        color[i] = 0;
        discover[i] = 0;
        finish[i] = 0;
        predecessor[i] = -1;
    }

    int time = 0,
        count = num_vertex-1,        // count 為 topologicalsort[] 的 index
        i = Start;

    for (int j = 0; j < num_vertex; j++) {
        if (color[i] == 0) {
            DFSVisit_TS(array, color, discover, finish, i, time, count);
        }
        i = j;
    }

}
```

## DFSVisit_TS()
- DFSVisit_TS()：==array[count--] = vertex==;，其中count為topologicalsort[]的index，用意是要按照「==探索結束」的先後==，將vertex依序從topologicalsort[]的==尾端放到前端==，如此一來，topologicalsort[]所存放的vertex，就會按照==finish[]由大到小==的順序。

```cpp=
void Graph_SP::DFSVisit_TS(int *array, int *color, int *discover, 
                           int *finish, int vertex, int &time, int &count){

    color[vertex] = 1;  // set gray
    discover[vertex] = ++time;
    for (std::list<std::pair<int,int> >::iterator itr = AdjList[vertex].begin(); 
         itr != AdjList[vertex].end(); itr++) {
        if (color[(*itr).first] == 0) {
            predecessor[(*itr).first] = vertex;
            DFSVisit_TS(array, color, discover, finish, (*itr).first, time, count);
        }
    }
    color[vertex] = 2;  // set black
    finish[vertex] = ++time;
    array[count--] = vertex;            // 產生Topological Sort
}
```
1. time：在整個DFS()的過程會有一條「時間軸」，若Graph中有==N個vertex==，「時間軸」上一共會有==2N個「時間點==」
2. discover與finish array：每個vertex會被標記上兩個「時間點」，分別是「==被發現==(discover)」的時間與「==結束==(finish)」的時間：
    - discover：例如，vertex(B)被vertex(A)找到，則==discover[B]會是discover[A]加一==，表示vertex(B)在整個時間軸上是在vertex(A)之後被找到(這其中便存在「==ancestor-descendant==」的關係)
    - finish：若vertex(B)已經經由有效edge探索過所有與之相連的vertex，==表示以vertex(B)為起點的探索已經結束==，便標上finish[B]。

3. color array：利用color標記哪些vertex已經「==被發現==」與「==結束==」。
    - 白色表示該vertex還沒有「被發現」；
    - 灰色表示該vertex已經「被發現」，但是還沒有「結束」
    - 黑色表示該vertex已經「結束」

4. predecessor array：記錄某個vertex是被哪一個vertex找到的，如此便能回溯路徑(如同BFS()，DFS()亦能生成一個Predecessor Subgraph)。


## Relax
把原本最短路徑的大於改成小於，代表要找最長路徑
```cpp=
void Graph_SP::Relax(int from, int to, int weight){

    if (distance[to] < distance[from] + weight) {
        distance[to] = distance[from] + weight;
        predecessor[to] = from;
    }
}
```
## leRelax
le是用倒推回去，因此weight用減的，且要找最小的
```cpp=
void Graph_SP::leRelax(int from, int to, int weight){

    if (ledistance[to] > ledistance[from] - weight) {
        ledistance[to] = ledistance[from] - weight;
    }
}
```