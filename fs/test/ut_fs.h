#ifndef UT_FS_H
#define UT_FS_H

#include <sys/stat.h>
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/info_content_visitor.h"


#include <algorithm>

void compare_multi_path(std::vector<std::string> all_path,std::vector<std::string> expect_path);
std::vector<std::string> split_path_into_vector(std::string);
// TEST (MiscTest, lstatOnFolder)
// {
//   const char * path = "./test_data";
//   struct stat st;
//   ASSERT_EQ(0, lstat(path, &st));
//   ASSERT_EQ(128, st.st_size);
//   ASSERT_EQ(true, S_ISDIR(st.st_mode));
//   ASSERT_EQ(false, S_ISREG(st.st_mode));
//   ASSERT_EQ(false, S_ISLNK(st.st_mode));
// }

// TEST (FileSystemTest, Size)
// {
  // Node * test_data = new Folder ("./test_data");
  // ASSERT_EQ(128,test_data->size());
  // Node * folder = new Folder("./test_data/folder");
  // ASSERT_EQ(96, folder->size());
  // Node * hello_cpp = new File("./test_data/hello.cpp");
  // ASSERT_EQ(83, hello_cpp->size());
  // Node * a_out = new File("./test_data/folder/a.out");
  // ASSERT_EQ(8432, a_out->size());
  // test_data->add(folder);
  // test_data->add(hello_cpp);
  // ASSERT_EQ(2,test_data->numberOfChildren());
// }

// TEST (FileSystemTest, InfoContent)
// {
//   Node * a_out = new File("./test_data/folder/a.out");
//   ASSERT_EQ(8432, a_out->infoContent());
//   Node * hello_cpp = new File("./test_data/hello.cpp");
//   ASSERT_EQ(83, hello_cpp->infoContent());
//   Node * folder = new Folder("./test_data/folder");
//   folder->add(a_out);
//   ASSERT_EQ(8432, folder->infoContent());
//   Node * test_data = new Folder("./test_data");
//   test_data->add(folder);
//   test_data->add(hello_cpp);
//   ASSERT_EQ(8515, test_data->infoContent());
// }

// TEST (FileSystemTest, Visitor)
// {
//   Node * a_out = new File("./test_data/folder/a.out");
//   InfoContentVisitor icv = new InfoContentVisitor();
// }

// TEST (FileSystemTest, GetFileName)
// {
//   Node * hello_cpp = new File("./test_data/hello.cpp");
//   Node * a_out = new File("./test_data/folder/a.out");

//   ASSERT_EQ("hello.cpp",hello_cpp->name());
//   ASSERT_EQ("a.out",a_out->name());
// }

// TEST (FileSystemTest, GetFolderName)
// {
//   Node * folder = new Folder("./test_data/folder");
//   Node * test_data = new Folder("./test_data");
//   ASSERT_EQ("folder",folder->name());
//   ASSERT_EQ("test_data",test_data->name());
// }

TEST (, FileSearchItsSelf)
{
  InfoContentVisitor * icv = new InfoContentVisitor("a.out");
  Node * a_out = new File("./test_data/folder/a.out");
  a_out->acceptFind(icv, "");
  ASSERT_EQ("a.out", icv->getPath());
}
TEST (, FileSearchNotItsSelf)
{
  InfoContentVisitor * icv = new InfoContentVisitor("b.out");
  Node * a_out = new File("./test_data/folder/a.out");
  a_out->acceptFind(icv, "");
  ASSERT_EQ("",icv->getPath());
}
TEST (, FolderSearchItsSelf)
{
  InfoContentVisitor * icv = new InfoContentVisitor("folder");
  Node * folder = new Folder("./test_data/folder");
  folder->acceptFind(icv, "");
  ASSERT_EQ("",icv->getPath());
}
TEST (, FolderSearchNotItsSelf)
{
  InfoContentVisitor * icv = new InfoContentVisitor("test_data");
  Node * folder = new Folder("./test_data/folder");
  folder->acceptFind(icv, "");
  ASSERT_EQ("",icv->getPath());
}

TEST (, SearchFileInFolder)
{
  InfoContentVisitor * icv = new InfoContentVisitor("a.out");
  Node * folder = new Folder("./test_data/folder");
  Node * a_out = new File("./test_data/folder/a.out");
  folder->add(a_out);
  folder->acceptFind(icv, "");
  ASSERT_EQ("./a.out",icv->getPath());
}

TEST (, SearchFolderInFolder)
{
  InfoContentVisitor * icv = new InfoContentVisitor("folder");
  Node * test_data = new Folder ("./test_data");
  Node * folder = new Folder("./test_data/folder");
  test_data->add(folder);
  test_data->acceptFind(icv, "");
  ASSERT_EQ("./folder",icv->getPath());
}

