#include "Card.h"
#include <string>

using namespace std;

Card::Card() : suit_(NO_SUIT), rank_(NO_RANK){}

Card::Card(Suit suit, Rank rank) : suit_(suit), rank_(rank){}


Card::~Card(void){
  // nothing yet
}

Card::Rank Card::getRank() const{
  return rank_;
}

Card::Suit Card::getSuit() const{
  return suit_;
}

bool Card::operator ==(const Card& rhs) const{
  return this->rank_ == rhs.rank_ && this->suit_ == rhs.suit_;
}

void Card::incrementRank(Rank& rank){
  int higher_rank = static_cast<int>(rank) + 1;
  rank = static_cast<Rank>(higher_rank);
}

ostream& operator << (ostream& os, const Card& card){
  os << Card::rank_symbols_[card.rank_] << Card::suit_symbols_[card.suit_];
  return os;
}

char * Card::initSuitSymbols(){
  char * dynTmp = new char[MAX_SUITS];
  dynTmp[HEARTS] = 'H';
  dynTmp[DIAMONDS] = 'D';
  dynTmp[CLUBS] = 'C';
  dynTmp[SPADES] = 'S';
  return dynTmp;
}

string * Card::initRankSymbols(){
  const char * tmpRankSymbols[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
  string * dynTmp = new string[MAX_RANKS];
  for(int i = 0; i < MAX_RANKS; i++){
    dynTmp[i] = string(tmpRankSymbols[i]);
  }
  
  return dynTmp;
}

char * Card::suit_symbols_ = Card::initSuitSymbols();
string * Card::rank_symbols_ = Card::initRankSymbols();