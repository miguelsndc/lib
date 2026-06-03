vector<int> g[ms]; stack<int> st;
int dfn[ms], low[ms], scc_id[ms], timer = 0,scc_cnt=0, in_st[ms];
void tarjan(int u) {
    dfn[u] = low[u] = timer++;
    st.push(u); in_st[u]=true;
    for (int v:g[u]) {
        if (dfn[v]==-1){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        } else if (in_st[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]) {
        scc_cnt++;
        while(true){
            int v=st.top();st.pop();
            in_st[v]=false;
            scc_id[v]=scc_cnt;
            if(u==v)break;
        }
    }
}

/*
  grafo de condensacao:
  pra cada vertice u do grafo original, se existir aresta (u,v) tal que id[u] != id[v] adiciona
  u -> v no dag
*/
