#ifndef GRAPH_ALL_IN_ONE_H
#define GRAPH_ALL_IN_ONE_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstdlib>

#define MAX_VTXS 256
#define INF 9999

using namespace std;

// ==========================================================
// 1. 필요한 기본 자료구조 (CircularQueue - BFS용) [cite: 4445]
// ==========================================================
class CircularQueue {
    int front, rear;
    int data[MAX_VTXS];
public:
    CircularQueue() { front = rear = 0; }
    bool isEmpty() { return front == rear; }
    bool isFull() { return (rear + 1) % MAX_VTXS == front; }
    void enqueue(int val) {
        if (!isFull()) {
            rear = (rear + 1) % MAX_VTXS;
            data[rear] = val;
        }
    }
    int dequeue() {
        if (!isEmpty()) {
            front = (front + 1) % MAX_VTXS;
            return data[front];
        }
        return -1;
    }
};

// ==========================================================
// 2. 인접 행렬을 이용한 기본 그래프 (11장) [cite: 4400, 4401, 4402, 4403, 4404, 4405, 4406, 4407]
// ==========================================================
class AdjMatGraph {
protected:
    int size;
    char vertices[MAX_VTXS];
    int adj[MAX_VTXS][MAX_VTXS];
public:
    AdjMatGraph() { reset(); }
    char getVertex(int i) { return vertices[i]; }
    int getEdge(int i, int j) { return adj[i][j]; }
    void setEdge(int i, int j, int val) { adj[i][j] = val; }
    bool isEmpty() { return size == 0; }
    bool isFull() { return size >= MAX_VTXS; }

    void reset() {
        size = 0;
        for (int i = 0; i < MAX_VTXS; i++)
            for (int j = 0; j < MAX_VTXS; j++)
                setEdge(i, j, 0);
    }
    void insertVertex(char name) {
        if (!isFull()) vertices[size++] = name;
        else printf("Error: 그래프 정점 개수 초과\n");
    }
    void insertEdge(int u, int v) {
        setEdge(u, v, 1);
        setEdge(v, u, 1);
    }
    void display(FILE* fp = stdout) {
        fprintf(fp, "%d\n", size);
        for (int i = 0; i < size; i++) {
            fprintf(fp, "%c ", getVertex(i));
            for (int j = 0; j < size; j++)
                fprintf(fp, " %3d", getEdge(i, j));
            fprintf(fp, "\n");
        }
    }
};

// ==========================================================
// 3. 그래프 탐색 알고리즘 추가 (DFS, BFS) [cite: 4434, 4436, 4437, 4445, 4446, 4447, 4448]
// ==========================================================
class SrchAMGraph : public AdjMatGraph {
protected:
    bool visited[MAX_VTXS];
public:
    void resetVisited() {
        for (int i = 0; i < size; i++)
            visited[i] = false;
    }
    bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

    void DFS(int v) {
        visited[v] = true;
        printf("%c ", getVertex(v));
        for (int w = 0; w < size; w++)
            if (isLinked(v, w) && visited[w] == false)
                DFS(w);
    }

    void BFS(int v) {
        visited[v] = true;
        printf("%c ", getVertex(v));
        CircularQueue que;
        que.enqueue(v);
        while (!que.isEmpty()) {
            int cur = que.dequeue();
            for (int w = 0; w < size; w++) {
                if (isLinked(cur, w) && visited[w] == false) {
                    visited[w] = true;
                    printf("%c ", getVertex(w));
                    que.enqueue(w);
                }
            }
        }
    }
};

// ==========================================================
// 4. 연결 성분 찾기 [cite: 4450, 4451, 4452, 4453]
// ==========================================================
class ConnectedComponentGraph : public SrchAMGraph {
    int label[MAX_VTXS];
public:
    void labelDFS(int v, int color) {
        visited[v] = true;
        label[v] = color;
        for (int w = 0; w < size; w++)
            if (isLinked(v, w) && visited[w] == false)
                labelDFS(w, color);
    }
    void findConnectedComponent() {
        int count = 0;
        for (int i = 0; i < size; i++)
            if (visited[i] == false)
                labelDFS(i, ++count);
        printf("그래프 연결성분 개수 == %d\n", count);
        for (int i = 0; i < size; i++)
            printf("%c=%d ", getVertex(i), label[i]);
        printf("\n");
    }
};

