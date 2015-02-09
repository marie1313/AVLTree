//Marie Goff
//Jake Thorne

#ifndef LCMAP_H
#define LCMAP_H
#include <algorithm>
#include <list>
#include <functional>
#include <cstddef>


template <typename K, typename V, typename Comparator = std::less<K> >
class LCMap{

 private:

	class LCMapNode
	{
		public:
			V value_;
			K key_;
			int height_;

			LCMapNode* left_;
			LCMapNode* right_;
			LCMapNode* parent_;
			
			LCMapNode()
			{
   
			left_ = NULL;
			right_ = NULL;
			parent_ = NULL;
			height_=0;
			}
			 LCMapNode(K key, V value, LCMapNode* left=NULL, LCMapNode* right=NULL,LCMapNode* parent=NULL, int height = 0)
			 {
			   key_ = key;
			   value_ = value;
			   left_ = left;
			   right_ = right;
			   parent_ = parent;
			   height_ = height;
			 }
		
			 LCMapNode(const LCMapNode& orig)
			 {
			   value_ = orig.value_;
			   key_ = orig.key_;
			   left_ = orig.left_;
			   right_ = orig.right_;
			   height_ = orig.height_;
			 }
	
 };

 int size_;
 LCMapNode* root_;
 Comparator c_;

 /*recursive helper for insert*/
 bool insert(LCMapNode*& cursor, const K& key, const V& value=V(), LCMapNode* parent= NULL)
 {
	 bool inserted = false;

	 if(!(lookup(key, cursor)))
	 {
		 if(cursor == NULL)
		 {
			 //make my new node here
		   cursor = new LCMapNode(key, value, NULL, NULL, parent);
		   ++size_;
		   inserted = true;
		   balanceTree(cursor);
		 }
		else if(c_(cursor->key_, key))//if the key is greater
		{
			inserted=insert(cursor->right_, key, value, cursor);
		}
		else if(c_(key, cursor->key_))//if the key is less
		{
			inserted=insert(cursor->left_, key, value, cursor);
		}	 
		
		balanceTree(cursor);
	}
	return inserted;
 }

 	/*rotate the tree node with left child*/
void rotateLeft(LCMapNode*& node)
{
	LCMapNode *k1 = node->left_;
	node->left_ = k1->right_;
	k1->right_ =node;
	//node->height_ = std::max(height( node->left_->key_), height( node->right_->key_)) +1;
	//k1->height_ = std::max(height( k1->left_->key_),node->height_) +1;
	node = k1;
}

	/*rotate the tree node with right child*/
void rotateRight(LCMapNode*& node)
{
	LCMapNode *k1 = node->right_;
	node->right_ = k1->left_;
	k1->left_ =node;
	//node->height_ = std::max( height(node->right_->key_), height( node->left_->key_)) +1;
	//k1->height_ = std::max(height( k1->right_->key_),node->height_) +1;
	node = k1;
	//add parent pointer update
}

void doubleRotateRight(LCMapNode*& k3)
{
	rotateLeft(k3->right_);
	rotateRight(k3);
}

void doubleRotateLeft(LCMapNode*& k3)
{	
	rotateRight(k3->left_);
	rotateLeft(k3);
}

int balanceFactor(LCMapNode* node)
{
	int bf = ((height(node->left_))-(height(node->right_)));
	return bf;
}

int height(LCMapNode *node)
 {
	 int returnHeight = -1;
	 if(node != NULL)
	 {
		 returnHeight = node->height_;
	 }
	 return returnHeight;
 }

void balanceTree(LCMapNode*& cursor)
 {
	 if(cursor != NULL)
	 {
		 if((balanceFactor(cursor)) == 2)//book has >1
		 {
			if(balanceFactor(cursor->left_)==1)
			{
				rotateLeft(cursor);
			}
			else if(balanceFactor(cursor->left_)==-1)
			{
				doubleRotateLeft(cursor);
			}
		}
		else if(balanceFactor(cursor)==-2)
		{
			if(balanceFactor(cursor->right_)==-1)
			{
				rotateRight(cursor);
			}
			else if(balanceFactor(cursor->right_)==1)
			{
				doubleRotateRight(cursor);
			}
		}
	
		 cursor->height_= std::max(height(cursor->left_), height(cursor->right_)) +1;
	 }
 }

LCMapNode* findMin(LCMapNode* pNode)//only finds the smallest
 {
   //if(pNode != NULL && pNode->left_ != NULL)
   if(pNode->left_	!= NULL)
     {
       pNode = findMin(pNode->left_);
     }
   return pNode;
 }

void removeNodeSimple(LCMapNode*& cursor)
 {
   if(cursor->left_==NULL && cursor->right_ == NULL)
     {
       delete cursor;
       cursor = NULL;
     }
   else if(cursor->left_ != NULL)
     {
       LCMapNode* tmp = cursor;
       cursor = cursor->left_;		
       delete tmp;
     }
     else if(cursor->right_ != NULL)
     {
       LCMapNode* tmp = cursor;
       cursor = cursor->right_;		
       delete tmp;
     }
 }

void erase(LCMapNode*& cursor, const K& key)
 {
   if(cursor != NULL)
     {
       if(c_(key, cursor->key_))  //if the key is less then the cursor...
	 {
	   erase(cursor->left_, key);
	   //get the previous
	 }
       else if(c_(cursor->key_, key))//if the cursor is less then the key
	 {
	   erase(cursor->right_, key);
	   //get the previous
	 }		
       else if(cursor->right_ != NULL && cursor->left_ != NULL)//if node has 2 children
	 {
	   LCMapNode* tmp = findMin(cursor->right_);
	   
	   cursor->key_=tmp->key_;
	   cursor->value_ = tmp->value_;
	   
	   erase(cursor->right_, cursor->key_);
	   
	 }			
       else  //handles 0 & 1 children
	 {
	   removeNodeSimple(cursor);
	   --size_;
	 }
     }
   balanceTree(root_);
 }

void clear(LCMapNode*& node)
 {
   if(node != NULL)
     {
       clear(node->left_);
       clear(node->right_);
       delete node;			
     }
   node=NULL;
 }

