#pragma once
#include <ec/component.h>
#include <string>

class Mesh;
class Camera;
class Transform;

class MeshRenderer : public ec::Component, public ec::RenderComponent {
private:
	Mesh* _mesh = nullptr;
	Camera* _cam = nullptr;
	Transform* _tr = nullptr;
public:
	__CMPID_DECL__(ec::comp::MESH_RENDERER)

	MeshRenderer() : _mesh(nullptr) {}
	MeshRenderer(Mesh* mesh) : _mesh(mesh) {}
	~MeshRenderer();

	void render() const override;

	void initComponent() override;

	void serialize(cme::JsonSerializer& s) const override;
	void deserialize(cme::JsonSerializer& s) override;

	std::string serializeID() const override { return "MeshRenderer"; }
};