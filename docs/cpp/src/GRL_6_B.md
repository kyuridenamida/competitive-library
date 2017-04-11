## GRL_6_B.cpp

```
int main() {
  int V, E, F;
  scanf("%d%d%d", &V, &E, &F);
  Graph<int, int> g(V);
  while (E--) {
    int u, v, c, d;
    scanf("%d%d%d%d", &u, &v, &c, &d);
    add_edge(g, u, v, c, d);
  }
  printf("%d\n", min_cost_flow(g, 0, V-1, F));
  return 0;
}
```

- [Back](../)