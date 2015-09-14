
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */


int bitAnd(int x, int y) {

  /* rVar is the return variable; the bitAnd has been found using De Morgan's law  */

  int rVar ;
  rVar = ~(~x | ~y);
  return rVar;

}
/* 
 * getByte - Extract byte n (8) from word x (16)
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {




/*
Let's discuss this function by using the example given above:
0x12 34 56 78 , which in binary is '000010010   00110100  01010110 01111000'.
As you can see, there are 4 possible bytes (0 to 3) in the above bit string 
and the function requires us to give the required byte (specified by int 'n').
We intuitively know that the shifts are the multiple of 8 (2^3); therefore n (from 0 to 3)
has to be multiplied  by 8 ( 8 * n) if we want to extract a byte. So in the case of the
example, the n is '1', so we should shift 8*(1) bits rightward: what happens is that 
we are left with 000010010   00110100  01010110 (equal to 1193046 in binary & 0x123456 in hex).
But it doesn't suffice because we only want '01010110' (i.e. 0x56) so we need some function 
that would zerofy all other bits: for this we will use the famous 'bit masking' and
AND the entire remaining bit string with 255 (i.e. 11111111). So something like following would
happen:

000010010   00110100  01010110
&&&&&&&&&   &&&&&&&&  &&&&&&&&
000000000   00000000  11111111

and now we have '01010110'. It is what we wanted! 

One thing to note is that in arithmetic left shift, the vacant bits are filled with 0s; whereas, 
in arithmetic right shift, the vacants bits mimic the MSB / signed bit

*/ 

int nShift, bMask, rVar; 

nShift = n << 3; /*this left-shifting is similar to 8 * n; because we cannot use '*' 
                  (multiplication operator) so instead
                  we decided to shift n thirce leftwards: in case of 1 i.e 000.... 0000 0001, 
                  it would become 000.... 0000 1000 (which is eight) */

bMask = 0xFF; /* 0xFF = 255 */

rVar = (x >> nShift) & bMask;
   
return rVar;

}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {

  int rVar;

  int iVar = 1; //intial variable i.e. 1 or 0b0000.......0001 (32 bits)
  iVar= iVar << 31; //iVar = 0b1000...0000 (32 bits); the noteworthy thing here is that in left shift, the vacant bits (n-1) are filled with 0s
  iVar = (iVar >> n) << 1; /*in, contrary when I shift rightwards, the shifted bits before n are filled with the leftmost signed bit (MSB){in this case
                            with '1' ; and then to keep the first
                            digit, we again shifted the string once toward left*/

  x = x >> n; //the Arithemetic shift toward right

  rVar = x & ~iVar;
  return rVar; //zeros now cancel the intial values of n

}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */


int bitCount(int x) {
  int v55, v33, v0f, vff, vff2;

  /*since we cannot use 0x55555555, we can take 0x55 instead and or it with 8 bits leftward shifted 0x55 
  and we will get the 16 bit 0101 0101 ... 0101 , similarly , we will OR again it with 16 bit leftward shifted v55-- same goes 
  for the other pattern. */
  
  v55 = 0x55 | (0x55 << 8); 
  v55 = v55 | (v55 << 16); //32 1010.. 
  v33 = 0x33 | (0x33 << 8);
  v33 = v33 | (v33 << 16);
  v0f = 0x0f | (0x0f << 8);
  v0f = v0f | (v0f << 16);
  vff = 0xff | (0xff << 16);
  vff2 = 0xff | (0xff << 8);

  /*hamming weight divide and conquer*/
  x = (x & v55) + ((x >> 1) & v55); 
  x = (x & v33) + ((x >> 2) & v33);
  x = (x & v0f) + ((x >> 4) & v0f);
  x = (x & vff) + ((x >> 8) & vff);
  x = (x & vff2) + ((x >> 16) & vff2);
  return x;

}

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  /* the leftmost bit of the string 'x' 
  if orred with its compliment is 1 
   except when the 'x' is 0*/
  

  int compVar = (~x + 1) | x;  // x getting orred with its second compliment 

  int rVar = (compVar >> 31) + 1; /*shifting MSB to LSB; since it is an arithmetic rightshift, 
                                the MSB will be replicated by all vacant bits (all 1s); 
                                when 1 would be added to it, it will give a 0, in
                                case of 0 as input, the output will be 1 -- that's what we wanted!  */
  return rVar;

}

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {

  int rVar;
  rVar = 1 << 31;
  return rVar; /*As the Rating suggests,this function is very easy; 
                   the mininum 2nd comp number is 1000...000 (32 bits) 
                   so shift the LSB of 1 to the MSB of the new string */

}

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /* The idea is simple:  "x << (32 - n)) >> (32 - n)" should return x to be in the range of nbit 2nd compliment */
  int rVar, conVar; //conVar is the condition variable 
  conVar = 33 + ~n; //32 - n; we could have done 32 + (1 + ~n) but in that way , we saved an operation
  rVar = (x << conVar) >> conVar; // x << (32 - n)) >> (32 - n) 
  rVar = !(rVar ^ x); /*Therefore, it rVar and x are equal, the parity of them would return 0 (for if x=y, parity is zero) & !0 = 1
                       In all other cases such as !1, !2 (in case of difference between rVar and x) , it is 0  */
  return rVar;

}

/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {

   //(x + 2^n - 1) / 2^n; in the case of positive and zero, (2n - 1) = 0
    
    int rVar, conVar;
    conVar = (1 << n) + ~0; // It is how we represented 2^n - 1 using the given operators
    conVar = conVar & (x >> 31);/* after doing this, we are sure as to whether the conVar 
                                 is positive or zero (x >= 0),  because conVar now will be zero if it is (x >= 0)
                                 else 2^n - 1)*/


    rVar = (x + conVar) >> n; 
    return rVar;
}


/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {


  int rVar;
  rVar = ~x + 1; /*the second compliment*/
  return rVar;

}

/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  
  int rVar;
  rVar = ((x >> 31) & 1) ^ 1;
  rVar = rVar ^  (!x);      /*I guess it could have worked without parity !x (the last step before return) 
                          if zero hadn't been there. 
                                        */
  return rVar;

}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int rVar, yVar, xVar;

  yVar = xVar =  (y >> 31) & 1; //checking the signs of X AND Y 
  rVar = !(yVar ^ xVar) & (((x + ~y) >> 31) & 1);
  rVar = rVar | (!yVar & xVar);

  return rVar;

}