TEST (, SearchTAFileInFolder)
{
  InfoContentVisitor * icv = new InfoContentVisitor("a.out");
  InfoContentVisitor * icv1 = new InfoContentVisitor("ta_folder");
  InfoContentVisitor * icv2 = new InfoContentVisitor("ta.out");
  Node * folder = new Folder("./test_data/folder");
  Node * ta_out = new File("./test_data/folder/ta_folder/ta.out");
  Node * ta_folder = new Folder("./test_data/folder/ta_folder");
  Node * a_out = new File("./test_data/folder/a.out");
  folder->add(a_out);
  folder->add(ta_folder);
  ta_folder->add(ta_out);
  folder->acceptFind(icv, "");
  folder->acceptFind(icv1, "");
  folder->acceptFind(icv2, "");
  ASSERT_EQ("./a.out",icv->getPath());
  ASSERT_EQ("./ta_folder",icv1->getPath());
  ASSERT_EQ("./ta_folder/ta.out",icv2->getPath());

}

TEST (, SearchFileInTest_DataFolder)
{
  InfoContentVisitor * icv = new InfoContentVisitor("a.out");
  InfoContentVisitor * icv1 = new InfoContentVisitor("a.out");
  Node * test_data = new Folder ("./test_data");
  Node * folder = new Folder("./test_data/folder");
  Node * hello_cpp = new File("./test_data/hello.cpp");
  Node * a_out = new File("./test_data/folder/a.out");
  test_data->add(folder);
  test_data->add(hello_cpp);
  folder->add(a_out);
  test_data->acceptFind(icv, "");
  folder->acceptFind(icv1, "");
  //ASSERT_EQ("./", folder->getTempPath());
  ASSERT_EQ("./folder/a.out",icv->getPath());
  ASSERT_EQ("./a.out",icv1->getPath());
  

}


TEST (, SearchSameNameFileInFolder)
{
  InfoContentVisitor * icv = new InfoContentVisitor("a.out");
  InfoContentVisitor * icv1 = new InfoContentVisitor("a.out");
  Node * test_data = new Folder ("./test_data");
  Node * folder = new Folder("./test_data/folder");
  Node * hello_cpp = new File("./test_data/hello.cpp");
  Node * a_out = new File("./test_data/folder/a.out");
  Node * ta_out = new File("./test_data/folder/ta_folder/ta.out");
  Node * a_out_2 = new File("./test_data/folder/ta_folder/a.out");
  Node * ta_folder = new Folder("./test_data/folder/ta_folder");
  Node * a_out_3 = new File("./test_data/a.out");
  test_data->add(folder);
  test_data->add(hello_cpp);
  test_data->add(a_out_3);
  folder->add(ta_folder);
  ta_folder->add(ta_out);
  ta_folder->add(a_out_2);
  folder->add(a_out);
  test_data->acceptFind(icv, "");
  folder->acceptFind(icv1, "");

  std::vector<std::string> all_path;
  std::vector<std::string> expect_path;

  expect_path = split_path_into_vector("./folder/ta_folder/a.out\n./folder/a.out\n./a.out");
  all_path = split_path_into_vector(icv->getPath());
  compare_multi_path(expect_path,all_path);

  expect_path = split_path_into_vector("./ta_folder/a.out\n./a.out");
  all_path = split_path_into_vector(icv1->getPath());
  compare_multi_path(expect_path,all_path);
  // ASSERT_EQ("./folder/ta_folder/a.out\n./folder/a.out\n./a.out",test_data->find("a.out"));
  // ASSERT_EQ("./ta_folder/a.out\n./a.out",folder->find("a.out"));

}

