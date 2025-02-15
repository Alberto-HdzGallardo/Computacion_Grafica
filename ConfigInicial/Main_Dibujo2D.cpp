/*Práctica 2												Hernandez Gallardo Alberto Javier
  Fecha de entrega:	14 de febrero de 2025					313113439
*/

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Práctica 2 Alberto", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		0.0f,  0.0f, 0.0f,    1.0f,0.549f,0.0f,  // Atorso(0)
		0.6f, 0.0f, 0.0f,    1.0f,0.549f,0.0f,  // Btorso(1)
		0.05f, -0.52f, 0.0f,   1.0f,0.549f,0.0f,  // Ctorso(2)
		-0.25f,  -0.65f, 0.0f,   1.0f,1.0f,1.0f,	//DpataFrontal(3)
		-0.2f,  -0.53f, 0.0f,    1.0f,1.0f,1.0f,// EpataFrontal(4)
		0.68f,  -0.4f, 0.0f,    1.0f,0.52f,0.0f,	//FpataTrasera(5)
		0.6f,  -0.6f, 0.0f,    1.0f,0.52f,0.0f,	//GpataTrasera1(6)
		0.48f,  -0.6f, 0.0f,    1.0f,0.52f,0.0f,	//HpataTrasera(7)
		0.48f,  -0.53f, 0.0f,    1.0f,1.0f,0.0f,//IpataTrasera(8)
		0.54f,  -0.49f, 0.0f,    1.0f,0.52f,0.0f,	//JpataTrasera(9)
		0.53f,  -0.42f, 0.0f,    1.0f,0.52f,0.0f,	//KpataTrasera(10)
		0.36f,  -0.24f, 0.0f,    1.0f,1.0f,0.0f,	//LpataTrasera(11)
		0.47f,  -0.56f, 0.0f,    1.0f,1.0f,0.0f,	//MpataTrasera(12)
		-0.38f,  -0.47f, 0.0f,    1.0f,0.52f,0.0f,	//Qmelena(13)
		-0.60f,  -0.25f, 0.0f,    1.0f,0.52f,0.0f,	//Pmelena(14)
		-0.60f,  -0.0f, 0.0f,    1.0f,0.52f,0.0f,	//Omelena(15)
		-0.31f,  0.4f, 0.0f,    1.0f,1.0f,0.0f,	//Nmelena(16)
		-0.25f,  -0.49f, 0.05f,    0.72f,0.4f,0.078f,// RpataFrontal2(17)
		-0.29f,  -0.6f, 0.05f,    0.72f,0.4f,0.078f,// SpataFrontal2(18)
		-0.18f,  -0.5f, 0.05f,    0.72f,0.4f,0.078f,// TpataFrontal2(19)
		0.49f,  -0.58f, 0.05f,    0.72f,0.4f,0.078f,// UpataTrasera2(20)
		0.43f,  -0.58f, 0.05f,    0.72f,0.4f,0.078f,// VpataTrasera2(21)
		0.43f,  -0.51f, 0.05f,    0.72f,0.4f,0.078f,// WpataTrasera2(22)
		0.5f,  -0.48f, 0.05f,    0.72f,0.4f,0.078f,// ZpataTrasera2(23)
		-0.31f,  0.43f, 0.2f,    1.0f,0.9f,0.0f,	//A1rostro(24)
		-0.35f,  0.40f, 0.2f,    1.0f,0.9f,0.0f,	//B1rostro(25)
		-0.70f,  -0.08f, 0.2f,    1.0f,0.9f,0.0f,	//C1rostro(26)
		-0.66f,  -0.2f, 0.2f,    1.0f,0.9f,0.0f,	//D1rostro(27)
		-0.58f,  -0.33f, 0.2f,    1.0f,0.9f,0.0f,	//E1rostro(28)
		-0.27f,  -0.17f, 0.2f,    1.0f,0.9f,0.0f,	//F1rostro(29)
		0.60f,  -0.03f, -0.2f,    1.0f,0.9f,0.0f,	//G1cola1(30)
		0.76f,  -0.12f, -0.2f,    1.0f,0.9f,0.0f,	//H1cola1/2(31)
		0.62f,  -0.13f, -0.2f,    1.0f,0.9f,0.0f,	//I1cola2(32)
		0.67f,  -0.12f, -0.4f,    1.0f,0.52f,0.0f,	//J1cola2(33)
		0.74f,  -0.42f, -0.4f,    1.0f,0.52f,0.0f,	//K1cola2(34)
		0.79f,  -0.45f, -0.4f,    1.0f,0.52f,0.0f,	//L1cola2/3(35)
		0.92f,  -0.45f, -0.8f,    0.72f,0.4f,0.078f,//M1cola3(36)
		0.97f,  -0.4f, -0.8f,    0.72f,0.4f,0.078f,	//N1cola3(37)
		0.79f,  -0.4f, -0.8f,    0.72f,0.4f,0.078f,	//O1cola3(38)
	};
	unsigned int indices[] = {  // note that we start from 0!
		0,1,2,4,// torso
		2,3,4,	//pata delantera 1
		1,5,6,7,8,9,10,11,12,	//pata trasera 1
		0,4,13,14,15,16,			//melena
		20,21,22,23,			//pata trasera 2
		24,25,26,27,28,29,		//rostro
		33,34,35,31,				//cola_parte2
		35,36,37,38,				//cola_parte3
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our shapes
        ourShader.Use();
        glBindVertexArray(VAO);


        //glPointSize(10);
        //glDrawArrays(GL_POINTS,0,4);
        
        //glDrawArrays(GL_LINES,0,4);
        //glDrawArrays(GL_LINE_LOOP,0,5);
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(36 * sizeof(unsigned int))); //cola_parte3
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(32 * sizeof(unsigned int))); //cola_parte2
		glDrawArrays(GL_TRIANGLES, 30, 3);														//cola_parte1
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(26 * sizeof(unsigned int)));//rostro
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(22 * sizeof(unsigned int)));//pata trasera2
		glDrawArrays(GL_TRIANGLES, 17, 3);														//pata delantera2
		glDrawArrays(GL_TRIANGLES, 2, 3);														//pata delantera1
        glDrawElements(GL_TRIANGLE_FAN,8,GL_UNSIGNED_INT, (void*)(7 * sizeof(unsigned int)));	//pata trasera1
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, nullptr);								//torso
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(16 * sizeof(unsigned int)));//melena
		
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}