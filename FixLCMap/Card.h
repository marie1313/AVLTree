#ifndef CARD_H
#define CARD_H

#include <ostream>

class Card
{
  // member data
 public:
  enum Suit{HEARTS = 0, CLUBS, DIAMONDS, SPADES, NO_SUIT};
  enum Rank{TWO = 0, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, NO_RANK};
  const static int MAX_RANKS = 13;
  const static int MAX_SUITS = 4;
  // Number of cards in a deck
  const static int CARDS_PER_DECK = 52;

 private:
  Suit suit_;
  Rank rank_;
  
  static std::string *rank_symbols_;
  static char *suit_symbols_;
  
  static std::string * initRankSymbols();
  static char * initSuitSymbols();
  
  // member functions
 public:
  Card();
  Card(Suit suit, Rank rank);
  virtual ~Card(void);
  
  Suit getSuit() const;
  Rank getRank() const;

  bool operator ==(const Card&) const;

  /*
   * Increment the rank using the standard formula, e.g., 2->3, 3->4, ..., K->A.
   */
  static void incrementRank(Rank& rank);
  
  friend std::ostream& operator << (std::ostream& os, const Card& card);
};

#endif //CARD_H

