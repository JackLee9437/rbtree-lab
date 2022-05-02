#include "rbtree.h"

#include <stdlib.h>

node_t _NIL = {
    .color = RBTREE_BLACK,
    .key = 0,
    .left = NULL,
    .right = NULL,
    .parent = NULL};
node_t *NIL = &_NIL;

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  p->nil = NIL;
  p->root = p->nil;
  // TODO: initialize struct if needed
  return p;
}
void delete_node(rbtree *t, node_t *p);
void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  delete_node(t, t->root);
  free(t);
}

void delete_node(rbtree *t, node_t *p)
{
  if (p != t->nil)
  {
    delete_node(t, p->left);
    delete_node(t, p->right);
    free(p);
  }
}


void rotate_left(node_t *p);
void rotate_right(node_t *p);
void change_color(node_t *p);

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // TODO: implement insert
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p)
{
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  return 0;
}
