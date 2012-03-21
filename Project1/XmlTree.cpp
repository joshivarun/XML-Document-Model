///////////////////////////////////////////////////////////////////////////
// XmlTree.cpp  -  Holds information extracted from Xml string or file   //
// ver 1.1                                                               //
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
 * This module defines a Node class. Its instances perform operations like
 * binding a child  to its parent, removing a child from its parent,
 * retrieving the number of children associated to a particular node,
 * storing the attributes associated to a node, storing the element type
 * using the XML file as input, storing an element associated to a particular
 * node.

 *  A Node is an important part of an XML parser, used to create an internal 
 *  representation and store the information about each element of an XML file.
 * 
 *
 * Public Interface:
 * =================
 *  XmlTree t								// create Tree instance
 *  t.walk(root)							// traverses the tree with root as the starting node
 *  t.clearMarks()						// prepares for the next traversal
 *  XmlNode* pnode = t.findid(id)			// returns a node pointer by finding a node with the specified id
 *  vector<Node*> v=findbytag(tag)			// adds a child to a node with the specified Tag
 *  t.addtoid(id)					// adds a child to a node with the specified id attribute
 *  t.setRoot(root)						// sets root as the root node
 *  t.getRoot()							// returns root node of the tree
 *  t.show()							// displays the elements of the tree on the console
 *  t.removebytag(Tag)					// deletes all the children of the node with the specefied tag
 *  t.removeSpace()						// returns a string used for processing the cases of self ending nodes in an XML
 *
 */


#include <vector>
#include <iostream>
#include <string>
#include "XmlTree.h"

using namespace XmlProcessing;
/*
XmlTree::XmlTree()
{
}
*/
//----< give tree an operation to apply to each node during traversal >----
/*
void XmlTree::setOperation(Operation* pOper)
{
  delete pOper_;
  pOper_ = pOper;
}
*/

//----< depth first search based traversal >-------------------------------
/*
void XmlTree::walk()
{
  (*pOper_)(pRoot);
  pRoot->clearMarks();
  XmlNode* pTemp;
  while(pTemp = pRoot->nextUnmarkedChild())
  {
    walk(pTemp);
  }
}
*/
//----< traversal starting at specific node >------------------------------

void XmlTree::walk(XmlNode* pParent)
{
  tempNodes.push_back(pParent);
  XmlNode* pChild;
  for(size_t i=0; i<pParent->size(); ++i)
  {
    pChild = pParent->nextUnmarkedChild();
    if(pChild != 0)
    {
     walk(pChild);
    }
  }
}

//----< find node with specified value >-----------------------------------

XmlNode* XmlTree::findbyid(std::string tag)
{
  int flag = 0;
  tag = "\""+tag+"\"";
  clearMarks();
  tempNodes.clear();
  walk(pRoot);
  XmlNode* pMNode = 0;
  std::vector<std::pair<std::string, std::string>> temp;
  for(size_t i=0; i < tempNodes.size(); ++i)
  {
    temp = tempNodes[i]->getAttribs();
    if(temp.size() > 0)
    {
      for(size_t j=0; j < temp.size(); ++j)
        if((temp[j].first == "id") && (temp[j].second == tag))
        {
          pMNode = tempNodes[i];
          flag = 1;
          break;
        }
    }
    temp.clear();
    if(flag == 1)
      break;
  }
  if(flag == 0)
    std::cout<<"The id"<<" "<<tag<<" "<<"does not exist"<<"\n\n\n";
  else
    std::cout<<"The id"<<" "<<tag<<" "<<"exists"<<"\n\n\n";
  clearMarks();
  tempNodes.clear();
  temp.clear();
  return(pMNode);
}

//----------< clean up all visitation marks >-----------

void XmlTree::clearMarks()
{
  for(size_t i=0; i < tempNodes.size(); ++i)
    tempNodes[i]->isMarked() = false;
}
//----< delete tree nodes on the way back from DFS traversal >-------------
/*
void XmlTree::delete_walk(XmlNode* pStart)
{
  std::cout << "\n  deleting tree nodes is left as an exercise\n\n";
}
*/
//------< returns the vector of nodes found by tag >------------

std::vector<XmlNode*>XmlTree::findbytag(const std::string &tagname)
{
	clearMarks();
  tempNodes.clear();
	walk(pRoot);
	for(size_t i=0; i < tempNodes.size(); ++i)
  {
    if (tempNodes[i]->value() == tagname)
		{
			tempElement.push_back(tempNodes[i]);
		}
	}
  if(tempElement.size() == 0)
		std::cout<<"The tag"<<" "<<tagname<<" "<<"does not exist"<<"\n\n";
  else
  {
    std::cout<< "The tag"<<" "<<tagname<<" "<<"exists"<<"\n\n";
    for(size_t i=0;i < tempElement.size(); i++)
    {
     std::cout<<"The tags are :- "<<tempElement[i]->value();
    }
    clearMarks();
    tempNodes.clear();
  }
    return(tempElement);
}

