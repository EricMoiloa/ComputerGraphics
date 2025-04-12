#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

// Function to draw a line using the Digital Differential Analyzer (DDA) Algorithm

// Function to get the maximum absolute value between dx and dy
int getMaxSteps(int dx, int dy) {
    if (abs(dx) > abs(dy)) {  // Compare absolute values of dx and dy
        return abs(dx);  // If dx is greater, return dx
    }
    else {
        return abs(dy);  // Otherwise, return dy
    }
}


void DrawLine(int x1, int y1, int x2, int y2) {
    // Calculate the difference between the start and end points
    GLfloat dx = x2 - x1;  // Change in x 
    GLfloat dy = y2 - y1;  // Change in y 

    // Use the function to determine the number of steps
    GLfloat steps = getMaxSteps(dx, dy);

    // Calculate increments for x and y per step

    GLfloat xIncrement = dx / steps;  // Determines how much x should change per step
    GLfloat yIncrement = dy / steps;  // Determines how much y should change per step

    // Initialize starting point
    GLfloat x = x1, y = y1;

    // Begin OpenGL point drawing
    glBegin(GL_POINTS);

    // Loop through all steps to plot the points
    for (int i = 0; i <= steps; i++) {

        glVertex2i((int)x, (int)y);  // Plot rounded (integer) pixel at (x, y)
        x += xIncrement;  // Update x coordinate
        y += yIncrement;  // Update y coordinate
    }

    glEnd();  // End OpenGL drawing
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
    GLFWwindow* window = glfwCreateWindow(500, 500, "Digital Differential Analyze Line Drawing in C", NULL, NULL);
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

        DrawLine(220, 450, 220, 350);  // Draw a line

        glfwSwapBuffers(window);  // Swap buffers
        glfwPollEvents();  // Handle user input
    }

    glfwTerminate();  // Clean up
    return 0;
}
