#pragma once
#include <vector>
#include <unordered_map>

class SkeletonNode
{
public:
	SkeletonNode();
	~SkeletonNode();

	// getter and setter
	int id1() const
	{
		return id;
	}

	void set_id(int id)
	{
		this->id = id;
	}

	bool is_leaf() const
	{
		return isLeaf;
	}

	void set_is_leaf(bool is_leaf)
	{
		isLeaf = is_leaf;
	}

	SkeletonNode* parent() const
	{
		return _parent;
	}

	void set_parent(SkeletonNode* skeleton_node)
	{
		_parent = skeleton_node;
	}

	std::vector<SkeletonNode*> children_nodes() const
	{
		return _childrenNodes;
	}

	void set_children_nodes(const std::vector<SkeletonNode*>& skeleton_nodes)
	{
		_childrenNodes = skeleton_nodes;
	}

	std::unordered_map<std::string, std::string> value_pair() const
	{
		return _value_pair;
	}

	void set_value_pair(const std::unordered_map<std::string, std::string>& pairs)
	{
		_value_pair = pairs;
	}

private:
	int id;       // if leaf node, should have an id
	bool isLeaf;  // leaf nodes and kont nodes
	SkeletonNode* _parent;
	std::vector<SkeletonNode*> _childrenNodes;
	std::unordered_map<std::string, std::string> _value_pair;
};

