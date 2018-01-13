#include <iostream>
#include <list>

class node {
  public:
    node* left;
    node* right;
    node* parent;
    int key;
    int val;

    void splay();
    int find(int);
    void insert(int,int);

    void print_whole_tree();
    node* get_root();
};

node* node::get_root() {
  node* n = this;
  while (n->parent)
    n = n->parent;
  return n;
}

void node::splay() {
  while (parent) {
    if (parent->left == this) {
      node* b = this->right;
      this->right = parent;
      parent->left = b;
    } else {
      node* b = this->left;
      this->left = parent;
      parent->right = b;
    }
    if (parent->parent) {
      if (parent->parent->left == parent)
        parent->parent->left = this;
      else
        parent->parent->right = this;
    }
    node* p = this->parent;
    this->parent = p->parent;
    p->parent = this;
  }
}

int node::find(int k) {
  if (k == key)
    return val;
  else if (k < key)
    return left->find(k);
  else
    return right->find(k);
}

void node::insert(int k, int v) {
  if (k == key)
    val = v;
  else if (k > key) {
    if (this->right != nullptr) {
      this->right->insert(k,v);
    } else {
      this->right = new node{nullptr,nullptr,this,k,v};
      this->right->splay();
    }
  } else {
    if (this->left != nullptr) {
      this->left->insert(k,v);
    } else {
      this->left = new node{nullptr,nullptr,this,k,v};
      this->left->splay();
    }
  }
}

void node::print_whole_tree() {
  node* curr = this;
  while(curr->parent)
    curr = curr->parent;

  std::string out = "digraph {\n -1 [shape=point] \n";
  
  std::list<node*> stack;
  stack.push_back(curr);
  while ( not stack.empty() ) {
    node* u = stack.back();
    stack.pop_back();
    if (u->left) {
      out += std::to_string(u->key) + " -> " + std::to_string(u->left->key) + "\n";
      stack.push_back(u->left);
    } else {
      out += std::to_string(u->key) + " -> -1"  + "\n";
    }
    if (u->right) {
      out += std::to_string(u->key) + " -> " + std::to_string(u->right->key) + "\n";
      stack.push_back(u->right);
    } else {
      out += std::to_string(u->key) + " -> -1"  + "\n";
    }
  }

  out += "}\n";
  std::cout << out;
}


int main() {

  node* n = new node{0,0,0,5,5};
  n->print_whole_tree();
  n->get_root()->insert(2,2);
  n->print_whole_tree();
  n->get_root()->insert(6,6);
  n->print_whole_tree();
  n->get_root()->insert(3,3);
  n->print_whole_tree();
  n->get_root()->insert(1,1);
  n->print_whole_tree();


  return 0;
}
