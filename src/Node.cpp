#include "../header/Node.h"
#include <cmath>

Node::Node() : coordinate(Coordinate()), selected(false) {

}

Node::Node(Coordinate c) : coordinate(c), selected(false) {

}

Coordinate& Node::getCoordinate() {
    return coordinate;
}

std::vector<Node *> Node::getChildren() const {
    return children;
}

void Node::setCoordinate(Coordinate coordinate) {
    this->coordinate = coordinate;
}

void Node::appendChild(Node *node) {
    this->children.push_back(node);
}

std::vector<Node *> Node::getVectorPath(int indexOffirstChildToGo) {
    std::vector<Node*> nodes;
    nodes.push_back(this);
    nodes.push_back(children[indexOffirstChildToGo]);
    getAllDescendent(children[indexOffirstChildToGo], nodes);
    return nodes;
}

void Node::getAllDescendent(Node *parent, std::vector<Node*> &nodes) {
    for (auto node : parent->children) {
        nodes.push_back(node);
        getAllDescendent(node, nodes);
    }
}

bool Node::isSelected() {
    return selected;
}

void Node::verifyCollision(float x, float y) {
    for (auto node : children) {
        verifyCollision(x, y, this, node);
        node->verifyCollision(x, y);
    }
}

void Node::verifyCollision(float x, float y, Node *parent, Node *child) {
    Coordinate p2 = normalizedPoint(parent->getCoordinate(), child->getCoordinate());
    float p1ToP2 = pointLength(parent->getCoordinate(), child->getCoordinate());
    float p1ToP3 = pointLength(parent->getCoordinate(), child->getCoordinate());
    float p2ToP3 = pointLength(p2, child->getCoordinate());
    acosf((p1ToP2 * p1ToP2 + p1ToP3 * p1ToP3 - p2ToP3 * p2ToP3) / (2 * p1ToP2 * p1ToP3));
}

Coordinate Node::normalizedPoint(Coordinate &cParent, Coordinate &cChild) {
    return Coordinate(cChild.x, cParent.y, cChild.z);
}

float Node::pointLength(Coordinate &p1, Coordinate &p2) {
    float n1 = (p1.x - p2.x);
    float n2 = (p1.y - p2.y);
    return sqrtf(n1 * n1 + n2 * n2);
}
