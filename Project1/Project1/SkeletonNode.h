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

private:
	int _id;     
	std::string _name;
	glm::vec3 _direction;
	float _length;
	std::vector<std::string> _dof;
	std::vector<glm::vec2> _limits;
};

