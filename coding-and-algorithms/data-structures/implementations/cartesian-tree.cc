#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <istream>
#include <sstream>
#include <list>

//  5   1   2   3   8   0
std::string tst = "5 1 2 3 8 0";

struct node {
  node* left;
  node* right;
  node* parent;
  int value;
};


int main() {
  std::istringstream itst(tst);

  node* last;
  node* root;

  while ( not itst.eof() ) {
    int a;
    itst >> a;

    if (not last) {
      last = new node{0,0,0,a};
      root = last;
    } else {
      node* up = last;
      node* curr = new node{0,0,up,a};
      if (up->value > curr->value)
        last = up;
      while (up->value > curr->value) {
        if (up->parent) {
          curr->parent = up->parent;
          if (up->parent->left == up)
            up->parent->left = curr;
          else
            up->parent->right = curr;
          curr->right = up;
        } else {
          curr->right = up;
        }
      }
    }
  }

  std::list<node*> stack = { root };
  while ( ! stack.empty() ) {
    node* u = *stack.end();
    stack.pop_back();

    if (u->left) {
      stack.push_back(u);
    }
    std::cout << 

  }
}
