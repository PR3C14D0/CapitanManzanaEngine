#pragma once
#include <array>
#include <vector>
#include <functional>
#include <ec/ec.h>

class Camera;

class Scene
{
protected:
	/// @param gameObjectsByLayer vectores de objetos según la layer a la que pertencen
	/// El vector de gameObjectsByLayer[n] tendría todos los objetos pertencientes a la layer n 
	std::array<std::vector<ec::entity_t>, ec::ent::maxGroupLayer> _gameObjectsByGroup;

	/// @brief inicializa la escena creando todos los objetos que vayan a haber en la misma
	virtual void init() {};

	Camera* _cam = nullptr;
public:
	Scene();

	virtual ~Scene();

	/// @brief renderiza todos los objetos de la escena según la layer y posteriormente renderiza la UI
	void render() const;

	/// @brief actualiza todos los objetos de la escena
	void update();

	/// @brief quita todos los objetos que no estén activos de la escena
	void refresh();

	/// @brief permite añadir objetos a la escena
	/// @param grID Grupo al que añadir al objeto creado
	ec::entity_t addGameObject(Scene* scene, ec::ent::groupID grID = ec::ent::None);

	const std::array<std::vector<ec::entity_t>, ec::ent::maxGroupLayer>& getSceneObjects() { return _gameObjectsByGroup; }
	Camera* getCamera() { return _cam; }
};

