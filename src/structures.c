/*H*
 * 
 * FILENAME: structures.h
 * DESCRIPTION: Operations with structures for SAT problem
 * AUTHORS: José Antonio Riaza Valverde
 * UPDATED: 19.10.2018
 * 
 *H*/

#include "structures.h"



/**
  * 
  * This function creates a formula of $nbvar variables and $nbclauses
  * clauses, returning a pointer to a newly initialized Formula struct.
  * 
  **/
Formula *formula_alloc(int nbvar, int nbclauses) {
	int i;
	Formula *F = malloc(sizeof(Formula));
	F->arr_clauses = malloc(nbclauses * sizeof(ClauseNode*));
	F->arr_unitaries = malloc(nbclauses * sizeof(ClauseNode*));
	F->sat_clauses = malloc(nbclauses * sizeof(ClauseNode*));
	F->occurrences = malloc(nbvar * sizeof(ClauseNode*));
	F->interpretation = malloc(nbvar * sizeof(Bool));
    F->lst_clauses = NULL;
    F->lst_unitaries = NULL;
    F->length = nbclauses;
    F->size = nbclauses;
    F->original_size = nbclauses;
    F->alloc_size = nbclauses;
    F->variables = nbvar;
    for(i = 0; i < nbclauses; i++) {
		F->arr_clauses[i] = NULL;
		F->arr_unitaries[i] = NULL;
		F->sat_clauses[i] = 0;
	}
	for(i = 0; i < nbvar; i++) {
		F->occurrences[i] = NULL;
		F->interpretation[i] = UNKNOWN;
	}
    return F;
}

/**
  * 
  * This function creates a clause of $nbvar variables, returning a
  * pointer to a newly initialized Clause struct.
  * 
  **/
Clause *clause_alloc(int nbvar) {
	int i;
	Clause *clause = malloc(sizeof(Clause));
	clause->id = 0;
	clause->arr_literals = malloc(nbvar * sizeof(LiteralNode*));
	clause->lst_literals = NULL;
	clause->length = 0;
	clause->size = 0;
	clause->literals = NULL;
	for(i = 0; i < nbvar; i++)
		clause->arr_literals[i] = NULL;
	return clause;
}

/**
  * 
  * This function creates a trace of $nbvar variables, returning a
  * pointer to a newly initialized Trace struct.
  * 
  **/
Trace *trace_alloc(int nbvar) {
	int i;
	Trace *trace = malloc(sizeof(Trace));
	trace->lst_traces = NULL;
	trace->decisions = malloc(nbvar * sizeof(TraceNode*));
	trace->length = 0;
	for(i = 0; i < nbvar; i++)
		trace->decisions[i] = NULL;
	return trace;
}

/** Initialize a new implication graph */
void init_graph(Graph *G, int size) {
	G->nodes = malloc((size+1)*sizeof(GraphNode));
	G->size = size;
	G->max_level = 0;
	for(; size >= 0; size--)
		G->nodes[size] = NULL;
}

/** Add a new node into a graph */
int add_graph_node(Graph *G, Atom atom, Bool value, int level, Decision decision, Clause *clause) {
	int index = decision == CONFLICTIVE ? G->size : atom;
	int i, degree = clause == NULL || decision == ARBITRARY ? 0 : clause->size;
	if(G->nodes[index] != NULL)
		return 0;
	GraphNode *node = malloc(sizeof(GraphNode));
	G->nodes[index] = node;
	node->atom = atom;
	node->value = value;
	node->decision = decision;
	node->degree = degree;
	node->level = level;
	node->antecedents = clause;
	return 1;
}
