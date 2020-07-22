import queue

#adj_v=[[1,7,12],[0,2,3,4],[1],[1,5,6],[1],[3],[3],[0,8,9],[7,10,11],[7],[8],[8],[0,13],[12,14,15],[13,16],[13],[14]]
#    g[0]={1,7,12,16}; g[1]={0,2,3,4}; g[2]={1,5}; g[3]={1,5,6}; g[4]={1,8}; g[5]={2,3,6,16};
#    g[6]={3,5,10}; g[7]={0,8,9,11}; g[8]={4,7,10,11}; g[9]={7}; g[10]={6,8,11}; g[11]={7,8,10,14};
#    g[12]={0,13}; g[13]={12,14,15}; g[14]={11,13,15,16}; g[15]={13,14,16}; g[16]={0,5,14};

def Search_adjList(adj_list, start, found_list):
    num_vertex = len(adj_list)
    found = [False] * num_vertex
    inQueue = [False] * num_vertex
    que = queue.Queue()
    que.put(start)
    inQueue[start] = True

    while not que.empty():
        current_vertex = que.get()
        found_list.append(current_vertex)
        found[current_vertex] = True
        for next_vertex in adj_list[current_vertex]:
            if found[next_vertex]: continue
            if inQueue[next_vertex]: continue
            que.put(next_vertex)
            inQueue[next_vertex] = True

adj_v=[[1,7,12],[0,2,3,4],[1],[1,5,6],[1],[3],[3],[0,8,9],[7,10,11],[7],[8],[8],[0,13],[12,14,15],[13,16],[13],[14]]
found_list_bfs=[]
Search_adjList(adj_v, 0, found_list_bfs)
print(found_list_bfs)