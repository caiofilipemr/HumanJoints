#include "../header/Node.h"
#include "../header/RotationTransformation.h"

#define AREA_SIZE 1

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

std::vector<Node *> Node::getVectorPath() {
    int indexOfFirstChildSelected = -1;
    for (int i = 0; i < children.size() && indexOfFirstChildSelected < 0; ++i) {
        if (children[i]->isSelected()) {
            indexOfFirstChildSelected = i;
        }
    }
    return getVectorPath(indexOfFirstChildSelected);
}

std::vector<Node *> Node::getVectorPath(int indexOfFirstChildToGo) {
    std::vector<Node*> nodes;
    nodes.push_back(this);
    nodes.push_back(children[indexOfFirstChildToGo]);
    getAllDescendent(children[indexOfFirstChildToGo], nodes);
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

bool Node::verifyCollision(float &x, float &y) {
    for (auto node : children) {
        if (hasCollision(x, y, this, node)) {
            return (this->selected = node->selected = true);
        }

        if (node->verifyCollision(x, y)) {
            return true;
        }
    }
    return false;
}

bool Node::hasCollision(float &x, float &y, Node *parent, Node *child) {
    auto area = getCollisionArea(parent->coordinate, child->coordinate);
    return x >= smallerX(area)
        && x <= biggerX(area)
        && y >= smallerY(area)
        && y <= biggerY(area);
}

std::vector<Coordinate> Node::getCollisionArea(Coordinate p1, Coordinate p2) {
    std::vector<Coordinate> area;
    Coordinate point = getPoint(p1, p2, 90);
    area.push_back(point);
    point = getPoint(p2, p1, 90);
    area.push_back(point);
    return area;
}

Coordinate Node::getPoint(Coordinate &p1, Coordinate &p2, float degree) const {
    std::vector<Coordinate> line;
    line.push_back(p1.clone());
    line.push_back(p2.clone());

    RotationTransformation rt(0, 0, degree);
    line = rt.transform(line);

    float d = sqrtf(powf(line[1].x - line[0].x, 2) + powf(line[1].y - line[0].y, 2));
    float r = AREA_SIZE / d;

    Coordinate point;
    point.x = r * line[1].x + (1 - r) * line[0].x;
    point.y = r * line[1].y + (1 - r) * line[0].y;
    return point;
}

float Node::smallerX(std::vector<Coordinate> area) {
    return area[0].x < area[1].x ? area[0].x : area[1].x;
}

float Node::biggerX(std::vector<Coordinate> area) {
    return area[0].x > area[1].x ? area[0].x : area[1].x;
}

float Node::smallerY(std::vector<Coordinate> area) {
    return area[0].y < area[1].y ? area[0].y : area[1].y;
}

float Node::biggerY(std::vector<Coordinate> area) {
    return area[0].y > area[1].y ? area[0].y : area[1].y;
}

void Node::deselectedAll() {
    this->selected = false;
    for (auto child : children) {
        child->deselectedAll();
    }
}

Node *Node::getSelectedIfAny() {
    if (selected)
        return this;

    for (auto child : children) {
        if (Node *selected = child->getSelectedIfAny()) {
            return selected;
        }
    }
    return nullptr;
}
