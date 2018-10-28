#include <vector>
#include "node.h"
#include "info_content_visitor.h"

class Folder:public Node{
public:
  friend class InfoContentVisitor;

  Folder(const char* path):Node(path)
  {
    _tempPath = "./";
  }

  void add(Node *node)
  {
    _children.push_back(node);
  }

  int numberOfChildren() const
  {
    return _children.size();
  }

  void accept(InfoContentVisitor * icv)
  {
    icv->visitFolder(this);
  }

  void acceptFind(InfoContentVisitor * icv, std::string path)
  {
    if(path != "")
    {
      if(path == "./")
      {
        _tempPath = (path + Node::name());
      }
      else
      {
        _tempPath = (path + "/" + Node::name());
      }
    }
    else
    {
      _tempPath = "./";
    }
    icv->findVisitFolder(this);
  }

  std::vector<std::string> recursive(std::string nodeName)
  {
    std::vector<std::string> result;
    for (int i  = 0; i < _children.size(); i++)
    {
      if(_children[i]->name() == nodeName)
      {
        result.push_back(nodeName);
      }
      if(_children[i]->numberOfChildren() > 0)
      {
        std::vector<std::string> temp;
        temp = _children[i]->recursive(nodeName);
        for(int j = 0; j < temp.size(); j++)
        {
          std::string path = _children[i]->name() + "/" + temp[j];
          result.push_back(path);
        }
      }
    }
    return result;
  }

  std::string find(std::string nodeName)
  {
    std::vector<std::string> resultVector;
    std::string result = "";
    resultVector = recursive(nodeName);
    for (int i = 0; i < resultVector.size(); i++)
    {
      std::string temp = "./" + resultVector[i];
      result += temp;
      if (resultVector[i] != resultVector.back())
      {
        result += "\n";
      }
    }
    return result;
  }

private:
  std::vector<Node *> _children;
};
