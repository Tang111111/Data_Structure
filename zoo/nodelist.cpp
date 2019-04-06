#include "nodelist.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#define MAX 100000
using namespace std;
bool compare1(const node *n1,const node *n2);
bool compare2(const node *n1,const node *n2);
bool compare3(const node *n1,const node *n2);
bool compare4(const node *n1,const node *n2);
bool compare1(const node *n1, const node *n2)
{
    return n1->name>n2->name;
}
bool compare2(const node *n1, const node *n2)
{
    return n1->people_number>n2->people_number;
}
bool compare3(const node *n1, const node *n2)
{
    return n1->popularity>n2->popularity;
}
bool compare4(const node *n1,const  node *n2)
{
    return n1->recreation_number>n2->recreation_number;
}
void nodelist::addNode(string name, int data1, int data2, int data3)
{
    node *node1=new node(name,data1,data2,data3);
    nodeList.push_back(node1);
}
void nodelist::addEdge(string begin, string end, int dis)
{
    int n=findnode(begin);
    int m=findnode(end);
    if(n==-1||m==-1)
    {
        cout<<"Fail! No such node"<<endl;
        return;
    }
    edge *edge1=new edge(nodeList[m],dis);
    nodeList[n]->edgelist.push_back(edge1);
}
int nodelist::findnode(string name)
{
    for(int i=0;i<nodeList.size();i++)
    {
        if(nodeList[i]->name==name)
            return i;
    }
    return -1;
}
void nodelist::show_info_by_name(string name)
{
    int n=findnode(name);
    if(n==-1)
    {
        cout<<"No such animal!"<<endl;
        return;
    }
    else{
        cout<<"Name: "<<nodeList[n]->name<<" Popularity: "<<nodeList[n]->popularity<<" current visitor number: "<<nodeList[n]->people_number
        <<" recreation spots: "<<nodeList[n]->recreation_number<<endl;
    }
}

