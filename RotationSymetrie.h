#pragma once

class CRotationSymetrie
{
public:
	bool same;
	size_t _nbRot;
	bool symetrie;

	CRotationSymetrie(bool param1, size_t param2, bool param3)
	{
		same = param1;
		_nbRot = param2;
		symetrie = param3;
	}
};