/*
Práctica 6: Carga de modelos y cámara sintética
Fecha de entrega: 16 de marzo del 2025
Hernandez Gallardo Alberto Javier
No. cuenta: 313113439
*/




// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 1280, HEIGHT = 800;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera( glm::vec3(-8.0f, 2.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;



int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Carga de modelos y camara sintetica Alberto Hernandez", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shader/modelLoading.vs", "Shader/modelLoading.frag" );
    
    // Load models
    Model dog((char*)"Models/RedDog.obj");
    Model farm((char*)"Models/Farm_2.obj");
	Model terrain((char*)"Models/Low Poly Farm Asset/terrain_sm.obj");
	Model corns_sm((char*)"Models/Low Poly Farm Asset/corns_sm.obj");
	Model hay((char*)"Models/Low Poly Farm Asset/hay.obj");
	Model tree((char*)"Models/Low Poly Farm Asset/tree.obj");
	Model stone_path_lowpoly((char*)"Models/Low Poly Farm Asset/stone_path_lowpoly.obj");
	Model barrel((char*)"Models/Low Poly Farm Asset/barrel.obj");
	Model barn((char*)"Models/Low Poly Farm Asset/barn.obj");
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
  

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model Dog
        glm::mat4 model(1);
        glm::mat4 doggy(1);
        doggy = glm::translate(doggy, glm::vec3(0.0f, 2.0f, 0.0f));
        model = doggy;
        doggy = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        doggy = glm::translate(doggy, glm::vec3(5.0f, 0.0f, 5.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(doggy));
        dog.Draw(shader);
        

        //Terreno base
        model = glm::translate(model, glm::vec3(-8.0f, -0.4f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        terrain.Draw(shader);

        //Edificio principal
        model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -3.0f));
        model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        farm.Draw(shader);
        
        //Maiz 1
        model = glm::translate(model, glm::vec3(1.0f, 0.0f, 180.0f));
        model = glm::scale(model, glm::vec3(9.0f, 18.0f, 9.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        corns_sm.Draw(shader);
        
        //Maiz 2
        //NO se necesita transformacion de escala ya que se mantiene igual al modelo Maiz 1
		//Debido a que comparten el mismo modelo se genera en la misma posicion por lo que se traslada 6 unidades en el eje Z a partir de la posicion de Maiz 1
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 6.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        corns_sm.Draw(shader);

        //Maiz 3
		//De la misma forma que Maiz 2, comparten el mismo modelo y se trasladan 3 unidades en el eje X a partir de la posicion de Maiz 2
        model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        corns_sm.Draw(shader);

        //Maiz 4
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -6.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        corns_sm.Draw(shader);
        
		//Heno 1
        glm::mat4 model2(1);
        model2 = glm::translate(model2, glm::vec3(-18.0f, 1.7f, -9.0f));
        model2 = glm::scale(model2, glm::vec3(0.5f, 0.5f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model2));
        hay.Draw(shader);

        //Heno 2
		//Mismo concepto que los maices, se modelan los demas Henos a partir de la posicion y escala del modelo original Heno 1
        model2 = glm::translate(model2, glm::vec3(0.0f, 0.0f, -2.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model2));
        hay.Draw(shader);

        //Heno 3
        model2 = glm::translate(model2, glm::vec3(2.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model2));
        hay.Draw(shader);

        //Heno 4
        model2 = glm::translate(model2, glm::vec3(0.0f, 0.0f, 2.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model2));
        hay.Draw(shader);
        
		//Arbol 1
        model = glm::translate(model, glm::vec3(-38.0f, 0.0f, -58.0f));
        model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tree.Draw(shader);
        model2 = model;

		//Arbol 2
        model = glm::translate(model, glm::vec3(58.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tree.Draw(shader);

		//Arbol 3
        model2 = glm::translate(model2, glm::vec3(-8.0f, 0.0f, 4.0f));
        model2 = glm::rotate(model2, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model2));
        tree.Draw(shader);

		//Arbol 4
        model2 = glm::translate(model2, glm::vec3(-8.0f, 0.0f, 3.0f));
        model2 = glm::rotate(model2, glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model2));
        tree.Draw(shader);
        
        //Camino 1
		//Se crea otra matriz para el camino para que sea mas sencillo de manipular
        glm::mat4 camino(1);
        camino = glm::translate(camino, glm::vec3(-16.7f, 1.6f, -5.7f));
        glm::mat4 barril(1);
        barril = camino;
        camino = glm::rotate(camino, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(camino));
        stone_path_lowpoly.Draw(shader);

		//Camino 2
        camino = glm::translate(camino, glm::vec3(0.0f, 0.0f, 4.2f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(camino));
        stone_path_lowpoly.Draw(shader);

		//Camino 3
        camino = glm::translate(camino, glm::vec3(0.0f, 0.0f, 4.2f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(camino));
        stone_path_lowpoly.Draw(shader);

        //Barril 1
        barril = glm::translate(barril, glm::vec3(1.5f, 0.05f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(barril));
        barrel.Draw(shader);

        //Barn
		barril = glm::translate(barril, glm::vec3(18.0f, 0.0f, 18.0f));
		model2 = barril;
        barril = glm::rotate(barril, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		barril = glm::scale(barril, glm::vec3(0.5f, 0.5f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(barril));
		barn.Draw(shader);

		//Arbol 5
		model2 = glm::translate(model2, glm::vec3(9.0f, 0.0f, -2.0f));
        model = model2;
        model2 = glm::rotate(model2, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model2));
		tree.Draw(shader);

        //Arbol 6
        model = glm::translate(model, glm::vec3(-33.0f, 0.0f, 8.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tree.Draw(shader);

        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime + 0.0005f);
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime + 0.0005f);
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime + 0.0005f);
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime + 0.0005f);
    }

   
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

 

 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

