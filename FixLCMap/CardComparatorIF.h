#ifndef CARD_COMPARATOR_IF_H
#define CARD_COMPARATOR_IF_H

#include "Card.h"

class CardComparatorIF{
 public:
  // returns true if the first card should be ordered before the second
  virtual bool operator()(const Card&, const Card&) = 0;
};

#endif
