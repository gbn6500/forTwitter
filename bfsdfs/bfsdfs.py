#define NUM_VERTEX 17
adj_list=[[1,7,12],[0,2,3,4],[1],[1,5,6],[1],[3],[3],[0,8,9],[7,10,11],[7],[8],[8],[0,13],[12,14,15],[13,16],[13],[14]]

#void SetGraph_2(graph& g) // 閉回路あり
#{
#    g[0]={1,7,12,16}; g[1]={0,2,3,4}; g[2]={1,5}; g[3]={1,5,6}; g[4]={1,8}; g[5]={2,3,6,16};
#    g[6]={3,5,10}; g[7]={0,8,9,11}; g[8]={4,7,10,11}; g[9]={7}; g[10]={6,8,11}; g[11]={7,8,10,14};
#    g[12]={0,13}; g[13]={12,14,15}; g[14]={11,13,15,16}; g[15]={13,14,16}; g[16]={0,5,14};
#}

for v in adj_list:
    print(adj_list[0])
    for e in v:
        print(e, end=', ')
    print("")

'''
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
'''