TEST (, SearchSameNameFolderInFolder)
{
  InfoContentVisitor * icv = new InfoContentVisitor("ta_folder");
  InfoContentVisitor * icv1 = new InfoContentVisitor("ta_folder");
  Node * test_data = new Folder ("./test_data");
  Node * folder = new Folder("./test_data/folder");
  Node * hello_cpp = new File("./test_data/hello.cpp");
  Node * a_out = new File("./test_data/folder/a.out");
  Node * ta_out = new File("./test_data/folder/ta_folder/ta.out");
  Node * a_out_2 = new File("./test_data/folder/ta_folder/a.out");
  Node * ta_folder = new Folder("./test_data/folder/ta_folder");
  Node * ta_folder2 = new Folder("./test_data/folder/ta_folder/ta_folder");
  Node * a_out_3 = new File("./test_data/a.out");
  test_data->add(folder);
  test_data->add(hello_cpp);
  test_data->add(a_out_3);
  folder->add(ta_folder);
  ta_folder->add(ta_folder2);
  ta_folder->add(ta_out);
  ta_folder->add(a_out_2);
  folder->add(a_out);
  folder->acceptFind(icv, "");
  test_data->acceptFind(icv1, "");

  std::vector<std::string> all_path;
  std::vector<std::string> expect_path;
  // std::cout<<folder->find("ta_folder")<<std::endl;
  expect_path = split_path_into_vector("./ta_folder\n./ta_folder/ta_folder");
  all_path = split_path_into_vector(icv->getPath());
  compare_multi_path(expect_path,all_path);

  expect_path = split_path_into_vector("./folder/ta_folder\n./folder/ta_folder/ta_folder");
  all_path = split_path_into_vector(icv1->getPath());
  compare_multi_path(expect_path,all_path);

}

std::vector<std::string> split_path_into_vector(std::string path){
  std::vector<std::string> all_path;
  char *cstr = new char[path.length() + 1];
  strcpy(cstr, path.c_str());
  char * pch;
  pch = strtok (cstr,"\n");
  while (pch != NULL)
  {
    all_path.push_back(std::string(pch));
    pch = strtok (NULL, "\n");
  }
  return all_path;
}

void compare_multi_path(std::vector<std::string> expect_path,std::vector<std::string> all_path){
  if(expect_path.size() != all_path.size())
    FAIL()<<"You should find " + std::to_string(expect_path.size())+ " different path\nYour path mount: "+ std::to_string(all_path.size());

  std::sort(all_path.begin(),all_path.end(),[](std::string a, std::string b){
    return a.size()<b.size();
  });
  std::sort(expect_path.begin(),expect_path.end(),[](std::string a, std::string b){
    return a.size()<b.size();
  });
  for(int i = 0;i<expect_path.size();i++){
    if(all_path[i]!=expect_path[i])
      FAIL()<<"expect path : " + expect_path[i] + "\nActual path : " + all_path[i];
  }
}


/*
TEST (MiscTest, lstatOnFolder)
{
  const char * path = "./test_data";
  struct stat st;
  ASSERT_EQ(0, lstat(path, &st));
  ASSERT_EQ(136, st.st_size);
  ASSERT_EQ(true, S_ISDIR(st.st_mode));
  ASSERT_EQ(false, S_ISREG(st.st_mode));
  ASSERT_EQ(false, S_ISLNK(st.st_mode));
}

TEST (FileSystemTest, Size)
{
  Node * test_data = new Folder ("./test_data");
  ASSERT_EQ(136,test_data->size());
  Node * folder = new Folder("./test_data/folder");
  ASSERT_EQ(102, folder->size());
  Node * hello_cpp = new File("./test_data/hello.cpp");
  ASSERT_EQ(83, hello_cpp->size());
  Node * a_out = new File("./test_data/folder/a.out");
  ASSERT_EQ(8432, a_out->size());
  test_data->add(folder);
  test_data->add(hello_cpp);
  ASSERT_EQ(2,test_data->numberOfChildren());
}

TEST (FileSystemTest, Visitor)
{
  File * a_out = new File("./test_data/folder/a.out");
  InfoContentVisitor * icv = new InfoContentVisitor();
  a_out->accept(icv);
  ASSERT_EQ(8432, icv->getContentSize());
  delete icv;
  // icv = new InfoContentVisitor();
  InfoContentVisitor * icv2 = new InfoContentVisitor();
  Node * folder = new Folder("./test_data/folder");
  folder->add(a_out);
  folder->accept(icv2);
  ASSERT_EQ(8432, icv2->getContentSize());

  InfoContentVisitor * icv3 = new InfoContentVisitor();
  Node * test_data = new Folder("./test_data");
  Node * hello_cpp = new File("./test_data/hello.cpp");
  test_data->add(folder);
  test_data->add(hello_cpp);
  test_data->accept(icv3);
  ASSERT_EQ(8515,icv3->getContentSize());

}*/

TEST(FileSystem, find)
{
  InfoContentVisitor * icv4 = new InfoContentVisitor("hello.cpp");
  Node * test_data = new Folder("./test_data");
  Node * hello_cpp = new File("./test_data/hello.cpp");
  Node * folder = new Folder("./test_data/folder");
  test_data->add(folder);
  test_data->add(hello_cpp);
  test_data->acceptFind(icv4, "");
  ASSERT_EQ("./hello.cpp", icv4->getPath());
}

#endif
