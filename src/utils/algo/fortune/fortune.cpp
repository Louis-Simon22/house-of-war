#include "fortune.h"
#include <QDebug>
#include "../../datastructures/binarytree.h"
#include "../../datastructures/doublylinkedgraph.h"

Fortune::Fortune(QVector<QVector2D> points)
{
    this->points = points;
}

QVector<QPolygonF> Fortune::sweep()
{
    const auto& cmp = [](QVector2D left, QVector2D right) { return left.x() > right.x(); };
    auto eventsQueue = priority_queue<QVector2D, vector<QVector2D>, decltype(cmp)>(cmp, vector<QVector2D>());
    auto binaryTree = binary_tree<QVector2D, decltype(cmp)>(cmp);
    auto doublyLinkedGraph = doubly_linked_graph<QVector2D, float>(this->points[0]);
    auto beachline = QLinkedList<QVector2D>();

    for(long i = 1; i < this->points.size(); i++)
    {
        doublyLinkedGraph.add_node(this->points[i]);
    }

    return QVector<QPolygonF>();
}

