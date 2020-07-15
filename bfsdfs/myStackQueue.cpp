#include <stdio.h>
#include <vector>
using std::vector;
using ll = long long;

#define DEFAULT_BUFFER_SIZE 1024

class GbnStaQue{
private:
    ll front_ptr, rear_ptr, buf_size;
    bool isStack; // true なら stack, false なら queue
    ll *staque;
    void Init(bool stk, ll initial_size){
        if (initial_size < 2) initial_size = 2; staque = new ll[initial_size];
        front_ptr = rear_ptr = 0; buf_size = initial_size; isStack = stk;
    };
    void Spread();
public:
    GbnStaQue(){ Init(true, DEFAULT_BUFFER_SIZE); }; // 指定がなければ stack
    GbnStaQue(bool isStk, ll initial_size = DEFAULT_BUFFER_SIZE){ Init(isStk, initial_size); }; // true なら stack, false なら queue
    ~GbnStaQue(){ delete[] staque; };
    ll push(ll l);
    ll pop();
    ll pop(bool *isEffective);
    ll GetSize() { return (rear_ptr - front_ptr); };
    void Show();
    bool empty() { return (front_ptr == rear_ptr); };
};

void GbnStaQue::Spread(){
    ll *tmp = new ll[buf_size];
    for (ll i = 0; i < buf_size; ++i) tmp[i] = staque[i];
    delete[] staque; staque = new ll[buf_size * 2];
    for (ll i = 0; i < buf_size; ++i) staque[i] = tmp[i];
    buf_size *= 2;
}

void GbnStaQue::Show(){
    if (empty()) {puts("empty"); return;}

    printf("front = %lld, rear = %lld, size = %lld\n", front_ptr, rear_ptr, buf_size);

    if (isStack)
        for (ll p = rear_ptr - 1; p >= front_ptr; --p) printf("%lld: [%lld]\n", p, staque[p]);
    else
        for (ll p = front_ptr; p < rear_ptr; ++p) printf("%lld: [%lld]\n", p, staque[p]);
}

ll GbnStaQue::push(ll l){
    staque[rear_ptr++] = l;
    if (rear_ptr >= buf_size) Spread();
    return rear_ptr;
}

ll GbnStaQue::pop(bool *isEffective){
    if (rear_ptr == front_ptr) { puts("pop: Empty"); *isEffective = false; return 0; }
    
    ll ret;
    if (isStack)
        ret = staque[--rear_ptr];
    else
        ret = staque[front_ptr++];
    
    *isEffective = true;
    return ret;
}

ll GbnStaQue::pop(){
    if (rear_ptr == front_ptr) { puts("pop: Empty"); return 0; }
    
    ll ret;
    if (isStack)
        ret = staque[--rear_ptr];
    else
        ret = staque[front_ptr++];
    
    return ret;
}

#define NUM_VERTEX 17
using graph = vector<vector<int> >;

void SetGraph(graph& g) // 閉回路なし
{
    g[0]={1,7,12}; g[1]={0,2,3,4}; g[2]={1}; g[3]={1,5,6}; g[4]={1}; g[5]={3};
    g[6]={3}; g[7]={0,8,9}; g[8]={7,10,11}; g[9]={7}; g[10]={8}; g[11]={8};
    g[12]={0,13}; g[13]={12,14,15}; g[14]={13,16}; g[15]={13}; g[16]={14};
}

void SetGraph_2(graph& g) // 閉回路あり
{
    g[0]={1,7,12,16}; g[1]={0,2,3,4}; g[2]={1,5}; g[3]={1,5,6}; g[4]={1,8}; g[5]={2,3,6,16};
    g[6]={3,5,10}; g[7]={0,8,9,11}; g[8]={4,7,10,11}; g[9]={7}; g[10]={6,8,11}; g[11]={7,8,10,14};
    g[12]={0,13}; g[13]={12,14,15}; g[14]={11,13,15,16}; g[15]={13,14,16}; g[16]={0,5,14};
}

ll Search_adjList(graph& adj_list, ll start, vector<ll>& found_list, bool type)
{
    ll num_vertex = adj_list.size();
    vector<bool> visited(num_vertex, false);
    vector<bool> inBuffer(num_vertex, false);
    GbnStaQue sq(type); // 引数は DFS の場合は true, BFS の場合は false
    ll num_found = 0;
    ll current_vertex = start;
    sq.push(start); inBuffer[start] = true;

    while(!sq.empty()){
        current_vertex = sq.pop();
        visited[current_vertex] = true;
        found_list.push_back(current_vertex);
        num_found++;
        for(auto next_vertex:adj_list[current_vertex]){
            if(visited[next_vertex]) continue;
            if(inBuffer[next_vertex]) continue;
            sq.push(next_vertex); inBuffer[next_vertex] = true;
        }
    }
    return num_found;
}

int main(int argc, char **argv)
{
    graph gp(NUM_VERTEX);
    if (argc <= 2) // 引数が無しなら
        SetGraph(gp); // 閉回路無しの隣接リストを使用
    else            // 引数があれば
        SetGraph_2(gp); // 閉回路有りの隣接リストを使用

    ll start = 0; // 検索を開始する頂点
    ll num_found;

#define BFS false
#define DFS true
    vector<ll> found_list_bfs;
    num_found = Search_adjList(gp, start, found_list_bfs, BFS);
    puts("BFS");
    for(ll i=0; i < num_found; ++i)
        printf("%2lld: v%lld\n", i, found_list_bfs[i]);

    vector<ll> found_list_dfs;
    num_found = Search_adjList(gp, start, found_list_dfs, DFS);
    puts("\nDFS");
    for(ll i=0; i < num_found; ++i) 
        printf("%2lld: v%lld\n", i, found_list_dfs[i]);

    return 0;
}
