/*H*
 * 
 * FILENAME: io.h
 * DESCRIPTION: Read propositional formulas in DIMACS format
 * AUTHORS: José Antonio Riaza Valverde
 * DATE: 07.10.2018
 * 
 *H*/

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"



/** Read a formula in DIMACS format */
int dimacs_read_file(char *path, Formula *F);
/** Write a formula for the stardard output */
void write_formula(Formula *F);
/** Write a clause for the stardard output */
void write_clause(ClauseNode *clause_node);
/** Write a literal for the stardard output */
void write_literal(Atom atom, Literal literal);
/** Write a interpretation for the stardard output */
void write_interpretation(Interpretation *I);
