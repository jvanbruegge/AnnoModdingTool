#pragma once
#include <fstream>
#include <stdint.h>

#include "../ModelConverter.hpp"

class PlyConverter : public ModelConverter
{
public:
	Model importModel(std::string path);
	void exportModel(const Model& model, std::string location);

private:

};