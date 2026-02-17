#include"graph.h"
#include<iostream>
#include<string>
#include<stack>
#include<numeric>
#include<algorithm>

using namespace std;

int main()
{
    cout<<"----------------------NETWORK A----------------------\n";
    cout<<boolalpha;
    Graph<string, int> G1;
    cout<<"Size: "<<G1.size()<<'\n'<<"Is Empty? "<<G1.empty()<<"\n\n";

    cout<<"\nADD EDGE\n";
    G1.add_edge("A", "B", 5);
    G1.add_edge("B", "C", 10);
    G1.add_edge("C", "D", 3);
    G1.add_edge("D", "A", 5);
    G1.add_edge("A", "B", 100);
    G1.add_edge("B", "C", 150);
    G1.add_edge("A", "C", 5);
    
    G1.disp();

    cout<<"\nSize: "<<G1.size()<<'\n'<<"Is Empty? "<<G1.empty()<<"\n\n"; 

    cout<<"\nMODIFY\n";
    G1.modify_edge("A", "B", 6);
    G1.modify_edge("B", "C", 150);

    G1.disp();

    cout<<"\nDELETE\n";
    G1.delete_edge("B", "C");

    G1.disp();
    cout<<endl;

    Graph<string, int>::breadth_first_search_iterator bfs1(G1, G1.find("A"));
    cout<<"BFS:\t";
    while(!bfs1.bfsend())
    {
        cout<<(*bfs1).first<<"\t";
        ++bfs1;
    }
    cout<<endl;

    Graph<string, int>::depth_first_search_iterator dfs1(G1, G1.find("C"));
    cout<<"DFS:\t";
    while(!dfs1.dfsend())
    {
        cout<<(*dfs1).first<<"\t";
        ++dfs1;
    }
    cout<<endl;

    cout<<"\n\nVertices   Shortest Path Cost    ShortestPath\n";
    map<string,pair<string,int>> m1 = G1.dijkstra("A");
    string str;
    stack<string> st1;
    for(auto x: m1)
    {
        cout<<x.first<<"\t\t"<<x.second.second<<"\t\t";
        str = x.first;
        while(str!="A")
        {
            st1.push(str);
            str = m1[str].first;
        }
        st1.push("A");
        while(!st1.empty())
        {
            cout<<"->"<<st1.top();
            st1.pop();
        }
        cout<<endl;
    }

    cout<<"\n\n\n----------------------NETWORK B----------------------";

    Graph<int, int> G2;
    cout<<"\nSize: "<<G2.size()<<'\n'<<"Is Empty? "<<G2.empty()<<"\n\n";
    cout<<"\nADD EDGE\n";
    G2.add_edge(0, 2);
    G2.add_edge(0, 4);
    G2.add_edge(1, 5, 5);
    G2.add_edge(1, 6, 10);
    G2.add_edge(2, 5, 5);
    G2.add_edge(2, 6, 5);
    G2.add_edge(3, 5, 25);
    G2.add_edge(5, 6, 25);
    G2.add_edge(5, 7, 35);
    
    G2.disp();

    cout<<"\nSize: "<<G2.size()<<'\n'<<"Is Empty? "<<G2.empty()<<"\n\n";

    cout<<"\nMODIFY\n";
    G2.modify_edge(1, 2, 6);
    G2.modify_edge(3, 4, 0);

    G2.disp();

    cout<<"\nDELETE\n";
    G2.delete_edge(3, 4);
    G2.delete_edge(6, 2);

    G2.disp();
    cout<<endl;

    Graph<int,int>::breadth_first_search_iterator bfs2(G2, G2.find(1));
    cout<<"BFS:\t";
    while(!bfs2.bfsend())
    {
        cout<<(*bfs2).first<<"\t";
        ++bfs2;
    }
    cout<<endl;

    Graph<int,int>::depth_first_search_iterator dfs2(G2, G2.find(5));
    cout<<"DFS:\t";
    while(!dfs2.dfsend())
    {
        cout<<(*dfs2).first<<"\t";
        ++dfs2;
    }
    cout<<endl;

    cout<<"\n\nVertices   Shortest Path Cost    ShortestPath\n";
    map<int,pair<int,int>> m2 = G2.dijkstra(5);
    int s;
    stack<int> st2;
    for(auto x: m2)
    {
        cout<<x.first<<"\t\t"<<x.second.second<<"\t\t";
        s = x.first;
        while(s!=5)
        {
            st2.push(s);
            s = m2[s].first;
        }
        st2.push(5);
        while(!st2.empty())
        {
            cout<<"->"<<st2.top();
            st2.pop();
        }
        cout<<endl;
    }

    //FIND MAX ELEMENT
    int max = INT32_MIN;
    pair<int, int> tmp;
    Graph<int, int>::breadth_first_search_iterator bfsmax(G2, G2.find(0));   
    int src, dest;
    
    while(!bfsmax.bfsend())
    {
        tmp = *max_element(bfsmax->second.begin(), bfsmax->second.end(), 
                    [](pair<int, int> p1, pair<int, int> p2) { return p1.second < p2.second;});
        if(max < tmp.second)
        {
            max = tmp.second;
            src = bfsmax->first;
            dest = tmp.first;
        }
        ++bfsmax;
    }
    cout<<"MAX EDGE is between "<<src<<" and "<<dest<<" with weight "<<max<<'\n';

    //ACCUMULATE
    Graph<int, int>::breadth_first_search_iterator bfsacc1(G2, G2.find(0));
    Graph<int, int>::breadth_first_search_iterator bfsacc2(G2, G2.find(0));
    while(!bfsacc2.bfsend())
        ++bfsacc2;

    int ele = accumulate(bfsacc1, bfsacc2, 0, [](int x, auto y){ return x + y.first; });
    cout<<"ACCUMULATE SUM OF NODES : "<<ele<<'\n';

    //CYCLE CHECK    
    //G2.delete_edge(2, 5);
    //G2.delete_edge(1, 5);
    Graph<int, int>::breadth_first_search_iterator bfscyc(G2, G2.find(0));
    unordered_map<int, bool> visited;
    int c;
    bool flag = false;
    while(!bfscyc.bfsend())
    {
        c = 0;
        visited[bfscyc->first] = true;
        auto setitr = bfscyc->second.begin();
        while(setitr != bfscyc->second.end())
        {
            if(visited[setitr->first] == true)
                ++c;
            else
                visited[setitr->first] = true;
            ++setitr;
        }
        if(c > 1)
        {
            flag = true;
            break;
        }
        ++bfscyc;
    }
    cout<<"CYCLE PRESENT : "<<flag<<'\n';
}