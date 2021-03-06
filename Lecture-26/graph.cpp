#include<iostream>
#include<list>
#include<queue>
#include<stack>
using namespace std;
class graph{
    int v;
    list<int> * l;

public:
    graph(int v){
        this->v = v;
        l = new list<int>[v];
    }
    void addEdge(int start,int end, bool bidir = false){
        l[start].push_back(end);
        if(bidir){
            l[end].push_back(start);
        }
    }
    void bfsDriver(int src,vector<bool> &visited){
        queue<int> q;
        cout<<src<<" ";
        visited[src] = true;
        q.push(src);
        while(!q.empty()){
            int top = q.front();
            q.pop();
            for(auto it = l[top].begin();it!=l[top].end();it++){
                if(!visited[*it]){
                    cout<<*it<<" ";
                    visited[*it] = true;
                    q.push(*it);
                }
            }
        }
    }
    void bfs(){
        vector<bool>visited;
        for(int i=0;i<v;i++){
            visited.push_back(0);
            // visited[i] = 0;   not possible here
        }
        for(int i=0;i<v;i++){
            if(!visited[i]){
                bfsDriver(i,visited);
            }
        }
    }
    void dfsDriver(int src,vector<bool> &visited){
        if(visited[src]){
            return;
        }
        cout<<src<<" ";
        visited[src] = true;
        for(auto it = l[src].begin();it!=l[src].end();it++){
            dfsDriver(*it,visited);
        }
        return;
    }
    void dfs(){
        vector<bool>visited;
        for(int i=0;i<v;i++){
            visited.push_back(false);
            // visited[i] = 0;   not possible here
        }
        for(int i=0;i<v;i++){
            if(!visited[i]){
                dfsDriver(i,visited);
            }
        }
    }
    void bfsDist(int src){
        vector<bool> visited;
        vector<int> dist;
        for(int i=0;i<v;i++){
            visited.push_back(false);
            dist.push_back(INT_MAX);
        }
        queue<int>q;
        dist[src] = 0;
        visited[src] = true;
        q.push(src);
        while(!q.empty()){
            int top = q.front();
            q.pop();
            int parentDist = dist[top];
            for(auto it = l[top].begin();it!=l[top].end();it++){
                if(!visited[*it]){
                    dist[*it] = parentDist + 1;
                    visited[*it] = true;
                    q.push(*it);
                }
            }
        }
        for(int i=0;i<v;i++){
            cout<<dist[i]<<" ";
        }
        cout<<endl;
    }

    bool cycleDriver(int vertex,vector<bool>&visited,vector<bool>&inStack){
        if(visited[vertex]==true){
            return false;
        }
        visited[vertex] = true;
        inStack[vertex] = true;
        for(auto it = l[vertex].begin();it!=l[vertex].end();it++){
            int v =*it;
            if(visited[v] && inStack[v]){
                return true;
            }
            bool isCycle = cycleDriver(v,visited,inStack);
            if(isCycle){
                return true;
            }
            inStack[v] = false;
        }
        inStack[vertex] = false;
        return false;
    }
    bool cycle(){
        vector<bool>visited;
        vector<bool>inStack;
        for(int i=0;i<v;i++){
            visited.push_back(false);
            inStack.push_back(false);
            // visited[i] = 0;   not possible here
        }
        for(int i=0;i<v;i++){
            bool cycle = cycleDriver(i,visited,inStack);
            if(cycle){
                return true;
            }
        }
        return false;
    }
    void topoDriver(int vertex,vector<bool>&visited,stack<int>&s){
        if(visited[vertex]){
            return;
        }
        visited[vertex] = true;
        list<int>:: iterator it;
        for(it = l[vertex].begin();it!=l[vertex].end();it++){
            topoDriver(*it,visited,s);
        }
        s.push(vertex);
        return;
    }
    void toptOrder(){
        vector<bool>visited;
        stack<int>s;
        for(int i=0;i<v;i++){
            visited.push_back(false);
        }
        for(int i=0;i<v;i++){
            topoDriver(i,visited,s);
        }
        while(!s.empty()){
            cout<<s.top();
            s.pop();
        }
        cout<<endl;
    }
    void print(){
        for(int i=0;i<v;i++){
            cout<<i<<" -->";
            list<int>::iterator it;
            for(it = l[i].begin(); it!=l[i].end();it++){
                cout<<*it<<" ";
            }
            cout<<"NULL"<<endl;
        }
    }
};
int main(){
    graph g(7);
    g.addEdge(0,1,0);
    g.addEdge(0,2,0);
    g.addEdge(0,3,0);
    g.addEdge(2,3,0);
    g.addEdge(2,5,0);
    g.addEdge(3,4,0);
    g.addEdge(5,6,0);
    g.print();
    g.bfs();
    cout<<endl;
    g.dfs();
    cout<<endl;
    g.bfsDist(0);
 g.toptOrder();
}
