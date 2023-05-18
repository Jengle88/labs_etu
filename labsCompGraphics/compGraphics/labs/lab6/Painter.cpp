//
// Created by evgeny on 18.05.23.
//

#include "Painter.h"


void Painter::wheel(double a, double b, double c) {
    glBegin(GL_QUADS);
    float angle_inc = M_PI / 8;
    float z_inc = 0.5;
    for (double z = -4; z < 4; z += z_inc) {
        double r = (1 + (pow(z, 2) / pow(c, 2))) * pow(a, 2) * pow(b, 2);
        double rNext = (1 + (pow(z + z_inc, 2) / pow(c, 2))) * pow(a, 2) * pow(b, 2);
        for (double angle = 0; angle < M_PI * 2; angle += angle_inc) {
            double x = (r * cos(angle)) / pow(b, 2), y = (r * sin(angle)) / pow(a, 2);
            double x2 = (r * cos(angle + angle_inc)) / pow(b, 2), y2 = (r * sin(angle + angle_inc)) / pow(a, 2);
            double xNext = (rNext * cos(angle)) / pow(b, 2), yNext = (rNext * sin(angle)) / pow(a, 2);
            double x2Next = (rNext * cos(angle + angle_inc)) / pow(b, 2), y2Next = (rNext * sin(angle + angle_inc)) / pow(a, 2);
            glVertex3d(x, y, z);
            glVertex3d(xNext, yNext, z + z_inc);
            glVertex3d(x2Next, y2Next, z + z_inc);
            glVertex3d(x2, y2, z);
        }
    }
    glEnd();
    glBegin(GL_TRIANGLES);
    double r = (1 + (pow(-4, 2) / pow(c, 2))) * pow(a, 2) * pow(b, 2);
    for(double angle = 0; angle < M_PI * 2; angle += angle_inc){
        double x = (r * cos(angle)) / pow(b, 2), y = (r * sin(angle)) / pow(a, 2);
        double x2 = (r * cos(angle + angle_inc)) / pow(b, 2), y2 = (r * sin(angle + angle_inc)) / pow(a, 2);
        glVertex3d(x, y, -4);
        glVertex3d(0, 0, -6);
        glVertex3d(x2, y2, -4);
    }
    glEnd();
    glBegin(GL_TRIANGLES);
    r = (1 + (pow(4, 2) / pow(c, 2))) * pow(a, 2) * pow(b, 2);
    for(double angle = 0; angle < M_PI * 2; angle += angle_inc){
        double x = (r * cos(angle)) / pow(b, 2), y = (r * sin(angle)) / pow(a, 2);
        double x2 = (r * cos(angle + angle_inc)) / pow(b, 2), y2 = (r * sin(angle + angle_inc)) / pow(a, 2);
        glVertex3d(x, y, 4);
        glVertex3d(0, 0, 6);
        glVertex3d(x2, y2, 4);
    }
    glEnd();
}

