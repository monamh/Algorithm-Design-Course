#include <iostream>
#include <list>
using namespace std;

class Graph{

    list<int>* adj;
    bool* visited;
    int v;

public:

    Graph(int n){
        v=n;
        adj=new list<int> [v];
        visited=new bool[v];
    }

    ~Graph(){
        delete []adj;
    }

    void add_edge(int a,int b){
      adj[a].push_back(b);
      return;
    }

    int DFS_count(int src,int& counter){
        visited[src]=true;
        list<int>::iterator i;
        for(i=adj[src].begin(); i!=adj[src].end(); i++){
            if(!visited[*i]){
                counter=counter+1;
                DFS_count(*i,counter);
            }
        }
        return counter;
    }

    int find_vertex_with_max_reachability_to_others(){
        int max=0; int index=0;
        for(int i=0; i<this->v; i++){
                int zero_valued=0;
                for(int i=0;i<this->v;i++)
                    visited[i]=false;
                int tmp=DFS_count(i,zero_valued);
                //cout<<"number for "<<i+1<<" is "<<tmp<<endl;
                if(tmp>max){
                    max=tmp;
                    index=i;
                }
                //if(tmp==v-1)
                    //return index;
        }
        return index;
    }


};





int main()
{
    int n, neighbourOfi, degreeOfi, aux;
    cin>>n;
    while(n!=0){
        Graph g(n);
        for(int i=0; i<n; i++){
            cin>>degreeOfi;
            for(int j=0;j<degreeOfi;j++){
                cin>>neighbourOfi;
                g.add_edge(i,(neighbourOfi-1));
            }
        }
        cout<<g.find_vertex_with_max_reachability_to_others()+1<<endl;
        cin>>n;
    }

    return 0;
}
