
#include "stdafx.h"
#include "modelimporter.h"


namespace graphic
{

	bool ReadRawMeshFileV1( const string &fileName, sRawMesh &raw );
	bool ReadRawMeshFileV2( const string &fileName, sRawMesh &raw );

}

using namespace graphic;


// load all exporter version
bool graphic::ReadRawMeshFile( const string &fileName, sRawMesh &raw )
{
	using namespace std;
	ifstream fin(fileName.c_str());
	if (!fin.is_open())
		return false;

	string version;
	fin >> version;

	if (version == "EXPORTER_V1")
	{
		return ReadRawMeshFileV1(fileName, raw);
	}
	else if (version == "EXPORTER_V2")
	{
		return ReadRawMeshFileV2(fileName, raw);
	}

	return true;
}


// load exporter version 1
bool graphic::ReadRawMeshFileV1( const string &fileName, sRawMesh &raw )
{
	using namespace std;
	ifstream fin(fileName.c_str());
	if (!fin.is_open())
		return false;

	string exporterVersion;
	fin >>exporterVersion;

	if (exporterVersion != "EXPORTER_V1")		
		return false;

	string vtx, eq;
	int vtxSize;
	fin >> vtx >> eq >> vtxSize;

	if (vtxSize <= 0)
		return  false;

	raw.vertices.reserve(vtxSize + vtxSize/2);

	float num1, num2, num3;
	for (int i = 0; i < vtxSize; i++)
	{
		fin >> num1 >> num2 >> num3;
		raw.vertices.push_back( Vector3(num1, num2, num3) );
	}


	// �ε��� ���� �ʱ�ȭ.
	string idx;
	int faceSize;
	fin >> idx >> eq >> faceSize;

	raw.indices.reserve(faceSize);

	if (faceSize > 0)
	{
		int num1, num2, num3;
		for (int i = 0; i < faceSize*3; i+=3)
		{
			fin >> num1 >> num2 >> num3;
			raw.indices.push_back(num1);
			raw.indices.push_back(num2);
			raw.indices.push_back(num3);
		}
	}

	string norm;
	int numNormal;
	fin >> norm >> eq >> numNormal;

	if (numNormal > 0)
	{
		float num1, num2, num3;
		vector<int> vertCount(vtxSize, 0);
		for (int i = 0; i < numNormal; i++)
		{
			fin >> num1 >> num2 >> num3;
			Vector3 n(num1, num2, num3);

			// ���������� ����� ���ؼ� �Ҵ��Ѵ�.
			for (int k=0; k < 3; ++k)
			{
				const int vtxIdx = raw.indices[ i*3 + k];
				raw.normals[ vtxIdx] += n;
				++vertCount[ vtxIdx];
			}
		}

		for (int i=0; i < vtxSize; ++i)
		{
			raw.normals[ i] /= (float)vertCount[ i];
			raw.normals[ i].Normalize();
		}
	}

	return true;
}


