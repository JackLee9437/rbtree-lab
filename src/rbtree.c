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


node_t *new_node(rbtree *t, const key_t key);
void rotate_left(rbtree *t, node_t *p);
void rotate_right(rbtree *t, node_t *p);
void rb_insert_fixup(rbtree *t, node_t *n);
node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // TODO: implement insert
  node_t *new = new_node(t, key);
  node_t *cur = t->root;
  node_t *p = t->nil;
  while (cur != t->nil)
  {
    p = cur;
    if (key < cur->key)
      cur = cur->left;
    else
      cur = cur->right;
  }
  new->parent = p;
  if (p == t->nil)
    t->root = new;
  else if (key < p->key)
    p->left = new;
  else
    p->right = new;

  rb_insert_fixup(t, new);
  return new;
}

node_t *new_node(rbtree *t, const key_t key)
{
  node_t *node = (node_t *)calloc(1, sizeof(node_t));
  node->color = RBTREE_RED;
  node->key = key;
  node->left = t->nil;
  node->right = t->nil;
  node->parent = t->nil;
  return node;
}
void rotate_left(rbtree *t, node_t *p)
{
  node_t *rc = p->right;
  p->right = rc->left;

  if (rc->left != t->nil)
    rc->left->parent = p;

  rc->parent = p->parent;
  if (p->parent == t->nil)
    t->root = rc;
  else if (p == p->parent->left)
    p->parent->left = rc;
  else
    p->parent->right = rc;
  rc->left = p;
  p->parent = rc;
}
void rotate_right(rbtree *t, node_t *p)
{
  node_t *lc = p->left;
  p->left = lc->right;

  if (lc->right != t->nil)
    lc->right->parent = p;

  lc->parent = p->parent;
  if (p->parent == t->nil)
    t->root = lc;
  else if (p == p->parent->right)
    p->parent->right = lc;
  else
    p->parent->left = lc;
  lc->right = p;
  p->parent = lc;
}
void rb_insert_fixup(rbtree *t, node_t *n)
{
  while (n->parent != t->nil && n->parent->color == RBTREE_RED)
  {
    if (n->parent == n->parent->parent->left)
    {
      node_t *u = n->parent->parent->right;
      if (u->color == RBTREE_RED)
      {
        n->parent->parent->color = RBTREE_RED;
        n->parent->color = u->color = RBTREE_BLACK;
        n = n->parent->parent;
      }
      else
      {
        if (n == n->parent->right)
        {
          n = n->parent;
          rotate_left(t, n);
        }
        n->parent->parent->color = RBTREE_RED;
        n->parent->color = RBTREE_BLACK;
        rotate_right(t, n->parent->parent);
      }
    }
    else
    {
      node_t *u = n->parent->parent->left;
      if (u->color == RBTREE_RED)
      {
        n->parent->color = u->color = RBTREE_BLACK;
        n->parent->parent->color = RBTREE_RED;
        n = n->parent->parent;
      }
      else
      {
        if (n == n->parent->left)
        {
          n = n->parent;
          rotate_right(t, n);
        }
        n->parent->parent->color = RBTREE_RED;
        n->parent->color = RBTREE_BLACK;
        rotate_left(t, n->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  node_t *cur = t->root;
  while (cur != t->nil && cur->key != key)
  {
    if (key < cur->key)
      cur = cur->left;
    else
      cur = cur->right;
  }
  if (cur == t->nil)
    return NULL;
  return cur;
}

node_t *rbtree_min(const rbtree *t)
{
  // TODO: implement find
  node_t *cur = t->root;
  while (cur != t->nil && cur->left != t->nil)
    cur = cur->left;
  return cur;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  node_t *cur = t->root;
  while (cur != t->nil && cur->right != t->nil)
    cur = cur->right;
  return cur;
}

int rbtree_erase(rbtree *t, node_t *p)
{
  // TODO: implement erase
  return 0;
}


int inorder_rbtree(const rbtree *t, const node_t *p, key_t *arr, const size_t n, int *i);
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  int i = 0;
  inorder_rbtree(t, t->root, arr, n, &i);
  return 0;
}

int inorder_rbtree(const rbtree *t, const node_t *p, key_t *arr, const size_t n, int *i)
{
  if (p != t->nil)
  {
    inorder_rbtree(t, p->left, arr, n, i);
    arr[(*i)++] = p->key;
    if (*i == n)
      return 0;
    inorder_rbtree(t, p->right, arr, n, i);
  }
  return 0;
}
