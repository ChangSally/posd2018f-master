#ifndef NODE_H
#define NODE_H
#include <sys/stat.h>
#include <string>
#include <sstream>
#include <vector>
class InfoContentVisitor;

class Node
{
public:
  friend class InfoContentVisitor;
  Node(const char * path): _path(path)
  {
    lstat(_path, &_st);
  }

  int size() const
  {
    return _st.st_size;
  }

  virtual void accept(InfoContentVisitor * icv) = 0;
  virtual void acceptFind(InfoContentVisitor * icv, std::string path) = 0;

  virtual void add(Node *node)
  {
    throw std::string("unable to add");
  }

  virtual int numberOfChildren() const
  {
    return 0;
  }

  std::string name()
  {
    std::vector<std::string> splitResult;
    std::istringstream ss(_path);
    std::string token;
    while(std::getline(ss, token, '/'))
    {
      splitResult.push_back(token);
    }
    return splitResult.back();
  }

  virtual std::string find(std::string nodeName) = 0;

  virtual std::vector<std::string> recursive(std::string nodeName)
  {
  }

  std::string getTempPath()
  {
    return _tempPath;
  }

private:
  const char * _path;
  struct stat _st;

protected:
  std::string _tempPath = "";
};

#endif
