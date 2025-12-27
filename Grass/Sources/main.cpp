#include <MiraEngine.hpp>

class GameWorld : public Mira::World {
public:
	GameWorld() {}

	void init() override {
		m_camera = new Mira::Camera;
		m_mesh = Mira::Mesh::cubeMesh();
		m_material = Mira::Material::createMaterial();

		Mira::Cube* cube = new Mira::Cube(m_camera);
		cube->setMaterial(m_material);
		cube->setMesh(m_mesh);

		m_entities.push_back(cube);
	}

	void shutdown() override {
		if (m_camera)
			delete m_camera;
	}

	~GameWorld() {}

private:
	Mira::Camera* m_camera;
	Mira::Mesh* m_mesh;
	Mira::Material* m_material;
};

class Grass : public Mira::Engine {
public:
	Grass() {
		setWorld(new GameWorld());
	}
	~Grass() {}

private:
};

CREATE_GAME(Grass);