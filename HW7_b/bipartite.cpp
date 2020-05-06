// C++ code
#include <iostream>
#include <vector>
#include <list>
#include <queue>

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

void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
    AdjList[to].push_back(from);
}

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

void Graph::printQ(void){

    while(A.size() != 0){
        std::cout << A.front() << " ";
        A.pop();
    };  
    std::cout << std::endl;  
    while(B.size() != 0){
        std::cout << B.front() << " ";
        B.pop();
    };    
    std::cout << std::endl;
}

int main(){

    while(!std::cin.eof()) {
        std::cout << "Input:" << std::endl;  

        int vertexes=0,edges=0,from=0,to=0;
        // Graph g1(8);    
        // g1.AddEdgeList(0, 1);
        // g1.AddEdgeList(0, 2);
        // g1.AddEdgeList(1, 3);
        // g1.AddEdgeList(2, 3);
        // g1.AddEdgeList(4, 5);
        // g1.AddEdgeList(5, 6);
        // g1.AddEdgeList(6, 7);
        std::cin >> vertexes;
        std::cin >> edges;
        Graph g1(vertexes);
        for(int i=0;i<edges;i++){
            std::cin >> from;
            std::cin >> to;
            g1.AddEdgeList(from, to);
    }  

    std::cout << "Output:" << std::endl;
    if(g1.isBipartite()){
        std::cout << "true" << std::endl;
        g1.printQ();
    }
    else
        std::cout << "false" << std::endl;
}
    return 0;
}
