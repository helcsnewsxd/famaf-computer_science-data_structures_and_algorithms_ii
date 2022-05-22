#include<stdlib.h>
#include <assert.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

//---------------- FUNCIONES AUXILIARES -------------------

bool asserting(bool b){ // Está para no tener que descomentar los assert uno por uno si los quiero usar
	bool ret = b;
	ret = true; // Comentar para que funcionen los assert
	return ret;
}

static bool invrep(dict_t dict) {
	bool ret = true;
	if(dict != NULL){
		ret &= dict->left == NULL || key_less((dict->left)->key, dict->key);
		ret &= dict->right == NULL || key_less(dict->key, (dict->right)->key);
		ret &= invrep(dict->left) && invrep(dict->right);
	}
    return ret;
}

dict_t search_father(dict_t dict, key_t key){
	assert(asserting( invrep(dict) ));
	dict_t father = NULL;

	if(dict != NULL){
		if(key_less(key, dict->key)){
			if(dict->left != NULL && key_eq((dict->left)->key, key)){
				father = dict;
			}else{
				father = search_father(dict->left, key);
			}
		}else if(key_less(dict->key, key)){
			if(dict->right != NULL  && key_eq((dict->right)->key, key)){
				father = dict;
			}else{
				father = search_father(dict->right, key);
			}
		}
	}
	assert(asserting( invrep(dict) ));
	return father;
}

dict_t create_node(key_t key, value_t value){
	dict_t new_node = malloc(sizeof(struct _node_t));
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->key = key;
	new_node->value = value;
	return new_node;
}

dict_t dict_max_key(dict_t dict){
	assert(asserting( invrep(dict) ));
	dict_t maxi = dict;

	if(dict->right != NULL){
		maxi = dict_max_key(dict->right);
	}

	assert(asserting( invrep(dict) ));
	return maxi;
}

dict_t dict_min_key(dict_t dict){
	assert(asserting( invrep(dict) ));
	dict_t mini = dict;

	if(dict->left != NULL){
		mini = dict_min_key(dict->left);
	}

	assert(asserting( invrep(dict) ));
	return mini;
}

void debug(dict_t dict){
	printf("===============================================\n");
	if(dict == NULL){
		printf("Nodo vacío\n");
	}else{
		printf("Key: "); key_dump(dict->key,stdout); printf("\n");
		printf("Value: "); value_dump(dict->value,stdout); printf("\n");
		if(dict->left == NULL){
			printf("Hijo izquierdo es NULL\n");
		}else{
			printf("Tengo hijo izquierdo\n");
		}
		if(dict->right == NULL){
			printf("Hijo derecho es NULL\n");
		}else{
			printf("Tengo hijo derecho\n");
		}
	}
	printf("===============================================\n");
}

//---------------------------------------------------------

dict_t dict_empty(void) {
	dict_t dict = NULL;

	assert(asserting( invrep(dict) && dict_length(dict) == 0));
	return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
	assert(asserting( invrep(dict) ));

	if(dict == NULL){
		dict = create_node(word,def);
	}else{
		if(key_eq(dict->key, word)){
			dict->value = def;
		}else if(key_less(word, dict->key)){
			if(dict->left == NULL){
				dict->left = create_node(word,def);
			}else{
				dict->left = dict_add(dict->left, word, def);
			}
		}else{
			if(dict->right == NULL){
				dict->right = create_node(word,def);
			}else{
				dict->right = dict_add(dict->right, word, def);
			}
		}
	}

	assert(asserting( invrep(dict) && key_eq(def, dict_search(dict,word)) ));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
	assert(asserting( invrep(dict) ));

    key_t def=NULL;

	if(dict != NULL){
		if(key_eq(dict->key, word)){
			def = dict->value;
		}else{
			dict_t father = search_father(dict,word);
			if(father != NULL){
				if(key_less(word, father->key)){
					def = (father->left)->value;
				}else{
					def = (father->right)->value;
				}
			}
		}
	}

	assert(asserting( (def != NULL) == dict_exists(dict,word) ));
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
	assert(asserting( invrep(dict) ));
	return !(dict==NULL || (!key_eq(dict->key, word) && search_father(dict,word) == NULL));
}

unsigned int dict_length(dict_t dict) {
	assert(asserting( invrep(dict) ));
	return (dict==NULL ? 0 : 1 + dict_length(dict->left) + dict_length(dict->right));
}

dict_t dict_remove(dict_t dict, key_t word) {
	assert(asserting( invrep(dict) ));

	if(dict != NULL){
		dict_t father = NULL, son = NULL;
		bool have_to_erase_father = false;
		if(key_eq(dict->key, word)){
			father = create_node(word,word);
			father->right = dict;
			have_to_erase_father = true;
		}else{
			father = search_father(dict,word);
		}

		if(father != NULL){
			if(key_less(word, father->key)){
				son = father->left;
			}else{
				son = father->right;
			}

			if(son->left == NULL && son->right == NULL){
				if(son == father->left){
					father->left = NULL;
				}else{
					father->right = NULL;
				}
				son = dict_destroy(son);
			}else if(son->left != NULL){
				dict_t new_data = dict_max_key(son->left);
				son->key = new_data->key;
				son->value = new_data->value;
				son->left = dict_remove(son->left, son->key);
			}else{
				dict_t new_data = dict_min_key(son->right);
				son->key = new_data->key;
				son->value = new_data->value;
				son->right = dict_remove(son->right, son->key);
			}
		}

		if(have_to_erase_father){
			father->right = NULL;
			father = dict_destroy(father);
			dict = son;
		}
	}

	assert(asserting( invrep(dict) && !dict_exists(dict,word) ));
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
	assert(asserting( invrep(dict) ));

	dict = dict_destroy(dict);

	assert(asserting( invrep(dict) && dict_length(dict) == 0 ));
	return dict;
}

void dict_dump(dict_t dict, FILE *file) {
	assert(asserting( invrep(dict) && file != NULL ));

	if(dict != NULL){
		dict_dump(dict->left,file);

		key_dump(dict->key, file); printf(": "); value_dump(dict->value, file); printf("\n");

		dict_dump(dict->right,file);
	}
}

dict_t dict_destroy(dict_t dict) {
	assert(asserting( invrep(dict) ));

	if(dict != NULL){
		dict->left = dict_destroy(dict->left);
		dict->right = dict_destroy(dict->right);
		free(dict);
		dict = NULL;
	}

	assert(asserting( dict == NULL ));
    return dict;
}

