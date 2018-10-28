#ifndef DOUBLYCONNECTEDEDGELIST_H
#define DOUBLYCONNECTEDEDGELIST_H

#include <vector>

using namespace std;

// TODO values as pointers??
template <class _nodevaluetype, class _edgevaluetype>
class doubly_linked_graph {
    private:
        vector<Node> nodesList;
        class Node {
            _nodevaluetype value;
            vector<Edge> edges;

            Node(_nodevaluetype value) : value(value), edges(vector<Edge>()) {}
        };
        class Edge {
            _edgevaluetype value;
            pair<Node*, Node*> nodes;

            Edge(Node* node1, Node* node2, _edgevaluetype value) : nodes(pair<Node*, Node*>(node1, node2)), value(value) {}
        };

    public:
        doubly_linked_graph() : nodesList(vector<Node>()) {}

    // TODO public-access object

}
#endif // DOUBLYCONNECTEDEDGELIST_H
