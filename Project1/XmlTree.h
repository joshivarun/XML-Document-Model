#ifndef XMLTREE_H
#define XMLTREE_H
///////////////////////////////////////////////////////////////////////////
// XmlTree.h  - M-ary tree class to hold an XmlDocument                  //
// ver 2.1                                                               //
// Language:    Visual C++, 2008                                         //
// Platform:    HP Pavilion dv4, Win7 Professional                       //
// Application: CSE687 - Demo for Project #1, Spring 2010                //
// Author:      Varun Joshi, Syracuse University                         //
//              (315) 706-7277, vjoshi@syr.edu                           //
// Source:      Jim Fawcett, Syracuse University, CST 4-187,             //
//              (315) 443-3948, jfawcett@twcny.rr.com                    //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * Provides an XmlTree class that holds a finite number of nodes and
 * and supports visitation of each node, using depth first search.
 *
 * Several things have been left as an exercise for students, e.g."
 * - deleting tree nodes in tree destructor
 * - finding specific nodes in tree
 * - Making nodes with capabilities to hold attributes
 * - Serialization is just started - see the ToString() method
 * - All editing operations
 * 
 * Required Files:
 * ===============
 * XmlTree.h, XmlTree.cpp, XmlNodes.h, XmlNodes.cpp
 *
 * Build Process:
 * ==============
 * cl /D:TEST_XMLTREE XmlTree.cpp XmlNodes.cpp
 * 
 * Maintenance History:
 * ====================
 * ver 1.0 : 01 Feb 10
 * - first release
 */


#include "XmlNodes.h"
#include "Parser.h"

using namespace XmlProcessing;

class XmlTree
{
public:
  
  void makeRoot(XmlNode*);
  void walk(XmlNode* pMNode);
  std::vector<XmlNode*> findbytag(const std::string& tagname); 
  XmlNode* getRoot(); 
  void show(XmlNode*);
  void removebytag(std::string);
  std::string removeSpace(std::string);
  void addtoid(std::string);
  void addtotag(std::string);
  XmlNode* findbyid(std::string tagname);
  void clearMarks();
private:
  std::vector<XmlNode*> tempNodes; 
  std::vector<XmlNode*> tempElement; 
  XmlNode* pRoot;
  
};

inline void XmlTree::makeRoot(XmlNode* pMNode){	pRoot = pMNode; }

//------< returns the root >---------------------

inline XmlNode* XmlTree::getRoot(){ return (pRoot) ; }

#endif
