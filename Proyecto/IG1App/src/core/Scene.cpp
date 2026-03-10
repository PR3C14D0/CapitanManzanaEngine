#include "Scene.h"
#include <ec/entity.h>
#include <core/Camera.h>

Scene::Scene() {
	_cam = new Camera();
}

Scene::~Scene() {

	for (int i = 0; i < ec::ent::maxGroupLayer; i++) {
		for (ec::Entity* gObj : _gameObjectsByGroup[i]) {
			delete gObj;
		}
	}

	delete _cam;
}

void Scene::refresh() {
	for (ec::groupID_t gId = 0; gId < ec::ent::maxGroupLayer; gId++) {
		auto& grpEnts = _gameObjectsByGroup[gId];
		grpEnts.erase(
			std::remove_if(grpEnts.begin(), grpEnts.end(),
				[](ec::entity_t e) {
					if (e->isAlive()) {
						return false;
					}
					else {
						delete e;
						return true;
					}
				}),
			grpEnts.end());
	}
}

void Scene::render() const {
	for (int i = 0; i < ec::ent::maxGroupLayer; i++) {
		for (ec::entity_t gObj : _gameObjectsByGroup[i]) {
			gObj->render();
		}
	}
}

void Scene::update() {
	for (int i = 0; i < ec::ent::maxGroupLayer; i++) {
		for (ec::entity_t gObj : _gameObjectsByGroup[i]) {
			gObj->update();
		}
	}
};

ec::entity_t Scene::addGameObject(Scene* scene, ec::ent::groupID grID) {
	ec::entity_t gObj = new ec::Entity(grID, scene);
	_gameObjectsByGroup[grID].push_back(gObj);
	return gObj;
}