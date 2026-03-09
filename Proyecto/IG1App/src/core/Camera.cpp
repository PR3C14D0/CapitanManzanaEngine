#include "Camera.h"
#include <core/GLApplication.h>
#include <core/Shader.h>
#include <utils/logger.h>
#include <managers/ResourceManager.h>
#include <core/Mesh.h>

Camera::Camera() {
	buildProjectionMat();
}

void Camera::buildProjectionMat() {
	if (_usePerspective) {
		_projection = glm::perspective(_fov, gla().width() / gla().height(), _nearDistance, _farDistance);
	}
	else {
		_projection = glm::ortho(0.0f, gla().width(), 0.0f, gla().height(), _nearDistance, _farDistance);
	}
}

void Camera::uploadToGPU(Mesh* m) {
	Shader* s = m->shader();
	uploadProjectionToGPU(s);
	uploadViewToGPU(s, m->modelMatrix());
}

void Camera::uploadProjectionToGPU(Shader* shader) {
	if (!shader) {
		LOG_WARN("El shader para hacer upload de la matriz de proyeccion es nulo");
		return;
	}

	shader->use();
	shader->setUniform("projection", _projection);
}

void Camera::uploadViewToGPU(Shader* shader, glm::mat4 model) {
	if (!shader) {
		LOG_WARN("El shader para hacer upload de la matriz de vista es nulo");
		return;
	}
	glm::mat4 modelView = _view * model;
	shader->use();
	shader->setUniform("modelView", modelView);
}