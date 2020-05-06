#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <iomanip>      // for std::setw()

#define min(a,b) ((a)<(b)?(a):(b))
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

void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
    AdjList[to].push_back(from);
}

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
int main(){
    // 定義一個具有八個vertex的Graph
    // Graph g2(10);
    // g2.AddEdgeList(0, 1); 
    // g2.AddEdgeList(1, 2);
    // g2.AddEdgeList(1, 3);
    // g2.AddEdgeList(2, 4);
    // g2.AddEdgeList(3, 4);
    // g2.AddEdgeList(3, 5);
    // g2.AddEdgeList(5, 6);
    // g2.AddEdgeList(5, 7);
    // g2.AddEdgeList(6, 7);
    // g2.AddEdgeList(7, 8);
    // g2.AddEdgeList(7, 9);


    // g2.DFS(0);    // 以vertex(0)DFS()的起點


	 while(!std::cin.eof()) {
	 	std::cout << "Input:" << std::endl;  
	    int vertexes=0,edges=0,from=0,to=0;
	    std::cin >> vertexes;
	    std::cin >> edges;
	    Graph g1(vertexes);
	    for(int i=0;i<edges;i++){
	        std::cin >> from;
	        std::cin >> to;
	        g1.AddEdgeList(from, to);
	    };
	    std::cout << "Output:" << std::endl;  
	    g1.DFS(0);
	}

    return 0;
}


