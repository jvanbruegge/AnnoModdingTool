#include "PlyConverter.hpp"

using namespace std;

Model PlyConverter::importModel(std::string path)
{
	return Model();
}

void PlyConverter::exportModel(const Model& model, std::string location)
{
	ofstream ply(location);

	if (ply.is_open())
	{
		ply << "ply" << endl;
		ply << "format ascii 1.0" << endl;
		ply << "element vertex " << model.vertices.size() << endl;
		ply << "property float x" << endl;
		ply << "property float y" << endl;
		ply << "property float z" << endl;
		ply << "element face " << model.triangles.size() << endl;
		ply << "property list uchar int vertex_indices" << endl;
		ply << "end_header" << endl;

		for (const Vertex& vertex : model.vertices)
		{
			ply << vertex.x << " " << vertex.y << " " << vertex.z << endl;
		}

		for (const Triangle& triangle : model.triangles)
		{
			ply << "3 " << triangle.a << " " << triangle.b << " " << triangle.c << endl;
		}

		ply.close();
	}
}