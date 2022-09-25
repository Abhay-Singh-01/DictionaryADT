//-----------------------------------------------------------------------------
// Abhay Singh, abrsingh
// 2022 Spring CSE101 PA#7
// Dictionary.cpp
// Dictionary ADT implementation
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include <stdexcept>
#include"Dictionary.h"

   // Class Constructors & Destructors ----------------------------------------
   
   // Creates new Dictionary in the empty state. 
   
   Dictionary::Node::Node(keyType k, valType v) {
       key = k;
       val = v;
       parent = left = right = nullptr;
   }

   Dictionary::Dictionary() {
        nil = new Node("*", -1);
        nil->left = nil;
        nil->right = nil;
        nil->parent = nil;
        root = nil;
        current = nil;
        num_pairs = 0;
   }

   // Copy constructor.
   Dictionary::Dictionary(const Dictionary& D) {
       nil = new Node("*", -1);
       nil->parent = nil;
       nil->left = nil;
       nil->right = nil;
       root = nil;
       current = nil;
       num_pairs = 0;
       preOrderCopy(D.root, D.nil);
   }

   // Destructor
   Dictionary::~Dictionary() {
       postOrderDelete(this->root);
       //delete current;
       //delete root;
       delete nil;
   }

   // Helper Functions--------------------------------------------------------------


      // inOrderString()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair in
   // tree R, arranged in order by keys.
   void Dictionary::inOrderString(std::string& s, Node* R) const {
       if (R != nil) {
           inOrderString(s, R->left);
           s += R->key;
           s += " : ";
           s += std::to_string(R->val);
           s+= "\n";
           inOrderString(s, R->right);
       }
   }

   // preOrderString()
   // Appends a string representation of the tree rooted at R to s. The appended
   // string consists of keys only, separated by "\n", with the order determined
   // by a pre-order tree walk.
   void Dictionary::preOrderString(std::string& s, Node* R) const {
       if (R != nil) {
           s += R->key;
           s += "\n";
           preOrderString(s, R->left);
           preOrderString(s, R->right);
       }
   }

   // preOrderCopy()
   // Recursively inserts a deep copy of the subtree rooted at R into this 
   // Dictionary. Recursion terminates at N.
   void Dictionary::preOrderCopy(Node* R, Node* N) {
       if (R != nil && R != N) {
           this->setValue(R->key, R->val);
           preOrderCopy(R->left, N);
           preOrderCopy(R->right, N);
       }
   }