 LCMapNode* lookup(const K& k, LCMapNode* node)
 {
   //LCMapNode* tmp = node;
   if(node != NULL)
   {
		if(c_(k,node->key_))
		{
			node = lookup(k, node->left_);
		}
		else if(c_(node->key_,k))
		{
			node = lookup(k, node->right_);
		}
     }
   return node;
 }

 LCMapNode* copy(LCMapNode* node)
 {
   //need a node to copy to
   LCMapNode* copyNode = NULL;
   
   //check to see if node is null
   if(node != NULL)
     {//if it's not null copy it all the way down the tree
       copyNode = new LCMapNode(node->key_, node->value_, copy(node->left_), copy(node->right_), copy(node->parent_));
     }	
   return copyNode;
 }
 
  void keyHelper(LCMapNode* node, std::list<K>& listKeys)
 {
   if(node != NULL)
     {
       keyHelper(node->left_,listKeys);
       listKeys.push_back(node->key_);
       keyHelper(node->right_,listKeys);
     }
 }

 public:
 /* constructor */
 LCMap(Comparator c = Comparator())
 {
   size_=0;
   root_ = NULL;
   c_ = c;
 }
 
 /* constructor */
 LCMap(K key, V value=V(),Comparator c = Comparator())
 {
   root_= new LCMapNode(key, value);   
   size_=1;
   c_ = c;
 }
 
 /* copy constructor */
 LCMap(const LCMap<K,V,Comparator>& orig)
 {
   c_=orig.c_;
   size_ = orig.size_;
   root_ = copy(orig.root_);   
 }
 
 /* cleans up all memory for storage and calls the destructor for the 
    keys and values stored */
 virtual ~LCMap(){ clear(); }
 
 /* assignment operator */
 LCMap<K,V,Comparator>& operator =(const LCMap<K,V,Comparator>& rhs)
 {
   if(this != &rhs)
     {
       clear();
       c_=rhs.c_;
       size_ = rhs.size_;
       root_ = copy(rhs.root_);
     }
   
   return *this;
 }
 
 /* inserts the key value pair */
 bool insert(const K& key, const V& value)
 {	
	 return insert(root_, key, value);//return a bool
 }
 
 /* erases key value pair referenced by key. 
    returns true if successful */
 bool erase(const K& key)
 {   
	 bool erased=lookup(key, root_);
	 if (erased)
	 {
		erase(root_, key);
		erased = (!(lookup(key, root_)));//get rid of this line after testing
	 }
   return erased;
 }
 
 /* lookup the value associated with a key. if the key is not in the 
    map, insert it with default value. Should provide l-value access to 
    value.*/
 V& operator[] (const K& k)
 {
   V* val = NULL;
   LCMapNode* cursor;
   //find the node for k or where that node should be
   cursor = lookup(k, root_);
   if(cursor != NULL)
     {
       val = &(cursor->value_);
     }
   else
     {
       insert(root_, k, V());
       val = &(lookup(k, root_)->value_);
     }
   return *val;
 }
  
 /* returns true if this key maps to a value */
 bool in(const K& k)
 {
   return lookup(k, root_);
 }
 
 /* returns a list of keys in this map */ 
 std::list<K> keys()
 {
   std::list<K> listKeys;
   keyHelper(root_, listKeys);
   return listKeys;
 }
 
 /* returns true if the map is empty */ 
 bool empty() const{ return size_==0; }
 
 /* number of key value pairs stored */
 int size() const {return size_; }
 
 /* empties the map */
 void clear()
 { 
   clear(root_);	
   size_ = 0;
   root_ = NULL;	
 }

  /*returns the height of the node that stores this key*/
 int height(const K& key)
 {
	 LCMapNode* node;
	 node=lookup(key,root_);
	 return height(node);   
 }


 
	class iterator
	{
		public:
		iterator(){postOrderStart(cursor_);}
		
		K& key(){return cursor_->key_;}
		V& value(){return cursor_->value_;}
		void operator++()
		{
			
		}
		
		private:

		LCMapNode* cursor_;

		void postOrderStart(LCMapNode*& cursor)
		{
			//recurse until we get to the node that will
			//be the first in the post order traversal
			
			//Check the left child
			if(cursor->left != NULL)//I don't think we can use != on left or right children only <
			{
				postOrderStart(cursor->left_);
			}
			//Check the right child 
			if(cursor->right_ != NULL)
			{
				postOrderStart(cursor->right);
			}
		}
	};

};

#endif /* LCMAP_H */
