#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <math.h>
#define M_PI 3.14159265358979323846

// Define global variables for shape type and coordinates
int shapeChoice;
int x1, y5, x2, y2, x3, y3, x4, y4;  // Coordinates for rectangle/triangle

// Transformation variables
float tx = 0, ty = 0; // Translation
float sx = 1, sy = 1; // Scaling
float angle = 0;      // Rotation
int reflectionAxis = 0; // Reflection (0: X-axis, 1: Y-axis)

// Bresenham's Line Drawing Algorithm
void bresenham_line(int x1, int y1, int x2, int y2) {

	int dx = abs(x2 - x1), dy = abs(y2 - y1);

	int sx = (x2 > x1) ? 1 : -1;  // Step in x-direction

	int sy = (y2 > y1) ? 1 : -1;  // Step in y-direction
	int err = dx - dy;  // Error term

	glBegin(GL_POINTS);
	while (1) {
		glVertex2i(x1, y1);
		if (x1 == x2 && y1 == y2) break;  // Exit when end-point is reached
		int e2 = 2 * err;
		if (e2 > -dy) { err -= dy; x1 += sx; }  // Adjust x
		if (e2 < dx) { err += dx; y1 += sy; }  // Adjust y
	}
	glEnd();
}
// Draw a rectangle using Bresenham's Line Algorithm
void draw_rectangle() {
	bresenham_line(x1, y5, x2, y2);
	bresenham_line(x2, y2, x3, y3);
	bresenham_line(x3, y3, x4, y4);
	bresenham_line(x4, y4, x1, y5);
}
// Draw a triangle using Bresenham's Line Algorithm
void draw_triangle() {
	bresenham_line(x1, y5, x2, y2);
	bresenham_line(x2, y2, x3, y3);
	bresenham_line(x3, y3, x1, y5);
}
// Display function
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0); // Red color
	glPointSize(2);

	if (shapeChoice == 1) {
		draw_rectangle();
	}
	else if (shapeChoice == 2) {
		draw_triangle();
	}

	glFlush();
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
// Translation function
void translate() {
	x1 += tx; y5 += ty;
	x2 += tx; y2 += ty;
	x3 += tx; y3 += ty;
	if (shapeChoice == 1) { x4 += tx; y4 += ty; }
}
// Scaling function
void scale() {
	x1 *= sx; y5 *= sy;
	x2 *= sx; y2 *= sy;
	x3 *= sx; y3 *= sy;
	if (shapeChoice == 1) { x4 *= sx; y4 *= sy; }
}
// Rotation function
void rotate() {
	float rad = angle * (M_PI / 180.0);
	int cx = (x1 + x2 + x3) / 3; // Center of shape
	int cy = (y5 + y2 + y3) / 3;
	// Rotate each point
	int temp;
	temp = x1; x1 = cx + (temp - cx) * cos(rad) - (y5 - cy) * sin(rad);
	y5 = cy + (temp - cx) * sin(rad) + (y5 - cy) * cos(rad);
	temp = x2; x2 = cx + (temp - cx) * cos(rad) - (y2 - cy) * sin(rad);
	y2 = cy + (temp - cx) * sin(rad) + (y2 - cy) * cos(rad);
	temp = x3; x3 = cx + (temp - cx) * cos(rad) - (y3 - cy) * sin(rad);
	y3 = cy + (temp - cx) * sin(rad) + (y3 - cy) * cos(rad);
	if (shapeChoice == 1) {
		temp = x4; x4 = cx + (temp - cx) * cos(rad) - (y4 - cy) * sin(rad);
		y4 = cy + (temp - cx) * sin(rad) + (y4 - cy) * cos(rad);
	}
}

// Reflection function
void reflect() {
	if (reflectionAxis == 0) { // X-axis
		y5 = -y5; y2 = -y2; y3 = -y3;
		if (shapeChoice == 1) { y4 = -y4; }
	}
	else if (reflectionAxis == 1) { // Y-axis
		x1 = -x1; x2 = -x2; x3 = -x3;
		if (shapeChoice == 1) { x4 = -x4; }
	}
}

// Function to handle transformations from user keyboards
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {
		case GLFW_KEY_T: // Translate
			tx = 10; ty = 10; // Example: move shape diagonally
			translate();
			break;
		case GLFW_KEY_S: // Scale
			sx = 1.1f; sy = 1.1f; // Scale up by 10%
			scale();
			break;
		case GLFW_KEY_R: // Rotate
			angle = 10; // Rotate by 10 degrees
			rotate();
			break;
		case GLFW_KEY_X: // Reflect across X-axis
			reflectionAxis = 0;
			reflect();
			break;
		case GLFW_KEY_Y: // Reflect across Y-axis
			reflectionAxis = 1;
			reflect();
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		}
	}
}

int main() {

	// Ask user for shape choice
	printf("Choose a shape:\n1. Rectangle\n2. Triangle\nEnter choice: ");
	scanf_s("%d", &shapeChoice);

	if (shapeChoice == 1) {
		// Hardcoded Rectangle Coordinates
		x1 = 100, y5 = 300;
		x2 = 300, y2 = 300;
		x3 = 300, y3 = 100;
		x4 = 100, y4 = 100;
	}
	else if (shapeChoice == 2) {
		// Hardcoded Triangle Coordinates
		x1 = 200, y5 = 300;
		x2 = 100, y2 = 100;
		x3 = 300, y3 = 100;
	}
	else {
		printf("Invalid choice! Exiting.\n");
		return 1;
	}

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
	glfwSetKeyCallback(window, key_callback);
	MyInit();  // Set up coordinate system
	// Main loop
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
		display();  // Draw a line
		glfwSwapBuffers(window);  // Swap buffers
		glfwPollEvents();  // Handle user input
	}
	// Main loop

	// Call transformation function
	//transformShape();

	glfwTerminate();  // Clean up
	return 0;
}
