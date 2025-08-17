// Сделать через массив вершин
#include <iostream>
#include <cmath>
#include <GL/freeglut.h>
#include <vector>
#define SEGMENTS 360
#define TRAJECTORY_RADIUS 2

int windowWidth = 500;
int windowHeight = 500;

int cur_t = 5;
bool isSun = true;
int sunSpeedCoef = 5;
std::vector<float> skyColor = {0.0, 0.0, 0.8};
std::vector<float> sunColor = {1, 1, 0};

std::pair<float, float> getCurCoordOfSun() {
    float teta = cur_t*3.14 * sunSpeedCoef / 360;
    return {1.1*std::cos(teta), 0.9*std::sin(teta)};
}

void drawFigure(int figureNum, unsigned long figure, std::vector<float> color, std::vector<std::pair<float, float>> coordinates) {
    GLfloat quadVertexArray[figureNum][2];
    GLfloat quadColorArray[figureNum][3];
    for (int i = 0; i < figureNum; ++i) {
        quadVertexArray[i][0] = coordinates[i].first;
        quadVertexArray[i][1] = coordinates[i].second;
        quadColorArray[i][0] = color[0];
        quadColorArray[i][1] = color[1];
        quadColorArray[i][2] = color[2];
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, quadVertexArray);
    glColorPointer(3, GL_FLOAT, 0, quadColorArray);
    glDrawArrays(figure, 0, figureNum);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void drawCircle(std::vector<float> color, float centerX, float centerY, float radius, int segments) {
    std::vector<std::pair<float, float>> circleVertices(segments);
    for (int i = 0; i < segments; ++i) {
        float theta = 2.0f * 3.14 * float(i) / float(segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        circleVertices[i] = {centerX + x, centerY + y};
    }
    drawFigure(segments, GL_POLYGON, color, circleVertices);
}

void display() {
    std::pair<float, float> curCoordOfSun = getCurCoordOfSun();
    if (curCoordOfSun.second < 0) {
        if (isSun) {
            skyColor = {0.0, 0, 0.3};
            sunColor = {1, 1, 1};
            isSun = false;
        }
        else {
            skyColor = {0.0, 0.0, 0.8};
            sunColor = {1, 1, 0};
            isSun = true;
        }
        cur_t = 5;
    }
    std::cout << skyColor[0];
    drawFigure(4, GL_QUADS, {skyColor[0], skyColor[1], skyColor[2]}, {{-1, 0}, {1, 0}, {1, 1}, {-1, 1}});
    drawFigure(4, GL_QUADS, {0.0, 0.8, 0.0}, {{-1, 0}, {1, 0}, {1, -1}, {-1, -1}});
    drawFigure(4, GL_QUADS, {0.7, 0.3, 0}, {{-0.125, 0}, {0.125, 0}, {0.125, 0.25}, {-0.125, 0.25}});
    drawFigure(3, GL_TRIANGLES, {0.7, 0.7, 0}, {{-0.15, 0.25}, {0, 0.4}, {0.15, 0.25}});
    drawFigure(3, GL_TRIANGLES, {0, 0.6, 0}, {{-0.85, 0.40}, {-0.7, 0.50}, {-0.55, 0.40}});
    drawFigure(3, GL_TRIANGLES, {0, 0.6, 0}, {{-0.85, 0.35}, {-0.7, 0.45}, {-0.55, 0.35}});
    drawFigure(4, GL_QUADS, {0.6, 0.3, 0}, {{-0.73, 0}, {-0.67, 0}, {-0.67, 0.35}, {-0.73, 0.35}});
    drawFigure(3, GL_TRIANGLES, {0, 0.6, 0}, {{0.75, 0.50}, {0.6, 0.60}, {0.45, 0.50}});
    drawFigure(3, GL_TRIANGLES, {0, 0.6, 0}, {{0.75, 0.45}, {0.6, 0.55}, {0.45, 0.45}});
    drawFigure(4, GL_QUADS, {0.6, 0.3, 0}, {{0.63, 0}, {0.57, 0}, {0.57, 0.45}, {0.63, 0.45}});
    drawCircle({sunColor[0], sunColor[1], sunColor[2]}, curCoordOfSun.first, curCoordOfSun.second, 0.1, 190);
    glutSwapBuffers();
    glFlush();
}

void timer(int value) {
    cur_t++;
    glutPostRedisplay();
    glutTimerFunc(32, timer, 0);
}

void reshape(int w, int h) {
    glutReshapeWindow(windowWidth, windowHeight);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(500, 120);
    glutCreateWindow("Sun Animation");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}