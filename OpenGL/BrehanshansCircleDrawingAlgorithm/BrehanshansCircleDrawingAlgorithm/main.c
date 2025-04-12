#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

//Defining the centre of the circle and the radius
int xc = 320, yc = 240, r = 100;
// Function to plot a point at (x, y), using 8-way symmetry
void plot_point(int x, int y) {
	glBegin(GL_POINTS); //Begin plotting points

	// Plot points all 8 symmetrical positions
	glVertex2i(xc + x, yc + y); // Quadrant 1
	glVertex2i(xc + x, yc - y);// quadrant 4
	glVertex2i(xc + y, yc + x);// rotated quadrant 1
	glVertex2i(xc + y, yc - x);// rotated quadrant 4
	glVertex2i(xc - x, yc - y);// quadrant 3
	glVertex2i(xc - y, yc - x);// rotated quadrant 3
	glVertex2i(xc - x, yc + y);// quadrant 2
	glVertex2i(xc - y, yc + x);// rotated quadrant 2
	glEnd(); //End plotting points
}
// Function to draw a circle using Bresenham's algorithm
void bresenham_circle() {

	int x = 0, y = r; // Start at the top of the circle
	int d = 3 - 2 * r; // Initial decision parameter

	plot_point(x, y); // Plot the first set of symmetrical points

	// Continue until x is greater than or equal to y(Ensure circle is fully drawn
	while (y >= x) {
		x++; // Increment x

		// Update decision parameter based on the circle's symmetry
		if (d > 0) {
			y--; // Decrement y(Move diagonally)
			d = d + 4 * (x - y) + 10;
		}
		else {
			d = d + 4 * x + 6; //Move Horizontally
		}
		plot_point(x, y); // Plot the next set of symmetrical points
	}

}
// Function to display the circle
void display() {
	glClear(GL_COLOR_BUFFER_BIT); //clear the screen Buffer
	glColor3f(1, 0, 0); // set drawing color to red
	glPointSize(2); // Set point size to 2
	bresenham_circle(); //call function to draw circle
	glFlush(); //Ensure all openGL commands are executed
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

		display();  // Draw a line

		glfwSwapBuffers(window);  // Swap buffers
		glfwPollEvents();  // Handle user input
	}

	glfwTerminate();  // Clean up
	return 0;
}