#include <iostream>
#include "linkedlist.hpp"

namespace utstl
{
class Graph
{
private:
    int vertices;

    utstl::LinkedList<int> *array;

public:
    explicit Graph(int vertices) : vertices{vertices}
    {
        array = new utstl::LinkedList<int>[vertices];
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

    ~Graph()
    {
        delete[] array;
    }
};
} // namespace utstl