void nodelist::sort_by_attribute(int i)
{
    switch (i)
    {
        case 1:
            sort(nodeList.begin(),nodeList.end(),compare1);
            cout<<"Sort by name: "<<endl;
            for(int i=0;i<nodeList.size();i++)
                cout<<"name: "<<nodeList[i]->name<<" popularity: "<<nodeList[i]->popularity
                <<" current visitor number: "<<nodeList[i]->people_number<<" Recreation number: "<<nodeList[i]->recreation_number<<endl;
            break;

        case 2:
            sort(nodeList.begin(),nodeList.end(),compare2);
            cout<<"Sort by current visitor number: "<<endl;
            for(int i=0;i<nodeList.size();i++)
                cout<<"name: "<<nodeList[i]->name<<" popularity: "<<nodeList[i]->popularity
                <<" current visitor number: "<<nodeList[i]->people_number<<" Recreation number: "<<nodeList[i]->recreation_number<<endl;
            break;
        case 3:
            sort(nodeList.begin(),nodeList.end(),compare3);
            cout<<"Sort by popularity: "<<endl;
            for(int i=0;i<nodeList.size();i++)
                cout<<"name: "<<nodeList[i]->name<<" popularity: "<<nodeList[i]->popularity
                    <<" current visitor number: "<<nodeList[i]->people_number<<" Recreation number: "<<nodeList[i]->recreation_number<<endl;
            break;
        case 4:
            sort(nodeList.begin(),nodeList.end(),compare4);
            cout<<"Sort by recreation number: "<<endl;
            for(int i=0;i<nodeList.size();i++)
                cout<<"name: "<<nodeList[i]->name<<" popularity: "<<nodeList[i]->popularity
                    <<" current visitor number: "<<nodeList[i]->people_number<<" Recreation number: "<<nodeList[i]->recreation_number<<endl;
            break;
        default:
            cout<<"Input Wrong!"<<endl;
            break;
    }
}
void nodelist::floyd()
{
    int n=(int)nodeList.size();
    int map[n][n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            map[i][j]=MAX;
    }
    for(int i=0;i<n;i++)
        map[i][i]=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<nodeList[i]->edgelist.size();j++)
        {
            map[i][findnode(nodeList[i]->edgelist[j]->end->name)]=nodeList[i]->edgelist[j]->dis;
        }
    }
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(map[i][j]>map[i][k]+map[k][j])
                    map[i][j]=map[i][k]+map[k][j];
    cout<<left<<setw(9)<<"";
    for(int i=0;i<n;i++)
        cout<<left<<setw(9)<<nodeList[i]->name;
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<left<<setw(9)<<nodeList[i]->name;
        for(int j=0;j<n;j++)
            cout<<left<<setw(9)<<map[i][j];
        cout<<endl;
    }
}
void nodelist::hamilton(string be, string en)
{
    for(int i=0;i<nodeList.size();i++)
    {
        nodeList[i]->parent=nullptr;
        nodeList[i]->visited=false;
        nodeList[i]->total_dis=0;
    }
    if(findnode(be)==-1||findnode(en)==-1)
    {
        cout<<"Input Wrong, no such animal!"<<endl;
        return;
    }
    bool flag=false;
    if(be==en)
        hamilton_DFS(be,en,1,nodeList.size()+1,&flag);
    else
        hamilton_DFS(be,en,1,nodeList.size(),&flag);
    if(flag==false)
    {
        cout<<"No traverse route between "<<en<<" and "<<be
        <<" But we have recommendation route for you starting from "<<en<<endl;
        prim(en);
    }
}
void nodelist::hamilton_DFS(string be, string en, int time, int size,bool *flag)
{
    int n=findnode(be);
    if(time==1)  //start node
    {
        nodeList[n]->visited=true;
        nodeList[n]->total_dis=0;
    }
    for(int i=0;i<nodeList[n]->edgelist.size();i++)
    {
        if(en.compare(nodeList[n]->edgelist[i]->end->name)==0&&time!=size-1)
            continue;
        else if(en.compare(nodeList[n]->edgelist[i]->end->name)==0&&time==size-1)
        {
            *flag=true;
            nodeList[n]->edgelist[i]->end->parent=nodeList[n];
            nodeList[n]->edgelist[i]->end->total_dis=nodeList[n]->edgelist[i]->dis+nodeList[n]->total_dis;
            node *end_node=nodeList[n]->edgelist[i]->end;
            cout<<"Distance: "<<end_node->total_dis<<endl;
            cout<<end_node->name;
            while(end_node->parent!=nullptr)
            {
                end_node=end_node->parent;
                cout<<"->"<<end_node->name;

            }
            cout<<endl;
            return;
        }
        else if(en.compare(nodeList[n]->edgelist[i]->end->name)!=0&&time==size-1)
            continue;
        else{
            if(!nodeList[n]->edgelist[i]->end->visited)
            {
                nodeList[n]->edgelist[i]->end->total_dis=nodeList[n]->total_dis+nodeList[n]->edgelist[i]->dis;
                nodeList[n]->edgelist[i]->end->visited=true;
                nodeList[n]->edgelist[i]->end->parent=nodeList[n];
                be=nodeList[n]->edgelist[i]->end->name;
                hamilton_DFS(be,en,time+1,nodeList.size(),flag);
                nodeList[n]->edgelist[i]->end->visited= false;
            }
            else{
                continue;
            }
        }
    }
    return;
}
void nodelist::print_route(node *node1)
{
    node *n=node1;
    cout<<"Distance: "<<n->total_dis<<endl;
    cout<<n->name;
    while(n!=nullptr)
    {
        cout<<n->parent->name;
        n=n->parent;
    }
    cout<<endl;
}
void nodelist::prim(string be)
{
    int n=findnode(be);
    node *node1,*node2,*node3;
    edge *edge1;
    if(n==-1)
    {
        cout<<"No such animal!"<<endl;
        return;
    }
    nodelist *list2=new nodelist(); //list that contain the prim node
    node *start=new node(nodeList[n]->name);
    list2->nodeList.push_back(start);
    while(list2->nodeList.size()!=nodeList.size())
    {
        int dis=MAX;
        for(int i=0;i<list2->nodeList.size();i++)
        {
            node1=list2->nodeList[i];
            int m=findnode(node1->name);
            for(int j=0;j<nodeList[m]->edgelist.size();j++)  //traverse the neighbour node of node1
            {
                if(list2->findnode(nodeList[m]->edgelist[j]->end->name)!=-1)
                    continue;
                if(dis>nodeList[m]->edgelist[j]->dis)
                {
                    edge1=nodeList[m]->edgelist[j];
                    dis=nodeList[m]->edgelist[j]->dis;
                    node2=nodeList[m]->edgelist[j]->end;
                    node2->parent=node1;
                }
            }
        }
        node3=new node(node2->name);
        list2->nodeList.push_back(node3);
        node2->parent->edgelist.push_back(edge1);
    }
    int time=1;
    int n1=list2->findnode(be);
    string str=be;  //record the route
    prim_DFS(be,time,list2,str);
    delete list2;
    list2= nullptr;
}
int nodelist::findedge(string be, string en)
{
    int n=findnode(be);
    for(int i=0;i<nodeList[n]->edgelist.size();i++)
    {
        if(nodeList[n]->edgelist[i]->end->name==en)
            return i;
    }
    return -1;
}
void nodelist::prim_DFS(string &be, int &time,nodelist* list,string &str)
{
    string begin=be;
    string en;
    for(int i=0;i<list->nodeList[list->findnode(begin)]->edgelist.size();i++)
    {
        en=list->nodeList[list->findnode(begin)]->edgelist[i]->end->name;
        if(list->findedge(be,en)!=-1)
        {
            list->nodeList[list->findnode(en)]->total_dis=list->nodeList[list->findnode(be)]->total_dis+list->nodeList[list->findnode(be)]->edgelist[list->findedge(be,en)]->dis;
            str=str+"->"+en;
            if(time==nodeList.size()-1)
            {
                cout<<"Distance:  "<<list->nodeList[list->findnode(en)]->total_dis<<endl;
                cout<<str<<endl;
                return;
            }
            else{
                be=en;
                time++;
                prim_DFS(be,time,list,str);
            }
        }
        else{
            int dis=Dijkstra(en,be,str,false);
            list->nodeList[list->findnode(en)]->total_dis=dis+list->nodeList[list->findnode(be)]->total_dis;
            if(time==nodeList.size()-1)
            {
                cout<<"Distance:  "<<list->nodeList[list->findnode(en)]->total_dis<<endl;
                cout<<str<<endl;
                return;
            }
            else{
                be=en;
                time++;
                prim_DFS(be,time,list,str);
            }
        }
    }
}
int nodelist::Dijkstra(string start, string en,string &str,bool flag)
{
    for(int i=0;i<nodeList.size();i++)
    {
        nodeList[i]->visited=false;
        nodeList[i]->total_dis=0;
        nodeList[i]->parent= nullptr;
    }
    int start_number=findnode(start);
    int end_number=findnode(en);
    if(start_number==-1||end_number==-1)
    {
        cout<<"Input Wrong!"<<endl;
        return -1;
    }
    nodeList[start_number]->visited=true;
    vector<node*> visited;
    visited.push_back(nodeList[start_number]);
    while(!nodeList[end_number]->visited)
    {
        int min_dis=INT_MAX;
        node *visited_node, *parent;
        for(int i=0;i<visited.size();i++)
        {
            for(int j=0;j<visited[i]->edgelist.size();j++)
            {
                if(!visited[i]->edgelist[j]->end->visited)
                {
                    int dis=visited[i]->edgelist[j]->dis+visited[i]->total_dis;
                    if(dis<min_dis)
                    {
                        visited_node=visited[i]->edgelist[j]->end;
                        min_dis=dis;
                        parent=visited[i];
                    }
                }
            }
        }
        visited_node->total_dis=min_dis;
        visited_node->parent=parent;
        visited_node->visited=true;
        visited.push_back(visited_node);
    }
    node *n=nodeList[end_number]->parent;
    while(n!= nullptr)
    {
        str=str+"->"+n->name;
        n=n->parent;
    }
    if(flag==true)
    {
        cout<<"Distance: "<<nodeList[end_number]->total_dis<<endl;
        cout<<str<<endl;
    }
    return nodeList[end_number]->total_dis;
}
