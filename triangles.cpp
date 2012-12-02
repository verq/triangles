#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define NUMBER_OF_VERTEX 18

GLfloat first_triangle[NUMBER_OF_VERTEX];
GLfloat second_triangle[NUMBER_OF_VERTEX];

double scale = 1.0;


GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
int openWindow();

void init_first_triangle();
void init_second_triangle();
void draw(GLuint program, GLfloat* triangle, GLuint vertexbuffer);
		

int main() {
	if (openWindow() == -1) return -1;
	
	init_first_triangle();
	init_second_triangle();
	
	glfwEnable( GLFW_STICKY_KEYS );
	
	glClearColor(0.0f, 0.0f, 0.6f, 0.0f);
	
	GLuint first_triangleID = LoadShaders("VertexShader.glsl", "FragmentShader.glsl");
	GLuint second_triangleID = LoadShaders("VertexShader.glsl", "FragmentShader2.glsl");
	
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)36);
		
		draw(first_triangleID, first_triangle, vertexbuffer);
		draw(second_triangleID, second_triangle, vertexbuffer);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glfwSwapBuffers();
	} while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED));

	glfwTerminate();
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(first_triangleID);
	glDeleteProgram(second_triangleID);

	return 0;
}


void draw(GLuint program, GLfloat* triangle, GLuint vertexbuffer) {
		glUseProgram(program);
		GLuint scaleID = glGetUniformLocation(program, "scale");
		
		glBufferData(GL_ARRAY_BUFFER, NUMBER_OF_VERTEX * sizeof(triangle), triangle, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		glProgramUniform1f(program, scaleID, scale);

		glDrawArrays(GL_TRIANGLES, 0, 3);
}

void init_first_triangle() {
	for (int i = 0; i < NUMBER_OF_VERTEX / 2; i++) {
		if (i % 3 == 2) first_triangle[i] = 0.0f;
	}
	first_triangle[0] = 0.5f;
	first_triangle[1] = -0.5f;
	
	first_triangle[3] = 0.5f; 
	first_triangle[4] = 0.5f; 
	
	first_triangle[6] = -0.5f; 
	first_triangle[7] = 0.5f;
	
	for (int i = NUMBER_OF_VERTEX / 2; i < NUMBER_OF_VERTEX; i++) {
		if (i % 4 == 1) first_triangle[i] = 1.0f;
		else first_triangle[i] = 0.0f;
	}	
}

void init_second_triangle() {
	for (int i = 0; i < NUMBER_OF_VERTEX / 2; i++) {
		if (i % 3 == 2) second_triangle[i] = 0.0f;
	}
	second_triangle[0] = 0.5f;
	second_triangle[1] = -0.5f;
	
	second_triangle[3] = -0.5f; 
	second_triangle[4] = -0.5f; 
	
	second_triangle[6] = -0.5f; 
	second_triangle[7] = 0.5f;
	
	for (int i = NUMBER_OF_VERTEX / 2; i < NUMBER_OF_VERTEX; i++) {
		if (i % 4 == 1) second_triangle[i] = 1.0f;
		else second_triangle[i] = 0.0f;
	}	
}

int openWindow() {
	if (!glfwInit()) {
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

	if(!glfwOpenWindow(800, 600, 0,0,0,0, 32,0, GLFW_WINDOW)) {
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		return -1;
	}

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	glfwSetWindowTitle("Triangles");
	return 0;
}

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()){
		std::string Line = "";
		while (getline(VertexShaderStream, Line)) VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	} else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		return 0;
	}

	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while(getline(FragmentShaderStream, Line)) FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

