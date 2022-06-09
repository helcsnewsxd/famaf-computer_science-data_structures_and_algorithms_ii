#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

//----------------------------- FUNCIONES AUXILIARES --------------------------

abb create_node(abb_elem e){
	abb ret=malloc(sizeof(struct _s_abb));
	ret->left=NULL;
	ret->right=NULL;
	ret->elem=e;
	return ret;
}

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
	bool ret = true;

	if(tree!=NULL){
		ret &= tree->left==NULL || elem_less((tree->left)->elem,tree->elem);
		ret &= tree->right==NULL || elem_less(tree->elem,(tree->right)->elem);
		ret &= invrep(tree->left) && invrep(tree->right);
	}

	return ret;
}

abb search_father(abb tree,abb_elem e){
	assert(!abb_is_empty(tree) && !elem_eq(tree->elem,e));
	abb ret=NULL;
	if(tree->left!=NULL && elem_less(e,tree->elem)){
		if(elem_eq((tree->left)->elem,e)){
			ret=tree;
		}else{
			ret=search_father(tree->left,e);
		}
	}else if(tree->right!=NULL && elem_less(tree->elem,e)){
		if(elem_eq((tree->right)->elem,e)){
			ret=tree;
		}else{
			ret=search_father(tree->right,e);
		}
	}
	return ret;
}

//------------------------------------------------------------------------------

abb abb_empty(void) {
    abb tree = NULL;

    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));

	if(tree==NULL){
		tree=create_node(e);
	}else if(elem_less(e,tree->elem)){
		if(tree->left==NULL){
			(tree->left)=create_node(e);
		}else{
			(tree->left)=abb_add(tree->left,e);
		}
	}else if(elem_less(tree->elem,e)){
		if(tree->right==NULL){
			(tree->right)=create_node(e);
		}else{
			(tree->right)=abb_add(tree->right,e);
		}
	}

    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty=false;
    assert(invrep(tree));

	is_empty=(tree==NULL);

    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));

	exists = !( tree==NULL || (tree->elem!=e && search_father(tree,e)==NULL) );

    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));

	if(tree != NULL){
		length = 1 + abb_length(tree->left) + abb_length(tree->right);
	}

    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));

	if(tree!=NULL){
		bool do_destroy_father = false;

		abb father = NULL;
		abb son = NULL;
		if(tree->elem == e){
			father = create_node(e+1); //No me importa que sea ABB
			father->left = tree;
			do_destroy_father = true;
		}else{
			father = search_father(tree,e);
		}

		if(father!=NULL){
			if(do_destroy_father){
				son = tree;
			}else if(elem_less(e,father->elem)){
				son = father->left;
			}else{
				son = father->right;
			}

			if(son->left == NULL && son->right == NULL){
				if(father->left == son){
					father->left = NULL;
				}else{
					father->right = NULL;
				}
				son = abb_destroy(son);
			}
			else if(son->left != NULL){
				son->elem = abb_max(son->left);
				son->left = abb_remove(son->left,son->elem);
			}
			else if(son->right != NULL){
				son->elem = abb_min(son->right);
				son->right = abb_remove(son->right,son->elem);
			}
		}

		if(do_destroy_father){
			father->left = NULL;
			father = abb_destroy(father);
			tree = son;
		}
	}

    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));

	root = tree->elem;

    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));

	if(tree->right==NULL){
		max_e = tree->elem;
	}else{
		max_e = abb_max(tree->right);
	}

    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));

	if(tree->left==NULL){
		min_e = tree->elem;
	}else{
		min_e = abb_min(tree->left);
	}

    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
	//---- Si tengo en el dump los nros X Y, si se cumple que
	//---- Y < X entonces Y es padre de X
	//---- caso contrario, Y es otra hoja
	//---- Al final, me quedan varias componentes sueltas solo con
	//---- left father. Los right father se ponen para que se cumpla el ABB
    assert(invrep(tree));
    if (tree != NULL) {
        abb_dump(tree->left);
        abb_dump(tree->right);
        printf("%d ", tree->elem);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));

	if(tree!=NULL){
		abb_destroy(tree->left);
		abb_destroy(tree->right);
		free(tree);
		tree=NULL;
	}

    assert(tree == NULL);
    return tree;
}

