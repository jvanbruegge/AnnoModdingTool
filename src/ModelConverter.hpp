#pragma once
#include <string>

#include "ModelStructs.hpp"

class ModelConverter
{
public:
	virtual Model importModel(std::string path) = 0;
	virtual void exportModel(const Model& model, std::string location = "") = 0;

private:

};