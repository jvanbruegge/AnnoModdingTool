#include "RpmConverter.hpp"

using namespace std;

Model RpmConverter::importModel(std::string path)
{
	ifstream file(path, ios::binary | ios::ate);
	Model model;

	if (file.is_open())
	{
		streampos size = file.tellg();
		uint8_t* data = new uint8_t[size];

		file.seekg(0, ios::beg);
		file.read((char*)data, size);
		file.close();

		int start = skipToStart(data);
		uint32_t vertexCount = data[start] | (data[start + 1] << 8) | (data[start + 2] << 16) | (data[start + 3] << 24);
		uint32_t vertexDataSize = data[start + 4] | (data[start + 5] << 8) | (data[start + 6] << 16) | (data[start + 7] << 24);
		start += 8;

		model.vertices.resize(vertexCount);

		for (int i = 0; i < vertexCount; i++) {
			float x, y, z;
			uint16_t hx = data[start] | (data[start + 1] << 8);
			uint16_t hy = data[start + 2] | (data[start + 3] << 8);
			uint16_t hz = data[start + 4] | (data[start + 5] << 8);
			float32(&x, hx);
			float32(&y, hy);
			float32(&z, hz);
			start += 8;

			float nx = 0; //(float)(data[start + 0] | (data[start + 1] << 8) | (data[start + 2] << 16) | (data[start + 3] << 24));
			float ny = 0; //(float)(data[start + 7] | (data[start + 6] << 8) | (data[start + 5] << 16) | (data[start + 4] << 24));
			float nz = 0; //(float)(data[start + 11] | (data[start + 10] << 8) | (data[start + 9] << 16) | (data[start + 8] << 24));
			start += 12;

			float u, v;
			uint16_t hu = data[start] | (data[start + 1] << 8);
			uint16_t hv = data[start + 2] | (data[start + 3] << 8);
			float32(&u, hu);
			float32(&v, hv);
			start += 4;

			model.vertices[i] = Vertex(x, y, z, nx, ny, nz, u, v);
		}

		uint32_t indexCount = data[start] | (data[start + 1] << 8) | (data[start + 2] << 16) | (data[start + 3] << 24);
		uint32_t indexDataSize = data[start + 4] | (data[start + 5] << 8) | (data[start + 6] << 16) | (data[start + 7] << 24);
		start += 8;

		model.triangles.resize(indexCount / 3);

		for (int i = 0; i < indexCount / 3; i++)
		{
			uint16_t i1 = data[start] | (data[start + 1] << 8);
			uint16_t i2 = data[start + 2] | (data[start + 3] << 8);
			uint16_t i3 = data[start + 4] | (data[start + 5] << 8);
			model.triangles[i] = Triangle(i1, i2, i3);
			start += 6;
		}

		delete[] data;
	}

	return model;
}

void RpmConverter::exportModel(const Model& model, std::string location)
{

}

int RpmConverter::skipToStart(const uint8_t* data)
{
	int start = 0x9C; //jumps to first variable-length string, more infos here: http://forum.xentax.com/viewtopic.php?f=10&t=7641&p=102989&hilit=rdm#p102989
	int skip1 = skipString(start, data);
	int skip2 = skipString(skip1, data) + 4 * 34;
	return skipString(skip2, data) + 4 * 46;
}

int RpmConverter::skipString(const int start, const uint8_t* data)
{
	uint32_t strLen = data[start] | (data[start + 1] << 8) | (data[start + 2] << 16) | (data[start + 3] << 24);
	return start + 8 + strLen;
}

void RpmConverter::float32(float* out, const uint16_t in)
{
	uint32_t t1;
	uint32_t t2;
	uint32_t t3;

	t1 = in & 0x7fff;                       // Non-sign bits
	t2 = in & 0x8000;                       // Sign bit
	t3 = in & 0x7c00;                       // Exponent

	t1 <<= 13;                              // Align mantissa on MSB
	t2 <<= 16;                              // Shift sign bit into position

	t1 += 0x38000000;                       // Adjust bias

	t1 = (t3 == 0 ? 0 : t1);                // Denormals-as-zero

	t1 |= t2;                               // Re-insert sign bit

	*((uint32_t*)out) = t1;
};