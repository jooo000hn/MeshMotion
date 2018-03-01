#pragma once
#include <vector>
#include <unordered_map>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SkeletonNode
{
public:
	SkeletonNode();
	~SkeletonNode();

	// getter and setter

	int Id() const
	{
		return _id;
	}

	void SetId(int id)
	{
		this->_id = id;
	}

	std::string Name() const
	{
		return _name;
	}

	void SetName(const std::string& cs)
	{
		_name = cs;
	}

	glm::vec3 Direction() const
	{
		return _direction;
	}

	void SetDirection(const glm::vec3& highp_vec3)
	{
		_direction = highp_vec3;
	}

	float Length() const
	{
		return _length;
	}

	void SetLength(float length)
	{
		_length = length;
	}

	std::vector<std::string> Dof() const
	{
		return _dof;
	}

//	void SetDof(const std::vector<std::string>& basic_strings)
//	{
//		_dof = basic_strings;
//	}

	void AddDof(const std::string s)
	{
		_dof.push_back(s);
	}

	std::vector<glm::vec2> Limits() const
	{
		return _limits;
	}

//	void SetLimits(const std::vector<glm::vec2>& tvec2s)
//	{
//		_limits = tvec2s;
//	}

	void AddLimits(glm::vec2 l)
	{
		_limits.push_back(l);
	}

	std::vector<std::string> Axis() const
	{
		return _axis;
	}

	void SetAxis(const std::vector<std::string>& basic_strings)
	{
		_axis = basic_strings;
	}


	std::vector<SkeletonNode*> Children() const
	{
		return _children;
	}

	void AddChildren(SkeletonNode* n)
	{
		if(n!=nullptr)
			_children.push_back(n);
	}


	SkeletonNode* Parent() const
	{
		return _parent;
	}

	void SetParent(SkeletonNode* skeleton_node)
	{
		_parent = skeleton_node;
	}

private:
	int _id;     
	std::string _name;
	glm::vec3 _direction;
	float _length;
	std::vector<std::string> _axis;
	std::vector<std::string> _dof;
	std::vector<glm::vec2> _limits;
	std::vector<SkeletonNode*> _children;
	SkeletonNode* _parent;
};

