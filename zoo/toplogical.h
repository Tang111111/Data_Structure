#include <iostream>
#include <vector>
using namespace std;
struct top_node;
struct pair_node{
    string start;
    string end;
    pair_node(string s,string e)
    {
        start=s;
        end=e;
    }
};
/*struct top_edge{
    string en;

};*/
struct top_node{
    string name;
    int in_number; //the number of incoming nodes
    //int out_number; //the number of outcoming nodes
    vector<top_node*> nodes; //the node that top_node points to
    top_node(string n)
    {
        name=n;
        in_number=0;
        //out_number=0;
    }
};
class toplogical{
public:
    void top_logical(vector<pair_node> p);
private:
    vector<top_node*> top_node_list;
    void addNode(string name);
    int findnode(string name);
};