#pragma once
#include "ParticleSystem.h"
#include "../model.h"


enum class EmmitterShape
{
	SPHERE = 0,
	CONE = 1,
	BOX = 2,
	CYLINDER = 3

};

class ParticleSystemManager
{
public:
	ParticleSystemManager();
	~ParticleSystemManager();

	void StartParticleSystem(EmmitterShape shape);
	void AddDefaultModelToEmitter();
	void AddModelToEmitter(Model* model);
	void RemoveModelFromEmitter(Model* model);

	void Update(float deltaTime);



private:

	ParticleSystem* particleSystem;
	Model* defaultModel;
	EmmitterShape m_EmmitterShapes;

};

