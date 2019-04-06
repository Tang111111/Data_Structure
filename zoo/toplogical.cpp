#include "toplogical.h"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int toplogical::findnode(string n)
{
    for(int i=0;i<top_node_list.size();i++)
        if(top_node_list[i]->name==n)
            return i;
        return -1;
}
void toplogical::addNode(string name)
{
    top_node *tNode=new top_node(name);
    top_node_list.push_back(tNode);

}
void toplogical::top_logical(vector<pair_node> p)
{
    vector<top_node*> results;
    for(int i=0;i<p.size();i++)
        cout<<p[i].start<<"->"<<p[i].end<<endl;
    for(int i=0;i<p.size();i++)
    {
        if(findnode(p[i].start)==-1&&findnode(p[i].end)==-1)
        {
            addNode(p[i].start);
            addNode(p[i].end);
        }
        else if(findnode(p[i].start)!=-1&&findnode(p[i].end)==-1)
            addNode(p[i].end);
        else if(findnode(p[i].start)==-1&&findnode(p[i].end)!=-1)
            addNode(p[i].start);
        else{

        }
        top_node_list[findnode(p[i].start)]->nodes.push_back(top_node_list[findnode(p[i].end)]);
        top_node_list[findnode(p[i].end)]->in_number++;
    }
    int n=top_node_list.size();
    queue<top_node*> q; //node that have no incoming
    for(int i=0;i<top_node_list.size();i++)
    {
        if(top_node_list[i]->in_number==0)
            q.push(top_node_list[i]);
    }
    if(q.size()==0)
    {
        //cout<<"111"<<endl;
        cout<<"There is a loop route in it! "<<endl;
        return;
    }
    while(!q.empty())
    {
        top_node *p=q.front();
        q.pop();
        results.push_back(p);
        for(int j=0;j<p->nodes.size();j++)
        {
            p->nodes[j]->in_number--;
            if(p->nodes[j]->in_number==0)
                q.push(p->nodes[j]);
        }
    }
    if(results.size()!=n)
    {
        //cout<<"222"<<endl;
        cout<<"There is a loop route in it! "<<endl;
        return;
    }
    //cout<<"111"<<n<<"  "<<results.size()<<endl;
    for(int i=0;i<results.size()-1;i++)
        cout<<results[i]->name<<"->";
    cout<<results[results.size()-1]->name<<endl;
}