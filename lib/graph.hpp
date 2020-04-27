#include <iostream>
#include "linkedlist.hpp"

namespace utstl
{
class Graph
{
private:
    int vertices;

    LinkedList<int> *array;

public:
    explicit Graph(int vertices) : vertices{vertices}
    {
        array = new LinkedList<int>[vertices];
    }

    void addEdge(int source, int destination)
    {
        if (source < vertices && destination < vertices)
            array[source].insert(destination);
    }

    void print()
    {
        std::cout << "Adjacency List for the graph:\n";
        for (auto i = 0; i < vertices; ++i)
        {
            std::cout << "|" << i << "| => ";
            array[i].forEach([](int data) { std::cout << data << " -> "; });
            std::cout << "NULL\n";
        }
    }

    LinkedList<int> *getArray() { return array; }

    int getVertices() { return vertices; }

    ~Graph()
    {
        delete[] array;
    }
};
} // namespace utstl