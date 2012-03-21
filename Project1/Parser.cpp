///////////////////////////////////////////////////////////////////////////
//  Parser.cpp     Parser for XML as demonstrated in SemiExpression.cpp	 //
//  ver 1.0                                                              //
//                                                                       //
//  Language:      Visual C++, 2008                                  //
//  Platform:      HP Pavilion dv4, Win7 Professional                    //	                       
//  Author:        Varun Joshi,Syracuse University                       //
//                 (315) 706-7277, vjoshi@syr.edu                        //
//  Source:        Jim Fawcett, Syracuse University, CST 4-187,          //
//                 (315) 443-3948, jfawcett@twcny.rr.com                 //
//                                                                       //  
///////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Parser.h"

using namespace XmlProcessing;


//-- creates a node while parsing --representing an element in the XML file
  
XmlNode* Parser::createNode(const std::string &tagname)
{
	int i=0;
	XmlNode *pNode= new XmlNode(tagname);
	if(parts.length()>1)
  {
    if(tagname == parts[1])
    {
      while(parts[i] != ">")
      {
        if(parts[i]== "=")
          pNode->setAttribs(parts[i-1],parts[i+1]);
        i++;
      }
      if(parts[parts.length()-2] != "/")
        pNode->setType("tag");
      else pNode->setType("selfending");
    }
  }
  pNode->setElement(makeelement());
  //pNode->setElement(makeElement());
	NodeStack.top()->add(pNode);
	return(pNode);
}

//-----------< remove spaces from the element >---------------

std::string Parser::makeelement()
{
	if(parts.length() == 0)
    return "";
  std::string temp = parts[0];
  
  if((parts[0] == "<") && (parts.length()>1))
  {
	  int i=1;
	  while(parts[i] != ">")
  {
	  if((parts[i-1] == "<") || (parts[i-1]=="?") || (parts[i-1]=="/") || (parts[i-1]=="!"))
		  temp = temp+parts[i];
	  else temp = temp+" "+parts[i];
	  i++;
  }
	  temp = temp+parts[i];
  }
  else temp = parts.show();
  
	
	return(temp);
}


//-- Implements the parsing of the XML file

XmlNode* Parser::walkScopes()
{
  Document = new XmlNode("Document");
  NodeStack.push(Document);
  std::string tok = "";
  while(parts.get())
  {
	std::string firstTok;
    if(parts.length() > 1)
	   firstTok = parts[1];
    if (firstTok == "/") 
    {
      NodeStack.pop();
      if(NodeStack.size() == 0)
        std::cout << "\n"; 
      continue;
    }
    else if(firstTok == "?")  
      tok = "Processing";
    else if(firstTok == "!")
			tok = "Comment";
    else if(parts[0]== "<")
		  tok = parts[1];

    else tok = parts.show();
    XmlNode* newnode = createNode(tok);
    if((tok != "Comment") && (tok != parts.show()) && (tok != "Processing") && (parts[parts.length()-2] != "/"))
      NodeStack.push(newnode);
  }
  return(NodeStack.top());
}

//----------------< TEST STUB >----------------------------

#ifdef TEST_XMLPARSER


int main(int argc, char* argv[])
{ 
  std::cout << "\n  XML Document Object Model \n "<< std::string(20,'=') << std::endl;
  if(argc < 2)  
  { 
    std::cout << "\n  please enter name of file to process on command line\n\n";
    return 1;  
  }    
  for(int i=1; i<argc; ++i)
  { 
    std::cout << "\n  Processing  " << argv[i];
    std::cout << "\n  " << std::string(16+ strlen(argv[i]),'-') << "\n";
    try
    { 
      if(argv[1][0] == '<')  
      {
     	Toker toker(argv[i], false); //for xml string
	    toker.setMode(Toker::xml);  
      XmlParts parts(&toker);
      Parser sc(parts);
	    XmlTree t;
	    t.makeRoot(sc.walkScopes());
	    t.show(t.getRoot());
	    t.clearMarks();
	    std::cout << "\n\n";
      t.show(t.getRoot());
	    t.addtoid("testId");
      std::cout<<"\nThe new tree after adding testTag to testId :-) \n\n";
      t.show(t.getRoot()); 
	    t.clearMarks();
	    std::cout << "\n\n";
	    std::cout << "\n\n"<<"Finding the tag title\n\n";
      t.findbytag("title");
      
      std::cout << "\n\n"<<"Finding the id testId\n\n";
      t.findbyid("testId");
      }
	}
    catch(std::exception ex)
    {
      std::cout << "\n  " << ex.what() << "\n\n";
    }
  }
}

#endif



