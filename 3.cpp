#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <iostream>
#include <vector>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint textureIDs[6];
bool useTexture = false;
bool isLight = true;
int _width, _height, nrChannels;
unsigned char *data;

GLfloat texCoords[48] = {
    // Верхняя грань 
    0.0f, 0.0f,
     1.0f, 0.0f,
     1.0f, 1.0f,
     0.0f, 1.0f,

    // Нижняя грань
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,

    // Передняя грань
    0.0f, 0.0f,
     1.0f, 0.0f,
     1.0f, 1.0f,
     0.0f, 1.0f,

    // Задняя грань
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,

    // Левая грань
    0.0f, 0.0f,
     1.0f, 0.0f,
     1.0f, 1.0f,
     0.0f, 1.0f,

    // Правая грань
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
};



int width = 800;
int height = 600;


float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;


float cubeSize = 0.2;
float shift = -0.2;
bool isTransparent = false;
GLfloat lightAngle = 0.0;

GLfloat vertices[] = { // Координаты вершин куба
    
    cubeSize, cubeSize, -cubeSize,
    -cubeSize, cubeSize, -cubeSize,
    -cubeSize, cubeSize, cubeSize,
    cubeSize, cubeSize, cubeSize,

    
    cubeSize, -cubeSize, cubeSize,
    -cubeSize, -cubeSize, cubeSize,
    -cubeSize, -cubeSize, -cubeSize,
    cubeSize, -cubeSize, -cubeSize,

    
    cubeSize, cubeSize, cubeSize,
    -cubeSize, cubeSize, cubeSize,
    -cubeSize, -cubeSize, cubeSize,
    cubeSize, -cubeSize, cubeSize,

    
    cubeSize, -cubeSize, -cubeSize,
    -cubeSize, -cubeSize, -cubeSize,
    -cubeSize, cubeSize, -cubeSize,
    cubeSize, cubeSize, -cubeSize,

    
    -cubeSize, cubeSize, cubeSize,
    -cubeSize, cubeSize, -cubeSize,
    -cubeSize, -cubeSize, -cubeSize,
    -cubeSize, -cubeSize, cubeSize,

    
    cubeSize, cubeSize, -cubeSize,
    cubeSize, cubeSize, cubeSize,
    cubeSize, -cubeSize, cubeSize,
    cubeSize, -cubeSize, -cubeSize
};


GLfloat colors[] = { // Цвета граней
    
    1.0f, 0.0f, 0.0f, 1.0f, 
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
 

    0.0f, 1.0f, 0.0f, 1.0f, 
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
 

    0.0f, 0.0f, 1.0f, 1.0f, 
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
 

    1.0f, 1.0f, 0.0f, 1.0f, 
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
 

    1.0f, 0.0f, 1.0f, 1.0f, 
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
 
    
    0.0f, 1.0f, 1.0f, 1.0f, 
    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f
};

GLfloat normals[] = { // Нормали - для задания освещения
    0.0, 1.0, 0.0,    0.0, 1.0, 0.0,    0.0, 1.0, 0.0,    0.0, 1.0, 0.0,  
    0.0, -1.0, 0.0,   0.0, -1.0, 0.0,   0.0, -1.0, 0.0,   0.0, -1.0, 0.0, 
    0.0, 0.0, 1.0,    0.0, 0.0, 1.0,    0.0, 0.0, 1.0,    0.0, 0.0, 1.0,  
    0.0, 0.0, -1.0,   0.0, 0.0, -1.0,   0.0, 0.0, -1.0,   0.0, 0.0, -1.0, 
    -1.0, 0.0, 0.0,   -1.0, 0.0, 0.0,   -1.0, 0.0, 0.0,   -1.0, 0.0, 0.0, 
    1.0, 0.0, 0.0,    1.0, 0.0, 0.0,    1.0, 0.0, 0.0,    1.0, 0.0, 0.0   
};

std::vector<bool> keyStates(256, false); // Для плавности обработки клавиш

void expandCube() { // Раздвижение куба
    vertices[1] += shift;
    vertices[4] += shift;
    vertices[7] += shift;
    vertices[10] += shift;

    // Нижняя грань
    vertices[13] -= shift;
    vertices[16] -= shift;
    vertices[19] -= shift;
    vertices[22] -= shift;

    // Передняя грань
    vertices[26] += shift;
    vertices[29] += shift;
    vertices[32] += shift;
    vertices[35] += shift;

    // // Задняя грань
    vertices[38] -= shift;
    vertices[41] -= shift;
    vertices[44] -= shift;
    vertices[47] -= shift;

    // Левая грань
    vertices[48] -= shift;
    vertices[51] -= shift;
    vertices[54] -= shift;
    vertices[57] -= shift;

    // // Правая грань
    vertices[60] += shift;
    vertices[63] += shift;
    vertices[66] += shift;
    vertices[69] += shift;
}

GLuint loadTexture(const char *filename) {
    GLuint textureID;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    //Устанавливаем параметры фильтрации и перехвата текстур
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *data = stbi_load(filename, &_width, &_height, &nrChannels, 0);
    std::cout << nrChannels << std::endl;
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        // gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }
    // glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
    stbi_image_free(data);

    return textureID;
}

