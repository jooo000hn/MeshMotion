#pragma once
#include <vector>
#include <unordered_map>

class SkeletonNode
{
public:
	SkeletonNode();
	~SkeletonNode();

	// getter and setter

	int Id() const
	{
		return id;
	}

	void SetId(int id)
	{
		this->id = id;
	}

	bool IsLeaf() const
	{
		return isLeaf;
	}

	void SetIsLeaf(bool is_leaf)
	{
		isLeaf = is_leaf;
	}

	SkeletonNode* Parent() const
	{
		return _parent;
	}

	void SetParent(SkeletonNode* skeleton_node)
	{
		_parent = skeleton_node;
	}

	std::vector<SkeletonNode*> ChildrenNodes() const
	{
		return _childrenNodes;
	}

	void AddChildrenNode(SkeletonNode* n)
	{
		_childrenNodes.push_back(n);
	}

	std::unordered_map<std::string, std::string> ValuePair() const
	{
		return _value_pair;
	}

	void SetValuePair(const std::unordered_map<std::string, std::string>& pairs)
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