//    postOrderDelete()
//    Deletes all Nodes in the subtree rooted at R, sets R to nil.
   void Dictionary::postOrderDelete(Node* R) {
       if (R == nil) {
           return;
       }
       postOrderDelete(R->left);
       postOrderDelete(R->right);
       delete R;
   }

   // search()
   // Searches the subtree rooted at R for a Node with key==k. Returns
   // the address of the Node if it exists, returns nil otherwise.
   Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
       if (R == nil || k == R->key) {
           return R;
       } else if (k < R->key) {
           return search(R->left, k);
       } else {
           return search(R->right, k);
       }
   }

   // findMin()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // leftmost Node in that subtree, otherwise returns nil.
   Dictionary::Node* Dictionary::findMin(Node* R) {
       while(R->left != nil) {
           R = R->left;
       }
       return R;
   }

   // findMax()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // rightmost Node in that subtree, otherwise returns nil.
   Dictionary::Node* Dictionary::findMax(Node* R) {
       while (R->right != nil) {
           R = R->right;
       }
       return R;
   }

   // findNext()
   // If N does not point to the rightmost Node, returns a pointer to the
   // Node after N in an in-order tree walk.  If N points to the rightmost 
   // Node, or is nil, returns nil. 
   Dictionary::Node* Dictionary::findNext(Node* N) {
       if (N->right != nil) {
           return findMin(N->right);
       }
       Node* y = N->parent;
       while( y != nil && N == y->right ) {
           N = y;
           y = y->parent;
       }
       return y;
   }

   // findPrev()
   // If N does not point to the leftmost Node, returns a pointer to the
   // Node before N in an in-order tree walk.  If N points to the leftmost 
   // Node, or is nil, returns nil.
   Dictionary::Node* Dictionary::findPrev(Node* N) {
       if (N->left != nil) {
           return findMax(N->left);
       }
       Node* y = N->parent;
       while( y != nil && N == y->left ) {
           N = y;
           y = y->parent;
       }
       return y;
   }

   void Dictionary::Transplant(Node* u, Node* v) {
       if (u->parent == nil) {
           this->root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nil) {
            v->parent = u->parent;
        }
   }


    // Access functions --------------------------------------------------------

   // size()
   // Returns the size of this Dictionary.
   int Dictionary::size() const {
       return this->num_pairs;
   }

   // contains()
   // Returns true if there exists a pair such that key==k, and returns false
   // otherwise.
   bool Dictionary::contains(keyType k) const {
       Node* y = search(this->root, k);
       if (y == nil) {
           return false;
       } else {
           return true;
       }
   }

   // getValue()
   // Returns a reference to the value corresponding to key k.
   // Pre: contains(k)
   valType& Dictionary::getValue(keyType k) const {
       if (this->contains(k)) {
           Node*y = search(this->root, k);
           return y->val;
       } else {
           throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
       }
   }

   // hasCurrent()
   // Returns true if the current iterator is defined, and returns false 
   // otherwise.
   bool Dictionary::hasCurrent() const {
       if (this->current != nil) {
           return true;
       } else {
           return false;
       }
   }

   // currentKey()
   // Returns the current key.
   // Pre: hasCurrent() 
   keyType Dictionary::currentKey() const {
       if (this->hasCurrent()) {
           return this->current->key;
       } else {
           throw std::logic_error("Dictionary: currentKey(): current undefined");
       }
   }

   // currentVal()
   // Returns a reference to the current value.
   // Pre: hasCurrent()
   valType& Dictionary::currentVal() const {
       if (this->hasCurrent()) {
           return this->current->val;
       } else {
           throw std::logic_error("Dictionary: currentVal(): current undefined");
       }
   }


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Resets this Dictionary to the empty state, containing no pairs.
   void Dictionary::clear() {
       this->postOrderDelete(this->root);
       this->root = nil;
       this->current = nil;
       this->num_pairs = 0;   
   }

   // setValue()
   // If a pair with key==k exists, overwrites the corresponding value with v, 
   // otherwise inserts the new pair (k, v).
   void Dictionary::setValue(keyType k, valType v) {
       Node* y = nil;
       Node* x = this->root;
       Node* z = new Node(k, v);
       z->left = z->right = z->parent = nil;
       while (x != nil) {
           y = x;
           if (z->key < x->key) {
               x = x->left;
            }else if (z->key == x->key) {
                x->val = v;
                delete z;
                return;
           } else {
               x = x->right;
           }
       }
        z->parent = y;
        if (y == nil) {
            this->root = z;
            this->num_pairs += 1;
        } else if (z->key < y->key) {
            y->left = z;
            this->num_pairs += 1;
        } else {
            y->right = z;
            this->num_pairs += 1;
        }
   }


   // remove()
   // Deletes the pair for which key==k. If that pair is current, then current
   // becomes undefined.
   // Pre: contains(k).
   void Dictionary::remove(keyType k) {
       if (this->contains(k)) {
           Node* y = search(this->root, k);
           if (y == this->current) {
               this->current = nil;
           }
           if (y->left == nil) {
               this->Transplant(y, y->right);
           } else if (y->right == nil) {
               this->Transplant(y, y->left);
           } else {
               Node* z = findMin(y->right);
               if (z->parent != y) {
                   this->Transplant(z, z->right);
                   z->right = y->right;
                   z->right->parent = z;
               }
               this->Transplant(y, z);
               z->left = y->left;
               z->left->parent = y;
           }
           this->num_pairs -= 1;
           delete y;
       } else {
           throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
       }
   }

   // begin()
   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void Dictionary::begin() {
       if (this->num_pairs > 0) {
           this->current = this->findMin(this->root);
       }
   }

   // end()
   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void Dictionary::end() {
       if (this->num_pairs > 0) {
           this->current = this->findMax(this->root);
       }
   }

   // next()
   // If the current iterator is not at the last pair, advances current 
   // to the next pair (as defined by the order operator < on keys). If 
   // the current iterator is at the last pair, makes current undefined.
   // Pre: hasCurrent()
   void Dictionary::next() {
       if (this->hasCurrent()) {
           if (this->current != this->findMax(this->root)) {
               this->current = this->findNext(this->current);
           } else {
               this->current = nil;
           }
       } else {
           throw std::logic_error("Dictionary: next(): current not defined");
       }

   }

   // prev()
   // If the current iterator is not at the first pair, moves current to  
   // the previous pair (as defined by the order operator < on keys). If 
   // the current iterator is at the first pair, makes current undefined.
   // Pre: hasCurrent()
   void Dictionary::prev() {
       if (this->hasCurrent()) {
           if (this->current != this->findMin(this->root)) {
               this->current = this->findPrev(this->current);
           } else {
               this->current = nil;
           }
       } else {
           throw std::logic_error("Dictionary: prev(): current not defined");
       }
   }


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this Dictionary. Consecutive (key, value)
   // pairs are separated by a newline "\n" character, and the items key and value 
   // are separated by the sequence space-colon-space " : ". The pairs are arranged 
   // in order, as defined by the order operator <.
   std::string Dictionary::to_string() const {
       std::string s = "";
       this->inOrderString(s, this->root);
       return s;
   }

   // pre_string()
   // Returns a string consisting of all keys in this Dictionary. Consecutive
   // keys are separated by newline "\n" characters. The key order is given
   // by a pre-order tree walk.
   std::string Dictionary::pre_string() const {
       std::string s = "";
       this->preOrderString(s, this->root);
       return s;
   }

   // equals()
   // Returns true if and only if this Dictionary contains the same (key, value)
   // pairs as Dictionary D.
   bool Dictionary::equals(const Dictionary& D) const {
       if (this->num_pairs != D.num_pairs) {
           return false;
       }
       if (this->root == nil && D.root == nil) {
           return true;
       }
        Dictionary copy;
        copy.preOrderCopy(this->root, nil);
        Dictionary copy2 = D;

        Node* check = copy.findMax(copy.root);
        Node* check2 = copy2.findMax(copy2.root);

        copy.begin();
        copy2.begin();

        while (copy.current->key == copy2.current->key && copy.current->val == copy2.current->val) {
            if (copy.current == check && copy2.current == check2) {
                return true;
            }
            copy.next();
            copy2.next();

        }

        return false;
   }

   // Overloaded Operators ----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of Dictionary D into stream, as defined by
   // member function to_string().
   std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
       return stream << D.Dictionary::to_string();
   }

   // operator==()
   // Returns true if and only if Dictionary A equals Dictionary B, as defined
   // by member function equals(). 
   bool operator==( const Dictionary& A, const Dictionary& B ) {
       return A.Dictionary::equals(B);
   }

   // operator=()
   // Overwrites the state of this Dictionary with state of D, and returns a
   // reference to this Dictionary.
   Dictionary& Dictionary::operator=( const Dictionary& D ) {
       if (this != &D) {
           Dictionary temp = D;

            std::swap(this->nil, temp.nil);
           std::swap(this->current, temp.current);
           std::swap(this->root, temp.root);
           std::swap(this->num_pairs, temp.num_pairs);
           preOrderCopy(this->root, this->nil);
       }
       return *this;
   }



