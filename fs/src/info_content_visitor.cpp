#include "info_content_visitor.h"
#include "file.h"
#include "folder.h"

InfoContentVisitor::InfoContentVisitor(): _size(0)
{
}

InfoContentVisitor::InfoContentVisitor(std::string targetName): _size(0), _targetName(targetName)
{
}

void InfoContentVisitor::visitFile(File * file)
{
  _size += file->size();
}

void InfoContentVisitor::visitFolder(Folder * folder)
{
  for (int i = 0; i < folder->numberOfChildren(); i++)
  {
    folder->_children[i]->accept(this);
  }
}

void InfoContentVisitor::findVisitFile(File * file)
{
  //_path = file->find(_targetName);
  if(file->name() == _targetName)
  {
    _path += (file->_tempPath + _targetName + "\n");
  }
}

void InfoContentVisitor::findVisitFolder(Folder * folder)
{
  //_path = folder->find(_targetName);
  for(int i = 0; i < folder->numberOfChildren(); i++)
  {
    if(folder->_children[i]->name() == _targetName)
    {
      if(folder->_tempPath != "./")
      {
        _path += (folder->_tempPath + "/" + _targetName + "\n");
      }
      else
      {
        _path += (folder->_tempPath + _targetName + "\n");
      }
    }
    if(folder->_children[i]->numberOfChildren()>0)
    {
      folder->_children[i]->acceptFind(this, folder->_tempPath);
    }
  }
}