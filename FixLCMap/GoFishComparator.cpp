//Marie Goff
//Jake Thorne

#include "GoFishComparator.h"

GoFishComparator::GoFishComparator()
{
	heartsValue_ = 2;
	clubsValue_ = 0;
	spadesValue_ = 1;
	diamondsValue_ = 3;
	aceValue_ = -1;
}

bool GoFishComparator::operator()(const Card& left, const Card& right)
  {
	//hold the suit and rank values to update for the gofish game
	  int leftSuit = left.getSuit();
	  int leftRank = left.getRank();

	  int rightSuit = right.getSuit();
	  int rightRank = right.getRank();

	  //switch for gofish suit values
	  switch(leftSuit)
	  {
	  case Card::HEARTS:
		  leftSuit = heartsValue_;
		  break;
	  case Card::CLUBS:
		  leftSuit = clubsValue_;
		  break;
	  case Card::DIAMONDS:
		  leftSuit = diamondsValue_;
		  break;
	  case Card::SPADES:
		  leftSuit = spadesValue_;
		  break;
	  }
	  	  
	   switch(rightSuit)
	  {
	  case Card::HEARTS:
		  rightSuit = heartsValue_;
		  break;
	  case Card::CLUBS:
		  rightSuit = clubsValue_;
		  break;
	  case Card::DIAMONDS:
		  rightSuit = diamondsValue_;
		  break;
	  case Card::SPADES:
		  rightSuit = spadesValue_;
		  break;
	  }

	   //account for ace being the high card
	   if(leftRank == Card::ACE)
	   {leftRank = aceValue_;}

	   	if(rightRank == Card::ACE)
	   {rightRank = aceValue_;}

		//if card rank > handcard rank is True or if ranks are equal then check the suits
		return leftRank > rightRank || (leftRank == rightRank && leftSuit > rightSuit);				 
  }

