#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_VTXS 20
#define INF 9999
#include <cstdio>

class AdjMatGraph {
protected:
    int size;
    char vertices[MAX_VTXS];
    int adj[MAX_VTXS][MAX_VTXS];
public:
    AdjMatGraph() { reset(); }
    void reset() {
        size = 0;
        for (int i = 0; i < MAX_VTXS; i++)
            for (int j = 0; j < MAX_VTXS; j++) adj[i][j] = 0;
    }
    char getVertex(int i) { return vertices[i]; }
    int getEdge(int i, int j) { return adj[i][j]; }
    void setEdge(int i, int j, int val) { adj[i][j] = val; }
    void insertVertex(char name) { if (size < MAX_VTXS) vertices[size++] = name; }

    void insertEdge(int u, int v) { setEdge(u, v, 1); setEdge(v, u, 1); }

    void load(const char* filename) {
        FILE* fp = fopen(filename, "r");
        if (fp) {
            int n; fscanf(fp, "%d", &n);
            for (int i = 0; i < n; i++) {
                char str[80]; fscanf(fp, "%s", str);
                insertVertex(str[0]);
                for (int j = 0; j < n; j++) {
                    int val; fscanf(fp, "%d", &val);
                    setEdge(i, j, val);
                }
            }
            fclose(fp);
        }
    }
    void display(FILE* fp = stdout) {
        for (int i = 0; i < size; i++) {
            fprintf(fp, "%c ", getVertex(i));
            for (int j = 0; j < size; j++) fprintf(fp, " %3d", getEdge(i, j));
            fprintf(fp, "\n");
        }
    }
};

class SrchAMGraph : public AdjMatGraph {
    bool visited[MAX_VTXS];
public:
    void resetVisited() { for (int i = 0; i < size; i++) visited[i] = false; }
    bool isLinked(int u, int v) { return getEdge(u, v) != 0; }
    void DFS(int v) {
        visited[v] = true; printf("%c ", getVertex(v));
        for (int w = 0; w < size; w++)
            if (isLinked(v, w) && !visited[w]) DFS(w);
    }
};

class WGraph : public AdjMatGraph {
public:
    void insertEdge(int u, int v, int weight) {
        if (weight > INF) weight = INF;
        setEdge(u, v, weight);
        setEdge(v, u, weight);
    }
    bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }
};

// 가중치 그래프
class WGraph : public AdjMatGraph {
public:
    void insertEdge(int u, int v, int weight) {
        if (weight > INF) weight = INF;
        setEdge(u, v, weight);
    }

    bool hasEdge(int i, int j) {
        return (getEdge(i, j) < INF);
    }

    void load(const char* filename) {
        FILE* fp;
        fopen_s(&fp, filename, "r");
        if (fp != NULL) {
            int n, val;
            fscanf_s(fp, "%d", &n);
            for (int i = 0; i < n; i++) {
                char str[80];
                int val;
                fscanf_s(fp, "%s", str, sizeof(str));
                insertVertex(str[0]);
                for (int j = 0; j < n; j++) {
                    fscanf_s(fp, "%d", &val);
                    insertEdge(i, j, val);
                }
            }
        }
        fclose(fp);
    }
};