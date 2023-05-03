/*
 * evaluate.h
 *
 *  Created on: Mar 15, 2016
 *      Author: sushil
 */

#ifndef EVALUATE_H_
#define EVALUATE_H_

#include <individual.h>
#include <cstring>

void evaluate(ga::Individual *ent);
void xSquared(ga::Individual *ent);
void convertToString(int *vec, int size, char *chrom);
#endif /* EVALUATE_H_ */
