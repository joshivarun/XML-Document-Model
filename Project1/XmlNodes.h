#ifndef XMLNodes_H
#define XMLNodes_H
///////////////////////////////////////////////////////////////////////////
// XmlNodes.h - Nodes that represent parts of an XML document            //
// ver 1.1                                                               //
// Language:    Visual C++, 2008                                         //
// Platform:    HP Pavilion dv4, Win7 Professional                       //
// Application: CSE687 - Demo for Project #1, Spring 2009                //
// Author:      Varun Joshi, Syracuse University                         //
//              (315) 706-7277, vjoshi@syr.edu                           //
// Source:      Jim Fawcett, Syracuse University, CST 4-187,             //
//              (315) 443-3948, jfawcett@twcny.rr.com                    //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * Provides an XmlNode class that holds a finite number of pointers
 * to child nodes, and a visitation predicate.  
 *
 * Public Interface:
 * =================
 * XmlNode *pNode				// create Node instance
 * pNode.add(XmlNode *child);				// add child to pnode
 * pNode.size()							// return the number of children of pNode
 * pChild = pParent->nextUnmarkedChild() // returns the child that has not been marked
 * pNode->isMarked() = false				// sets the value of the variable "visited" to false
 * pNode->value()						// returns the tagname for pNode
 * pNode->setAttribs(str1,str2)			// sets str1 as the attribute name , and str2 as the attribute value 
 * pNode->setElement(temp)				// stores an XML element described by temp with the node
 * pNode->setType(type)					// stores the type(Tag,Preprocessor,selfending node,etc  of XML element with the node
 * child1=pNode->getChild(1)			// returns the child node of pNode
 * pNode->remove()						// removes the children vector of pNode
 *
 */

#include <vector>
#include <string>
#include <sstream>

namespace XmlProcessing
{
  class XmlNode
  {
  public:
    XmlNode(const std::string& value="");
    ~XmlNode();
    void add(XmlNode* pXmlNode);
    size_t size(); 
    bool remove(XmlNode* pXmlNode);
    XmlNode* nextUnmarkedChild(); 
    std::string& value();
    //virtual std::string ToString();
    bool &isMarked(); 
    void remove(); 
    void setAttribs(const std::string&, const std::string&); 
    std::vector<std::pair<std::string, std::string>> getAttribs(); 
    XmlNode* getChild(int i); 
    void setElement(const std::string&);
    std::string& getElement(); 
    void setType(const std::string&);
    std::string& getType();
    // Compiler generated copy and assignment are shallow.
    // That makes sense for a Node class.
  private:
    std::vector<XmlNode*> children; //instead of nodeptrs
    std::string tag; //instead of std::string value_
    std::vector<std::pair<std::string, std::string>> attrib;
    std::string element, type;
    bool visited;
  
  };

  //----< construct accepts value, can be used as void ctor >--------------

  inline XmlNode::XmlNode(const std::string& value) : visited(false), tag(value) {}

  //----< add child node >-------------------------------------------------

  inline void XmlNode::add(XmlNode* pXmlNode)
  {
    children.push_back(pXmlNode);
  }
  
  //----< return instance of template type >-------------------------------

  inline std::string& XmlNode::value() { return tag; }

  //-----< return the number of children >-----------------------------

  inline size_t XmlNode::size() { return children.size(); }

  //--------< return whether a node is marked or not >-------------------
  
  inline bool& XmlNode::isMarked() { return visited; }

  //----------<  type of element >-----------------------

  inline void XmlNode::setType(const std::string& tag) { type = tag; }

  //-----------< returns the type of element >------------------

  inline std::string& XmlNode::getType() { return type; }

  //-----------< removes the children of the node >-------------------

  inline void XmlNode::remove() { children.clear(); }

}

#endif