// load exporter version 2
bool graphic::ReadRawMeshFileV2( const string &fileName, sRawMesh &raw )
{
	using namespace std;
	ifstream fin(fileName.c_str());
	if (!fin.is_open())
		return false;

	string exporterVersion;
	fin >>exporterVersion;

	if (exporterVersion != "EXPORTER_V2")
		return false;

	string vtx, eq;
	int vtxSize;
	fin >> vtx >> eq >> vtxSize;

	if (vtxSize <= 0)
		return  false;

	raw.vertices.reserve(vtxSize + vtxSize/2);

	float num1, num2, num3;
	for (int i = 0; i < vtxSize; i++)
	{
		fin >> num1 >> num2 >> num3;
		raw.vertices.push_back( Vector3(num1, num2, num3) );
	}


	// �ε��� ���� �ʱ�ȭ.
	string idx;
	int faceSize;
	fin >> idx >> eq >> faceSize;

	raw.indices.reserve(faceSize);

	if (faceSize > 0)
	{
		int num1, num2, num3;
		for (int i = 0; i < faceSize*3; i+=3)
		{
			fin >> num1 >> num2 >> num3;
			raw.indices.push_back(num1);
			raw.indices.push_back(num2);
			raw.indices.push_back(num3);
		}
	}

	string norm;
	int numNormal;
	fin >> norm >> eq >> numNormal;

	if (numNormal > 0)
	{
		float num1, num2, num3;
		vector<int> vertCount(vtxSize, 0);
		for (int i = 0; i < numNormal; i++)
		{
			fin >> num1 >> num2 >> num3;
			Vector3 n(num1, num2, num3);

			// ���������� ����� ���ؼ� �Ҵ��Ѵ�.
			for (int k=0; k < 3; ++k)
			{
				const int vtxIdx = raw.indices[ i*3 + k];
				raw.normals[ vtxIdx] += n;
				++vertCount[ vtxIdx];
			}
		}

		for (int i=0; i < vtxSize; ++i)
		{
			raw.normals[ i] /= (float)vertCount[ i];
			raw.normals[ i].Normalize();
		}
	}


/*
	string tex;
	int numTex;
	fin >> tex >> eq >> numTex;

	if (numTex > 0)
	{
		float fnum1, fnum2;
		vector<Vector3> texVertices(numTex);
		for (int i = 0; i < numTex; i++)
		{
			fin >> fnum1 >> fnum2;
			texVertices[ i] = Vector3(fnum1, fnum2, 0);
		}

		string strTexFace;
		int numTexFace;
		fin >> strTexFace >> eq >> numTexFace;

		vector<int> texFaces;
		texFaces.reserve(numTexFace*3);
		if (numTexFace > 0)
		{
			int num1, num2, num3;
			for (int i=0; i < numTexFace; ++i)
			{
				fin >> num1 >> num2 >> num3;
				texFaces.push_back( num1 );
				texFaces.push_back( num2 );
				texFaces.push_back( num3 );
			}
		}

		map<int, vector<int> > vtxIdxMap; // vertex index, vertex index array
		for (int i=0; i < vtxSize; ++i)
		{
			vector<int> varray;
			varray.reserve(4);
			varray.push_back(i);
			vtxIdxMap[ i] = varray;
		}

		// �ؽ��� ��ǥ�� ���ؽ� ���ۿ� �����Ѵ�. 
		// ���ؽ� ������ uv ���� �ʱ�ȭ ���� �ʾҴٸ�, �ʱ�ȭ �Ѵ�.
		// ���ؽ��� �ϳ� �̻��� uv���� �����Ѵٸ�, ���ؽ��� �߰��ϰ�, �ε������۸� �����Ѵ�.
		for (int i=0; i < (int)texFaces.size(); ++i)
		{
			const Vector3 tex = texVertices[ texFaces[ i]];
			const int vtxIdx = raw.indices[ i];

			bool isFind = false;
			for (int k=0; k < (int)vtxIdxMap[ vtxIdx].size(); ++k)
			{
				const int subVtxIdx = vtxIdxMap[ vtxIdx][ k];

				// �ؽ��� ��ǥ�� ���ؽ� ���ۿ� ����Ǿ� �ִٸ�, index buffer ���� �ش� vertex index ��
				// ���� �Ѵ�.
				if ((-100 == raw.vertices[ subVtxIdx].u) &&
					(-100 == raw.vertices[ subVtxIdx].v))
				{
					raw.vertices[ subVtxIdx].u = tex.x;
					raw.vertices[ subVtxIdx].v = tex.y;
					isFind = true;
					break;
				}
				else if ((tex.x == raw.vertices[ subVtxIdx].u) && 
					(tex.y == raw.vertices[ subVtxIdx].v))
				{
					raw.indices[ i] = subVtxIdx;
					isFind = true;
					break;
				}
			}

			// ���ؽ� ���ۿ� ���� uv ��ǥ���, �� ���ؽ��� ���ؽ����ۿ� �߰��Ѵ�.
			// �ε��� ���ۿ��� ���� �߰��� ���ؽ� �ε������� �ִ´�.
			if (!isFind)
			{
				Vertex v = raw.vertices[ vtxIdx];
				v.u = tex.x;
				v.v = tex.y;
				raw.vertices.push_back(v);
				const int newVtxIdx = raw.vertices.size()-1;
				vtxIdxMap[ vtxIdx].push_back( newVtxIdx );
				raw.indices[ i] = newVtxIdx;
			}
		}
	}
	/**/

	// �ؽ��� �����̸� �ε�.
	string textureTok, texFilePath;
	fin >> textureTok >> eq;
	std::getline(fin, texFilePath);
	string  textureFileName = common::GetFilePathExceptFileName(fileName) + "\\" + 
		common::trim(texFilePath);
//	texture.Create( textureFileName);

	return true;
}

