#include "SceneManager.h"
#include <core/Scene.h>
#include <ec/entity.h>
#include <component/Transform.h>
#include <component/MeshRenderer.h>
#include <core/mesh/CubeMesh.h>
#include <managers/ResourceManager.h>
#include <core/serialize/JsonSerializer.h>

SceneManager::~SceneManager() {
	delete _currentScene;
}

bool SceneManager::init() {
	return true;
}

void SceneManager::update() {
	if (!_currentScene) return;

	_currentScene->update();
}

void SceneManager::render() const {
	if (!_currentScene) return;

	_currentScene->render();
}

void SceneManager::loadScenes(std::string& path) {
	cme::JsonSerializer serializer;
	serializer.load(path);
	if (_currentScene) delete _currentScene;

	_currentScene = new Scene("");
	_currentScene->deserialize(serializer);
}

void SceneManager::saveActiveScene(std::string& path) const{
	cme::JsonSerializer serializer;
	_currentScene->serialize(serializer);
	serializer.save(path);
}