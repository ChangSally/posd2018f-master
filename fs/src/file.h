#ifndef FILE_H
#define FILE_H

#include "node.h"
#include "info_content_visitor.h"

class File: public Node{
public:
  File(const char * path): Node(path)
  {
    
  }

  void accept(InfoContentVisitor * icv)
  {
    icv->visitFile(this);
  }

  void acceptFind(InfoContentVisitor * icv, std::string path)
  {
    if(path != "" && path != "./")
    {
      _tempPath = (_tempPath + "/" + Node::name());
    }
    icv->findVisitFile(this);
  }

  std::string find(std::string nodeName)
  {
    std::string fileName = Node::name();
    if (strcmp(fileName.c_str(), nodeName.c_str()) == 0)
    {
      return nodeName;
    }
    else
    {
      return "";
    }
  }
};

#endif
