#include <iostream>
#include <vector>
using namespace std;
struct node;
struct edge{
    node *end;
    int dis;
    edge(node *e,int d)
    {
        this->end=e;
        this->dis=d;
    }
};
struct node{
    string name;
    int popularity;
    int people_number;
    int recreation_number;
    int total_dis;
    bool visited;
    vector<edge*> edgelist;
    node *parent;
    node()
    {
        this->parent=nullptr;
        this->visited=false;
        total_dis=0;
    }
    node(string name,int popularity,int people_number,int recreation_number)
    {
        //this->filename=filename;
        this->name=name;
        this->parent= nullptr;
        this->people_number=people_number;
        this->popularity=popularity;
        this->recreation_number=recreation_number;
        this->visited=false;
        total_dis=0;
    }
    node(string name)
    {
        this->name=name;
        this->visited=false;
        this->parent= nullptr;
        total_dis=0;
    }
};
class nodelist{
public:
    int findnode(string name);
    void show_info_by_name(string name);
    void sort_by_attribute(int i);
    void floyd();
    void addNode(string name,int data1,int data2,int data3);
    void addEdge(string begin,string end,int dis);
    void hamilton(string be,string en);
    void prim(string be);
    int Dijkstra(string start,string en,string &str,bool flag);

private:
    vector<node*> nodeList;
    void hamilton_DFS(string be,string en,int i,int size,bool *flag);
    void print_route(node *node1);
    void prim_DFS(string &be,int &time,nodelist *list,string &str);
    int findedge(string be,string en);
};