void Painter::button(double a1, double b1, double c1, double a2, double b2, double c2) {
    glBegin(GL_QUADS);
    float angle_inc = M_PI / 8;
    float z_inc = 0.3;
    for (double z = -4; z < 0; z += z_inc) {
        double r = (1 - (pow(z, 2) / pow(c1, 2))) * pow(a1, 2) * pow(b1, 2);
        double rNext = (1 - (pow(z + z_inc, 2) / pow(c1, 2))) * pow(a1, 2) * pow(b1, 2);
        for (double angle = 0; angle < M_PI * 2; angle += angle_inc) {
            double x = (r * cos(angle)) / pow(b1, 2), y = (r * sin(angle)) / pow(a1, 2);
            double x2 = (r * cos(angle + angle_inc)) / pow(b1, 2), y2 = (r * sin(angle + angle_inc)) / pow(a1, 2);
            double xNext = (rNext * cos(angle)) / pow(b1, 2), yNext = (rNext * sin(angle)) / pow(a1, 2);
            double x2Next = (rNext * cos(angle + angle_inc)) / pow(b1, 2), y2Next = (rNext * sin(angle + angle_inc)) / pow(a1, 2);
            glVertex3d(x, y, z);
            glVertex3d(xNext, yNext, z + z_inc);
            glVertex3d(x2Next, y2Next, z + z_inc);
            glVertex3d(x2, y2, z);
        }
    }
    glEnd();

    double deltaZ = 16;
    glTranslated(0, 0, -deltaZ);
    glBegin(GL_QUADS);
    for (double z = deltaZ; z < deltaZ + 2; z += z_inc) {
        double r = ((pow(z, 2) / pow(c2, 2))) * pow(a2, 2) * pow(b2, 2);
        double rNext = ((pow(z + z_inc, 2) / pow(c2, 2))) * pow(a2, 2) * pow(b2, 2);
        for (double angle = 0; angle < M_PI * 2; angle += angle_inc) {
            double x = (r * cos(angle)) / pow(b2, 2), y = (r * sin(angle)) / pow(a2, 2);
            double x2 = (r * cos(angle + angle_inc)) / pow(b2, 2), y2 = (r * sin(angle + angle_inc)) / pow(a2, 2);
            double xNext = (rNext * cos(angle)) / pow(b2, 2), yNext = (rNext * sin(angle)) / pow(a2, 2);
            double x2Next = (rNext * cos(angle + angle_inc)) / pow(b2, 2), y2Next = (rNext * sin(angle + angle_inc)) / pow(a2, 2);
            glVertex3d(x, y, z);
            glVertex3d(xNext, yNext, z + z_inc);
            glVertex3d(x2Next, y2Next, z + z_inc);
            glVertex3d(x2, y2, z);
        }
    }
    glEnd();
}

void Painter::doorhandle(double a1, double b1, double c1, double a2, double b2, double c2) {
    glBegin(GL_QUADS);
    float angle_inc = M_PI / 8;
    float z_inc = 0.5;
    for (double z = -4; z < 4; z += z_inc) {
        double r = (1 + (pow(z, 2) / pow(c1, 2))) * pow(a1, 2) * pow(b1, 2);
        double rNext = (1 + (pow(z + z_inc, 2) / pow(c1, 2))) * pow(a1, 2) * pow(b1, 2);
        for (double angle = 0; angle < M_PI * 2; angle += angle_inc) {
            double x = (r * cos(angle)) / pow(b1, 2), y = (r * sin(angle)) / pow(a1, 2);
            double x2 = (r * cos(angle + angle_inc)) / pow(b1, 2), y2 = (r * sin(angle + angle_inc)) / pow(a1, 2);
            double xNext = (rNext * cos(angle)) / pow(b1, 2), yNext = (rNext * sin(angle)) / pow(a1, 2);
            double x2Next = (rNext * cos(angle + angle_inc)) / pow(b1, 2), y2Next = (rNext * sin(angle + angle_inc)) / pow(a1, 2);
            glVertex3d(x, y, z);
            glVertex3d(xNext, yNext, z + z_inc);
            glVertex3d(x2Next, y2Next, z + z_inc);
            glVertex3d(x2, y2, z);
        }
    }
    glEnd();
    double deltaZ = 8.5;
    glTranslated(0, 0, -deltaZ); // 6, 0.6, 0.6, 1.7
    glBegin(GL_QUADS);
    for (double z = 0; z < 4.1; z += z_inc) {
        double r = ((pow(z, 2) / pow(c2, 2))) * pow(a2, 2) * pow(b2, 2);
        double rNext = ((pow(z + z_inc, 2) / pow(c2, 2))) * pow(a2, 2) * pow(b2, 2);
        for (double angle = 0; angle < M_PI * 2; angle += angle_inc) {
            double x = (r * cos(angle)) / pow(b2, 2), y = (r * sin(angle)) / pow(a2, 2);
            double x2 = (r * cos(angle + angle_inc)) / pow(b2, 2), y2 = (r * sin(angle + angle_inc)) / pow(a2, 2);
            double xNext = (rNext * cos(angle)) / pow(b2, 2), yNext = (rNext * sin(angle)) / pow(a2, 2);
            double x2Next = (rNext * cos(angle + angle_inc)) / pow(b2, 2), y2Next = (rNext * sin(angle + angle_inc)) / pow(a2, 2);
            glVertex3d(x, y, z);
            glVertex3d(xNext, yNext, z + z_inc);
            glVertex3d(x2Next, y2Next, z + z_inc);
            glVertex3d(x2, y2, z);
        }
    }
    glEnd();
}
