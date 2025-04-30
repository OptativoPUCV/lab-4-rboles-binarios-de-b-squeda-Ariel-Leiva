#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    TreeMap *nuevo = (TreeMap *) malloc(sizeof(TreeMap));
    if(nuevo == NULL) return NULL;
    nuevo->root = NULL;
    nuevo->current = NULL;
    nuevo->lower_than = lower_than;
    return nuevo;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode *nuevo = createTreeNode(key, value);
    if(!nuevo) return;
    if(!tree->root){
        tree->root = nuevo;
        tree->current = nuevo;
        return;
    }

    TreeNode *actual = tree->root, *padre = NULL;
    while(actual){
        padre = actual;
        if(is_equal(tree,key,actual->pair->key)){
            actual->pair->value = value;
            tree->current = actual;
            free(nuevo->pair);
            free(nuevo);
            return;
        }
        actual = tree->lower_than(key, actual->pair->key) ? actual->left : actual->right;
    }
    
    nuevo->parent = padre;
    if(tree->lower_than(key, padre->pair->key))padre->left = nuevo;
    else padre->right = nuevo;
    tree->current = nuevo;    

}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode *aux = tree->root;
    while(aux != NULL){
        if( is_equal(tree, key, aux->pair->key)){
            tree->current = aux;
            return aux->pair;
        }
        else if(tree->lower_than(key,aux->pair->key)) aux = aux->left;

        else aux = aux->right;
    }
    tree->current = NULL;
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
