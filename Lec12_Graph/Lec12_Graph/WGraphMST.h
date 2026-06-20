#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX_VTXS = 100;
const int INF = 9999;
const int MAX_HEAP_NODE = MAX_VTXS * MAX_VTXS;

// ===============================
// 인접 행렬 그래프 클래스
// ===============================
class AdjMatGraph {
protected:
    int size;                         // 정점 개수
    char vertices[MAX_VTXS];          // 정점 이름
    int adj[MAX_VTXS][MAX_VTXS];      // 인접 행렬

public:
    AdjMatGraph() {
        reset();
    }

    void reset() {
        size = 0;

        for (int i = 0; i < MAX_VTXS; i++) {
            for (int j = 0; j < MAX_VTXS; j++) {
                if (i == j)
                    adj[i][j] = 0;
                else
                    adj[i][j] = INF;
            }
        }
    }

    bool isFull() const {
        return size >= MAX_VTXS;
    }

    void insertVertex(char name) {
        if (isFull()) {
            cout << "정점 개수 초과" << endl;
            return;
        }

        vertices[size++] = name;
    }

    char getVertex(int i) const {
        return vertices[i];
    }

    int getEdge(int i, int j) const {
        return adj[i][j];
    }

    void setEdge(int i, int j, int value) {
        adj[i][j] = value;
    }

    void display(const char* msg = "Graph") const {
        cout << msg << endl << endl;

        cout << "     ";
        for (int i = 0; i < size; i++) {
            cout << setw(5) << vertices[i];
        }
        cout << endl;

        for (int i = 0; i < size; i++) {
            cout << setw(5) << vertices[i];

            for (int j = 0; j < size; j++) {
                if (adj[i][j] >= INF)
                    cout << setw(5) << "INF";
                else
                    cout << setw(5) << adj[i][j];
            }

            cout << endl;
        }

        cout << endl;
    }
};

// ===============================
// 가중치 그래프 클래스
// 강의자료의 WGraph 역할
// ===============================
class WGraph : public AdjMatGraph {
public:
    void insertEdge(int u, int v, int weight) {
        if (weight > INF)
            weight = INF;

        setEdge(u, v, weight);
    }

    bool hasEdge(int i, int j) const {
        return getEdge(i, j) < INF;
    }

    void load(const char* filename) {
        ifstream fin(filename);

        if (!fin) {
            cout << "파일을 열 수 없습니다: " << filename << endl;
            return;
        }

        reset();

        int n;
        fin >> n;

        if (n > MAX_VTXS) {
            cout << "정점 개수가 너무 많습니다." << endl;
            return;
        }

        for (int i = 0; i < n; i++) {
            char name;
            fin >> name;

            insertVertex(name);

            for (int j = 0; j < n; j++) {
                int value;
                fin >> value;

                insertEdge(i, j, value);
            }
        }

        fin.close();
    }
};

// ===============================
// Union-Find 클래스
// 강의자료의 VertexSets 역할
// ===============================
class VertexSets {
private:
    int parent[MAX_VTXS];     // 부모 정점의 id
    int nSets;                // 집합의 개수

public:
    VertexSets(int n) : nSets(n) {
        for (int i = 0; i < nSets; i++) {
            parent[i] = -1;   // 처음에는 모든 정점이 독립 집합
        }
    }

    bool isRoot(int i) const {
        return parent[i] < 0;
    }

    int findSet(int v) const {
        while (!isRoot(v)) {
            v = parent[v];
        }

        return v;
    }

    void unionSets(int s1, int s2) {
        parent[s1] = s2;
        nSets--;
    }
};

// ===============================
// 힙에 저장할 간선 노드 클래스
// 강의자료의 HeapNode 역할
// ===============================
class HeapNode {
private:
    int key;    // 간선의 가중치
    int v1;     // 정점 1
    int v2;     // 정점 2

public:
    HeapNode(int k = 0, int u = 0, int v = 0)
        : key(k), v1(u), v2(v) {
    }

    void setKey(int k, int u, int v) {
        key = k;
        v1 = u;
        v2 = v;
    }

    int getKey() const {
        return key;
    }

    int getV1() const {
        return v1;
    }

    int getV2() const {
        return v2;
    }
};

