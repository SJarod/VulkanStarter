
#include <glad/gl.h>

// glu
#define APIENTRY __stdcall
#define CALLBACK __stdcall
#include <GL/glu.h>

// imgui
#include <imgui.h>

#include "demo_test.hpp"

#include "types.hpp"
#include "maths.hpp"

static void drawGizmo()
{
    /*
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_LINES);

    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(1.f, 0.f, 0.f);

    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, 1.f, 0.f);

    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, 0.f, 1.f);

    glColor3f(1.f, 1.f, 1.f);

    glEnd();
    glEnable(GL_DEPTH_TEST);
    */
}

static void drawQuad()
{
    /*
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.f);
    glVertex3f( 0.5f, -0.5f, 0.f);
    glVertex3f( 0.5f,  0.5f, 0.f);
    glVertex3f(-0.5f,  0.5f, 0.f);
    glEnd();
    */
}

void DemoTest::display()
{
    ImGuiIO& io = ImGui::GetIO();

    time += io.DeltaTime;

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
    // Projection
    glMatrixMode(GL_PROJECTION);

    // Setup a perspective projection matrix
    {
        glLoadIdentity();
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        gluPerspective(90.f, viewport[2] / (float)viewport[3], 0.001f, 10.f);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Setup camera position
    static float cameraX = 0.f;
    ImGui::DragFloat("cameraX", &cameraX, 0.1f);
    static float cameraY = 0.f;
    ImGui::DragFloat("cameraY", &cameraY, 0.1f);
    static float cameraZ = 3.f;
    ImGui::DragFloat("cameraZ", &cameraZ, 0.1f);
    glTranslatef(-cameraX, -cameraY, -cameraZ);

    // Draw scene
    static bool showGizmo = true;
    ImGui::Checkbox("showGizmo", &showGizmo);
    if (showGizmo)
        drawGizmo(); // Draw gizmo at origin

    glPushMatrix();
        glTranslatef(2.f, 0.f, 0.f);
        //glScalef(0.5f, 0.5f, 0.5f);
        glRotatef(time * 90.f, 0.f, 1.f, 0.f);
        //glColor3f(0.4f, 0.2f, 0.8f);
        drawQuad();

        //glPushMatrix();
        //    glTranslatef(2.f, 0.f, 0.f);
        //    glScalef(0.5f, 0.5f, 0.5f);
        //    glColor3f(0.8f, 0.5f, 0.f);
        //    drawQuad();
        //glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-2.f, 0.f, 0.f);
        glRotatef(-time * 90.f, 0.f, 1.f, 0.f);
        drawQuad();
    glPopMatrix();

    glDisable(GL_DEPTH_TEST);
    */
}
