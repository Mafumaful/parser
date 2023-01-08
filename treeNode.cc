#include "treeNode.h"

TreeNode::TreeNode(std::string cntt) : content{cntt} {}

std::string TreeNode::getContent() const
{
  // your code starts here
  return this->content;

  // return "";
}

TreeNode *TreeNode::getLeftChild() const
{
  // your code starts here
  return this->leftChild;

  // return nullptr;
}
TreeNode *TreeNode::getRightChild() const
{
  // your code starts here
  return this->rightChild;

  // return nullptr;
}

void TreeNode::updateLeftChild(TreeNode *lChild)
{
  // your code starts here
  this->leftChild = lChild;
}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild)
{
  // your code starts here
  this->leftChild = lChild;
  this->rightChild = rChild;
}

OperatorNode::OperatorNode(std::string cntt) : TreeNode{cntt} {}

bool OperatorNode::evaluate(const std::map<std::string, bool> &assignment) const
{
  // your code starts here
  if (this->getContent() == "+")
    return this->getLeftChild()->evaluate(assignment) | this->getRightChild()->evaluate(assignment);

  if (this->getContent() == "*")
    return this->getLeftChild()->evaluate(assignment) & this->getRightChild()->evaluate(assignment);

  if (this->getContent() == "-")
    return !this->getLeftChild()->evaluate(assignment);

  return false;
}

ConstantNode::ConstantNode(std::string cntt) : TreeNode{cntt} {}

bool ConstantNode::evaluate(const std::map<std::string, bool> &assignment) const
{
  // your code starts here
  if (this->getContent() == "0")
    return false;
  if (this->getContent() == "1")
    return true;

  return false;
}

VariableNode::VariableNode(std::string cntt) : TreeNode{cntt} {}

bool VariableNode::evaluate(const std::map<std::string, bool> &assignment) const
{
  // your code starts here
  auto it = assignment.find(this->getContent());
  if (it != assignment.end()) // if it's find
    return it->second;
  else
    return false;
}

TreeNode::~TreeNode()
{
  // your code starts here
}
