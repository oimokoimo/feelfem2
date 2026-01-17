#include "string.hpp"
#include "list.hpp"

main()
{
  list <string>strLst;

  string oimo;

  oimo = "No.1";
  

  strLst.add(oimo);

  oimo = "No.2";

  strLst.add(oimo);

  oimo = "No.3";

  strLst.add(oimo);


  listIterator <string>itr(strLst);
  for(itr.init();!itr;++itr) {
    
    cout << "LIST " << itr() << endl;
  }

  //  strLst.deleteAllValuesWithContents();


}

    
 

