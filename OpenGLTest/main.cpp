//
//  main.cpp
//  OpenGLTest
//
//  Created by Max Czapanskiy on 1/8/14.
//  Copyright (c) 2014 Max Czapanskiy. All rights reserved.
//
// https://developer.apple.com/library/mac/qa/qa1613/_index.html

#include <iostream>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "utils.h"
#include "Angel.h"

const int NumPoints = 100000;

void init()
{
    point3 points[NumPoints];
    
    // A triangle in the plane z = 0
    point3 vertices[3] = {point3(-1.0,-1.0,0.0),point3(0.0,1.0,0.0),point3(1.0,-1.0,0.0)};
    
    // Arbitrary initial point inside the triangle
    points[0] = rand_point_in_triangle(vertices[0], vertices[1], vertices[2]);
    
    // Compute and store NumPoints-1 new points
    for(int k = 1; k < NumPoints; k++)
    {
        int j = rand() % 3; // pick a vertex at random
        
        //Compute the point halfway btw selected vertex and previous point
        points[k] = (points[k-1]+vertices[j])/2.0;
    }
    
    // Create a vertex array object
    GLuint vao[1];
    glGenVertexArraysAPPLE(1, vao);
    glBindVertexArrayAPPLE(vao[0]);
    
    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    
    // Load shaders and use the resulting shader program
    GLuint program = InitShader("/Users/maxczapanskiy/Projects/CSE457/OpenGLTest/OpenGLTest/vshader21.glsl", "/Users/maxczapanskiy/Projects/CSE457/OpenGLTest/OpenGLTest/fshader21.glsl");
    glUseProgram(program);
    
    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    
    glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // clear the window
    glDrawArrays(GL_POINTS, 0, NumPoints);
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 033:
            exit(EXIT_SUCCESS);
            break;
    }
}

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(512, 512);
    
    glutCreateWindow("Sierpinski Gasket");
    
    init();
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}