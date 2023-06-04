#ifndef DIJKSTRA_CIRCULARARRAY_H
#define DIJKSTRA_CIRCULARARRAY_H
#include <list>
#include <vector>

struct Node {
    Node* next;
    int key;
    Node() : next(nullptr) {}
    ~Node() {
        next = nullptr;
    }
};

class List {
    Node* head;
    void clear(Node*);
    int size;
public:
    List() : head(nullptr), size(0) {}
    int get_front();
    void push_front(int element);
    bool empty();
    void remove_front();
    ~List();
    int get_size();
};

class CircularArray {
    std::vector<List> array;
    int size;
public:
    int get_element(int key);
    void set_element(int element, int key);
    CircularArray() = default;
    explicit CircularArray(int _size);
    ~CircularArray();
    void delete_element(int key);
    int get_size();
    int get_ful_size();
    bool empty(int key);
};

#endif //DIJKSTRA_CIRCULARARRAY_H