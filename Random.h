/*
 * Random.h
 *
 *  Created on: Apr 2, 2014
 *      Author: XinTong
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <cstdlib>

int randGen(int min, int max)
{
   // x is in [0,1[
   double x = rand()/static_cast<double>(RAND_MAX);

   // [0,1[ * (max - min) + min is in [min,max[
   int that = min + static_cast<int>( x * (max - min) );

   return that;
}

#endif /* RANDOM_H_ */
