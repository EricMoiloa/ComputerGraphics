#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

// Function to draw a line using Bresenham’s Algorithm
void DrawLine(int x1, int y1, int x2, int y2) {

    int dx = x2 - x1;
    int dy = y2 - y1;
    int x = x1, y = y1;
    int p = 2 * dy - dx;

    glBegin(GL_POINTS);
    glVertex2i(x, y);  // Plot the first point

    while (x < x2) {
        x++;
        if (p < 0) {
            p += 2 * dy;
        }
        else {
            p += 2 * dy - 2 * dx;
            y++;
        }
        glVertex2i(x, y);
    }
    glEnd();
}

// Function to set up the coordinate system
void MyInit() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -1, 1); // Set coordinate system
    glMatrixMode(GL_MODELVIEW);
}

// Callback function to adjust viewport when window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }
    // Create a 500x500 window
    GLFWwindow* window = glfwCreateWindow(500, 500, "Bresenham's Line Drawing in C", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    // Make the OpenGL context current
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    MyInit();  // Set up coordinate system
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen

        DrawLine(120, 50, 150, 350);  // Draw a line

        glfwSwapBuffers(window);  // Swap buffers
        glfwPollEvents();  // Handle user input
    }

    glfwTerminate();  // Clean up
    return 0;
}
