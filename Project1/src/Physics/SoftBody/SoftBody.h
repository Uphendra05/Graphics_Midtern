#pragma once
#ifndef SOFTBODY_H
#define SOFTBODY_H


#include "../../src/model.h"
#include "../PhysicsCollisionTypes.h"
#include"../PhysicsObject.h"

struct Point
{
	Point() = default;

	glm::vec3 curPosition = glm::vec3(0.0f);
	glm::vec3 oldPosition = glm::vec3(0.0f);

	Vertex* vertexData = nullptr;
	bool isLocked = false;
};


struct Constraints
{
	Constraints() = default;
	Constraints(Point* pA, Point* pB) : pointA(pA), pointB(pB) 
	{
		length = glm::distance(pointA->curPosition, pointB->curPosition);
	
	};

	Point* pointA;
	Point* pointB;

	float length = 0;
	bool isActive = true;
};


class SoftBodyObjs : public Model
{

public:

	SoftBodyObjs() ;
	~SoftBodyObjs();

	bool isSoftBodyActive = true;

	void InitializeSoftBody();

	void SimulatePoints(float deltaTime);
	void SimulateConstraints(float deltaTime);
	void StartSimultaion(float deltaTime);

	void PointAndConstraintsSetup();

	void UpdateMeshVertices();


	void CalculateMatrixForVertices(std::shared_ptr<Mesh> vertSize) const;
	void SetupPoints(std::shared_ptr<Mesh> vertSize);
	void SetupConstraints(std::shared_ptr<Mesh> vertSize);

	void DrawProperties()override;
	void SceneDraw()override;

	 void Start() override;
	 void Update(float deltaTime) override;
	 void Render()override;
	 void OnDestroy()override;

private:

	bool showDebug = true;
	float tightnessFactor = 1;

	void CleanZeroes(glm::vec3& value);
	void UpdateNormals();

	const double MAX_DELTATIME = 1.0 / 60.0;

	float renderRadius = 0.025f;
	float lockRadius;
	glm::vec3 lockSphereCenter;

	glm::vec3 acceleration = glm::vec3(0.0f,-1.0f,0.0f);

	std::vector<Triangle> m_ListOfTriangles;
	std::vector<Point*> m_ListOfPoints;
	std::vector<Constraints*> m_ListOfConstraints;


};

#endif // SOFTBODY_H