void doTexture() {
    useTexture = !useTexture;
    glutPostRedisplay();
}


void doTransparency() {
    isTransparent = !isTransparent;

    for (int i = 0; i < 96; i += 4) {
        if (isTransparent) {
            colors[i + 3] = 0.5f;
        } else {
            colors[i + 3] = 1.0f;
        }
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    keyStates[key] = true; 
    if (key == 32) {
        if (shift > 0) {
            shift = -0.2;
        }
        else {
            shift = 0.2;
        }
        expandCube(); 
    }
    else if (key == 27) { // Esc
        exit(0);
    }
    else if (key == 't') { // t
        doTransparency();
    }
    else if (key == 'b') { // b
        doTexture();
    }
    else if (key == 'l') {
        isLight = !isLight;
    }
}


void keyboardUp(unsigned char key, int x, int y) {
    keyStates[key] = false; 
}


void updateLight() {
    lightAngle += 0.01;
    if (lightAngle > 360.0) {
        lightAngle -= 360.0;
    }

    GLfloat lightX = cos(lightAngle);
    GLfloat lightZ = sin(lightAngle);
    GLfloat lightY = 0.0;

    GLfloat lightPosition[] = {lightX, lightY, lightZ, 1.0}; // Последний параметр - 1.0 для точечного источника света
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glPushMatrix(); // Для того, чтобы не менять все объекты на сцене
    glDisable(GL_LIGHTING);
    glTranslatef(lightX, lightY, lightZ);
    glColor3f(1.0, 1.0, 0.0);
    glutSolidSphere(0.1, 20, 20);
    glEnable(GL_LIGHTING);
    if (isLight) {
        GLfloat lightDiffuse[] = {1.0, 1.0, 1.0, 1.0}; // Полная интенсивность
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    } else {
        GLfloat lightDiffuse[] = {0.0, 0.0, 0.0, 1.0}; // Нулевая интенсивность
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    }
    glPopMatrix();
}

void drawOrbit() {
    glColor3f(1.0, 1.0, 1.0); 
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float theta = 2.0 * 3.14159 * float(i) / 360.0;
        float x = 1.0 * cosf(theta);
        float z = 1.0 * sinf(theta);
        glVertex3f(x, 0.0, z); 
    }
    glEnd();
}


void display() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 3.0f,  
              0.0f, 0.0f, 0.0f,  
              0.0f, 1.0f, 0.0f); 

    

    if(keyStates['a']) {
        angleY -= 2.5f;
    }
    if(keyStates['d']) {
        angleY += 2.5f;
    }
    if(keyStates['w']) {
        angleX += 2.5f;
    }
    if(keyStates['s']) {
        angleX -= 2.5f;
    }
    if(keyStates['i']) {
        angleZ += 2.5f;
    }
    if(keyStates['j']) {
        angleZ -= 2.5f;
    }
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    updateLight();
    drawOrbit();
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);

    if (!useTexture) {
        glDisable(GL_TEXTURE_2D);
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_FLOAT, 0, colors);
    }
    else {
        glEnable(GL_TEXTURE_2D);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        if (isTransparent) {
            glEnableClientState(GL_COLOR_ARRAY);
            GLfloat c[96];
            for (int i = 0; i < 24; ++i) {
                c[4*i] = 1.0f;
                c[1+4*i] = 1.0f;
                c[2+4*i] = 1.0f;
                c[3+4*i] = 0.5f;
                
            }
            glColorPointer(4, GL_FLOAT, 0, c);
        }
    }

    // Рисуем грани куба
    for (int i = 0; i < 6; i++) {
        if (useTexture) {
            glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
            glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
        }

        glDrawArrays(GL_POLYGON, i * 4, 4);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisable(GL_TEXTURE_2D);



    
    glutSwapBuffers();
}


void reshape(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}


void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); 
}

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(350, 100);
    glutCreateWindow("3D Cube");

    
    glEnable(GL_DEPTH_TEST);

    // Включаем освещение
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Включаем смешивание
    glEnable(GL_BLEND);

    // Устанавливаем функцию смешивания
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLfloat lightAmbient[] = {0.2, 0.2, 0.2, 1.0}; // Включаем ambient - для увелечения яркости неосвещенных граней
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

    glEnable(GL_COLOR_MATERIAL); // Включаем цвет материалов - для отображения цвета неосвещенных граней
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // Включаем двусторонее освещение - для освещения куба изнутри

    // Устанавливаем цвет источника света (белый)
    GLfloat lightColor[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);

    textureIDs[0] = loadTexture("1.jpeg");
    textureIDs[1] = loadTexture("2.jpeg");
    textureIDs[2] = loadTexture("3.jpeg");
    textureIDs[3] = loadTexture("4.jpeg");
    textureIDs[4] = loadTexture("5.jpeg");
    textureIDs[5] = loadTexture("6.jpeg");

    // Включаем нормализацию нормалей
    glEnable(GL_NORMALIZE);

    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutTimerFunc(0, timer, 0);

    
    glutMainLoop();

    return 0;
}