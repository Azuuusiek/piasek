#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <GL/gl.h>
#include "Libs/noise/noise.h"
#include "Libs/noise/module/module.h"
#include "Libs/noise/module/perlin.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
float map(float v, float x1, float y1, float x2, float y2) {
    return x2 + (y2 - x2) * ((v - x1) / (y1 - x1));
}
const int WIDTH = 800;
const int HEIGHT = 600;
const int scl = 2;
float x = WIDTH / 2;
float y = HEIGHT / 2;
int arr2[400][401];
int w = 400;
int h = 300;
//bool arr[400][401];
std::pair<bool, std::pair<float, std::pair<float, float> > > arr[400][401];
int main() {

    if (!glfwInit()) {
        return -1;
    }
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "con", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glViewport(0, 0, WIDTH, HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, 0, HEIGHT, -700, 400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glPointSize(4);
    int z = 0;
    int o = 0;
    float p = 0;
    float d = 0.05;
    while (!glfwWindowShouldClose(window)) {

      //  noise::module::Perlin perlin = noise::module::Perlin::Perlin();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE_LOOP);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        z++;
        o++;
        p += d;
        if (p <= 0) {
            p = 0.01;
            d *= -1;
        }
        if (p >= 200) {
            p = 99;
            d *= -1;
        }
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
               

                glPointSize(2);
                if (arr[i][j].first) {
                   
                 //   float c = e % 100;
                    
                   // e /= 100;
                   // float c2 = e % 100;
                    //e /= 100;
                    //float c3 = e % 100;
                    //std::cout << c << " " << c2 << " " << c3 << '\n';
                    glColor3f(0.96f, 0.87f, 0.70f);
                    //float c= arr[i][j].second.first;
                 //   glColor3f(c/100, c2/100, c3/100);
                    glColor3f(arr[i][j].second.first, arr[i][j].second.second.first, arr[i][j].second.second.second);
                    glBegin(GL_POINTS);
                    glVertex2f(i * scl, j * scl);
                    glEnd();
                }
            }
        }


        //    if (o > 30) {    
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int x = floor(xpos / scl);
        int y = floor((HEIGHT - ypos) / scl);

        if (xpos >= 0 && xpos < WIDTH && ypos >= 0 && ypos < HEIGHT && !arr[x][y].first) {
            float c1 = map(p, 0,400, 0.7, 1);
            float c2 = map(p, 0, 600, 0.9, 0.6);
            float c3 = map(p, 0, 200, 0.2, 0.66);
            arr[x][y] = { true,{c1,{c2,c3}} };
         //   float c3 = 1;// map(p, 0, 10, 0.5, 0.75);
           // arr[x][y] = { true,{c,{c2,c3}} };
        //    std::cout << arr[x][y].second.first << " " << arr[x][y].second.second.first << " " << arr[x][y].second.second.second << '\n';
        }
        o = 0;
        //  }
      //    if (z > 10) {
        z = 0;
        for (int j = 1; j < h; j++) {
            for (int i = 0; i < w; i++) {

                if (arr[i][j].first && !arr[i][j - 1].first) {
                    arr[i][j - 1] = arr[i][j];
                    arr[i][j].first = false;
                }
                else {
                    if (arr[i][j].first && i > 0 && i < w - 1) {
                        if (!arr[i + 1][j - 1].first || !arr[i - 1][j - 1].first) {
                            if (!arr[i + 1][j - 1].first && !arr[i - 1][j - 1].first) {
                                int k = rand() % 420;
                                if (k % 2 == 0) {
                                    arr[i + 1][j - 1] = arr[i][j];
                                }
                                else {
                                    arr[i - 1][j - 1] = arr[i][j];
                                }
                                arr[i][j].first = false;

                            }
                            else {
                                if (!arr[i + 1][j - 1].first) {
                                    arr[i + 1][j - 1] = arr[i][j];
                                }
                                else {
                                    arr[i - 1][j - 1] = arr[i][j];
                                }
                                arr[i][j].first = false;
                            }
                        }
                    }
                    else {
                        if (arr[i][j].first && i == 0) {
                            if (arr[i][j - 1].first && !arr[i + 1][j - 1].first) {
                                arr[i + 1][j - 1] = arr[i][j];
                                arr[i][j].first = false;
                                
                            }
                        }
                        else {
                            if (arr[i][j].first && i == w - 1) {
                                if (arr[i][j - 1].first && !arr[i - 1][j - 1].first) {
                                    arr[i - 1][j - 1] = arr[i][j];
                                    arr[i][j].first = false;
                                    
                                }
                            }
                        }
                    }
                }
            }


        }

        // }

        glPointSize(3.0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}