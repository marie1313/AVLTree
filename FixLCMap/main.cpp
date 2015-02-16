#include <iostream>
#include <cassert>
#include <list>
#include "LCMap.h"
#include "Pancake.h"
#include "Card.h"
#include "GoFishComparator.h"

using namespace std;

int main()
{
    LCMap<int, char> m;
	bool testbool;

    cout << m.size() << endl;

    assert(!m.in(6));
    assert(m.empty()); //empty true test
    m.clear();
    testbool=m.erase(5);
   testbool= m.insert(6, 'c');   //No Children insert and delete
    cout << m.size() << endl;

    assert(m.in(6));
    assert(!m.empty());
  testbool=  m.erase(5);
    cout << m.size() << endl;

    assert(m.in(6));
    m.erase(6);
    cout << m.size() << endl;

    assert(!m.in(6));
    assert(m.empty());


    m.insert(6, 'c');   //Left child insert and delete
    cout << m.size() << endl;

    assert(m.in(6));
    m.insert(5, 'd');
    cout << m.size() << endl;

    assert(!m.empty());
    m.erase(5);
    cout << m.size() << endl;

    assert(!m.empty());
    m.insert(5, 'd');
    cout << m.size() << endl;

    assert(!m.empty());
    m.erase(6);
    cout << m.size() << endl;

    assert(!m.in(6));
    cout << m.size() << endl;

    assert(!m.empty());


    m.insert(8, 'r');   //Right child insert and delete
    m.erase(8);
    m.insert(8, 't');
    m.erase(5);



    m.insert(9, 'd');   //Two child insert and delete
    m.insert(6, 't');
    cout << m.size() << endl;
    m.erase(6);
    m.insert(6, 'f');
    m.erase(9);
    m.insert(9, 'd');
    m.erase(8);
    cout << m.size() << endl;


    m.insert(10, 'e');   //Many keys test
    m.insert(7, 'e');
    m.insert(11, 't');
    m.insert(8, 'e');
    m.insert(5, 'x');
    m.insert(12, 'q');
    assert(!m.insert(12, 'q'));

    assert(m.in(12));
    assert(m.in(10));
    assert(!m.in(99));

    LCMap<int,char> copyMap(m);     //Copy Constructor, Assignment operator, and keys to sorted list tests
    LCMap<int,char> assMap = m;

    list<int> keys = m.keys();
    list<int> copyKeys = copyMap.keys();
    list<int> assKeys = assMap.keys();

    for (list<int>::iterator it = keys.begin(); it != keys.end(); ++it)
        cout << *it << " ";
    cout << m.size() << endl;

	std::pair<int, char> mypair;
	for(LCMap<int, char>::Iterator iter = m.begin(); iter != m.end(); ++iter)
	{
		mypair = *iter;
		cout << mypair.first << " ";
	}

    for (list<int>::iterator it = copyKeys.begin(); it != copyKeys.end(); ++it)
        cout << *it << " ";
    cout << copyKeys.size() << endl;

    for (list<int>::iterator it = assKeys.begin(); it != assKeys.end(); ++it)
        cout << *it << " ";
    cout << assKeys.size() << endl << endl;



    assMap.clear();               //Clear test
    assert(assMap.empty());
    assMap.clear();

    keys = m.keys();
    copyKeys = copyMap.keys();
    assKeys = assMap.keys();

    for (list<int>::iterator it = keys.begin(); it != keys.end(); ++it)
        cout << *it << " ";
    cout << m.size() << endl;

	

    for (list<int>::iterator it = copyKeys.begin(); it != copyKeys.end(); ++it)
        cout << *it << " ";
    cout << copyKeys.size() << endl << "Next line should only have a 0" << endl;

    for (list<int>::iterator it = assKeys.begin(); it != assKeys.end(); ++it)
        cout << *it << " ";
    cout << assKeys.size() << endl << endl;


    assert (m[10] == 'e');
    assert (m[7] == 'e');
    assert (m[11] == 't');

    m[22] = 'u';
    assert(m[22] == 'u');
/*
    const LCMap<int, char> constMap(m);
    assert (constMap[22] == 'u');
*/
/*
    try                             { constMap[23] = 'z'; } //Throws an error if we try this
    catch (LCMap<int,char>::Exp e)  { e.what(); }

*/


///////////////////////////////////////////////
//          non primitive tests              //
///////////////////////////////////////////////

//pancake class declarations

    Pancake blue;
    Pancake choc    ("chocolate chip",6,7);
    Pancake bannana ("bananna",8,4);
    Pancake plain   ("plain",5,2);


    LCMap <int ,Pancake> pmap;

    assert(pmap.empty());//do we have an empty pancake map
    pmap.insert(1,blue);//insert a blueberry pancake

    assert(!pmap.empty());//check to see if that insert works
    assert(pmap[1].getName()   =="blueberry");
    assert(pmap[1].getGuilt()  == 2);
    assert(pmap[1].getFluffy() == 5);

    assert(!pmap.insert(1,blue));//try inserting the same item

    assert(pmap.erase(1));
    assert(!pmap.erase(1));


    assert(pmap.empty());//do we have an empty pancake map
    pmap.insert(1,blue);//insert a blueberry pancake

    assert(!pmap.empty());//check to see if that insert works
    assert(pmap[1].getName()   =="blueberry");
    assert(pmap[1].getGuilt()  == 2);
    assert(pmap[1].getFluffy() == 5);

    pmap.insert(2,choc);
    assert(!pmap.empty());//check to see if that insert works
    assert(pmap[2].getName()   =="chocolate chip");
    assert(pmap[2].getGuilt()  == 7);
    assert(pmap[2].getFluffy() == 6);

    pmap.insert(0,bannana);
    assert(!pmap.empty());//check to see if that insert works
    assert(pmap[0].getName()   =="bananna");
    assert(pmap[0].getGuilt()  == 4);
    assert(pmap[0].getFluffy() == 8);

    LCMap<int,Pancake> cpy_of_pmap(pmap);
    LCMap<int,Pancake> cpy_ctr_of_pmap=pmap;

    assert(!cpy_of_pmap.empty());//check to see if that insert works
    assert(cpy_of_pmap[0].getName()   =="bananna");
    assert(cpy_of_pmap[0].getGuilt()  == 4);
    assert(cpy_of_pmap[0].getFluffy() == 8);

    assert(!cpy_ctr_of_pmap.empty());//check to see if that insert works
    assert(cpy_ctr_of_pmap[0].getName()   =="bananna");
    assert(cpy_ctr_of_pmap[0].getGuilt()  == 4);
    assert(cpy_ctr_of_pmap[0].getFluffy() == 8);


    /*************************************************
    Non-Primitive type with nondefault comparator test
    */

    Card as(Card::SPADES, Card::ACE);
    Card tc(Card::CLUBS, Card::TEN);
    Card fh(Card::HEARTS, Card::FIVE);
    Card sd(Card::DIAMONDS, Card::SEVEN);
    Card ts(Card::SPADES, Card::TEN);
    Card sc(Card::CLUBS, Card::SEVEN);
    Card kh(Card::HEARTS, Card::KING);
    Card jd(Card::DIAMONDS, Card::JACK);

    LCMap<Card, int, GoFishComparator> cardMap;

    cout << cardMap.size() << endl;

    assert(!cardMap.in(as));
    assert(cardMap.empty()); //empty true test
    cardMap.clear();
    cardMap.erase(tc);
    cardMap.insert(as, 6);   //No Children insert and delete
    cout << cardMap.size() << endl;

    assert(cardMap.in(as));
    assert(!cardMap.empty());
    cardMap.erase(tc);
    cout << cardMap.size() << endl;

    assert(cardMap.in(as));
    cardMap.erase(as);
    cout << cardMap.size() << endl;

    assert(!cardMap.in(as));
    assert(cardMap.empty());


    cardMap.insert(as, 6);   //Left child insert and delete
    cout << cardMap.size() << endl;

    assert(cardMap.in(as));
    cardMap.insert(tc, 3);
    cout << cardMap.size() << endl;

    assert(!cardMap.empty());
    cardMap.erase(tc);
    cout << cardMap.size() << endl;

    assert(!cardMap.empty());
    cardMap.insert(tc, 3);
    cout << cardMap.size() << endl;

    assert(!cardMap.empty());
    cardMap.erase(as);
    cout << cardMap.size() << endl;

    assert(!cardMap.in(as));
    cout << cardMap.size() << endl;

    assert(!cardMap.empty());


    cardMap.insert(fh, 'r');   //Right child insert and delete
    cardMap.erase(fh);
    cardMap.insert(fh, 9);
    cardMap.erase(tc);



    cardMap.insert(sd, 3);   //Two child insert and delete
    cardMap.insert(as, 9);
    cout << cardMap.size() << endl;
    cardMap.erase(as);
    cardMap.insert(as, 11);
    cardMap.erase(sd);
    cardMap.insert(sd, 3);
    cardMap.erase(fh);
    cout << cardMap.size() << endl;

    cardMap.insert(ts, 4);   //Many keys test
    cardMap.insert(sc, 4);
    cardMap.insert(kh, 9);
    cardMap.insert(fh, 4);
    cardMap.insert(tc, 12);
    cardMap.insert(jd, 13);
    assert(!cardMap.insert(jd, 13));


    LCMap<Card, int, GoFishComparator> copyCardMap(cardMap);     //Copy Constructor, Assignment operator, and keys to sorted list tests
    LCMap<Card, int, GoFishComparator> assCardMap = cardMap;

    list<Card> cardMapKeys = cardMap.keys();
    list<Card> copyCardMapKeys = copyCardMap.keys();
    list<Card> assCardMapKeys = assCardMap.keys();

    for (list<Card>::iterator it = cardMapKeys.begin(); it != cardMapKeys.end(); ++it)
        cout << *it << " ";
    cout << cardMap.size() << endl;

    for (list<Card>::iterator it = copyCardMapKeys.begin(); it != copyCardMapKeys.end(); ++it)
        cout << *it << " ";
    cout << copyCardMapKeys.size() << endl;

    for (list<Card>::iterator it = assCardMapKeys.begin(); it != assCardMapKeys.end(); ++it)
        cout << *it << " ";
    cout << assCardMapKeys.size() << endl << endl;



    assCardMap.clear();               //Clear test
    assert(assCardMap.empty());
    assCardMap.clear();

    cardMapKeys = cardMap.keys();
    copyCardMapKeys = copyCardMap.keys();
    assCardMapKeys = assCardMap.keys();

    for (list<Card>::iterator it = cardMapKeys.begin(); it != cardMapKeys.end(); ++it)
        cout << *it << " ";
    cout << cardMap.size() << endl;

    for (list<Card>::iterator it = copyCardMapKeys.begin(); it != copyCardMapKeys.end(); ++it)
        cout << *it << " ";
    cout << copyCardMapKeys.size() << endl << "Next line should only have a 0" << endl;

    for (list<Card>::iterator it = assCardMapKeys.begin(); it != assCardMapKeys.end(); ++it)
        cout << *it << " ";
    cout << assCardMapKeys.size() << endl << endl;


    assert (cardMap[jd] == 13);
    assert (cardMap[ts] == 4);
    assert (cardMap[kh] == 9);

    Card td(Card::DIAMONDS, Card::TWO);
    cardMap[td] = 22;
    assert(cardMap[td] == 22);
/*
    const LCMap<Card, int, comparatorGofish> constCardMap(cardMap);
    assert (constCardMap[td] == 22);
*/

    LCMap<char, int> charMap;

    assert(!charMap.in('d'));

    charMap.insert('m', 3);
    assert(!charMap.insert('m', 3));
    assert(charMap.in('m'));
    assert(charMap['m'] == 3);
    charMap['m'] = 4;
    assert(charMap['m'] == 4);

    charMap.insert('r', 3);
    assert(!charMap.insert('r', 3));
    assert(charMap.in('r'));
    assert(charMap['r'] == 3);
    charMap['r'] = 5;
    assert(charMap['r'] == 5);

    charMap.insert('z', 3);
    assert(!charMap.insert('z', 3));
    assert(charMap.in('z'));
    assert(charMap['z'] == 3);
    charMap['z'] = 6;
    assert(charMap['z'] == 6);

    charMap.insert('j', 3);
    assert(!charMap.insert('j', 3));
    assert(charMap.in('j'));
    assert(charMap['j'] == 3);
    charMap['j'] = 7;
    assert(charMap['j'] == 7);

    charMap.insert('g', 3);
    assert(!charMap.insert('g', 3));
    assert(charMap.in('g'));
    assert(charMap['g'] == 3);
    charMap['g'] = 8;
    assert(charMap['g'] == 8);

    charMap.insert('p', 3);
    assert(!charMap.insert('p', 3));
    assert(charMap.in('p'));
    assert(charMap['p'] == 3);
    charMap['p'] = 9;
    assert(charMap['p'] == 9);

    charMap['t'] = 11;
    charMap['t'] = 13;

   // charMap.erase('g');
   // charMap.erase('
/*
    charMap.insert('p', 3);
    charMap.insert('p', 3);

    charMap.insert('f', 3);
    charMap.insert('f', 3);

    charMap.insert('x', 3);
    charMap.insert('x', 3);
*/
    list<char> charKeys = charMap.keys();
    for (list<char>::iterator it = charKeys.begin(); it != charKeys.end(); ++it)
    {
        cout << *it << " ";
        assert(charMap.in(*it));
        //charMap.erase(*it);
        //assert(!charMap.in(*it));
    }

    cout << endl;

//    assert(charMap.empty());
/*
    charMap.erase('d');
    assert(!charMap.in('d'));
    charMap.erase('p');
    assert(!charMap.in('p'));
    charMap.erase('c');
    charMap.erase('b');
*/


    LCMap<char, int> killTest;

    killTest.insert('m', 1);
    killTest.insert('f', 2);
    killTest.insert('j', 3);
    killTest.insert('r', 4);
    killTest.insert('c', 5);
    killTest.insert('p', 6);
    killTest.insert('h', 7);
    killTest.insert('i', 8);
    killTest.insert('g', 9);

    cout << "Current KillTest size: " << killTest.size() << endl;

    killTest.erase('f');
    killTest.erase('r');

    cout << "Current KillTest size: " << killTest.size() << endl;

    assert(!killTest.in('f'));
    assert(!killTest.in('r'));

    assert(killTest['g'] == 9);
    assert(killTest['p'] == 6);

    assert(killTest.in('h'));
    assert(!killTest.in('z'));
    assert(killTest.in('j'));

    cout << "\nIf you are reading this than all tests have passed\n";

    return 0;
}
