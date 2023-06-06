#include <list>
#include <vector>
#include "CircularArray.h"

int List::get_front() {
    return head->key;
}

void List::push_front(int element) {
    if (head != nullptr) {
        auto head_cp = head;
        head = new Node();
        head->next = head_cp;
        head->key = element;
    } else {
        head = new Node();
        head->key = element;
    }
    size++;
}

bool List::empty() {
    return head == nullptr;
}

void List::remove_front() {
    if (head) {
        auto tmp = head;
        head = head->next;
        tmp->next = nullptr;
        delete tmp;
        size--;
    }
}

List::~List() {
    clear(head);
}

void List::clear(Node* node) {
    if (node == nullptr) return;
    if (node->next == nullptr) {
        delete node;
    } else {
        clear(node->next);
    }
}

int List::get_size() {
    return size;
}

void List::remove_element(int element) {
    if (!head) {
        return;
    }
    if (!head->next) {
        remove_front();
        return;
    }
    if (head->key == element) {
        remove_front();
        return;
    }
    auto tmp = head;
    Node* prev;
    while (tmp->next and tmp->key != element) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp->next) {
        prev->next = tmp->next;
        delete tmp;
        size--;
    }
}

CircularArray::CircularArray(int _size) : size(_size) {
    array = std::vector<List>(_size, List());
}

void CircularArray::set_element(int element, int key) {
    array[key%size].push_front(element);
}

int CircularArray::get_element(int key) {
    return array[key%size].get_front();
}

CircularArray::~CircularArray() {
}

void CircularArray::delete_element(int key, int element) {
    array[key%size].remove_element(element);
}

int CircularArray::get_size() {
    return size;
}

bool CircularArray::empty(int key) {
    return array[key%size].empty();
}

int CircularArray::get_ful_size() {
    int sum_size = 0;
    for (int i = 0; i < size; i++) {
        sum_size += array[i].get_size();
    }
    return sum_size;
}

int CircularArray::get_bucket_size(int key) {
    return array[key].get_size();
}