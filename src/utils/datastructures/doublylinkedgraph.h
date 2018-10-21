#ifndef DOUBLYCONNECTEDEDGELIST_H
#define DOUBLYCONNECTEDEDGELIST_H

#include <vector>

using namespace std;

// TODO values as pointers??
template <class _nodevaluetype, class _edgevaluetype> class doubly_linked_graph {
    private:
        struct edge;
        struct node {
            vector<pair<edge, int>> edges;
            _nodevaluetype nodeValue;

            node(_nodevaluetype nodeValue) : nodeValue(nodeValue), edges(vector<pair<edge, int>>()) {}

            void addEdge(edge newEdge, int edgeIndex){
                edges.push_back(make_pair<edge, int>(newEdge, edgeIndex));
            }
        };
        struct edge {
            pair<node, node> nodes;
            _edgevaluetype edgeValue;

            edge(node node1, node node2, _edgevaluetype edgeValue) : edgeValue(edgeValue){
                this->nodes = make_pair<node, node>(node1, node2);
            }
        };
        node root;

    public:
        doubly_linked_graph(_nodevaluetype nodeValue) : root(node(nodeValue)) {}

        void add_node(node targetNode, _nodevaluetype nodeValue, _edgevaluetype edgeValue) {
            auto newNode = node(nodeValue);
            const auto& newEdge = edge(targetNode, newNode, edgeValue);
            targetNode.addEdge(newEdge, 0);
            newNode.addEdge(newEdge, 1);
        }

    // TODO public-access object

}
#endif // DOUBLYCONNECTEDEDGELIST_H