// ==========================================================
// 5. 가중치 그래프 기본 클래스 (12장) [cite: 3053, 3054, 3056, 3057, 3058]
// ==========================================================
class WGraph : public AdjMatGraph {
public:
    WGraph() {}
    void insertEdge(int u, int v, int weight) {
        if (weight > INF) weight = INF;
        setEdge(u, v, weight);
    }
    bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }

    void load(const char* filename) {
        FILE* fp = fopen(filename, "r");
        if (fp != NULL) {
            int n, val;
            fscanf(fp, "%d", &n);
            for (int i = 0; i < n; i++) {
                char str[80];
                fscanf(fp, "%s", str);
                insertVertex(str[0]);
                for (int j = 0; j < n; j++) {
                    fscanf(fp, "%d", &val);
                    insertEdge(i, j, val);
                }
            }
            fclose(fp);
        }
    }
};

// ==========================================================
// 6. Kruskal 알고리즘을 위한 Union-Find 및 최소 힙 [cite: 3081, 3082, 3083, 3084]
// ==========================================================
class VertexSets {
    int parent[MAX_VTXS];
    int nSets;
public:
    VertexSets(int n) : nSets(n) {
        for (int i = 0; i < nSets; i++)
            parent[i] = -1;
    }
    bool isRoot(int i) { return parent[i] < 0; }
    int findSet(int v) {
        while (!isRoot(v)) v = parent[v];
        return v;
    }
    void unionSets(int s1, int s2) {
        parent[s1] = s2;
        nSets--;
    }
};

class HeapNode {
    int key;
    int v1;
    int v2;
public:
    HeapNode() : key(0), v1(0), v2(0) {}
    HeapNode(int k, int u, int v) : key(k), v1(u), v2(v) {}
    void setKey(int k, int u, int v) { key = k; v1 = u; v2 = v; }
    int getKey() { return key; }
    int getV1() { return v1; }
    int getV2() { return v2; }
};

class MinHeap {
    HeapNode node[MAX_VTXS * 2];
    int size;
public:
    MinHeap() : size(0) {}
    bool isEmpty() { return size == 0; }
    bool isFull() { return size >= MAX_VTXS * 2 - 1; }
    HeapNode& getParent(int i) { return node[i / 2]; }

    void insert(int key, int u, int v) {
        if (isFull()) return;
        int i = ++size;
        while (i != 1 && key < getParent(i).getKey()) {
            node[i] = getParent(i);
            i /= 2;
        }
        node[i].setKey(key, u, v);
    }

    HeapNode remove() {
        if (isEmpty()) return HeapNode(-1, -1, -1);
        HeapNode item = node[1];
        HeapNode last = node[size--];
        int parent = 1;
        int child = 2;
        while (child <= size) {
            if (child < size && node[child].getKey() > node[child + 1].getKey())
                child++;
            if (last.getKey() <= node[child].getKey()) break;
            node[parent] = node[child];
            parent = child;
            child *= 2;
        }
        node[parent] = last;
        return item;
    }
};

// ==========================================================
// 7. 최소비용 신장트리 (Kruskal, Prim 기능 포함) [cite: 3086, 3095, 3096, 3097, 3098, 3099, 3100, 3101]
// ==========================================================
class WGraphMST : public WGraph {
public:
    void Kruskal() {
        MinHeap heap;
        for (int i = 0; i < size - 1; i++)
            for (int j = i + 1; j < size; j++)
                if (hasEdge(i, j))
                    heap.insert(getEdge(i, j), i, j);

        VertexSets set(size);
        int edgeAccepted = 0;
        while (edgeAccepted < size - 1) {
            HeapNode e = heap.remove();
            int uset = set.findSet(e.getV1());
            int vset = set.findSet(e.getV2());
            if (uset != vset) {
                printf("간선 추가 : %c - %c (비용:%d)\n",
                    getVertex(e.getV1()), getVertex(e.getV2()), e.getKey());
                set.unionSets(uset, vset);
                edgeAccepted++;
            }
        }
    }

    int getMinVertex(bool* selected, int* dist) {
        int minv = 0;
        int mindist = INF;
        for (int v = 0; v < size; v++)
            if (!selected[v] && dist[v] < mindist) {
                mindist = dist[v];
                minv = v;
            }
        return minv;
    }

