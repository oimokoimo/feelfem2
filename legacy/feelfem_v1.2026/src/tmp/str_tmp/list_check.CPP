#include <iostream.h>
#include "../class/list.hpp"





void main()
{
    list <int>lst;

    lst.addlast(1);
    lst.addlast(2);
    lst.addlast(3);

    listIterator<int> itr(lst);

    int i=0;
    for(itr.init(); !itr; itr++) {
      i++;
      cout <<"lst1 No." << i << "   " << itr() << "\n";
    }

    list <int>lst2 = lst;

    lst.deleteAllValues();
    lst.addlast(10);
    lst.addlast(20);
    lst.addlast(30);


    if(lst2.isEmpty()) cout << "lst2 is empty\n";
    listIterator<int> itr2(lst2);
    i=0;
    for(itr2.init(); !itr2; itr2++) {
      i++;
      cout <<"lst2 No." << i << "   " << itr2() << "\n";
    }
    for(itr.init(); !itr; itr++) {
      i++;
      cout <<"lst1 No." << i << "   " << itr() << "\n";
    }
}
