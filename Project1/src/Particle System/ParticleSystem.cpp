#include "ParticleSystem.h"

void ParticleSystem::EmmitterInfo::ParticlesPerSecond(float& pps)
{
	particlesPerSecond = pps;

}

ParticleSystem::ParticleSystem()
{

}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::InitializeParticles(EmmitterInfo& initialState)
{
	this->m_EmitterInitState = initialState;

	// Allocate all the particles now, not when they are needed. 
	// ("pool" of particles to draw from
	this->m_particles.clear();
	this->m_particles.reserve(initialState.maxNumParticles);

	// Assume the particles start invisible and dead.
	for (unsigned int count = 0; count != initialState.maxNumParticles; count++)
	{
		Particle newParticle;
		// TODO: Maybe we want to set some of the particles attributes?
		//
		this->m_particles.push_back(newParticle);
	}
	// At this point, we have maxNumParticles 'dead' particles


	return;
}

void ParticleSystem::GetParticleList(std::vector<ParticleRender>& vecParticles)
{
	vecParticles.clear();


	

	for (Particle& curParticle : this->m_particles)
	{
		if (curParticle.lifetime > 0.0)
		{
			ParticleRender drawnParticle;
			drawnParticle.position = curParticle.position;

			drawnParticle.orientation = curParticle.orientation;

			drawnParticle.scaleXYZ = curParticle.scaleXYZ;

			vecParticles.push_back(drawnParticle);
		}
	}
	return;

}

void ParticleSystem::Update(double deltaTime)
{
	if (deltaTime > MAX_DELTATIME)
	{
		deltaTime = MAX_DELTATIME;
	}

	// Update the seconds elapsed (for things that happen 'per second')
	this->m_SecondElapsedCounter += deltaTime;
	if (this->m_SecondElapsedCounter > 1.0)
	{
		// A second has passed
		this->m_SecondElapsedEvent();
		this->m_SecondElapsedCounter -= 1.0;
	}//if ( this->m_SecondElapsedCounter > 1.0 )

	// 'create' some particles this frame
	unsigned int numParticlesToCreate = this->m_EmitterInitState.particlesPerSecond;
	unsigned int numParticlesCreatedSoFar = 0;
	for (Particle& curParticle : this->m_particles)
	{
		// Created enough?
		if (numParticlesCreatedSoFar >= numParticlesToCreate)
		{
			// Exit for loop
			break;
		}

		if (curParticle.lifetime <= 0.0)
		{
			// It's dead, Jim
			// 'Revive' it
			curParticle.lifetime = this->m_GetRandFloat(this->m_EmitterInitState.minLifetime,
				this->m_EmitterInitState.maxLifetime);

			// TODO: Set the particle state
			curParticle.position = this->m_EmitterInitState.emitterPosition;
			curParticle.position += this->m_GetRandVec3Float(this->m_EmitterInitState.positionOffsetMin,
				this->m_EmitterInitState.positionOffsetMax);

			curParticle.velocity = this->m_GetRandVec3Float(this->m_EmitterInitState.initVelocityMin,
				this->m_EmitterInitState.initVelocityMax);

			curParticle.rotSpeed = glm::quat(this->m_GetRandVec3Float(this->m_EmitterInitState.orientationChangeMinRadians,
				this->m_EmitterInitState.orientationChangeMaxRadians));


			// TODO: Maybe we don't want this here? 
			curParticle.acceleration = this->m_EmitterInitState.constantForce;

			numParticlesCreatedSoFar++;
		}
	}//for (cParticle &curParticle :

	// Perfomrm a basic Euler integration step on any 'alive' partciles
	// std::vector< cParticle > m_particles;
	for (Particle& curParticle : this->m_particles)
	{
		if (curParticle.lifetime > 0.0)
		{
			// It's alive!!

			curParticle.velocity += curParticle.acceleration * (float)deltaTime;

			curParticle.position += curParticle.velocity * (float)deltaTime;

			// Orientation, too
			curParticle.orientation *= curParticle.rotSpeed;

			curParticle.lifetime -= (float)deltaTime;

			float scaleChange = this->m_GetRandFloat(this->m_EmitterInitState.uniformScaleChangeMin,
				this->m_EmitterInitState.uniformScaleChangeMax);
			curParticle.scaleXYZ.x += scaleChange;
			curParticle.scaleXYZ.y += scaleChange;
			curParticle.scaleXYZ.z += scaleChange;

		}
	}//for (cParticle &curParticle :


	return;
}

void ParticleSystem::UpdatePosition(glm::vec3 newPosition)
{
	this->m_EmitterInitState.emitterPosition = newPosition;
	return;
}

void ParticleSystem::UpdateConstantForce(glm::vec3 newForce, bool bUpdateParticlesToo)
{
	this->m_EmitterInitState.constantForce = newForce;

	if (bUpdateParticlesToo)
	{
		for (Particle& curParticle : this->m_particles)
		{
			curParticle.acceleration = this->m_EmitterInitState.constantForce;
		}
	}

	return;
}

glm::vec3 ParticleSystem::GetPosition(void)
{
	return this->m_EmitterInitState.emitterPosition;
}

void ParticleSystem::m_SecondElapsedEvent(void)
{
	//TODO : Some Cool event haha
}

float ParticleSystem::m_GetRandFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

glm::vec3 ParticleSystem::m_GetRandVec3Float(glm::vec3 min, glm::vec3 max)
{
	glm::vec3 randPoint;
	randPoint.x = this->m_GetRandFloat(min.x, max.x);
	randPoint.y = this->m_GetRandFloat(min.y, max.y);
	randPoint.z = this->m_GetRandFloat(min.z, max.z);

	return randPoint;
}

unsigned int ParticleSystem::m_GetRandomInt(unsigned int min, unsigned int max)
{
	unsigned int output = min + (rand() % static_cast<unsigned int>(max - min + 1));

	return output;
}
