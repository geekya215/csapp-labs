/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /*
   * De Morgan's laws
   * ~(x|y) = ~x & ~y
   * ~(x&y) = ~x | ~y
   *
   * x^y -> (x&~y) | (~x&y)
   *     -> ~(~(x&~y) & ~(~x&y))
   */
  return ~(~(x&~y) & ~(~x&y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /*
   * minimum two's complement integer (n bits) equal:
   *         -(2^(n-1)) = 1 << (n-1)
   *
   * minimum 32 bits integer:
   * \ 1 bit /
   *     |
   *     1000000...000000
   *       \  31 bits  /
   */
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /*
   * maximum 32 bits integer:
   * \ 1 bit /                               \ 1 bit /
   *     |                        x+x+1          |
   *     0111111...111111      ==========>       1111111...111111
   *       \  31 bits  /        x<<1 + 1           \  31 bits  /
   *
   * -1(exclude):
   *                                         (overflow)
   * \ 1 bit /                               \ 1 bit /
   *     |                        x+x+1          |
   *     1111111...111111      ==========>      (1)111111...111111
   *       \  31 bits  /        x<<1 + 1            \  32 bits  /
   */
  return !(~(x+x+1) | !(~x));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /*
   * 0xAA = 10101010 (maximum allowed all odd-numbered bits integer constant)
   * mask = 0xAAAAAAAA = 1010...1010
   *                     \ 32 bits /
   *
   * [mask&x]: reserve all odd-numbered bits in x
   * x==y -> !(x^y)
   */
  int mask = ((0xAA<<8 | 0xAA) << 16) | (0xAA<<8 | 0xAA);
  return !((mask&x) ^ mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /*
   * postive number:
   * \ 1 bit /                          \ 1 bit /
   *     |                      ~x          |
   *     0000000...000001    =======>       1111111...111110
   *       \  31 bits  /                      \  31 bits  /
   *
   * ~x = -2^31 + 2^31 - 1 - x
   *    = -1 - x
   *
   * 0:
   * ~x = 0xFFFFFFFF = -1 = -1 - x
   *
   * negative number:
   * \ 1 bit /                          \ 1 bit /
   *     |                      ~x          |
   *     1000000...000001    =======>       0111111...111110
   *       \   p part  /                      \  31 bits  /
   * x = -2^31 + p
   * ~x = 2^31 - 1 - p
   *    = 2^31 - 1 - x + (-2^31)
   *    = -1 - x
   */
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /*
   * low bound:  0x30(hex) = 110000(bin)
   * high bound: 0x39(hex) = 111001(bin)
   *
   * cond1: two lead bits should equal 11(0x3)
   * cond2: rest four bits(R) between 0x0 ~ 0x9, so R - 0xA < 0
   */
  int cond1 = !(x>>4 ^ 0x3);
  int cond2 = ((x&0xF) + (~0xA)+1) >> 31;
  return cond1 & cond2;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*
   * use !!x to set all non-zero numbers to 1
   *
   * non-zero: mask = 1 << 31 >> 31 = 1111...1111 (32 bits)
   * zero:     mask = 0 << 31 >> 31 = 0000...0000 (32 bits)
   *
   * x & 1111...1111 = x
   * x & 0000...0000 = 0
   */
  int mask = !!x << 31 >> 31;
  return (mask&y) | (~mask&z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /*
   * x > 0, y > 0 or x < 0, y < 0:
   * in this case y - x never be overflowed
   * x <= y -> y - x > 0
   *
   * x = 0, y = 0:
   * x - y == 0
   *
   * otherwise:
   * when x < 0, y > 0 will be return 1
   */
  int x_sign = x>>31 & 1;
  int y_sign = y>>31 & 1;
  int cond1 = x_sign & !y_sign;
  // cond2 = !(x_sign ^ y_sign) & !((~x+1+y) >> 31)
  // De Morgan laws
  int cond2 = !((x_sign ^ y_sign) | ((~x+1+y) >> 31));
  return cond1 | cond2;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  /*
   * for all non-zero signed numbers, at least one of the sign
   * bit of x and -x is 1
   *
   * non-zero:
   * \ sign bit /                        \ sign bit /
   *      |                    >> 31          |
   *      1bbbbbb...bbbbbb    =======>        1111111...111111
   *        \  31 bits  /                       \  31 bits  /
   *
   * \ sign bit /                        \ overflow /
   *      |                      +1          |
   *      1111111...111111    =======>       10000000...000000
   *        \  31 bits  /                      \   32 bits  /
   *
   * zero:
   * \ sign bit /                        \ sign bit /
   *      |                    >> 31          |
   *      0000000...000000    =======>        0000000...000000
   *        \  31 bits  /                       \  31 bits  /
   *
   * \ sign bit /                        \ sign bit /
   *      |                      +1           |
   *      0000000...000000    =======>        0000000...000001
   *        \  31 bits  /                       \  31 bits  /
   */
  return (((~x+1)|x) >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  /*
   * if x is negative, reverse all bit, and simulate
   * binary serach recursive function
   */
  int mask = x >> 31;
  x = (mask&~x) | (~mask&x);
  // if the left half bits is not equal to 0, the right half is
  // reversed, and then continue searching the left half, and vice versa
  int b16 = !!(x>>16) << 4;
  x >>= b16;
  int b8  = !!(x>>8) << 3;
  x >>= b8;
  int b4  = !!(x>>4) << 2;
  x >>= b4;
  int b2  = !!(x>>2) << 1;
  x >>= b2;
  int b1  = !!(x>>1);
  x >>= b1;
  int b0 = x;
  return b16 + b8 + b4 + b2 + b1 + b0 + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  return 2;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  return 2;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
