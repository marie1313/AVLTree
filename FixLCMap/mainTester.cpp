
//Marie Goff
//Jake Thorne
//hello

#include <iostream>
#include <list>
#include "LCMap.h"
#include <string>
#include "Card.h"
#include "GoFishComparator.h"

using namespace std;

int main()
{
	bool testbool = false;

	 LCMap<string,int> map;
	map["m"] = 87;

	GoFishComparator comparator;
	Card card1(Card::DIAMONDS, Card::EIGHT);
	Card card2(Card::SPADES, Card::ACE);
	list<Card> cardList;


  cardList.push_back(card1);
  cardList.push_back(card2);

  LCMap<int, list<Card>, GoFishComparator> cardmap(1, cardList, comparator);
  LCMap<Card, int, GoFishComparator> cardKeyMap(card1, 1, comparator);

  //cardmap[2] = cardList;
  testbool = cardKeyMap.erase(card1);
  


  testbool = cardKeyMap.insert(card2, 1);
  cout << "test card should be 1 " << testbool << endl;


	list<string> addStr;
	addStr.push_back("above");

    LCMap<string, list<string> > s1("b", addStr);

//[] operator
	//s1["a"];

	s1["a"].push_back("average");
	
    //test copy const
	LCMap<string, list<string> > s2(s1);
	
	//insert
	addStr.push_back("around");
	testbool = s1.insert("a",addStr );
	 cout << "insert a this should be 0 " << testbool << endl;
	
	testbool = s1.insert("b",addStr );	
	cout << "insert b this should be 0 " << testbool << endl;

	//insert
	addStr.push_back("hola");
	testbool = s1.insert("d",addStr );
	 cout << "insert d this should be 1 " << testbool << endl;

	 //insert
	addStr.push_back("something");
	testbool = s1.insert("c",addStr );
	 cout << "insert c this should be 1 " << testbool << endl;

	 //insert
	addStr.push_back("whatever");
	testbool = s1.insert("e",addStr );
	 cout << " insert e this should be 1 " << testbool << endl;
	
	//= operator
	s2 = s1;	

	//[] operator
	s1["a"].push_back("average");

	//erase(key)  calls findMin & removeNodeSimple
	testbool = s2.erase("a");
	 cout << "erase a this should be 1 " << testbool << endl;
	
	//in
	 testbool = false;
	testbool = s1.in("b");
	cout << "ck in for b this should be 1 " << testbool << endl;
	testbool = s1.in("f");
	cout << "ck in for f this should be 0 " << testbool << endl;

	//keys() returns a list of keys
	addStr = s1.keys();
	  for(list<string>::iterator it = addStr.begin();it != addStr.end(); ++it)
  {
	cout << "test keys() keys are: " << *it << endl;
  }

	//empty() returns size==0
	testbool = s1.empty();
	 cout << "test empty this should be 0 " << testbool << endl;

	//size() returns int
	int sizeOf = s1.size();
	cout << "test size this should be 5 " << sizeOf << endl;

	//erase(key)  calls findMin & removeNodeSimple
	testbool = s1.erase("d");
	 cout << "test erase d this should be 1 " << testbool << endl;

	//clear() ~destructor
	s1.clear();
	s2.clear();
	
	sizeOf = s1.size();
	     
	cout << "test clear this should be 0 " << sizeOf << endl;
  
	system("pause");

}
