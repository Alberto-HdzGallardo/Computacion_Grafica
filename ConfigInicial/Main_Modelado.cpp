/*Práctica 4 
  Fecha de entrega: 2 de marzo del 2025
  Hernandez Gallardo Alberto Javier
  No cuenta: 313113439
*/

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 900, HEIGHT = 700;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado geometrico Alberto Hernandez", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 1.0f, 0.24f,0.20f,//Front rojo (0-36)
		0.5f, -0.5f, 0.5f,  1.0f, 0.24f,0.20f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.24f,0.20f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.24f,0.20f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.24f,0.20f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.24f,0.20f,
		
	    -0.5f, -0.5f,-0.5f, 1.0f, 0.24f,0.20f,//Back
		 0.5f, -0.5f,-0.5f, 1.0f, 0.24f,0.20f,
		 0.5f,  0.5f,-0.5f, 1.0f, 0.24f,0.20f,
		 0.5f,  0.5f,-0.5f, 1.0f, 0.24f,0.20f,
	    -0.5f,  0.5f,-0.5f, 1.0f, 0.24f,0.20f,
	    -0.5f, -0.5f,-0.5f, 1.0f, 0.24f,0.20f,
		
		 0.5f, -0.5f,  0.5f,  1.0f, 0.24f,0.20f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.24f,0.20f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.24f,0.20f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.24f,0.20f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.24f,0.20f,
		 0.5f,  -0.5f, 0.5f, 1.0f, 0.24f,0.20f,
      
		-0.5f,  0.5f,  0.5f,  1.0f, 0.24f,0.20f,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.24f,0.20f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.24f,0.20f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.24f,0.20f,
		-0.5f, -0.5f,  0.5f,  1.0f, 0.24f,0.20f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.24f,0.20f,
		
		-0.5f, -0.5f, -0.5f, 1.0f, 0.24f,0.20f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.24f,0.20f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.24f,0.20f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.24f,0.20f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.24f,0.20f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.24f,0.20f,
		
		-0.5f,  0.5f, -0.5f, 1.0f, 0.24f,0.20f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.24f,0.20f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.24f,0.20f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.24f,0.20f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.24f,0.20f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.24f,0.20f,

		-0.5f, -0.5f, 0.5f, 0.40f, 0.50f,1.20f,// Color azul (36-73)
		0.5f, -0.5f, 0.5f,  0.40f, 0.50f,1.20f,
		0.5f,  0.5f, 0.5f,  0.40f, 0.50f,1.20f,
		0.5f,  0.5f, 0.5f,  0.40f, 0.50f,1.20f,
		-0.5f,  0.5f, 0.5f, 0.40f, 0.50f,1.20f,
		-0.5f, -0.5f, 0.5f, 0.40f, 0.50f,1.20f,

		-0.5f, -0.5f,-0.5f, 0.40f, 0.50f,1.20f,//Back
		 0.5f, -0.5f,-0.5f, 0.40f, 0.50f,1.20f,
		 0.5f,  0.5f,-0.5f, 0.40f, 0.50f,1.20f,
		 0.5f,  0.5f,-0.5f, 0.40f, 0.50f,1.20f,
		-0.5f,  0.5f,-0.5f, 0.40f, 0.50f,1.20f,
		-0.5f, -0.5f,-0.5f, 0.40f, 0.50f,1.20f,

		 0.5f, -0.5f,  0.5f,  0.40f, 0.50f,1.20f,
		 0.5f, -0.5f, -0.5f,  0.40f, 0.50f,1.20f,
		 0.5f,  0.5f, -0.5f,  0.40f, 0.50f,1.20f,
		 0.5f,  0.5f, -0.5f,  0.40f, 0.50f,1.20f,
		 0.5f,  0.5f,  0.5f,  0.40f, 0.50f,1.20f,
		 0.5f,  -0.5f, 0.5f, 0.40f, 0.50f,1.20f,

		-0.5f,  0.5f,  0.5f,  0.40f, 0.50f,1.20f,
		-0.5f,  0.5f, -0.5f,  0.40f, 0.50f,1.20f,
		-0.5f, -0.5f, -0.5f,  0.40f, 0.50f,1.20f,
		-0.5f, -0.5f, -0.5f,  0.40f, 0.50f,1.20f,
		-0.5f, -0.5f,  0.5f,  0.40f, 0.50f,1.20f,
		-0.5f,  0.5f,  0.5f,  0.40f, 0.50f,1.20f,

		-0.5f, -0.5f, -0.5f, 0.40f, 0.50f,1.20f,
		0.5f, -0.5f, -0.5f,  0.40f, 0.50f,1.20f,
		0.5f, -0.5f,  0.5f,  0.40f, 0.50f,1.20f,
		0.5f, -0.5f,  0.5f,  0.40f, 0.50f,1.20f,
		-0.5f, -0.5f,  0.5f, 0.40f, 0.50f,1.20f,
		-0.5f, -0.5f, -0.5f, 0.40f, 0.50f,1.20f,

		-0.5f,  0.5f, -0.5f, 0.40f, 0.50f,1.20f,
		0.5f,  0.5f, -0.5f,  0.40f, 0.50f,1.20f,
		0.5f,  0.5f,  0.5f,  0.40f, 0.50f,1.20f,
		0.5f,  0.5f,  0.5f,  0.40f, 0.50f,1.20f,
		-0.5f,  0.5f,  0.5f, 0.40f, 0.50f,1.20f,
		-0.5f,  0.5f, -0.5f, 0.40f, 0.50f,1.20f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,0.0f,//Color negro (72-109)
		0.5f, -0.5f, 0.5f,  0.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  0.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  0.0f, 0.0f,0.0f,
		-0.5f,  0.5f, 0.5f, 0.0f, 0.0f,0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,0.0f,

		-0.5f, -0.5f,-0.5f, 0.0f, 0.0f,0.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.0f, 0.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.0f,0.0f,
		-0.5f,  0.5f,-0.5f, 0.0f, 0.0f,0.0f,
		-0.5f, -0.5f,-0.5f, 0.0f, 0.0f,0.0f,

		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,//Color blanco (108-145)
		0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,//Back
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,

		0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO);

		//Torso
	
	    model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.4f, 0.07f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f)); //Se sube un poco el torso principal
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);
		
		//Detallado torso
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.1f, 0.1f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 3.85f, 0.0f)); //Posición de pecho/hombros
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.1f, 0.1f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 3.5f, 0.0f)); //Posición de detalle pecho 1
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.1f, 0.1f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f)); //Posición de detalle pecho 2
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 6.5f, 0.7f)); //Posición de detalle pecho central
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.07f, 0.1f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 1.2f, 0.0f)); //Posición de parte central (abdomen)
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.1f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f)); //Posición de cinturón
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		
		//Modelado del brazo derecho
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.04f, 0.1f));		 //Tamaño
		model = glm::translate(model, glm::vec3(4.0f, 9.5f, 0.0f)); //Posición
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.3f, 0.1f));		 //Tamaño del brazo
		model = glm::translate(model, glm::vec3(4.0f, 0.70f, 0.0f)); //Posición del brazo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.08f, 0.05f, 0.12f));		 //Tamaño mano derecha
		model = glm::translate(model, glm::vec3(3.5f, 1.5f, 0.0f)); //Posición mano derecha
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//Modelado del brazo izquierdo
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.04f, 0.1f));		 //Tamaño
		model = glm::translate(model, glm::vec3(-4.0f, 9.5f, 0.0f)); //Posición
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.3f, 0.1f));		 //Tamaño del brazo
		model = glm::translate(model, glm::vec3(-4.0f, 0.70f, 0.0f)); //Posición del brazo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.08f, 0.05f, 0.12f));		 //Tamaño mano izquierda
		model = glm::translate(model, glm::vec3(-3.5f, 1.5f, 0.0f)); //Posición mano izquierda
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//Modelado del cuello
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.08f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 9.0f, 0.0f)); //Posición de detalle cuello
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 0.05f, 0.06f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 9.0f, 0.0f)); //Posición de detalle cuello
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//Modelado de la pierna izquierda
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.2f, 0.06f));		 //Tamaño de la pierna
		model = glm::translate(model, glm::vec3(-1.6f, -0.5f, 0.0f)); //Posición de la pierna
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.08f, 0.05f, 0.1f));		 //Tamaño pie izquierdo
		model = glm::translate(model, glm::vec3(-1.4f, -3.5f, 0.0f)); //Posición pie izquierdo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		
		//Modelado de la pierna derecha
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.2f, 0.06f));		 //Tamaño de la pierna
		model = glm::translate(model, glm::vec3(1.6f, -0.5f, 0.0f)); //Posición de la pierna
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 73);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.08f, 0.05f, 0.1f));		 //Tamaño pie derecho
		model = glm::translate(model, glm::vec3(1.4f, -3.5f, 0.0f)); //Posición pie derecho
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		
		//Modelado de cabeza
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.1f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0.0f)); //Posición de cabeza
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Detallado de la cabeza
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.045f, 0.1f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 17.0f, 0.0f)); //Posición de parte superior cabeza
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.125f, 0.045f, 0.1f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 17.8f, 0.0f)); //Posición de parte superior cabeza 2
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.045f, 0.1f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 11.0f, 0.0f)); //Posición de parte inferior cabeza
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.03f, 0.25f, 0.1f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(4.68f, 2.5f, 0.0f)); //Posición de detalle lateral izquierdo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.03f, 0.17f, 0.1f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(5.7f, 3.7f, 0.0f)); //Posición de detalle lateral izquierdo 2
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.03f, 0.25f, 0.1f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(-4.68f, 2.5f, 0.0f)); //Posición de detalle lateral derecho
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.03f, 0.17f, 0.1f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(-5.7f, 3.7f, 0.0f)); //Posición de detalle lateral derecho 2
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Modelado de ojos
		//Ojo izquierdo
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.9f, 9.0f, 0.3f)); //Posición de ojo izquierdo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 145);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.03f, 0.07f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.9f, 19.5f, 0.3f)); //Posición de detalle inferior ojo izquierdo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.03f, 0.07f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.9f, 22.5f, 0.3f)); //Posición de detalle superior ojo izquierdo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.03f, 0.07f, 0.07f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(0.9f, 9.0f, 0.29f)); //Posición de detalle lateral 1 ojo izquierdo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.03f, 0.14f, 0.07f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(3.7f, 4.57f, 0.3f)); //Posición de detalle lateral 2 ojo izquierdo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);


		//Ojo derecho
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(-0.9f, 9.0f, 0.3f)); //Posición de ojo izquierdo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 145);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.03f, 0.07f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(-0.9f, 19.5f, 0.3f)); //Posición de detalle inferior ojo derecho
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.03f, 0.07f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(-0.9f, 22.5f, 0.3f)); //Posición de detalle superior ojo derecho
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.03f, 0.07f, 0.07f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(-0.9f, 9.0f, 0.29f)); //Posición de detalle lateral 1 ojo derecho
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.03f, 0.14f, 0.07f)); //Ancho,grosor y profundidad
		model = glm::translate(model, glm::vec3(-3.7f, 4.57f, 0.3f)); //Posición de detalle lateral 2 ojo izquierdo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 109);

		/*
		//
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.2f, 0.1f));		 //Tamaño de la pata
		model = glm::translate(model, glm::vec3(8.9f, -0.1f, -6.0f)); //Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 145);

		*/



		glBindVertexArray(0);

				

		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.002f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.002f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.002f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.002f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.002f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.002f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.05f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.05f;
 }


