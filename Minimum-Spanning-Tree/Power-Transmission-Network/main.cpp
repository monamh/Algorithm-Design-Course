#include <iostream>
#include <limits>
#define max_v 100000

using namespace std;
class Graph{

    int* adj[max_v];
    int* max_in_path[max_v]; //max weight edge in path
    bool* in_mst;
    int* parent;
    int v;

public:

    Graph(int n){
        v=n;
        for(int i=0; i<v; i++){
            adj[i]=new int[v];
            for(int j=0; j<v; j++)
                adj[i][j]=numeric_limits<int>::max();
        }
        for(int i=0; i<v; i++){
            max_in_path[i]=new int[v];
            for(int j=0; j<v; j++)
                max_in_path[i][j]=0;
        }

        parent=new int[v];
        in_mst=new bool[v];
    }
    /*

    ~Graph(){
        for(int i=0; i<v; i++){
            delete[] adj[i];
            delete[] max_in_path[i];
        }
        delete[] adj;
        delete[] max_in_path;
        delete[] parent;
        delete[] in_mst;
    }
    */

    void add_edge(int a,int b,int weight){
        adj[a][b]=weight;
        adj[b][a]=weight;
    }

    int extract_min(int arr[],int size){
        int min=numeric_limits<int>::max(); int index=0;
        for(int i=0; i<size; i++)
            if(arr[i]<min && in_mst[i]==false){
                min=arr[i];
                index=i;
        }
        return index;
    }

    int Prim_MST(){
        int cost=0;
        int* key=new int[v];
        for(int i=0; i<v; i++){
            parent[i]=-1;
            in_mst[i]=false;
            key[i]=numeric_limits<int>::max();
        }
        key[0]=0;
        //last round is not needed
        for(int i=0; i<v; i++){
            int next_vertex=extract_min(key,v);
            in_mst[next_vertex]=true;
            cost+=key[next_vertex];
            for(int j=0; j<v; j++)
                if(in_mst[j]==false && key[j]>adj[next_vertex][j]){
                    key[j]=adj[next_vertex][j];
                    parent[j]=next_vertex;
                }
        }
        //cout<<"cost is"<<cost<<endl;
        return cost;
    }


    void find_max_edge_in_paths(int src,int succ){
        //using parents instead of adjacents since tree is undirected
        for(int c=0; c<v; c++){
            if(parent[c]==succ || c==parent[succ]){
                    //cout<<"is here for c="<<c+1<<" while path is "<<src+1<<" to "<<succ+1<<endl;
            //for each neighbor of succeder of source
                //if max is not set
                if(max_in_path[src][c]==0 && src!=c){
                    if(adj[succ][c]>max_in_path[src][succ]){
                        max_in_path[src][c]=adj[succ][c];
                    }
                    else{
                        max_in_path[src][c]=max_in_path[src][succ];
                    }
                    //undirected
                    //cout<<"is seting max edge for path between "<<succ+1<<" and "<<c+1<<" to "<<max_in_path[src][c]<<endl;
                    find_max_edge_in_paths(src,c);
                }

            }
        }
    }

    int find_cost_second_MST(){
        int best_cost=Prim_MST();
        for(int i=0; i<v; i++){
            find_max_edge_in_paths(i,i);
        }
        int min_diff=numeric_limits<int>::max(); int endpoint_i=-1; int endpoint_j=-1;
        for(int i=0; i<v; i++){
            //upper half is enough
            for(int j=0; j<i; j++ ){
                if(i!=parent[j] && j!=parent[i] && adj[i][j]-max_in_path[i][j]<min_diff){
                min_diff=adj[i][j]-max_in_path[i][j];
                        endpoint_i=i;
                        endpoint_j=j;
                        //cout<<"candid for adding is "<<i+1<<","<<j+1<<endl;
                }
            }
        }
        if(endpoint_i==-1 && endpoint_j==-1)
            return -1;
        else
            return best_cost+min_diff;

    }
};


int main()
{
    /*
    Graph g(5);
    g.add_edge(3,1,4);
    g.add_edge(1,2,2);
    g.add_edge(1,4,2);
    g.add_edge(5,2,3);
    g.add_edge(5,1,3);
    g.add_edge(2,3,1);
    g.add_edge(5,4,1);
    */
    int n,m,x,y,w;
    cin>>n;
    cin>>m;
    Graph g(n);
    for(int i=0; i<m; i++){
        cin>>x;
        cin>>y;
        cin>>w;
        g.add_edge(x-1,y-1,w);
    }
    cout<<g.find_cost_second_MST()<<endl;

    return 0;
}
