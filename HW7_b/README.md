Data Structure Assignment 7
===
###### tags:`Data Structure`
[TOC]

# Bipartite graph


## Graph class
```cpp=
class Graph{
private:
    int num_vertex;
    std::vector< std::list<int> > AdjList;
    std::queue<int> A;
    std::queue<int> B;

public:
    Graph():num_vertex(0){};           // default constructor
    Graph(int N):num_vertex(N){        // constructor with input: number of vertex
        // initialize Adjacency List
        AdjList.resize(num_vertex);
    };
    void AddEdgeList(int from, int to);
    bool isBipartite(void);
    void printQ(void);
};
```
1. 使用STL的vector和list創建AdjList(方便動態增減)
2. use constructor to initialize Adjacency List

## AddEdgeList
```cpp=
void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
    AdjList[to].push_back(from);
}
```
因為是undirected graph，所以等於一次增加兩個方向

## isBipartite
```cpp=
bool Graph::isBipartite(void){
    // color values: 
    // 0 (un-colored), 1 (A set), -1 (B set)
    std::vector<int> color(num_vertex, 0);

    std::queue<int> q;

    for (int i = 0; i < num_vertex; ++i) {
        if (color[i] != 0) continue;

        // BFS to color neighbors in opposite colors
        color[i] = 1;
        q.push(i);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (std::list<int>::iterator itr = AdjList[cur].begin(); itr != AdjList[cur].end(); itr++) {   
                if (color[*itr] == 0) {
                    color[*itr] = -color[cur]; // use opposite color
                    q.push(*itr);

            }
            else if (color[*itr] == color[cur])
              return false; // same color used in neighbors
          }
        }
    }
    for(int i=0;i<num_vertex;i++){
        if(color[i]==1){
            A.push(i);
        }
        else
            B.push(i);
    }
    return true;

}
```



利用graph裡的BFS(Breadth-First Search)概念來判斷是否是Bipartite

- 創建一個color vector紀錄
還沒被找過用0
被分配到A組用1
被分配到B組用-1

- 最後根據color vector裡的內容分組到queue A和queue B(為了輸出成員)


## 時間複雜度
因為只需使用一次完整的遍歷(BFS)就能就能判斷是否Bipartite

因此每一個vertex只會被查找一次，每個edge也只會被走過一次

n=|V(G)| and
e=|E(G)| (| |is the cardinality of the set, that is, the number of elements in it)

因此時間複雜度為O(n+e)

# Bridge
## Graph class

```cpp=
class Graph{
	private:
	    int num_vertex;
	    std::vector< std::list<int> > AdjList;
	    int *color,             // 0:white, 1:gray
	        *low,
	        *discover;
	public:
	    Graph():num_vertex(0){};
	    Graph(int N):num_vertex(N){
	        // initialize Adj List
	        AdjList.resize(num_vertex);
	    };
	    void AddEdgeList(int from, int to);
	    void DFS(int start);
		void DFSVisit(int u,int parent);
};


```
1. 使用STL的vector和list創建AdjList(方便動態增減)
2. use constructor to initialize Adjacency List
3. color 用來記錄是否被拜訪過，還沒就是0,拜訪過就是1
4. discover用來記錄被拜訪的時間
5. low用來記錄如果有back edge就可以使low[i]的值比discover[i]的值小
## AddEdgeList
```cpp=
void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
    AdjList[to].push_back(from);
}
```
因為是undirected graph，所以等於一次增加兩個方向


## DFS(int Start)

進行初始化，以及確保可能有component會造成沒辦法一次完整的DFS就全部拜訪完成



```cpp=
void Graph::DFS(int Start){
    color = new int[num_vertex];           // 配置記憶體位置
    discover = new int[num_vertex];
    low = new int[num_vertex];

    for (int i = 0; i < num_vertex; i++) { 
        color[i] = 0;
        discover[i] = 0;
        low[i] = 0;
    }

    int i = Start;
    for (int j = 0; j < num_vertex; j++) { // 檢查所有Graph中的vertex都要被搜尋到
        if (color[i] == 0) {               // 若vertex不是白色, 則進行以該vertex作為起點之搜尋
            DFSVisit(i, -1);
        }
        i = j;                             // j會把AdjList完整走過一遍, 確保所有vertex都被搜尋過
    }
}
```

## DFSVisit(int u, int parent)

1. time使用static修飾，確保在做recursive時可以繼續被記錄
2. 一開始都會讓discover[u] = low[u] = time
3. 若做DFS找到的新鄰居發現還沒被拜訪過(color[\*itr] == 0)，則使用recursive繼續往下找
4. 更新low[u]
5. 如果出現low[\*itr] > discover[u] 則代表u的descendent沒有人有back edge到u之上，代表這兩個vertex之間就是bridge


```cpp=
void Graph::DFSVisit(int u, int parent){   // 一旦有vertex被發現而且是白色, 便進入DFSVisit()
	static int time = 1;
    color[u] = 1;                         // 把vertex塗成灰色
    discover[u] = time;                 // 更新vertex的discover時間
	low[u] = time;
	time++;
    for (std::list<int>::iterator itr = AdjList[u].begin();   // for loop參數太長
         itr != AdjList[u].end(); itr++) {                    // 分成兩段
        if (color[*itr] == 0) {                // 若搜尋到白色的vertex
            DFSVisit(*itr, u);              // 立刻以其作為新的搜尋起點, 進入新的DFSVisit()
			low[u]=min(low[u],low[*itr]);
			if(low[*itr] > discover[u])
				std::cout << u << " " << *itr << std::endl;
        }else if(*itr != parent){
			low[u]=min(low[u],low[*itr]);
		}
    }
}
```


## 時間複雜度
因為只需使用一次完整的遍歷(DFS)就能就能判斷bridge

因此每一個vertex只會被查找一次，每個edge也只會被走過一次

n=|V(G)| and
e=|E(G)| (| |is the cardinality of the set, that is, the number of elements in it)

因此時間複雜度為O(n+e)