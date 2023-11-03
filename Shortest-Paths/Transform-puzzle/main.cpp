#include <iostream>
#include <limits>
#define max_v 300
#define INF 100000

/*
struct vertex{
    int index;
    string label;
};
*/
using namespace std;

class Graph
{
    int v;
    int* adj[max_v]; //init to inf
    int* d[max_v];
    int* inter[max_v]; //init to -1

public:

    //kasiffff
    string* labels;
    Graph(int n){
        v=n;
        labels=new string[v];
        for(int i=0; i<v; i++){
            adj[i]=new int[v];
            for(int j=0; j<v; j++)
                adj[i][j]=INF;
            //for(int j=0;j<v;j++)
                //adj[i][i]=0;
        }
        for(int i=0; i<v; i++){
            inter[i]=new int[v];
            for(int j=0; j<v; j++)
                inter[i][j]=-1;
        }
        for(int i=0; i<v; i++){
            d[i]=new int[v];
            for(int j=0; j<v; j++)
                d[i][j]=INF;
        }
    }
    //kasif =)))
    int find_vertex(string a){
        for(int i=0; i<v; i++){
            if(labels[i]==a){
                return i;
            }
        }
        //if no vertex?
        return -1;
    }

    void add_edge(int i,int j){
        adj[i][j]=1;
        adj[j][i]=1;
    }

    void check_and_add_edge(string a,string b){
        if(are_convertable(a,b)){
            int i=find_vertex(a);
            int j=find_vertex(b);
            adj[i][j]=1;
            adj[j][i]=1;
        }
    }

    bool are_convertable(string a,string b){
        if((a.length()<b.length()&& a.length()+1<b.length()) || (b.length()<a.length()&& b.length()+1<a.length())){
                return false;
            //cout<<"is returning false for "<<a<<" and "<<b<<" b4 iteration "<<endl;
            //cout<<" a.length-b.length is "<<a.length()-b.length()<<endl;
        }
        else{
            std::string::iterator i,j,p,q;
            i=a.begin(); j=a.end();
            p=b.begin(); q=b.end();
            while(toupper(*i)==toupper(*p)){
                i++;
                p++;
            }
            while(j>=i && q>=p && toupper(*j)==toupper(*q)){
                j--;
                q--;
            }

            if(j-i<1 && q-p<1){
                //cout<<"is returning true for "<<a<<" and "<<b<<endl;
                return true;
            }
            else{
            //cout<<"is returning false for "<<a<<" and "<<b<<endl;
                return false;
            }
        }

    }

/*
    ~Graph(){
        for(int i=0; i<v; i++){
            delete[] d[i];
            delete[] adj[i];
            delete[] inter[i];
        }
        delete[] adj;
        delete[] d;
        delete[] inter;
        delete[] labels;
    }

*/
    //better use tagharon
    void Floyd_Warshal(){
        for(int i=0; i<v; i++){
            for(int j=0; j<v; j++){
                d[i][j]=adj[i][j];
            }
        }
        for(int k=0; k<v; k++)
        for(int i=0; i<v; i++){
            for(int j=0; j<v ; j++)
                if(i!=j && k!=j && k!=i){
                    //cout<<"distance of "<<i<<","<<j<<" before: "<<d[i][j]<<endl;
                        if(d[i][k]+d[k][j]<d[i][j]){
                            d[i][j]=d[i][k]+d[k][j];
                            //cout<<"setting distance of "<<labels[i]<<","<<labels[j]<<" to "<<d[i][k]+d[k][j]<<" with k="<<labels[k]<<endl;
                            inter[i][j]=k;
                    }
                }
        }
    }


    void print_path(int i,int j,int i_flag,int j_flag){
        if(d[i][j]>=INF)
            cout<<"*";
            //cout<<"*****"<<endl;
        else{
            if(inter[i][j]==-1){
                if(i_flag==1)
                    cout<<labels[i]<<" ";
                if(j_flag==1)
                    cout<<labels[j]<<" ";
            }
            else{
                if(i_flag==1 && j_flag==1){
                    print_path(i,inter[i][j],1,-1);
                    print_path(inter[i][j],j,1,1);
                }
                if(i_flag==-1 && j_flag==1){
                    print_path(i,inter[i][j],-1,-1);
                    print_path(inter[i][j],j,1,1);
                }
                if(i_flag==1 && j_flag==-1){
                    print_path(i,inter[i][j],1,-1);
                    print_path(inter[i][j],j,1,-1);
                }
                if(i_flag==-1 && j_flag==-1){
                    print_path(i,inter[i][j],-1,-1);
                    print_path(inter[i][j],j,1,-1);
                }
            //print_path(i,inter[i][j],1,-1);
            //print_path(inter[i][j],j,1,1);
            }
        }
    }


};


int main()
{
    int k,q; string s,e;
    cin>>k;
    cin>>q;
    Graph g(k);
    for(int i=0; i<k; i++){
        cin>>s;
        g.labels[i]=s;
        for(int j=0; j<i; j++){
            if(g.are_convertable(g.labels[i],g.labels[j]))
                g.add_edge(i,j);
        }
    }
    g.Floyd_Warshal();
    for(int i=0;i<q; i++){
            cin>>s;
            cin>>e;
            if(g.find_vertex(e)==-1 || g.find_vertex(s)==-1)
                cout<<"*";
                //cout<<"*****"<<endl;
            else
                g.print_path(g.find_vertex(s),g.find_vertex(e),1,1);
            cout<<endl;
    }

    return 0;
}
