///////////////////////////////////////////////////////////////////////////
// XmlNodes.cpp - demonstrate how to define a template node class        //
// ver 1.2                                                               //
// Language:    Visual C++, 2008                                         //
// Platform:    HP Pavilion dv4, Win7 Professional                       //
// Application: CSE382 - Algorithms and Data Structures Demo, Fall 2008  //
// Author:      Varun Joshi, Syracuse University                         //
//              (315) 706-7277, vjoshi@syr.edu                           //    
// Source:      Jim Fawcett, Syracuse University, CST 4-187,             //
//              (315) 443-3948, jfawcett@twcny.rr.com                    //
//              (HelpNode.cpp)                                               //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include "XmlNodes.h"

using namespace XmlProcessing;

//----< remove child node - returns false on failure, else true >--------

bool XmlNode::remove(XmlNode* pXmlNode)
{
  std::vector< XmlNode* >::iterator iter;
  for(iter=children.begin(); iter!=children.end(); ++iter)
  {
    if(*iter == pXmlNode)
    {
      children.erase(iter);
      return true;
    }
  }
  return false;
}
//----< return pointer to next unvisited child or null >-----------------

XmlNode* XmlNode::nextUnmarkedChild()
{
  for(size_t i=0; i<size(); ++i)
  {
    if(!children[i]->isMarked())
    {
      children[i]->isMarked() = true;
      return children[i];
    }
  }
  return 0;
}

//----< return default string representation of template type >----------
//
// This fails to compile if T instances can't be converted to std::string
//
/*
std::string XmlNode::ToString()
{
  std::ostringstream temp;
  temp << "<" << tag << ">";
  return temp.str();
}
*/
XmlNode* XmlNode::getChild(int i)
{
  return children[i];
}

//-----<defining the destructor to avoid memory leak >---------------

XmlNode::~XmlNode()
{
  for(size_t i=0;i < children.size(); ++i)
  {
    delete(children[i]);
  }
}

//------< returns the vector of attributes(i.e. name-value pairs) >--------

std::vector<std::pair<std::string, std::string>> XmlNode::getAttribs()
{
  return attrib;
}

//------< push the name-value pair onto a vector >-------------

void XmlNode::setAttribs(const std::string &name, const std::string &value)
{
	attrib.push_back(std::make_pair(std::string(name),std::string(value)));
}


//----------< node is added to the element >---------------

void XmlNode::setElement(const std::string& temp)
{
  element = temp;
  // temp = element;
}

//------------< returns the element >-------------------

std::string& XmlNode::getElement()
{
  return element;
}

#ifdef TEST_XMLNODE

void walk(XmlNode* pNode)
{
  std::cout << "\n  " << (pNode->value()).c_str();
  XmlNode* pTemp;
  for(size_t i=0; i<pNode->size(); ++i)
  {
    pTemp = pNode->nextUnmarkedChild();
    if(pTemp != 0)
      walk(pTemp);
  }
}
void main()
{
  std::cout << "\n  Testing Node class";
  std::cout << "\n ====================\n";
  typedef XmlNode Node;
  //-- create nodes

  Node root("root");
  Node child1("child1");
  Node child2("child2");
  Node grandchild11("grandchild11");
  
  //-- connect "tree"

  child1.add(&grandchild11);
  root.add(&child1);
  root.add(&child2);

  std::cout << "\n  walking connected nodes";
  walk(&root);

  std::cout << "\n\n  adding grandchildren";

  //-- unmark to prepare for next traversal

  root.isMarked() = false;
  child1.isMarked() = false;
  child2.isMarked() = false;
  grandchild11.isMarked() = false;
  
  //-- create more nodes

  Node grandchild21("grandchild21");
  Node grandchild22("grandchild22");
  
  //-- connect into "tree"

  child2.add(&grandchild21);
  child2.add(&grandchild22);

  std::cout << "\n\n  walking connected nodes";
  walk(&root);

  std::cout << "\n\n  removing grandchild";

  //-- unmark to prepare for next traversal

  root.isMarked() = false;
  child1.isMarked() = false;
  child2.isMarked() = false;
  grandchild11.isMarked() = false;
  grandchild21.isMarked() = false;
  grandchild22.isMarked() = false;
//  child2.removeChild(&grandchild21);
  walk(&root);

  std::cout << "\n\n";
}

#endif


