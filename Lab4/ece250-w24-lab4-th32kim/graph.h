// define your classes here...
#include <unordered_map>
#include <float.h>
#include <iostream>
#include <string>

class Graph{
    class Edge{
        public:
            double D;
            double S;
            double A;
            double T;
        Edge(double d=0, double s=0);
    };

    private:
        std::unordered_map<int,std::unordered_map<int,Edge>> Adjacency_List;

    public:
    Graph();
    //Insert function
    void insert(int a, int b, double d, double s);
    //Load function
    void load(std::string filepath);
    //traffic function (updating A value)
    bool traffic(int a, int b, double A);
    //update function
    void update(std::string filepath);

    //Print function (printing all verteies adjacent to given vertices)
    void print(int a);

    //Delete function
    void Delete(int a);

    //Path function
    void path(int a, int b);

    //lowest function
    void lowest(int a, int b);
    ~Graph();
};