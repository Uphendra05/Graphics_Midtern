#pragma once

#include <string>
#include "Renderer.h"
#include <vector>
#include "../src/Texture/BaseTexture.h"



#include <iostream>


class Texture : public BaseTexture
{

public:
	Texture() {}
	Texture(std::string& filePath);
	~Texture() {}
	unsigned int id;
	std::string path;
	std::string type;
	void LoadTexture(const std::string& filePath, const std::string& _type);


	void Bind() override;
	void Unbind() override;
	void SetTextureSlot(int place = 0) override;

private:
	unsigned int loadTextureID(char const* path);

	void DrawProperties() override;
	void SceneDraw() override;
};