#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Tool.h"

class MeshMotionFlow
{
public:
	MeshMotionFlow(int frames); // how many frames
	~MeshMotionFlow();

	std::vector<std::unordered_map<std::string, std::vector<float>>> Motions() const
	{
		return _motions;
	}

	void AddMotion(const unsigned int t, const std::unordered_map<std::string, std::vector<float>> frame)
	{
		if (t>_motions.size())
		{
			DEBUG("Error in frames!", "");
			return;
		}

		_motions[t] = frame;
	}

	void AddMotion(const unsigned int t, const std::string name, const std::vector<float> dof)
	{
		if(t>_motions.size())
		{
			DEBUG("Error in frames!", "");
			return;
		}

		_motions[t][name] = dof;
	}

private:
	std::vector<std::unordered_map<std::string, std::vector<float>>> _motions;
};

