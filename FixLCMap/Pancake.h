#ifndef PANCAKE_H
#define PANCAKE_H
#include <string>

/*
  The Pancake non -primitive testing class
  By: Michael Carey
*/

class Pancake
{

 public:
    //ctors
    Pancake(std::string name = "blueberry",int fluffy = 5,int guilt = 2):
        name_(name),fluffy_(fluffy),guilt_(guilt){}

    Pancake(const Pancake& other):name_(other.name_),
        fluffy_(other.fluffy_),guilt_(other.guilt_){}

    ~Pancake(){}//dtor

    //operators
    const Pancake& operator=(const Pancake& other)
    {
        name_= other.name_;
        fluffy_= other.fluffy_;
        guilt_= other.guilt_;
        return *this;
    }

    bool operator<(const Pancake& other){return fluffy_ < other.fluffy_ || guilt_ > other.guilt_;}
    bool operator>(const Pancake& other){return !(*this<other);}

    //get functions
    const std::string& getName  () { return name_;   }
    const int&         getFluffy() { return fluffy_; }
    const int&         getGuilt () { return guilt_;  }

private:
    std::string name_;
    int fluffy_;
    int guilt_;

};


#endif