    void Prim(int s) {
        bool selected[MAX_VTXS];
        int dist[MAX_VTXS];
        for (int i = 0; i < size; i++) {
            dist[i] = INF;
            selected[i] = false;
        }
        dist[s] = 0;
        for (int i = 0; i < size; i++) {
            int u = getMinVertex(selected, dist);
            selected[u] = true;
            if (dist[u] == INF) return;
            printf("%c ", getVertex(u));
            for (int v = 0; v < size; v++)
                if (getEdge(u, v) != INF)
                    if (!selected[v] && getEdge(u, v) < dist[v])
                        dist[v] = getEdge(u, v);
        }
        printf("\n");
    }
};

// ==========================================================
// 8. 최단경로 (Dijkstra) [cite: 3111, 3112, 3113, 3114, 3116, 3117, 3118]
// ==========================================================
class WGraphDijkstra : public WGraph {
    int dist[MAX_VTXS];
    bool found[MAX_VTXS];
public:
    int chooseVertex() {
        int min = INF;
        int minpos = -1;
        for (int i = 0; i < size; i++)
            if (dist[i] < min && !found[i]) {
                min = dist[i];
                minpos = i;
            }
        return minpos;
    }
    void printDistance() {
        for (int i = 0; i < size; i++)
            printf("%5d", dist[i]);
        printf("\n");
    }
    void ShortestPath(int start) {
        for (int i = 0; i < size; i++) {
            dist[i] = getEdge(start, i);
            found[i] = false;
        }
        found[start] = true;
        dist[start] = 0;
        for (int i = 0; i < size; i++) {
            printf("Step%2d:", i + 1);
            printDistance();
            int u = chooseVertex();
            if (u == -1) break;
            found[u] = true;
            for (int w = 0; w < size; w++) {
                if (found[w] == false)
                    if (dist[u] + getEdge(u, w) < dist[w])
                        dist[w] = dist[u] + getEdge(u, w);
            }
        }
    }
};

// ==========================================================
// 9. 최단경로 (Floyd) [cite: 3126, 3127, 3128]
// ==========================================================
class WGraphFloyd : public WGraph {
    int A[MAX_VTXS][MAX_VTXS];
public:
    void ShortestPathFloyd() {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                A[i][j] = getEdge(i, j);

        for (int k = 0; k < size; k++) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (A[i][k] + A[k][j] < A[i][j])
                        A[i][j] = A[i][k] + A[k][j];
                }
            }
            printA();
        }
    }
    void printA() {
        printf("===============================\n");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (A[i][j] == INF)
                    printf(" INF ");
                else
                    printf("%4d ", A[i][j]);
            }
            printf("\n");
        }
    }
};

// ==========================================================
// 10. (부록) 인접 리스트를 이용한 그래프 [cite: 4415, 4416, 4417, 4418, 4419, 4420, 4421, 4423, 4424, 4426, 4427, 4428]
// ==========================================================
class Node {
protected:
    int id;
    Node* link;
public:
    Node(int i, Node* l = NULL) : id(i), link(l) {}
    ~Node() { if (link != NULL) delete link; }
    int getId() { return id; }
    Node* getLink() { return link; }
    void setLink(Node* l) { link = l; }
};

class AdjListGraph {
protected:
    int size;
    char vertices[MAX_VTXS];
    Node* adj[MAX_VTXS];
public:
    AdjListGraph() : size(0) {
        for (int i = 0; i < MAX_VTXS; i++) adj[i] = NULL;
    }
    ~AdjListGraph() { reset(); }
    void reset(void) {
        for (int i = 0; i < size; i++)
            if (adj[i] != NULL) delete adj[i];
        size = 0;
    }
    bool isFull() { return size >= MAX_VTXS; }
    char getVertex(int i) { return vertices[i]; }

    void insertVertex(char val) {
        if (!isFull()) {
            vertices[size] = val;
            adj[size++] = NULL;
        }
        else {
            printf("Error: 그래프 정점 개수 초과\n");
        }
    }
    void insertEdge(int u, int v) {
        adj[u] = new Node(v, adj[u]);
        adj[v] = new Node(u, adj[v]);
    }
    void display() {
        printf("%d\n", size);
        for (int i = 0; i < size; i++) {
            printf("%c ", getVertex(i));
            for (Node* v = adj[i]; v != NULL; v = v->getLink())
                printf(" %c", getVertex(v->getId()));
            printf("\n");
        }
    }
    Node* adjacent(int v) { return adj[v]; }
};

#endif // GRAPH_ALL_IN_ONE_H