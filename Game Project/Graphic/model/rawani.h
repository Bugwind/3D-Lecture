#pragma once


namespace graphic
{

	struct sKeyPos
	{
		float t; // frame ����
		Vector3 p;
	};


	struct sKeyScale
	{
		float t; // frame ����
		Vector3 s;
	};


	struct sKeyRot
	{
		float t; // frame ����
		Quaternion q;
	};


	struct sRawAni
	{
		string name;
		float start; // frame ����
		float end; // frame ����
		vector<sKeyPos> pos;
		vector<sKeyRot> rot;
		vector<sKeyScale> scale;
	};

}
