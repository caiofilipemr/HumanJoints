#include <GL/glut.h>
#include "header/Node.h"

#define ORTHO_SIZE 50
#define JOINT_SIZE 2.f

GLfloat xRotation;
GLfloat yRotation;
GLfloat zRotation;
GLfloat lightPosition[] = {-25.f, 0.f, 50.f, 1.f};

Node *root;

void drawHuman(Node *pNode);

void createRoot();

void createHead(Node *root);

void createArms(Node *root);

void createLeftArm(Node *root);

void createRightArm(Node *root);

void drawJoint(Coordinate coordinate);

void createLegs(Node *root);

void createLeftLeg(Node *root);

void createRightLeg(Node *root);

void clearBuffers() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void setViewAngle() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(xRotation, 1, 0, 0);
    glRotatef(yRotation, 0, 1, 0);
    glRotatef(zRotation, 0, 0, 1);
}

void draw() {
    clearBuffers();
    setViewAngle();
    drawHuman(root);
    glutSwapBuffers();
}

void drawHuman(Node *root) {
    for (auto node : root->getChildren()) {
        drawHuman(node);
    }
    drawJoint(root->getCoordinate());
}

void drawJoint(Coordinate c) {
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glTranslatef(c.x, c.y, c.z);
    glutSolidSphere(JOINT_SIZE, 40, 40);
    glPopMatrix();
}

void definePerspective() {
    glMatrixMode(GL_PROJECTION);
    glOrtho(-ORTHO_SIZE, ORTHO_SIZE, -ORTHO_SIZE, ORTHO_SIZE, -ORTHO_SIZE, ORTHO_SIZE);
    glMatrixMode(GL_MODELVIEW);
}

void mouseClick(int button, int state, int x, int y) {
}

void mouseMove(int x, int y) {
}

void keyboardKeys(unsigned char key, int, int) {
    switch (key) {

    }
    glutPostRedisplay();
}

void keyboardSpecialKeys(int key, int, int) {
    switch (key) {

    }
    glutPostRedisplay();
}

void defineCallbacks() {
    glutDisplayFunc(draw);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);
    glutKeyboardFunc(keyboardKeys);
    glutSpecialFunc(keyboardSpecialKeys);
}

void defineWindowConfiguration() {
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_STENCIL | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("CSG OpenGL");
    glClearColor(1, 1, 1, 0);
}

void defineLightConfiguration() {
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);
}

void createTree() {
    createRoot();
    createHead(root->getChildren()[0]);
    createArms(root->getChildren()[0]);
    createLegs(root);
}

void createRoot() {
    root = new Node(Coordinate(0, 0, 0));
    root->appendChild(new Node(Coordinate(0, 10*JOINT_SIZE, 0)));
    root->appendChild(new Node(Coordinate(-3*JOINT_SIZE, -2*JOINT_SIZE, 0)));
    root->appendChild(new Node(Coordinate(3*JOINT_SIZE, -2*JOINT_SIZE, 0)));
}

void createHead(Node *root) {
    root->appendChild(new Node(Coordinate(0, 15*JOINT_SIZE, 0)));
}

void createArms(Node *root) {
    createLeftArm(root);
    createRightArm(root);
}

void createLeftArm(Node *root) {
    Node *hand = new Node(Coordinate(-10*JOINT_SIZE, 10*JOINT_SIZE, 0));
    Node *elbow = new Node(Coordinate(-5*JOINT_SIZE, 10*JOINT_SIZE, 0));
    elbow->appendChild(hand);
    root->appendChild(elbow);
}

void createRightArm(Node *root) {
    Node *hand = new Node(Coordinate(10*JOINT_SIZE, 10*JOINT_SIZE, 0));
    Node *elbow = new Node(Coordinate(5*JOINT_SIZE, 10*JOINT_SIZE, 0));
    elbow->appendChild(hand);
    root->appendChild(elbow);
}

void createLegs(Node *root) {
    createLeftLeg(root->getChildren()[1]);
    createRightLeg(root->getChildren()[2]);
}

void createLeftLeg(Node *root) {
    Node *finger = new Node(Coordinate(-5*JOINT_SIZE, -14*JOINT_SIZE, -2*JOINT_SIZE));
    Node *ankle = new Node(Coordinate(-3*JOINT_SIZE, -12*JOINT_SIZE, 0*JOINT_SIZE));
    Node *knee = new Node(Coordinate(-3*JOINT_SIZE, -7*JOINT_SIZE, 0*JOINT_SIZE));
    ankle->appendChild(finger);
    knee->appendChild(ankle);
    root->appendChild(knee);
}

void createRightLeg(Node *root) {
    Node *finger = new Node(Coordinate(1*JOINT_SIZE, -14*JOINT_SIZE, -2*JOINT_SIZE));
    Node *ankle = new Node(Coordinate(3*JOINT_SIZE, -12*JOINT_SIZE, 0*JOINT_SIZE));
    Node *knee = new Node(Coordinate(3*JOINT_SIZE, -7*JOINT_SIZE, 0*JOINT_SIZE));
    ankle->appendChild(finger);
    knee->appendChild(ankle);
    root->appendChild(knee);
}

void init() {
    defineWindowConfiguration();
    definePerspective();
    defineCallbacks();
    defineLightConfiguration();
    createTree();
    glutMainLoop();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    init();
    return 0;
}
