#include <cassert>
#include <iostream>

#include "intrusive_list.hpp"

struct Node {
    int value;
    IntrusiveListHook<Node> hook;

    Node(int v) : value(v) {}
};

void test_empty_list() {
    IntrusiveList<Node, &Node::hook> list;
    assert(list.empty());
    assert(list.size() == 0);
}

void test_push_back() {
    IntrusiveList<Node, &Node::hook> list;
    Node node1(1);
    Node node2(2);

    list.push_back(node1);
    assert(list.size() == 1);
    assert(list.begin()->value == 1);

    list.push_back(node2);
    assert(list.size() == 2);
    assert((++list.begin())->value == 2);

    list.clear();
}

void test_push_front() {
    IntrusiveList<Node, &Node::hook> list;
    Node node1(1);
    Node node2(2);

    list.push_front(node1);
    assert(list.size() == 1);
    assert(list.begin()->value == 1);

    list.push_front(node2);
    assert(list.size() == 2);
    assert(list.begin()->value == 2);
    assert((++list.begin())->value == 1);

    list.clear();
}

void test_pop_back() {
    IntrusiveList<Node, &Node::hook> list;
    Node node1(1);
    Node node2(2);

    list.push_back(node1);
    list.push_back(node2);
    list.pop_back();

    assert(list.size() == 1);
    assert(list.begin()->value == 1);

    list.clear();
}

void test_pop_front() {
    IntrusiveList<Node, &Node::hook> list;
    Node node1(1);
    Node node2(2);

    list.push_back(node1);
    list.push_back(node2);
    list.pop_front();

    assert(list.size() == 1);
    assert(list.begin()->value == 2);

    list.clear();
}

void test_insert() {
    IntrusiveList<Node, &Node::hook> list;
    Node node1(1);
    Node node2(2);
    Node node3(3);
    Node node4(4);

    list.insert(list.begin(), node1);
    assert(list.size() == 1);
    assert(list.begin()->value == 1);

    list.insert(list.begin(), node2);
    assert(list.size() == 2);
    assert(list.begin()->value == 2);
    assert((++list.begin())->value == 1);

    list.insert(list.end(), node3);
    assert(list.size() == 3);
    assert((++(++list.begin()))->value == 3);

    list.insert(++list.begin(), node4);
    assert(list.size() == 4);
    assert((++list.begin())->value == 4);
    assert((++(++list.begin()))->value == 1);

    IntrusiveList<Node, &Node::hook> emptyList;
    emptyList.insert(emptyList.begin(), node1);
    assert(emptyList.size() == 1);
    assert(emptyList.begin()->value == 1);

    list.clear();
    emptyList.clear();
}

void test_splice_empty_target() {
    IntrusiveList<Node, &Node::hook> list;
    Node node1(1);
    Node node2(2);

    list.push_back(node1);
    list.push_back(node2);

    IntrusiveList<Node, &Node::hook> otherList;
    otherList.splice(nullptr, list);

    assert(otherList.size() == 2);
    assert((otherList.begin())->value == 1);
    assert((++otherList.begin())->value == 2);

    otherList.clear();
}

void test_splice_single() {
    IntrusiveList<Node, &Node::hook> list;
    Node node1(1);
    list.push_back(node1);

    IntrusiveList<Node, &Node::hook> otherList;
    Node node2(2);
    otherList.push_back(node2);

    list.splice(list.begin(), otherList);

    assert(list.size() == 2);
    assert((++list.begin())->value == 1);

    list.clear();
}

void test_splice_with_single_node() {
    IntrusiveList<Node, &Node::hook> list;
    Node node1(1);
    list.push_back(node1);

    IntrusiveList<Node, &Node::hook> otherList;
    Node node2(2);
    otherList.push_back(node2);

    list.splice(list.end(), otherList);

    assert(list.size() == 2);
    assert((++list.begin())->value == 2);

    list.clear();
}

void test_splice_with_multiple_nodes() {
    IntrusiveList<Node, &Node::hook> list;
    Node node1(1);
    Node node2(2);
    Node node3(3);

    list.push_back(node1);
    list.push_back(node2);
    list.push_back(node3);

    IntrusiveList<Node, &Node::hook> otherList;
    Node node4(4);
    Node node5(5);

    otherList.push_back(node4);
    otherList.push_back(node5);

    list.splice(++list.begin(), otherList);

    assert(list.size() == 5);
    assert(list.begin()->value == 1);
    assert((++list.begin())->value == 4);
    assert((++(++list.begin()))->value == 5);
    assert((++(++(++list.begin())))->value == 2);

    list.clear();
}

void test_clear() {
    IntrusiveList<Node, &Node::hook> list;
    Node node1(1);
    Node node2(2);

    list.push_back(node1);
    list.push_back(node2);

    list.clear();
    assert(list.empty());
    assert(list.size() == 0);
}

void test_back_methods() {
    IntrusiveList<Node, &Node::hook> list;
    Node node1(1);
    Node node2(2);

    list.push_back(node1);
    list.push_back(node2);

    assert(list.back().value == 2);

    const IntrusiveList<Node, &Node::hook> const_list = list;
    assert(const_list.back().value == 2);

    list.clear();
}

int main() {
    test_empty_list();
    test_push_back();
    test_push_front();
    test_pop_back();
    test_pop_front();
    test_insert();
    test_splice_empty_target();
    test_splice_single();
    test_splice_with_single_node();
    test_splice_with_multiple_nodes();
    test_clear();
    test_back_methods();

    return 0;
}
