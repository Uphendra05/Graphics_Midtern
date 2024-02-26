#pragma once
#include <vector>
#include "PhysicsObject.h"
#include "SoftBody/SoftBody.h"


class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	static PhysicsEngine& GetInstance();
	float timer = 0;
	float fixedTimeStep = 0.01f;


	void AddPhysicsObjects(PhysicsObject* objs);
	void RemovePhysicsObject(PhysicsObject* objs);
	void RemoveAllPhysicsObject();

	void AddSoftBodyObject(SoftBodyObjs* objs);
	void RemoveSoftBodyObject(SoftBodyObjs* objs);

	void Update(float deltaTime);
	void UpdatePhysics(float deltatime);
	void UpdateVerlet(float deltatime);
	void UpdateMeshVertices();


	std::vector<glm::vec3> collisionPoints;
	std::vector<glm::vec3> collisionNormals;
	std::vector<SoftBodyObjs*> softbodyObjects;

private:
	std::vector<PhysicsObject*> physicsObjects;
     
};

