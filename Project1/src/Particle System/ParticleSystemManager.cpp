#include "ParticleSystemManager.h"

ParticleSystemManager::ParticleSystemManager()
{
	AddDefaultModelToEmitter();
}

ParticleSystemManager::~ParticleSystemManager()
{
}

void ParticleSystemManager::StartParticleSystem(EmmitterShape shape)
{
	switch (shape)
	{
	case EmmitterShape::SPHERE:
		//particleSystem->InitializeParticles(add the emmitter);

		break;
	case EmmitterShape::CONE:
		//particleSystem->InitializeParticles(add the emmitter);

		break;
	case EmmitterShape::BOX:
		//particleSystem->InitializeParticles(add the emmitter);

		break;
	case EmmitterShape::CYLINDER:
		//particleSystem->InitializeParticles(add the emmitter);

		break;
	default:
		break;
	}
}

void ParticleSystemManager::AddDefaultModelToEmitter()
{
	//add default quad model
}

void ParticleSystemManager::AddModelToEmitter(Model* model)
{
	// add desired model
}

void ParticleSystemManager::RemoveModelFromEmitter(Model* model)
{
	
	model = nullptr;
	AddDefaultModelToEmitter();
	// remove model
}

void ParticleSystemManager::Update(float deltaTime)
{
	particleSystem->Update(deltaTime);

	
}
