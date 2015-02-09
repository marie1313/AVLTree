//Marie Goff
//Jake Thorne


#ifndef GOFISH_COMPARATOR_H
#define GOFISH_COMPARATOR_H

#include "CardComparatorIF.h"
#include "Card.h"

class GoFishComparator: public CardComparatorIF
{
 public:
	 GoFishComparator();
  virtual bool operator()(const Card& left, const Card& right);

private:
	//hold the values of differences between gofish and card
	int heartsValue_;
	int clubsValue_;
	int spadesValue_;
	int diamondsValue_;
	int aceValue_;
};
#endif /* GOFISH_COMPARATOR_H */
