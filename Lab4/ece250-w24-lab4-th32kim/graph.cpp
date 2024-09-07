#include "graph.h"
#include <string>
#include <fstream>
#include <queue>
// implement classes' member functions here...
Graph::Graph(){}
Graph::Edge::Edge(double d, double s){
    D = d;
    S = s;
    A = 1.0;
    T = D/(S*A);
}

//Insert function
void Graph::insert(int a, int b, double d, double s){
    //Edge from a to b already exist, just updating its values
    if(Adjacency_List[a].find(b) != Adjacency_List[a].end()){
        Adjacency_List[a][b].D=d;
        Adjacency_List[a][b].S=s;
        Adjacency_List[a][b].T=Adjacency_List[a][b].D/(Adjacency_List[a][b].S*(Adjacency_List[a][b].A));
        Adjacency_List[b][a].D=d;
        Adjacency_List[b][a].S=s;
        Adjacency_List[b][a].T=Adjacency_List[a][b].D/(Adjacency_List[a][b].S*(Adjacency_List[a][b].A));
    }else{
        //No edge found, inputting a new edge
        Adjacency_List[a][b] = Edge(d,s);
        //Since it is undirected graph, need to update 'both' directions
        Adjacency_List[b][a] = Edge(d,s);
    }
}

//Load Function 
void Graph::load(std::string filepath){
    std::ifstream file(filepath);
    int input_a;
    int input_b;
    double input_d;
    double input_s;
    while(!file.eof()){
        file>>input_a;
        file>>input_b;
        file>>input_d;
        file>>input_s;
        insert(input_a,input_b,input_d,input_s);
    }
    std::cout<<"success"<<std::endl;
}

//Traffic function
bool Graph::traffic(int a, int b, double A){
    //Identifying if edge exists from a to b
    auto from = Adjacency_List.find(a);
    //vertex a exists
    if(from != Adjacency_List.end()){
        //identifying vertex a to b
        const auto& inner = from->second;
        auto to = inner.find(b);
        if(to != inner.end()){
            //edge from a to b exists (vice versa)
            if(A==0){
                //A is 0, making T value as infinite
                Adjacency_List[a][b].A=0;
                Adjacency_List[a][b].T=DBL_MAX;
                Adjacency_List[b][a].A=0;
                Adjacency_List[b][a].T=DBL_MAX;
            }else{
                //A is non zero, making T value as a result of the formula computation
                Adjacency_List[a][b].A=A;
                Adjacency_List[a][b].T=Adjacency_List[a][b].D/(Adjacency_List[a][b].S*A);
                Adjacency_List[b][a].A=A;
                Adjacency_List[b][a].T=Adjacency_List[b][a].D/(Adjacency_List[b][a].S*A);
            }
            return true;
        }

    }
    //Edge from a to b is not found (vice versa)
    return false;
}

//update function
void Graph::update(std::string filepath){
    std::ifstream file(filepath);
    int input_a;
    int input_b;
    double input_A;
    bool success=false;
    while(!file.eof()){
        file >> input_a;
        file >> input_b;
        file >> input_A;
        //Checking if any A values updated successfully
        if(traffic(input_a, input_b, input_A)){
            success=true;
        }
    }
    if(success){
        std::cout<<"success"<<std::endl;
    }else{
        std::cout<<"failure"<<std::endl;
    }
}

//print function
void Graph::print(int a){
    if(Adjacency_List.find(a) !=Adjacency_List.end()){
        //Non empty vertice, printing its adjacent vertices
        for(const auto& to : Adjacency_List[a]){
            int to_vertex = to.first;
            std::cout<<to_vertex<<" ";
        }
        std::cout<<std::endl;
    }
    else{
        //No vertices found, printing error message
        std::cout<<"failure"<<std::endl;
    }
}

//Delete function
void Graph::Delete(int a){
    if(Adjacency_List.find(a) != Adjacency_List.end()){
        //vertices containing a exist, deleting its own vertex
        Adjacency_List.erase(a);
        //Deleting any vertex connected to a
        for(auto& vertex:Adjacency_List){
            vertex.second.erase(a);
        }
        std::cout<<"success"<<std::endl;
    }else{
        std::cout<<"failure"<<std::endl;
    }
}

//path function
void Graph::path(int a, int b){
    //map to store the weight value between vertices (edges weight)
    std::unordered_map<int, double>t_val;
    //map to store parent nodes of the current node
    std::unordered_map<int,int>parent;
    //priority que for Dijikstra's algorithm (storing weight between each vertices)
    std::priority_queue<std::pair<double, int>> pq;

    //Setting initial Dijikstra's adjacency matrix to infinite values
    for(const auto&pair : Adjacency_List){
        int x = pair.first;
        t_val[x]=DBL_MAX;
        parent[x]=-1;//initializing the parent node values to -1 (representing n/a)
    }

    t_val[a]=0;//setting weight from node to current node (a to a) as 0
    pq.push({0,a});

    while(!pq.empty()){
        int x = pq.top().second;
        pq.pop();
        for(const auto& edge_pair:Adjacency_List[x]){
            //looping around each vertices, extracting the weight values to its Adjacent nodes
            int y=edge_pair.first;
            double weight = edge_pair.second.T;
            //if current 'weight' value in the Dijikstra Adjacent matrix is greater than 
            //newly calculated 'weight' value to its adjacent node, replace the value
            if(t_val[y]>t_val[x]+weight){
                t_val[y]=t_val[x]+weight;
                parent[y]=x;//storing the parent node as newly smaller weight edge is discovered
                pq.push({t_val[y],y});
            }
        }
    }

    if(t_val[b]==DBL_MAX){
        //no path found
        std::cout<<"failure"<<std::endl;
    }else{
        //path found, displaying the lowest path 
        std::vector<int> path;
        int current_vertex = b;
        //storing list of vertices stored within parent list (indicating vertices)
        while(current_vertex != -1){
            path.push_back(current_vertex);
            current_vertex = parent[current_vertex];
        }
        //printing vertices
        for(auto curr = path.rbegin(); curr != path.rend(); ++curr){
            std::cout<<*curr<<" ";
        }
        std::cout<<std::endl;
    }


}

//lowest function
void Graph::lowest(int a, int b){
    //Same logic as the one presented in the above path function
    std::unordered_map<int,double>t_val;
    std::priority_queue<std::pair<double, int>> pq;
    for(const auto& edge_pair:Adjacency_List){
        int x = edge_pair.first;
        t_val[x]=DBL_MAX;
    }

    t_val[a]=0;
    pq.push({0,a});
    while(!pq.empty()){
        int x = pq.top().second;
        pq.pop();
        for(const auto& edge_pair:Adjacency_List[x]){
            //looping around each vertices, extracting the weight values to its Adjacent nodes
            int y=edge_pair.first;
            double weight = edge_pair.second.T;
            //if current 'weight' value in the Dijikstra Adjacent matrix is greater than 
            //newly calculated 'weight' value to its adjacent node, replace the value
            if(t_val[y]>t_val[x]+weight){
                t_val[y]=t_val[x]+weight;
                pq.push({t_val[y],y});
            }
        }
    }

    if(t_val[b]==DBL_MAX){
        //No path found
        std::cout<<"failure"<<std::endl;
    }else{
        //path found, printing lowest weight of the path
        std::cout<<t_val[b]<<std::endl;
    }

}

Graph::~Graph(){}