#ifdef TEST_EXECUTIVE
/////////////////////////////////////////////////////////////////////
//  Executive.cpp - Executive Module for XML Document Model        //
//  ver 1.0                                                        //
//                                                                 //
//  Language:      Visual C++, 2008                                //
//  Platform:      HP Pavilion dv4, Win7 Professional              //
//  Application:   Prototype for CSE687 Pr1, Sp09                  //
//  Author:        Varun Joshi, Syracuse University                //
//                 (315) 706-7277, vjoshi@syr.edu                  //
//  Source:        Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
//                                                                 //
/////////////////////////////////////////////////////////////////////


#include <iostream>
#include "XmlTree.h"
#include "XmlNodes.h"
#include "Tokenizer.h"
#include "Parser.h"
#include "XmlElementParts.h"

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
    std::cout << "\n  " << std::string(16 + strlen(argv[i]),'-') << "\n";
    try
    { 
        Toker toker(argv[i]); 
	      toker.setMode(Toker::xml);  
        XmlParts parts(&toker);
        Parser sc(parts);
	      XmlTree t;
	      t.makeRoot(sc.walkScopes());
	      t.show(t.getRoot());
	      t.clearMarks();
	      std::cout << "\n\n"; 
	      t.addtoid("testId");
        std::cout<<"\nThe new tree after adding testTag to testId :-)"<<std::endl;
        t.show(t.getRoot()); 
	      t.clearMarks();
	      std::cout << "\n\n";
        t.removebytag("testTag");
        std:: cout << "--The new TREE after removing testTag"<< "\n\n";
	      t.show(t.getRoot());
	      t.clearMarks();
	      std::cout << "\n\n"<<"Finding the tag title\n\n";
        t.findbytag("testTag");
        std::cout << "\n\n"<<"Finding the id testId\n\n";
        t.findbyid("testId");
    }
  
    catch(std::exception ex)
    {
      std::cout << "\n  " << ex.what() << "\n\n";
    }
  }
}


#endif