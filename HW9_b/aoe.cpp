// C++ code
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <utility>          // for std::pair<>
#include <iomanip>          // for std::setw()

const int Min_Distance = -1;
const int Max_Distance = 100;
class Graph_SP{             // SP serves as Shortest Path
private:
    int num_vertex;
	int ct;
    std::vector<std::list<std::pair<int,int> > > AdjList;
    std::vector<std::list<std::pair<int,int> > > revAdjList;
    std::vector<std::pair<int,int> > activity;
    std::vector<int> wt;
    std::queue<int> ans;
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
	//std::cout << "\nprint discover time:\n";
	//PrintIntArray(discover);
	//std::cout << "\nprint finish time:\n";
	//PrintIntArray(finish);
}
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
	//std::cout << "\nprint predecessor:\n";
	PrintDataArray(predecessor);
	//std::cout << "\nprint distance:\n";
	//PrintDataArray(distance);

	//std::cout << "\nprint ledistance:\n";
	//PrintDataArray(ledistance);
}
void Graph_SP::PrintDataArray(std::vector<int> array){
	//for (int i = 0; i < num_vertex; i++)
		//std::cout << std::setw(4) << i;
	//std::cout << std::endl;
	//for (int i = 0; i < num_vertex; i++)
		//std::cout << std::setw(4) << array[i];
	std::cout << std::endl;
}
void Graph_SP::PrintIntArray(int *array){
	for (int i = 0; i < num_vertex; i++)
		std::cout << std::setw(4) << i;
	std::cout << std::endl;
	for (int i = 0; i < num_vertex; i++)
		std::cout << std::setw(4) << array[i];
	std::cout << std::endl;
}

void Graph_SP::PrintResult(){
	int l=0,e=0;

	std::cout << std::left << std::setw(8) << "event";
	std::cout << std::left << std::setw(8) << "ee";
	std::cout << std::left << std::setw(8) << "le";
    std::cout << std::endl;


    for (int i = 0; i < num_vertex; i++){
		if(distance[i]== -1)
			continue;
		std::cout << std::left << std::setw(8) << i;
		std::cout << std::left << std::setw(8) << distance[i];
		std::cout << std::left << std::setw(8) << ledistance[i];
		std::cout << std::endl;
	}

    std::cout << std::endl;
    std::cout << std::endl;

	std::cout << std::left << std::setw(8) << "act.";
	std::cout << std::left << std::setw(8) << "e";
	std::cout << std::left << std::setw(8) << "l";
	std::cout << std::left << std::setw(8) << "slack";
	std::cout << std::left << std::setw(8) << "critical";
    std::cout << std::endl;

    for (int i = 0; i < num_vertex; i++){
		std::cout << std::left << std::setw(8) << i+1;
		
		e = distance[activity[i].first];
		std::cout << std::left << std::setw(8) << e;
		l = ledistance[activity[i].second]-wt[i];
		std::cout << std::left << std::setw(8) << l;
		std::cout << std::left << std::setw(8) << l-e;
		if(l-e)
			std::cout << std::left << std::setw(8) << "No";
		else{
			std::cout << std::left << std::setw(8) << "Yes";
            ans.push(i+1);
        }
		std::cout << std::endl;
	}

    std::cout << std::endl;
    std::cout << std::endl;
    while(!ans.empty()){
        std::cout << ans.front() << " ";
        ans.pop();
    }

    std::cout << std::endl;
	
}
void Graph_SP::InitializeSingleSource(int Start){

    distance.resize(num_vertex);
    ledistance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; i++) {
        distance[i] = Min_Distance;
        ledistance[i] = Max_Distance;
        predecessor[i] = -1;
    }
    distance[Start] = 0;
}
void Graph_SP::Relax(int from, int to, int weight){

    if (distance[to] < distance[from] + weight) {
        distance[to] = distance[from] + weight;
        predecessor[to] = from;
    }
}

void Graph_SP::leRelax(int from, int to, int weight){

    if (ledistance[to] > ledistance[from] - weight) {
        ledistance[to] = ledistance[from] - weight;
    }
}
void Graph_SP::AddEdge(int from, int to, int weight){
    AdjList[from].push_back(std::make_pair(to,weight));
    revAdjList[to].push_back(std::make_pair(from,weight));
	activity[ct]=std::make_pair(from,to);
	wt[ct]=weight;
	ct++;
}

int main(){

    //Graph_SP g8(5);
    //g8.AddEdge(0, 1, 5);
	//g8.AddEdge(0, 2, 6);
    //g8.AddEdge(1, 3, 3);
	//g8.AddEdge(2, 3, 6);
    //g8.AddEdge(3, 4, 2);

    //g8.DAG_SP(0);        // 以vertex(0)作為起點
	//g8.PrintResult();


	 while(!std::cin.eof()) {
	 	std::cout << "Input:" << std::endl;  
	    int edges=0,from=0,to=0,w=0,a=0;
	    std::cin >> edges;
	    Graph_SP g1(edges);
	    for(int i=0;i<edges;i++){
	        std::cin >> a;
	        std::cin >> from;
	        std::cin >> to;
	        std::cin >> w;
	        g1.AddEdge(from, to,w);
	    };
	    std::cout << "Output:" << std::endl;  

		g1.DAG_SP(0);        // 以vertex(0)作為起點
		g1.PrintResult();
	}

    return 0;
}
