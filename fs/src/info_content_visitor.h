#ifndef INFO_CONTENT_VISITOR_H
#define INFO_CONTENT_VISITOR_H
#include <string>
class File;
class Folder;

class InfoContentVisitor
{
public:
  InfoContentVisitor();
  InfoContentVisitor(std::string targetName);

  void visitFile(File * file);
  void visitFolder(Folder * folder);
  void findVisitFile(File * file);
  void findVisitFolder(Folder * folder);

  int getContentSize()
  {
    return _size;
  }

  std::string getPath()
  {
    if(_path != "")
    {
      std::string::iterator i;
      i = _path.end()-1;
      _path.erase(i);
    }
    return _path;
  }

private:
  int _size;
  std::string _path;
  std::string _targetName = "";
};

#endif
