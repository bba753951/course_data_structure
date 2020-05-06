// C++ code
#include <iostream>
#include <vector>
#include <iomanip>      // for setw()
#include <stack>

const int MaxDistance = 1000;
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

Graph_SP_AllPairs::Graph_SP_AllPairs(int n):num_vertex(n){
    // Constructor, initialize AdjMatrix with 0 or MaxDistance
    AdjMatrix.resize(num_vertex);
    for (int i = 0; i < num_vertex; i++) {
        AdjMatrix[i].resize(num_vertex, MaxDistance);
        for (int j = 0; j < num_vertex; j++) {
            if (i == j){
                AdjMatrix[i][j] = 0;
            }
        }
    }
}
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
void Graph_SP_AllPairs::FloydWarshall(){

    InitializeData();

    //std::cout << "initial Distance[]:\n";
    //PrintData(Distance);
    //std::cout << "\ninitial Predecessor[]:\n";
    //PrintData(Predecessor);

    for (int k = 0; k < num_vertex; k++) {
        //std::cout << "\nincluding vertex(" << k << "):\n";
        for (int i = 0; i < num_vertex; i++) {
            for (int j = 0; j < num_vertex; j++) {
                if ((Distance[i][j] > Distance[i][k]+Distance[k][j]) 
                     && (Distance[i][k] != MaxDistance)) {
                    Distance[i][j] = Distance[i][k]+Distance[k][j];
                    Predecessor[i][j] = Predecessor[k][j];
                }
            }
        }
        // print data after including new vertex and updating the shortest paths
        //std::cout << "Distance[]:\n";
        //PrintData(Distance);
        //std::cout << "\nPredecessor[]:\n";
        //PrintData(Predecessor);
    }
}
void Graph_SP_AllPairs::PrintData(std::vector< std::vector<int> > array){

    for (int i = 0; i < num_vertex; i++){
        for (int j = 0; j < num_vertex; j++) {
            std::cout << std::setw(5) << array[i][j];
        }
        std::cout << std::endl;
    }
}
void Graph_SP_AllPairs::AddEdge(int from, int to, int weight){
    AdjMatrix[from][to] = weight;
}

void Graph_SP_AllPairs::PrintPath(){
    int cur;

    for (int i = 0; i < num_vertex; i++){
        for (int j = 0; j < num_vertex; j++) {
            cur = j;
            while(Predecessor[i][cur] != -1){
                ans.push(cur);
                cur = Predecessor[i][cur];
            }

            if(ans.empty()){
                //std::cout<< "Impossible:" << j <<std::endl;
                continue;
            }

            std::cout << cur;
            while(!ans.empty()){
                std::cout << "," << ans.top();
                ans.pop();
            }
            std::cout << " " << Distance[i][j] << std::endl;
        }
    }
}

int main(){

    //Graph_SP_AllPairs g10(3);
    //g10.AddEdge(0, 1, 4);
    //g10.AddEdge(0, 2, 11);
    //g10.AddEdge(1, 0, 6);
    //g10.AddEdge(1, 2, 2);
    //g10.AddEdge(2, 0, 3);

    //g10.FloydWarshall();
    //std::cout << "Output:" << std::endl;  
    //g10.PrintPath();

    while(!std::cin.eof()) {
        std::cout<< "Input:" <<std::endl;

	    int vertexes=0,edges=0,from=0,to=0,weight=0;
	    std::cin >> vertexes;
	    std::cin >> edges;
        Graph_SP_AllPairs g1(vertexes);
	    for(int i=0;i<edges;i++){
	        std::cin >> from;
	        std::cin >> to;
	        std::cin >> weight;
	        g1.AddEdge(from, to , weight);
	    };

        std::cout << std::endl;
        g1.FloydWarshall();
        std::cout << "Output:" << std::endl;  
        g1.PrintPath();
        std::cout << std::endl;

    }

    return 0;
}
