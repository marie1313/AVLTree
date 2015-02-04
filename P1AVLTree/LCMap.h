//Marie Goff
//Jake Thorne

#ifndef LCMAP_H
#define LCMAP_H
#include <algorithm>
#include <list>
#include <functional>

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
			
 LCMapNode()
 {
   left_ = NULL;
   right_ = NULL;
   height_=0;
 }
 LCMapNode(K key=K(), V value=V(), LCMapNode* left=NULL, LCMapNode* right=NULL, int height = 0)
 {
   key_ = key;
   value_ = value;
   left_ = left;
   right_ = right;
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
	

 //	/*recursive helper for insert*/
 bool insert(LCMapNode*& cursor, const K& key, const V& value=V())//still need to accout for value?
 {
   bool inserted = false;
   
   if(cursor == NULL)
     {
       cursor = new LCMapNode(key, value);
       ++size_;
       inserted =true;
     }
   else if(c_(cursor->key_, key))//if the key is greater
     {		
       inserted = insert(cursor->right_, key, value);		
       
     }
   else if(c_(key, cursor->key_))//if the key is less
     {		
       inserted = insert(cursor->left_, key, value);		
     }	
   return inserted;
 }

 void removeNodeSimple(LCMapNode*& cursor)
 {
   if(cursor->left_== NULL && cursor->right_ == NULL)
     {
       delete cursor;
       cursor = NULL;
	   --size_;
     }
   else if(cursor->left_ != NULL)
     {
       LCMapNode* tmp = cursor;
       cursor = cursor->left_;		
       delete tmp;
       tmp = NULL;
	   --size_;
     }
   else if(cursor->right_ != NULL)
     {
       LCMapNode* tmp = cursor;
       cursor = cursor->right_;		
       delete tmp;
       tmp = NULL;
	   --size_;
     }
 }

 void erase(LCMapNode*& cursor, const K& key)
 {
   //if(cursor != NULL)
   //{
   //	if(c_(key, cursor->key_))  //if the key is less then the cursor...
   //	{
   //		erase(cursor->left_, key);
   //		//get the previous
   //	}
   //	else if(c_(cursor->key_, key))//if the cursor is less then the key
   //	{
   //		erase(cursor->right_, key);
   //		//get the previous
   //	}		
   
   cursor = lookup(key, cursor);

   //if node has 2 children
   if(cursor->right_ != NULL && cursor->left_ != NULL)
     {			
       LCMapNode* tmp = findMin(cursor->right_);
       
       cursor->key_=tmp->key_;
       cursor->value_ = tmp->value_;
       removeNodeSimple(tmp);
       //erase(cursor->right_, cursor->key_);
       
     }			
   else  //handles 0 & 1 children
     {
       removeNodeSimple(cursor);       
     }
   //}
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

 LCMapNode* copy(LCMapNode* node)
 {
   //need a node to copy to
   LCMapNode* copyNode = NULL;
   
   //check to see if node is null
   if(node != NULL)
     {//if it's not null copy it all the way down the tree
       copyNode = new LCMapNode(node->key_, node->value_, copy(node->left_), copy(node->right_));
     }	
   return copyNode;
 }

 //bool lookup(const K& k, LCMapNode* node)
 //{
 //	bool contained = false;
 //
 //	if(node != NULL)
 //	{
 //		if((!(node->key_<k))&& (!(k < node->key_)))
 //		{
 //			contained = true;
 //		}
 //		else if(c_(k, node->key_))
 //		{
 //			contained = lookup(k, node->left_);
 //		}
 //		else if(c_(node->key_, k))
 //		{
 //			contained = lookup(k, node->right_);
 //		}
 //	}
 //	return contained;
 //
 //}

 LCMapNode* lookup(const K&k, LCMapNode* node)
 {
   if(!(node==NULL))
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

 /*returns the height of the node that stores this key*/
 int height(const K& key)
 {
   int returnHeight = -1;
   if(key != NULL)
     {
       returnHeight=key->height_;
     }
   return returnHeight;
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

 

public:
 /* constructor */
 LCMap(Comparator c = Comparator())
 {
   size_=0;
   root_ = NULL;
   c_ = c;
 }
 
 /* constructor */
 LCMap(K key, V value,Comparator c = Comparator())
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
 bool insert(const K& key, const V& value=V())
 {	
   return insert(root_,key, value);
 }
 
 /* erases key value pair referenced by key. 
    returns true if successful */
 bool erase(const K& key)
 {	
   erase(root_, key);
   
   LCMapNode* cursor;
   cursor = lookup(key, root_);
   return cursor == NULL;
 }
 
 /* lookup the value associated with a key. if the key is not in the 
    map, insert it with default value. Should provide l-value access to 
    value.*/
 V& operator[] (const K& k)
 {
   V* val;
   LCMapNode* cursor;
   bool flag;
   //find the node for k or where that node should be
   cursor = lookup(k, root_);
   if(cursor != NULL)
     {
       val = &(cursor->value_);
     }
   else
     {
       flag = insert(root_, k);
	   val = &(lookup(k, root_)->value_);
     }
   return *val;
 }
 
 //LCMapNode* findPosition(const K& k, LCMapNode* node)
 //{
 //	if(node != NULL)
 //	{
 //		if(c_(k,node->key_))
 //		{
 //			node = findPosition(k, node->left_);
 //		}
 //		else if(c_(node->key_,k))
 //		{
 //			node = findPosition(k, node->right_);
 //		}
 //	}
 //	return node;
 //}
 
 /* returns true if this key maps to a value */
 bool in(const K& k)
 {
   LCMapNode* cursor;
   cursor = lookup(k, root_);
   return cursor != NULL;
 }
 
 /* returns a list of keys in this map */ 
 std::list<K> keys()
 {
   std::list<K> listKeys;
   keyHelper(root_, listKeys);
   return listKeys;
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



};

#endif /* LCMAP_H */
