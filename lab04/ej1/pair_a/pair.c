#include "pair.h"

pair_t pair_new(int x, int y){
	pair_t nuevo = {x,y};
	return nuevo;
}

int pair_first(pair_t p){
	return p.fst;
}

int pair_second(pair_t p){
	return p.snd;
}

pair_t pair_swapped(pair_t p){
	pair_t q = {p.snd,p.fst};
	return q;
}

pair_t pair_destroy(pair_t p){
	return p;
}
