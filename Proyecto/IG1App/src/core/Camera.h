#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;
class Mesh;

/// @brief Clase que controla el punto de vista del la ventana, almacena la matriz de vista y la de proyeccion. Se puede configurar para que la camara renderice en formato perspectiva u ortografico.
class Camera
{
private:
	/// @brief Matriz de vista
	glm::mat4 _view = glm::mat4(1.0f);
	/// @brief Matriz de pryección
	glm::mat4 _projection;

	/// @brief Defide si se usa perspectiva (true) o si ortografico (false)
	bool _usePerspective = true;
	/// @brief El fiel of view de la camara
	float _fov = 45.0f;
	/// @brief Distancia a partir de donde se empiezan a ver las cosas
	float _nearDistance = 0.1f;
	/// @brief Distancia donde se dejan de ver las cosas
	float _farDistance = 100.0f;
public:
	Camera();

	/// @brief Manda a la GPU las matrices de proyeccion y vista
	/// @param m La mesh objetivo
	void uploadToGPU(Mesh* m);

	/// @brief La matriz de vista de la camara
	/// @return La matriz de vista
	glm::mat4 viewMatrix() { return _view; }

	/// @brief Establece la matriz de vista
	/// @param view La nueva matriz
	void setViewMat(glm::mat4 view) { _view = view; }
private:
	/// @brief Se encarga de construir la matriz de proyeccion de dependiedo de los parametros
	void buildProjectionMat();

	/// @brief Manda a la gpu la matriz de proyeccion
	/// @param shader El shader objetivo a modificar
	void uploadProjectionToGPU(Shader* shader);

	/// @brief Manda a la gpu la matriz de vista
	/// @param shader El shader objetivo a modificar
	/// @param model La matriz de modelado del mesh
	void uploadViewToGPU(Shader* shader, glm::mat4 model);
};

