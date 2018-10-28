# Pattern Oriented Software Design
#### Fall, 2018
#### Prof Y C Cheng
#### Dept. of Computer Science and Information Engineering
#### Taipei Tech

### TA's webpage
https://ssl-gitlab.csie.ntut.edu.tw/root/POSD2018f_Assignment/tree/master)

## Synapsis

We will learn object-oriented design patterns by solving two problems in class:
- Review of C++/OOP - Problem 1
  - git/gitlab/jenkins
  - unit testing with googletest  
  - strong-styled pair programming/mob programming
  - STL, lambda
- Design patterns: an object-oriented file system API - Problem 2
  - Composite, Iterator, Visitor, Proxy, Builder, and Interpreter
  - GUI (with wxWidgets) MVC, Observer, Mediator, and Adapter

## Textbook:
Gamma, Erich, et al. Design patterns: elements of reusable object-oriented software. Pearson Education, 1994.

## Grading policy

- Homework 40%
- Online programming test x2, 20% each
  - first midterm: 20 Oct 2018, 1:30pm - 5:30pm
  - second midterm: 8 Dec 2018, 1:30pm - 5:30pm
- Final (written) 20%

## Alternative course 通訊軟體設計

 Spends more time on OOP basics in C++) to elect : 資工所(必修二選一)

## Problems:

### Problem 1: sorting shapes

A simple geometry application called _geo_ is needed to sort shapes such as triangles, circles, rectangles and others. As a command line application, _geo_ reads shapes from an input file, sorts the shapes by area or perimeter in increasing order or decreasing order, and write the result to an output file. For example,
```
geo input.txt output.txt area inc
```
sorts the shapes in file _input.txt_ in increasing order by area, and writes the result to the file _output.txt_. And
```
geo input.txt output.txt perimeter dec
```
sorts the shapes in file _input.txt_ in decreasing order by perimeter, and writes the result to the file _output.txt_.

### Problem 2: object-oriented file system API

The file system is used in many apps ranging from document editors (e.g., Atom), file/directory browser, file sync/storage applications (e.g., Dropbox), etc. In these applications, it is necessary to open/save document(s) from/to a selected location in the file system. Many operations on the file system are needed; for example, adding/deleting a file to/from a directory; moving selected files from one directory to another, searching files with a given name, compressing or encrypting a file or a directory, etc. Also, certain information about the files and directories are often needed, for example, the storage space used by a file or a directory, the organization of a directory, etc.

File systems differ in different operating systems. In this problem, we shall assume that Unix file system is used. To be sure, it is possible to provide all of the above operations by invoking system calls and functions that comes in C-binding on Unix systems. However, the API bindings are usually terse and difficult to understand. Further, use of the API makes your applications directly dependent on the C-binding of Unix systems, which becomes a problem if you need to support file systems on Windows in the future. Thus, the problem is to develop an object-oriented API in C++ that is easier to understand and work with. In particular, we want to organize the file system into a tree structure, and allow the client of the API to use nodes inside the tree uniformly. We also want it to be easy to add various operations to the file system.

## Week 1

- Simple tooling
  - Atom, g++, make, git
- Organizing project directory: We will work with projects with many files
  - From:
```
  hello.cpp a.out
```
  - To:
```
  src/hello.cpp      // folder for production code
  bin/hello          // folder for executables
  test/              // folder for test code
  obj/               // folder for object code
  makefile
  readme.md // project info
```
- makefile objectives:
  - maintaining project structure
  - enabling recompilation when dependent files changes
  - actions:
    - compile
    - link
    - cleanup
    - statistics
- jenkins/gitlab/googletest

## Tasks for problem 1
- Take care of command line parameters
- Select sorting algorithm (week 2)
  - stl sort
  - lambda as call back for sort
- Representation of Shapes
  - install gtest, run it
  - org project folder
  - make/makefile: target, .PHONY
  - polymorphism (week 2)

__Check TA's webpage for first assignment!!__

https://ssl-gitlab.csie.ntut.edu.tw/root/POSD2018f_Assignment/tree/master

## Week 2:
- lambda, pointer to function, overloading functional call operator
- reading API document: [std::sort](http://www.cplusplus.com/reference/algorithm/sort/)
- container-iterator-algorithm: decoupling design in the standard library

[Second assignement](https://ssl-gitlab.csie.ntut.edu.tw/root/POSD2018f_Assignment/tree/master)

## Week 3:

Problem 2: object-oriented file system API

- Abstraction: keep only what you want to keep
- tree structure:
  - files, folders, links can inside folder: they are all nodes
  - file is a leaf
  - link points to exactly one other nodes
- what does a node do? (responsibilities of a node)

## Week 4:

Node, File, and Folder
- construct an example
- write test/code for the example
- refactoring: [Pull Up Method](https://refactoring.com/catalog/pullUpMethod.html) applied to size, add, and numberOfChildren
- [Composite](https://en.wikipedia.org/wiki/Composite_pattern)

## Week 5:

- organize folders and files into a tree structure
- treat Folder and File uniformly as Node
- responsibilities of a Node
  - maintaining tree structure: add, remove, numberOfChildren
  - provide information: name, physical size, modification time, etc.
- supporting additional operations on file system
  - find test_data -name "hello.cpp"
  - cat test_data, cat test_data/hello.cpp
  - ls test_data, ls test_data/folder_1
- options:
  - as member functions of NODE => interface bloating; lower cohesion
  - as external functions
  - as external objects => [Visitor](https://en.wikipedia.org/wiki/Visitor_pattern)

[Fourth assignement](https://ssl-gitlab.csie.ntut.edu.tw/root/POSD2018f_Assignment/tree/master)

## Week 6:

- Refactoring to Patterns: [Move Accumulation To Visitor](https://www.industriallogic.com/xp/refactoring/accumulationToVisitor.html)
- circular dependency
  - Node <---> InfoContentVisitor: double dispatch creates circular dependency
  - How to break the dependency?
    - class InfoContentVisitor forward decl <-- node.h (Node::accept)
    - class File, Folder forward decl <--
      info_content_visitor.h (InfoContentVisitor::visit(File/Folder))
    - node.h, info_content_visitor.h <-- file.h, folder.h
    - info_content_visitor.h, file.h, folder.h <-- info_content_visitor.cpp

  - where to put folder's accepting logic?
    - Folder::accept
    - InfoContentVisitor::visit
      - make InfoContentVisitor a friend of Folder
      - or provide make Folder provide access means => [Iterator](https://en.wikipedia.org/wiki/Iterator_pattern)
  - FolderIterator
    - .h, .cpp
    - friend to Folder
    - inner class to Folder

# first programming lab midterm: Sunday, 28 Oct 2018, 1:30pm - 5:30pm @lab 1222, 1223

## Week 7

- consequences of the Visitor pattern: to have Visitor? or not to have Visitors?
- "program to an interface, not an implementation"
- InformationContentVisitor is given *ad hoc visibility* to Folder through "friend": can remove this dependency by applying the Iterator pattern.

- learn from C++ STL: Vector and its iterator (as an public inner class)
