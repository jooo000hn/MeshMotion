#pragma once
#include "SkeletonNode.h"

class MeshSkeleton
{
public:
	MeshSkeleton();
	~MeshSkeleton();

	// getter and setter
	// getter and setter

	std::string Version() const
	{
		return _version;
	}

	void SetVersion(const std::string& cs)
	{
		_version = cs;
	}

	std::string Name() const
	{
		return _name;
	}

	void SetName(const std::string& cs)
	{
		_name = cs;
	}

	std::unordered_map<std::string, std::string> Units() const
	{
		return _units;
	}

	void SetUnits(const std::unordered_map<std::string, std::string>& pairs)
	{
		_units = pairs;
	}

	std::string Documentation() const
	{
		return _documentation;
	}

	void SetDocumentation(const std::string& cs)
	{
		_documentation = cs;
	}

	std::vector<std::string> RootOrder() const
	{
		return _root_order;
	}

	void SetRootOrder(const std::vector<std::string>& basic_strings)
	{
		_root_order = basic_strings;
	}

	std::vector<std::string> RootAxis() const
	{
		return _root_axis;
	}

	void SetRootAxis(const std::vector<std::string>& basic_strings)
	{
		_root_axis = basic_strings;
	}

	glm::vec3 RootPosition() const
	{
		return _root_position;
	}

	void SetRootPosition(const glm::vec3& highp_vec3)
	{
		_root_position = highp_vec3;
	}

	glm::vec3 RootOrientation() const
	{
		return _root_orientation;
	}

	void SetRootOrientation(const glm::vec3& highp_vec3)
	{
		_root_orientation = highp_vec3;
	}

	std::vector<SkeletonNode*> Bonedata() const
	{
		return _bonedata;
	}

	void SetBonedata(const std::vector<SkeletonNode*>& skeleton_nodes)
	{
		_bonedata = skeleton_nodes;
	}

private:
	std::string _version;
	std::string _name;
	std::unordered_map<std::string, std::string> _units;
	std::string _documentation;
	std::vector<std::string> _root_order;
	std::vector<std::string> _root_axis;
	glm::vec3 _root_position;
	glm::vec3 _root_orientation;
	std::vector<SkeletonNode*> _bonedata;
};

