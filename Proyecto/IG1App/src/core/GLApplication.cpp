#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLApplication.h"
#include <utils/logger.h>
#include <core/Camera.h>

#include <managers/ResourceManager.h>
#include "mesh/TriangleMesh.h"
#include "mesh/QuadMesh.h"
#include "mesh/CubeMesh.h"

GLApplication::~GLApplication() {
	if (ResourceManager::HasInstance()) {
		ResourceManager::Release();
	}

	glfwTerminate();
}

bool GLApplication::init() {
	// inicializar GLFW
	if (glfwInit() == GLFW_FALSE) {
		return false;
	}

	_window = glfwCreateWindow(_width, _height, "LearnOpenGL", NULL, NULL);
	if (_window == NULL)
	{
		LOG_ERROR("Failed to create GLFW window");
		return false;
	}

	glfwMakeContextCurrent(_window);
	// Inicializad GLAD que carga los punteros a las funciones
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERROR("Failed to initialize GLAD");
		return false;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	});

	if (!loadManagers()) return false;

	return true;
}

bool GLApplication::loadManagers() {
	if (!ResourceManager::Init()) {
		LOG_ERROR("Error al inicializar el Resource Manager");
		return false;
	}

	return true;
}

void GLApplication::start() {
	Camera* cam = new Camera();

	CubeMesh* mesh = new CubeMesh(rscrM().getShader("default"));
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1, 0, 1));
	mesh->setModelMatrix(model);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0, 0, -3.0f));
	cam->setViewMat(view);

	while (!glfwWindowShouldClose(_window))
	{
		processInput(_window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		model = glm::rotate(model, glm::radians(0.5f), glm::vec3(0, 1, 0));
		mesh->setModelMatrix(model);
		cam->uploadToGPU(mesh);
		mesh->render();

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	delete mesh;
	delete cam;
}

void GLApplication::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}