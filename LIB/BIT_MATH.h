/*
 * MATH.h
 *
 *  Created on: Mar 25, 2022
 *      Author: abdel
 */

#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_

#define BIT_MASK 1

#define CLR_BIT(Reg,BitNum) 		Reg &= ~(BIT_MASK<<BitNum)
#define SET_BIT(Reg,BitNum) 		Reg |= 	(BIT_MASK<<BitNum)
#define GET_BIT(Reg,BitNum)			((Reg>>BitNum) & BIT_MASK)

#define TOGGLE_BIT(Reg,BitNum)		Reg ^= (BIT_MASK<<BitNum)
#endif /* LIB_BIT_MATH_H_ */
