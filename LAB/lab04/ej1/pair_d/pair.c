#include<stdio.h>
#include<stdlib.h>
#include "pair.h"

struct s_pair_t{
	elem fst;
	elem snd;
};

pair_t pair_new(elem x, elem y){
	pair_t p = NULL;
	p = malloc(sizeof(pair_t));
	p->fst = x;
	p->snd = y;
	return p;
}

elem pair_first(pair_t p){
	return p->fst;
}

elem pair_second(pair_t p){
	return p->snd;
}

pair_t pair_swapped(pair_t p){
	pair_t q = pair_new(pair_second(p),pair_first(p));
	return q;
}

pair_t pair_destroy(pair_t p){
	free(p);
	return p;
}
