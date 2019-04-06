#include <iostream>
#include <fstream>
#include <sstream>
#include "nodelist.h"
#include "toplogical.h"
using  namespace std;
void menu()
{
    cout<<"1.Show the shortest distance between each two spots"<<endl;
    cout<<"2.Query spots"<<endl;
    cout<<"3.Sort spots by specific attribute"<<endl;
    cout<<"4.Find the shortest distance between two spots"<<endl;
    cout<<"5.Optimal route(Specify start and end spots)"<<endl;
    cout<<"6.Optimal route(Specify only start spot)"<<endl;
    cout<<"7.Make a visit plan with specific requests"<<endl;
    cout<<"8.Exit"<<endl;
}
int main(int argc,char *argv[])
{
    nodelist *list=new nodelist();
    ifstream nodefile(argv[1]);
    string line;
    //vector<node*> nodeList2;
    while(getline(nodefile,line))
    {
        stringstream ss(line);
        string name;
        string d1;
        string d2;
        string d3;
        getline(ss,name,' ');
        getline(ss,d1,' ');
        getline(ss,d2,' ');
        getline(ss,d3);
        int data1=stoi(d1);
        int data2=stoi(d2);
        int data3=stoi(d3);
        list->addNode(name,data1,data2,data3);
    }
    ifstream edgefile(argv[2]);
    while(getline(edgefile,line))
    {
        stringstream ss(line);
        string be;
        string en;
        string d;
        getline(ss,be,' ');
        getline(ss,en,' ');
        getline(ss,d);
        int dis=stoi(d);
        list->addEdge(be,en,dis);
    }
    menu();
    string input;
    getline(cin,input);
    while(input!="8")
    {
        int n=stoi(input);
        switch (n)
        {
            case 1:
                list->floyd();
                break;
            case 2:
                cout<<"Please input the spot name"<<endl;
                getline(cin,input);
                list->show_info_by_name(input);
                break;
            case 3:
            {
                cout<<"1 for name; 2 for current visitor number; 3 for popularity; 4 for number of recreation numbers "<<endl;
                cout<<"Please input the numebr"<<endl;
                getline(cin,input);
                int number=stoi(input);
                list->sort_by_attribute(number);
                break;
            }
            case 4:
            {
                string begin,end;
                cout<<"Please input the begin spot"<<endl;
                getline(cin,begin);
                cout<<"Please inout the end spot"<<endl;
                getline(cin,end);
                list->Dijkstra(end,begin,begin,true);
                break;
            }
            case 5:
            {
                string begin1,end1;
                cout<<"Please input the start spot"<<endl;
                getline(cin,begin1);
                cout<<"Please inout the end spot"<<endl;
                getline(cin,end1);
                list->hamilton(end1,begin1);
                break;
            }
            case 6:
            {
                string begin2;
                cout<<"Please inout the start spot"<<endl;
                getline(cin,begin2);
                list->prim(begin2);
                break;
            }
            case 7:
            {
                toplogical *t=new toplogical();
                vector<pair_node> p;
                cout<<"How many specific request do you have?"<<endl;
                getline(cin,input);
                int number2=stoi(input);
                while(number2!=0)
                {
                    string begin3,end3;
                    cout<<"Please inout the start spot"<<endl;
                    getline(cin,begin3);
                    cout<<"Please inout the end spot"<<endl;
                    getline(cin,end3);
                    if(list->findnode(begin3)==-1||list->findnode(end3)==-1)
                    {
                        cout<<"Input Wrong!"<<endl;
                        continue;
                    }
                    pair_node node(begin3,end3);
                    p.push_back(node);
                    number2--;
                }
                t->top_logical(p);
                delete t;
                break;
            }
            default:{
                cout<<"Input wrong! Please inout again!"<<endl;
                break;
            }
        }
        menu();
        getline(cin,input);
    }
    return 0;
}