// ===============================
// 최소 힙 클래스
// 가장 작은 가중치 간선을 꺼내기 위해 사용
// ===============================
class MinHeap {
private:
    HeapNode node[MAX_HEAP_NODE];
    int size;

public:
    MinHeap() : size(0) {
    }

    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return size >= MAX_HEAP_NODE - 1;
    }

    HeapNode& getParent(int i) {
        return node[i / 2];
    }

    void insert(int key, int u, int v) {
        if (isFull()) {
            cout << "Heap is full." << endl;
            return;
        }

        int i = ++size;

        // 새로 들어온 간선의 가중치가 부모보다 작으면 위로 이동
        while (i != 1 && key < getParent(i).getKey()) {
            node[i] = getParent(i);
            i /= 2;
        }

        node[i].setKey(key, u, v);
    }

    HeapNode remove() {
        if (isEmpty()) {
            cout << "Heap is empty." << endl;
            return HeapNode();
        }

        HeapNode item = node[1];
        HeapNode last = node[size--];

        int parent = 1;
        int child = 2;

        while (child <= size) {
            // 오른쪽 자식이 있고, 오른쪽 자식이 더 작으면 오른쪽 선택
            if (child < size &&
                node[child].getKey() > node[child + 1].getKey()) {
                child++;
            }

            // 마지막 노드가 자식보다 작거나 같으면 제자리
            if (last.getKey() <= node[child].getKey()) {
                break;
            }

            node[parent] = node[child];
            parent = child;
            child *= 2;
        }

        node[parent] = last;

        return item;
    }
};

// ===============================
// MST 기능이 추가된 가중치 그래프
// 강의자료의 WGraphMST 역할
// ===============================
class WGraphMST : public WGraph {
public:
    void Kruskal() {
        MinHeap heap;

        // 1. 그래프의 모든 간선을 최소힙에 삽입
        // 무방향 그래프이므로 i < j 부분만 확인
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (hasEdge(i, j)) {
                    heap.insert(getEdge(i, j), i, j);
                }
            }
        }

        // 2. 처음에는 모든 정점이 각각 독립 집합
        VertexSets set(size);

        int edgeAccepted = 0;
        int totalCost = 0;

        // 3. MST는 정점이 n개일 때 n-1개의 간선을 가짐
        while (edgeAccepted < size - 1) {
            if (heap.isEmpty()) {
                cout << "그래프가 연결되어 있지 않아 MST를 만들 수 없습니다." << endl;
                return;
            }

            // 4. 최소 가중치 간선 선택
            HeapNode e = heap.remove();

            int uset = set.findSet(e.getV1());
            int vset = set.findSet(e.getV2());

            // 5. 두 정점이 서로 다른 집합이면 사이클이 생기지 않음
            if (uset != vset) {
                cout << "간선 추가 : "
                    << getVertex(e.getV1()) << " - "
                    << getVertex(e.getV2())
                    << " (비용:" << e.getKey() << ")" << endl;

                // 6. 두 집합을 합침
                set.unionSets(uset, vset);

                edgeAccepted++;
                totalCost += e.getKey();
            }

            // uset == vset인 경우:
            // 이미 같은 집합에 있으므로 간선을 추가하면 사이클 발생
            // 따라서 선택하지 않고 다음 간선으로 넘어감
        }

        cout << "MST 총 비용 : " << totalCost << endl;
    }
    void Prim(int s) {
        bool selected[MAX_VTXS]; // 정점이 이미 포함되었는?
        int dist[MAX_VTXS]; // 거리
        for (int i = 0; i < size; i++) { // 배열 초기화
            dist[i] = INF;
            selected[i] = false;
        }
        dist[s] = 0; // 시작 정점
        for (int i = 0; i < size; i++) {
            int u = selected[u] = true;
            if (dist[u] == INF) return;
            printf("%c ", getVertex(u));
            for (int v = 0; v < size; v++)
                if (getEdge(u, v) != INF)
                    if (!selected[v] && getEdge(u, v) < dist[v])
                        dist[v] = getEdge(u, v);
        }
        printf("\n");
        getMinVertex(selected, dist);
    }
    // MST에 포함되지 않은 정점들 중에서
    // MST와의 거리(dist)가 최소인 정점 선택
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
    // Dijkstra알고리즘의 최단 경로 탐색 기능이 추가된 그래프
    class WGraphDijkstra : public WGraph {
    int dist[MAX_VTXS]; bool found[MAX_VTXS]; public:
        // 시작노드로부터의 최단경로 거리
        // 방문한 정점 표시
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
        void printDistance() { // dist 상태를 출력하는 함수
            for (int i = 0; i < size; i++)
                printf("%5d", dist[i]);
            printf("\n");
        }
        // Dijkstra의 최단 경로 알고리즘: start 정점에서 시작함.
        void ShortestPath(int start) {
            for (int i = 0; i < size; i++) {
                dist[i] = getEdge(start, i);
                found[i] = false;
            }
            found[start] = true; dist[start] = 0; for (int i = 0; i < size; i++) {
                printf("Step%2d:", i + 1);
                printDistance();
                int u = chooseVertex();
                found[u] = true;
                for (int w = 0; w < size; w++) {
                    if (found[w] == false)
                        if (dist[u] + getEdge(u, w) < dist[w])
                            dist[w] = dist[u] + getEdge(u, w);
                    // 시작노드 방문 표시
                    // 최초 거리
                }
            }
        }
    };
	// Floyd 알고리즘의 최단 경로 탐색 기능이 추가된 그래프
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
};