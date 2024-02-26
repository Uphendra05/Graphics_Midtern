#pragma once
#include "../Renderer.h"
#include <iostream>






class ParticleSystem
{
public:

	ParticleSystem();
	~ParticleSystem();

	struct EmmitterInfo
	{
		unsigned int maxNumParticles = 0;
		glm::vec3 emitterPosition = glm::vec3(0.0f);

		glm::vec3 positionOffsetMin = glm::vec3(0.0f);
		glm::vec3 positionOffsetMax = glm::vec3(0.0f);

		void ParticlesPerSecond(float& pps);
		int particlesPerSecond;

		float minLifetime = 0.0f;
		float maxLifetime = 0.0f;
		glm::vec3 initVelocityMin = glm::vec3(0.0f);
		glm::vec3 initVelocityMax = glm::vec3(0.0f);

		glm::vec3 orientationChangeMinRadians = glm::vec3(0.0f);
		glm::vec3 orientationChangeMaxRadians = glm::vec3(0.0f);

		float uniformScaleChangeMin = 0.0f;
		float uniformScaleChangeMax = 0.0f;

		glm::vec3 constantForce = glm::vec3(0.0f);
	};




	void InitializeParticles(EmmitterInfo& initialState);

	struct ParticleRender
	{
		glm::vec3 position = glm::vec3(0.0f);
		glm::quat orientation = glm::quat(glm::vec3(0.0f));
		glm::vec3 scaleXYZ = glm::vec3(1.0f);
		// Maybe scale, orientation, etc.
	};

	void GetParticleList(std::vector<ParticleRender>& vecParticles);

	void Update(double deltaTime);
	void UpdatePosition(glm::vec3 newPosition);
	void UpdateConstantForce(glm::vec3 newForce, bool bUpdateParticlesToo = false);

	glm::vec3 GetPosition(void);


private:

	class Particle
	{
	public:
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 velocity = glm::vec3(0.0f);
		glm::vec3 acceleration = glm::vec3(0.0f);

		float lifetime = 0.0f;

		glm::quat orientation = glm::quat(glm::vec3(0.0f));
		glm::quat rotSpeed = glm::quat(glm::vec3(0.0f));
		glm::vec3 scaleXYZ = glm::vec3(0.0f);
	};

	std::vector<Particle> m_particles;
	EmmitterInfo m_EmitterInitState;

	double m_SecondElapsedCounter = 0.0;

	void m_SecondElapsedEvent(void);

	float m_GetRandFloat(float a, float b);
	glm::vec3 m_GetRandVec3Float(glm::vec3 min, glm::vec3 max);

	unsigned int m_GetRandomInt(unsigned int min, unsigned int max);

	const double MAX_DELTATIME = 1.0 / 60.0;

};

