#include "AMCParser.h"

AMCParser* AMCParser::_instance = nullptr;

AMCParser::AMCParser()
{
}


AMCParser::~AMCParser()
{
}

MeshMotionFlow AMCParser::ParsAMC(std::string file,unsigned int joints)
{
	DEBUG("We try to parse ", file);
	auto rowTokens = GetTokensByLine(file);
	if(rowTokens.size()==0)
	{
		return MeshMotionFlow(0);
	}

	int i = 0;
	while (rowTokens[i++][0] != ":DEGREES");

	unsigned int frames = static_cast<int>((rowTokens.size() - i) / (joints + 1));

	MeshMotionFlow mesh(frames);
	// parse specific movement information
	for(unsigned int f =0; f < frames;++f)
	{
		std::unordered_map<std::string, std::vector<float>> oneFrame;
		for(unsigned int j = 0; j < joints;++j)
		{
			auto currentRow = rowTokens[i + f*joints + j + 1];
			std::vector<float> dof;
			for(size_t di = 1; di < currentRow.size();++di)
			{
				dof.push_back(std::stof(currentRow[di]));
			}
			oneFrame[currentRow[0]] = dof;
		}
		mesh.AddMotion(f, oneFrame);
	}

	return mesh;
}
