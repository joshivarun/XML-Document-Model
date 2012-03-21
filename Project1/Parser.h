#ifndef XMLPARSER_H
#define XMLPARSER_H
///////////////////////////////////////////////////////////////////////////
//  Parser.h       Parser for XML as demonstrated in SemiExpression.cpp	 //
//  ver 1.1                                                              //
//  Language:      Visual C++, 2008                                      //
//  Platform:      HP Pavilion dv4, Win7 Professional                    //
//  Application:   Parser for an XML file                                //
//  Author:        Varun Joshi, Syracuse University                      //
//                 (315) 706-7277, vjoshi@syr.edu                        //
//  Source:        Jim Fawcett, Syracuse University, CST 4-187,          //
//                 (315) 443-3948, jfawcett@twcny.rr.com                 //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
/*
 *  Module Operations: 
 *  ==================
 *  This module shows how to begin building an XML (recursive descent)parser. 
 *  It uses the services of the Tokenizer and XmlElementParts modules to carry
 *  out all its currently defined activities.  Note that this is just
 *  a vehicle to get you started.
 *
 *  The file scope walker, demonstrated in test stub of SemiExpression.cpp, 
 *  shows you how to do a recursive descent parsing that you need to 
 *  build the XML document tree, required for this project.
 */

#include <stack>
#include "XmlNodes.h"
#include "XmlElementParts.h"
#include "XmlTree.h"


using namespace XmlProcessing;

class Parser
{
public:
  Parser(XmlParts& semi) : parts(semi) {}
  XmlNode* walkScopes();
  XmlNode* createNode(const std::string &);
  std::string makeelement();
private:
  std::stack<XmlNode*> NodeStack;
  XmlParts& parts;
  XmlNode * Document;
};

#endif
