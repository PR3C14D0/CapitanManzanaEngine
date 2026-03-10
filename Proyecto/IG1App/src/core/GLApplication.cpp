#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLApplication.h"
#include <utils/logger.h>

#include <managers/ResourceManager.h>
#include "mesh/CubeMesh.h"
#include <core/Scene.h>
#include <ec/entity.h>
#include <component/Transform.h>
#include <component/MeshRenderer.h>

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
	Scene* scene = new Scene();

	auto cube = scene->addGameObject(scene);
	auto tr =cube->addComponent<Transform>();
	cube->addComponent<MeshRenderer>(new CubeMesh(rscrM().getShader("default")));

	tr->setPosition(glm::vec3(0, 0, -3));
	float angle = 0.0f;
	while (!glfwWindowShouldClose(_window))
	{
		processInput(_window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		tr->setRotation(glm::vec3(0, angle++, angle));
		scene->render();

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	delete scene;
}

void GLApplication::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}