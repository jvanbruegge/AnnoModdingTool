#include <iostream>
#include <string>
#include <cstdio>

#include "ModelConverters\RpmConverter.hpp"
#include "ModelConverters\PlyConverter.hpp"
#include "ModelStructs.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	RpmConverter rpm;
	PlyConverter ply;

	cout << "Please enter model name (without .rdm)" << endl;
	string input;
	getline(cin, input);

	Model model = rpm.importModel(input + ".rdm");
	ply.exportModel(model, input + ".ply");

	cout << "Model successfully converted" << endl;
	cout << "Press any key to quit" << endl;
	getchar();
}