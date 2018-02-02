#include <iostream>
#include <unordered_map>
#include <unordered_set>

class Edge;
class Vertex {
    public:
        Vertex(const std::string& tmpName) : name(tmpName) {}
        bool addNeighbor(Vertex& vertex, Edge& edge) {
            if(isConnectedTo(vertex)) return false;
            connectedVertices.insert(&vertex);
            connectedEdges.insert(&edge);
            return true;
        }
        bool isConnectedTo(Vertex& v) { return connectedVertices.find(&v) != connectedVertices.end(); }
        std::string getName() { return name; }
    private:
        const std::string name;
        std::unordered_set<Vertex*> connectedVertices;
        std::unordered_set<Edge*> connectedEdges;
};
class Edge {
    public:
        Edge(Vertex& v1, Vertex& v2, int w = 1) : vPtr1(&v1), vPtr2(&v2), weight(w) {}
        void setWeight(int w) { weight = w; }
        int getWeight() { return weight; }
        Vertex* getEndVertex1() { return vPtr1; }
        Vertex* getEndVertex2() { return vPtr2; }
    private:
        int weight;
        Vertex* vPtr1;
        Vertex* vPtr2;
};
class Graph {
    public:
        bool addEdge(Vertex& v1, Vertex& v2) {
            if(v1.isConnectedTo(v2) || v2.isConnectedTo(v1)) return false;
            Edge* edge = new Edge(v1, v2);
            v1.addNeighbor(v2, *edge);
            v2.addNeighbor(v1, *edge);
            edges.insert(edge);
            return true;
        }
        bool addVertex(const std::string& name) {
            if(vertices.find(name) != vertices.end()) return false;
            vertices.insert({name, new Vertex(name)});
            return true;
        }
    private:
        std::unordered_map<std::string, Vertex*> vertices;
        std::unordered_set<Edge*> edges;
};