//-------< add a node to a tag >---------------

void XmlTree::addtotag(std::string tag)
{
	std::vector<XmlNode*> temp = findbytag(tag);
	if(tempElement.size() > 0)
	{
    XmlNode* pChild = new XmlNode("testTag");
		pChild->setElement("<testTag>");
		pChild->setType("tag");
		if(tempElement[0]->getType()=="selfending")
		{
			std::string result = removeSpace(tempElement[0]->getElement());
			tempElement[0]->getElement().clear();
			tempElement[0]->setElement(result);
			tempElement[0]->getType()="";
			tempElement[0]->setType("tag");
			result.clear();
		}
    tempElement[0]->add(pChild);
  }
  tempElement.clear();	
	temp.clear();
}

//-------< add a node to id >----------------------

void XmlTree::addtoid(std::string tag)
{
  XmlNode* pNode = findbyid(tag);
	if(pNode != 0)
	{
		XmlNode* pChild = new XmlNode("testTag");
		pChild->setElement("<testTag>");
		pChild->setType("tag");
		if(pNode->getType()=="selfending")
		{
			std::string result = removeSpace(pNode->getElement());
			pNode->getElement().clear();
			pNode->setElement(result);
			pNode->getType()="";
			pNode->setType("tag");
			result.clear();
		}
		pNode->add(pChild);
	}
}
//---------< for adding child to self-ending nodes >--------------

std::string XmlTree::removeSpace(std::string tempstr)
{
	int i=0;
	std::string temp="";
	while(i!=(tempstr.length()-3))
	{
		temp=temp+tempstr[i];
		i++;
	}
	temp= temp+tempstr[i+2];
	tempstr.clear();
	return temp;
}

//-------< remove the node by tag >---------------

void XmlTree::removebytag(std::string tag)
{
  tempElement.clear();
	std::vector<XmlNode*> temp = findbytag(tag);
	if(tempElement.size() >0)
	{
		for(size_t i=0; i < tempElement.size(); i++)
		{
			for(size_t j=0; j < tempElement[i]->size(); j++)
			{
				delete(tempElement[i]->getChild(j));
			}
			tempElement[i]->remove();
    }
	}
  tempElement.clear();
	temp.clear();
}

void XmlTree::show(XmlNode *pParent)
{
  tempNodes.push_back(pParent);
  std::cout<<pParent->getElement()<<"\n";
  XmlNode* pChild;
  if((pParent->size() == 0) && (pParent->getType() == "tag"))
    std::cout<< "</"<<pParent->value()<<">"<<"\n";
  for(size_t i=0; i < pParent->size(); ++i)
  {
    pChild = pParent->nextUnmarkedChild();
    if(pChild != 0)
    {
      show(pChild);
	  if(pParent->value() != "Document")
	  if( i == pParent->size()-1)
      std::cout<< "</"<<pParent->value()<<">"<<"\n\n"<<std::endl;
    }
  }
}

#ifdef TEST_XMLTREE

//------------<test stub >-------------
void main()
{
  typedef XmlNode Node; 
  std::cout << "\n  Testing Tree class";
  std::cout << "\n ====================\n";
  XmlTree t;
  //-- create nodes
  try{
  Node root("root");
  root.setElement("root");
  Node child1("child1");
  child1.setElement("child1");
  Node child2("child2");
  child2.setElement("child2");
  Node grandchild11("grandchild11");
  grandchild11.setElement("grandchild11");

//  t.setRoot(&root);
  
  //-- connect "tree"

  child1.add(&grandchild11);
  root.add(&child1);
  root.add(&child2);

  std::cout << "\n  walking connected nodes";
  t.show(&root);

  std::cout << "\n\n  adding grandchildren";

  //-- unmark to prepare for next traversal

  t.clearMarks();
  
  //-- create more nodes

  //Node grandchild21("grandchild21");
  //grandchild21.setElement("grandchild21");
  //Node grandchild22("grandchild22");
  //grandchild22.setElement("grandchild22");
  
  //-- connect into "tree"

  //child2.add(&grandchild21);
  //child2.add(&grandchild22);

 /* Node temp1 = (t.findbyid("child1")); 
  std::cout<< temp1.value()<<"\n";*/


  std::cout << "\n\n  walking connected nodes";
  t.clearMarks();
  t.show(&root);

  /*std::cout << "\n\n  removing grandchild";

  std::cout << "\n\n  walking connected nodes";
  t.show(&root);*/
  //delete(&child1);
  //child1.remove();

  std::cout << "\n\n";
  }
  catch(std::exception ex)
    {
      std::cout << "\n  " << ex.what() << "\n\n";
    }
}
#endif
