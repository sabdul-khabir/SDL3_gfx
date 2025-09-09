/*

SDL3_imageFilter.c: byte-image "filter" routines

Copyright (C) 2012-2014  Andreas Schiffler
Copyright (C) 2013  Sylvain Beucler

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.

Andreas Schiffler -- aschiffler at ferzkopp dot net

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "SDL3_imageFilter.h"

/* ------ Custom defines ----- */

/*!
\brief Swaps the byte order in a 32bit integer (LSB becomes MSB, etc.). 
*/
#define SWAP_32(x) (((x) >> 24) | (((x) & 0x00ff0000) >> 8)  | (((x) & 0x0000ff00) << 8)  | ((x) << 24))

#define MAX_BYTES_PER_PIXEL 16
/* ------------------------------------------------------------------------------------ */

/*!
\brief Filter using Add: D = saturation255(S1 + S2) 

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterAdd(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;
	
		/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	cursrc2 = Src2;
	curdst = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		result = (int) *cursrc1 + (int) *cursrc2;
		if (result > 255)
			result = 255;
		*curdst = (unsigned char) result;
		/* Advance pointers */
		cursrc1++;
		cursrc2++;
		curdst++;
	}

	return true;
}

/*!
\brief Filter using Mean: D = S1/2 + S2/2

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterMean(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;
	float tmp, fSrc1, fSrc2;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	cursrc2 = Src2;
	curdst = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		fSrc1 = cursrc1[i] / 255.0f;
		fSrc2 = cursrc2[i] / 255.0f;
		tmp = fSrc1 / 2 + fSrc2 / 2;
		curdst[i] = (unsigned char) (tmp * 255) ;
	}

	return true;
}

/*!
\brief Filter using Sub: D = saturation0(S1 - S2)

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterSub(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	cursrc2 = Src2;
	curdst = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		result = (int) cursrc1[i] - (int) cursrc2[i];
		if (result < 0)
			result = 0;
		curdst[i] = (unsigned char) result;
	}
	return true;
}

/*!
\brief Filter using AbsDiff: D = | S1 - S2 |

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterAbsDiff(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	cursrc2 = Src2;
	curdst = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		result = abs((int) *cursrc1 - (int) *cursrc2);
		*curdst = (unsigned char) result;
		/* Advance pointers */
		cursrc1++;
		cursrc2++;
		curdst++;
	}

	return true;
}

/*!
\brief Filter using Mult: D = saturation255(S1 * S2)

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterMult(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;
	float tmp, fSrc1, fSrc2;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	cursrc2 = Src2;
	curdst = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		fSrc1 = cursrc1[i] / 255.0f;
		fSrc2 = cursrc1[i] / 255.0f;
		tmp = fSrc1 * fSrc2;
		curdst[i] = (unsigned char) (tmp * 255);
	}

	return true;
}

/*!
\brief Filter using MultUnbound: D = S1 * S2 - No saturation

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterMultUnbound(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart, tmp;
	unsigned char *cursrc1, *cursrc2, *curdst;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	cursrc2 = Src2;
	curdst = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		tmp = (unsigned int) cursrc1[i] * (unsigned int) cursrc2[i];
		curdst[i] = (unsigned char) tmp;
	}

	return true;
}

/*!
\brief Filter using MultInv: D = 255 - ((255 - S1) * (255 - S2))

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterMultInv(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;
	float tmp, fSrc1, fSrc2;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	cursrc2 = Src2;
	curdst = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		fSrc1 = cursrc1[i] / 255.0f;
		fSrc2 = cursrc2[i] / 255.0f;
		tmp = 1.0f - ((1.0f - fSrc1) * (1.0f - fSrc2));
		curdst[i] = (unsigned char) (tmp * 255);
	}

	return true;
}

/*!
\brief Filter using MultDivby2: D = saturation255(S1/2 * S2)

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterMultDivby2(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;
	int result;
	float tmp, fSrc1, fSrc2;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	cursrc2 = Src2;
	curdst = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		fSrc1 = cursrc1[i] / 255.0f;
		fSrc2 = cursrc2[i] / 255.0f;
		tmp = (fSrc1 * fSrc2) / 2.0f;
		if (tmp > 1.0f)
			tmp = 1.0f;
		curdst[i] = (unsigned char) (tmp * 255);
	}

	return true;
}

/*!
\brief Filter using MultDivby4: D = saturation255(S1/2 * S2/2)

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterMultDivby4(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;
	int result;
	float tmp, fSrc1, fSrc2;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	cursrc2 = Src2;
	curdst = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		fSrc1 = cursrc1[i] / 255.0f;
		fSrc2 = cursrc2[i] / 255.0f;
		tmp = (fSrc1 * fSrc2) / 4.0f;
		if (tmp > 1.0f)
			tmp = 1.0f;
		curdst[i] = (unsigned char) (tmp * 255);
	}

	return true;
}

/*!
\brief Filter using BitAnd: D = S1 & S2

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterBitAnd(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	cursrc2 = Src2;
	curdst = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		*curdst = (*cursrc1) & (*cursrc2);
		/* Advance pointers */
		cursrc1++;
		cursrc2++;
		curdst++;
	}

	return true;
}

/*!
\brief Filter using BitOr: D = S1 | S2

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterBitOr(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	cursrc2 = Src2;
	curdst = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		*curdst = *cursrc1 | *cursrc2;
		/* Advance pointers */
		cursrc1++;
		cursrc2++;
		curdst++;
	}

	return true;
}

/*!
\brief Filter using Div: D = S1 / S2

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterDiv(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;
	float tmp, fSrc1, fSrc2;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;
	
	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	cursrc2 = Src2;
	curdst = Dest;

	for (i = istart; i < length; i++) {
		if (cursrc2[i] == 0) {
			curdst[i] = 0;
		} else {
			fSrc1 = cursrc1[i] / 255.0f;
			fSrc2 = cursrc2[i] / 255.0f;
			tmp = cursrc1[i] / cursrc2[i];
			if (tmp > 1.0f)
				tmp = 1.0f;
			curdst[i] = (unsigned char) (tmp * 255);
		}
	}

	return true;
}

/* ------------------------------------------------------------------------------------ */

/*!
\brief Filter using BitNegation: D = !S

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterBitNegation(unsigned char *Src1, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *curdst;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	curdst = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		*curdst = ~(*cursrc1);
		/* Advance pointers */
		cursrc1++;
		curdst++;
	}

	return true;
}

/*!
\brief Filter using AddByte: D = saturation255(S + C) 

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param C Constant value to add (C).

\return Returns true for success or false for error.
*/
bool SDL_imageFilterAddByte(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char C)
{
	unsigned int i, istart;
	int iC;
	unsigned char *cursrc1, *curdest;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Special case: C==0 */
	if (C == 0) {
		memcpy(Src1, Dest, length);
		return true;
	}

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	curdest = Dest;

	/* C routine to process image */
	iC = (int) C;
	for (i = istart; i < length; i++) {
		result = (int) *cursrc1 + iC;
		if (result > 255)
			result = 255;
		*curdest = (unsigned char) result;
		/* Advance pointers */
		cursrc1++;
		curdest++;
	}
	return true;
}

/*!
\brief Filter using AddUint: D = saturation255((S[i] + Cs[i % BPP])

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param bpp The bytes per unit length (BPP)
\param C Constant to add (C).

\return Returns true for success or false for error.
*/
bool SDL_imageFilterAddUint(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned int bpp, unsigned int C)
{
	unsigned int i, j, istart;
	int iC[MAX_BYTES_PER_PIXEL], k;
	unsigned char *cursrc1;
	unsigned char *curdest;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Special case: C==0 */
	if (C == 0) {
		memcpy(Src1, Dest, length);
		return true;
	}

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	curdest = Dest;

	/* Routine to process uint */
	for (k = bpp; k >= 0; k--) {
		iC[k] = (int) ((C >> (8*(bpp - k))) & 0xff);
	}

	/* Routine to process bytes */
	for (i = istart; i < length; i += bpp) {
		for (j = 0; j < bpp; j++) {
			if ((i+j) < length) {
				result = cursrc1[i+j] + iC[j];
				if (result > 255){
					result = 255;
				}
				curdest[i+j] = (unsigned char) result;
			}
		}
	}
	return true;
}

/*!
\brief Filter using AddByteToHalf: D = saturation255(S/2 + C)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param C Constant to add (C).

\return Returns true for success or false for error.
*/
bool SDL_imageFilterAddByteToHalf(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char C)
{
	unsigned int i, istart;
	int iC;
	unsigned char *cursrc1;
	unsigned char *curdest;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	curdest = Dest;

	/* Routine to process image */
	iC = (int) C;
	for (i = istart; i < length; i++) {
		result = (int) (*cursrc1 / 2) + iC;
		if (result > 255)
			result = 255;
		*curdest = (unsigned char) result;
		/* Advance pointers */
		cursrc1++;
		curdest++;
	}

	return true;
}

/*!
\brief Filter using SubByte: D = saturation0(S - C)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.
\param C Constant to subtract (C).

\return Returns true for success or false for error.
*/
bool SDL_imageFilterSubByte(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char C)
{
	unsigned int i, istart;
	int iC;
	unsigned char *cursrc1;
	unsigned char *curdest;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Special case: C==0 */
	if (C == 0) {
		memcpy(Src1, Dest, length);
		return true;
	}

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	curdest = Dest;

	/* Routine to process image */
	iC = (int) C;
	for (i = istart; i < length; i++) {
		result = (int) *cursrc1 - iC;
		if (result < 0)
			result = 0;
		*curdest = (unsigned char) result;
		/* Advance pointers */
		cursrc1++;
		curdest++;
	}
	return true;
}

/*!
\brief Filter using SubUint: D = saturation0(S[i] - Cs[i % BPP])

\param Src1 Pointer to the start of the source byte array (S1).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param bpp The bytes per unit length (BPP)
\param C Constant to subtract (C).

\return Returns true for success or false for error.
*/
bool SDL_imageFilterSubUint(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned int bpp, unsigned int C)
{
	unsigned int i, j, istart;
	int iC[MAX_BYTES_PER_PIXEL], k;
	unsigned char *cursrc1;
	unsigned char *curdest;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

    /* Special case: C==0 */
	if (C == 0) {
		memcpy(Src1, Dest, length);
		return true;
	}

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	curdest = Dest;

	/* Routine to process uint */
	for (k = bpp; k >= 0; k--) {
		iC[k] = (int) ((C >> (8*(bpp - k))) & 0xff);
	}

	/* Routine to process bytes */
	for (i = istart; i < length; i += bpp) {
		for (j = 0; j < bpp; j++) {
			if ((i+j) < length) {
				result = cursrc1[i+j] - iC[j];
				if (result < 0){
					result = 0;
				}
				curdest[i+j] = (unsigned char) result;
			}
		}
	}
	
	return true;
}

/*!
\brief Filter using ShiftRightUint: D = saturation0((uint)S[i] >> N)

\param Src1 Pointer to the start of the source byte array (S1).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param N Number of bit-positions to shift (N). Valid range is 0 to 8.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterShiftRightUint(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned int bpp, unsigned char N)
{
	unsigned int i,istart;
	unsigned char *cursrc1, *curdest;
	unsigned int *icursrc1, *icurdest;
	int j, result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Check shift */
	if (N > 8) {
		return false;
	}

	/* Special case: N==0 */
	if (N == 0) {
		memcpy(Src1, Dest, length);
		return (0); 
	}

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	curdest = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i += bpp) {
		if ((i + bpp) < length) {
			result = 0;
			for (j = bpp; j >= 0; j--) {
				result |= (unsigned int) ((cursrc1[i + j] << (sizeof(unsigned int) * j)));
			}
			/* Do the actual uint shift */
			result = result >> N;
			/* Pass the shifted value to each byte */
			for (j = 0; j < bpp; j++) {
				curdest[i + j] = (result >> bpp) & 0xFF;
			}
		}
	}

	return true;
}

/*!
\brief Filter using MultByByte: D = saturation255(S * C)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.
\param C Constant to multiply with (C).

\return Returns true for success or false for error.
*/
bool SDL_imageFilterMultByByte(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char C)
{
	unsigned int i, istart;
	unsigned char *cursrc1;
	unsigned char *curdest;
	int result;
	float tmp, fSrc1, fC;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Special case: C==1 */
	if (C == 1) {
		memcpy(Src1, Dest, length);
		return true;
	}

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	curdest = Dest;

	/* Routine to process image */
	fC = C / 255.0f;
	for (i = istart; i < length; i++) {
		fSrc1 = cursrc1[i] / 255.0f;
		tmp = fSrc1 * fC;
		if (tmp > 1.0f)
			tmp = 1.0f;
		curdest[i] = (unsigned char) (tmp * 255);
	}

	return true;
}

/*!
\brief Filter using ShiftRightAndMultByByte: D = saturation255((S >> N) * C) 

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param N Number of bit-positions to shift (N). Valid range is 0 to 8.
\param C Constant to multiply with (C).

\return Returns true for success or false for error.
*/
bool SDL_imageFilterShiftRightAndMultByByte(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char N,
										   unsigned char C)
{
	unsigned int i, istart;
	unsigned char *cursrc1;
	unsigned char *curdest;
	int result;
	float tmp, fSrc1, fC;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Check shift */
	if (N > 8) {
		return false;
	}

	/* Special case: N==0 && C==1 */
	if ((N == 0) && (C == 1)) {
		memcpy(Src1, Dest, length);
		return true;
	}

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	curdest = Dest;
	
	/* Routine to process image */
	fC = C / 255.0f;
	for (i = istart; i < length; i++) {
		fSrc1 = (cursrc1[i] >> N) / 255.0f;
		tmp = fSrc1 * fC;
		if (tmp > 1.0f)
			tmp = 1.0f;
		curdest[i] = (unsigned char) (tmp * 255);
	}

	return true;
}

/*!
\brief Filter using ShiftRight: D = saturation0(S >> N)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.
\param N Number of bit-positions to shift (N). Valid range is 0 to 8.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterShiftRight(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char N)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *curdest;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Check shift */
	if (N > 8) {
		return false;
	}

	/* Special case: N==0 */
	if (N == 0) {
		memcpy(Src1, Dest, length);
		return (0); 
	}

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	curdest = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		result = ((int) cursrc1[i]) >> N;
		if (result < 0) {
			result = 0;
		}
		curdest[i] = (unsigned char) result;
	}

	return true;
}

/*!
\brief Filter using ShiftLeftByte: D = (S << N)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.
\param N Number of bit-positions to shift (N). Valid range is 0 to 8.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterShiftLeftByte(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char N)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *curdest;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	if (N > 8) {
		return (-1);
	}

	/* Special case: N==0 */
	if (N == 0) {
		memcpy(Src1, Dest, length);
		return true;
	}

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	curdest = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		result = ((int) *cursrc1 << N) & 0xff;
		*curdest = (unsigned char) result;
		/* Advance pointers */
		cursrc1++;
		curdest++;
	}

	return true;
}

/*!
\brief Filter using ShiftLeftUint: D = ((uint)S << N)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param N Number of bit-positions to shift (N). Valid range is 0 to 32.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterShiftLeftUint(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned int bpp, unsigned char N)
{
	unsigned int i, istart;
	int j;
	unsigned char *cursrc1, *curdest;
	unsigned int *icursrc1, *icurdest;
	unsigned int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	if (N > 32) {
		return false;
	}

	/* Special case: N==0 */
	if (N == 0) {
		memcpy(Src1, Dest, length);
		return true;
	}

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	curdest = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i += bpp) {
		if ((i + bpp) < length) {
			result = 0;
			for (j = bpp; j >= 0; j--) {
				result |= (int) ((cursrc1[i + j] << (sizeof(unsigned int) * j)));
			}
			/* Do the actual uint shift */
			result = result << N;
			/* Pass the shifted value to each byte position */
			for (j = 0; j < bpp; j++) {
				curdest[i + j] = (result >> bpp) & 0xFF;
			}
		}
	}

	return true;
}

/*!
\brief Filter ShiftLeft: D = saturation255(S << N)

\param Src1 Pointer to the start of the source byte array (S1).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param N Number of bit-positions to shift (N). Valid range is 0 to 8.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterShiftLeft(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char N)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *curdest;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	if (N > 8) {
		return false;
	}

	/* Special case: N==0 */
	if (N == 0) {
		memcpy(Src1, Dest, length);
		return true;
	}

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	curdest = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		result = ((int) cursrc1[i]) << N;
		if (result > 255) {
			result = 255;
		}
		curdest[i] = (unsigned char) result;
	}

	return true;
}

/*!
\brief Filter using BinarizeUsingThreshold: D = (S >= T) ? 255:0

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param T The threshold boundary (inclusive).

\return Returns true for success or false for error.
*/
bool SDL_imageFilterBinarizeUsingThreshold(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char T)
{
	unsigned int i, istart;
	unsigned char *cursrc1;
	unsigned char *curdest;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Special case: T==0 */
	if (T == 0) {
		memset(Dest, 255, length);
		return true;
	}

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	curdest = Dest;

	/* C routine to process image */
	for (i = istart; i < length; i++) {
		*curdest = (unsigned char)(((unsigned char)*cursrc1 >= T) ? 255 : 0);
		/* Advance pointers */
		cursrc1++;
		curdest++;
	}

	return true;
}

/*!
\brief Filter using ClipToRange: D = (S >= Tmin) & (S <= Tmax) S:Tmin | Tmax

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param Tmin Lower (inclusive) boundary of the clipping range.
\param Tmax Upper (inclusive) boundary of the clipping range.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterClipToRange(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char Tmin,
							   unsigned char Tmax)
{
	unsigned int i, istart;
	unsigned char *cursrc1;
	unsigned char *curdest;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return false;
	if (length == 0)
		return true;

	/* Special case: Tmin==0 && Tmax = 255 */
	if ((Tmin == 0) && (Tmax == 25)) {
		memcpy(Src1, Dest, length);
		return true;
	}

	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	curdest = Dest;

	/* Routine to process image */
	for (i = istart; i < length; i++) {
		if (*cursrc1 < Tmin) {
			*curdest = Tmin;
		} else if (*cursrc1 > Tmax) {
			*curdest = Tmax;
		} else {
			*curdest = *cursrc1;
		}
		/* Advance pointers */
		cursrc1++;
		curdest++;
	}

	return true;
}

/*!
\brief Filter using NormalizeLinear: D = saturation255((Nmax - Nmin)/(Cmax - Cmin)*(S - Cmin) + Nmin)

\param Src Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param Cmin Normalization constant.
\param Cmax Normalization constant.
\param Nmin Normalization constant.
\param Nmax Normalization constant.

\return Returns true for success or false for error.
*/
bool SDL_imageFilterNormalizeLinear(unsigned char *Src, unsigned char *Dest, unsigned int length, int Cmin, int Cmax, int Nmin,
								   int Nmax)
{
	unsigned int i, istart;
	unsigned char *cursrc;
	unsigned char *curdest;
	float dN, dC, factor, fCMin, fCMax;
	float fNMin, fNMax, fSrc1, tmp;

	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	/* Setup to process whole image */
	istart = 0;
	cursrc = Src;
	curdest = Dest;

	/* Routine to process image */
	fCMin = Cmin / 255.0f;
	fCMax = Cmax / 255.0f;
	fNMin = Nmin / 255.0f;
	fNMax = Nmax / 255.0f;

	dC = fCMax - fCMin;
	if (dC == 0)
		return true;
	dN = fNMax - fNMin;
	factor = dN / dC;
	for (i = istart; i < length; i++) {
		fSrc1 = cursrc[i] / 255.0f;
		tmp = (factor * (fSrc1 - fCMin)) + fNMin;
		if (tmp > 1.0f)
			tmp = 1.0f;
		curdest[i] = (unsigned char) (tmp * 255);
	}

	return true;
}

/* ------------------------------------------------------------------------------------ */

/*!
\brief Filter using ConvolveKernel3x3Divide: Dij = saturation0and255( ... ) 

\param Src The source 2D byte array to convolve. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >2.
\param columns Number of columns in source/destination array. Must be >2.
\param Kernel The 2D convolution kernel of size 3x3.
\param Divisor The divisor of the convolution sum. Must be >0.

Note: No implementation available for this function yet.

\return Returns true if filter was applied, false otherwise.
*/
bool SDL_imageFilterConvolveKernel3x3Divide(unsigned char *Src, unsigned char *Dest, int rows, int columns,
										   signed short *Kernel, unsigned char Divisor)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return false;

	if ((columns < 3) || (rows < 3) || (Divisor == 0))
		return false;

	/* No implementation yet */
	return false;
}

/*!
\brief Filter using ConvolveKernel5x5Divide: Dij = saturation0and255( ... ) 

\param Src The source 2D byte array to convolve. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >4.
\param columns Number of columns in source/destination array. Must be >4.
\param Kernel The 2D convolution kernel of size 5x5.
\param Divisor The divisor of the convolution sum. Must be >0.

Note: No implementation available for this function yet.

\return Returns true if filter was applied, false otherwise.
*/
bool SDL_imageFilterConvolveKernel5x5Divide(unsigned char *Src, unsigned char *Dest, int rows, int columns,
										   signed short *Kernel, unsigned char Divisor)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return false;

	if ((columns < 5) || (rows < 5) || (Divisor == 0))
		return false;

	/* No implementation yet */
	return false;
}

/*!
\brief Filter using ConvolveKernel7x7Divide: Dij = saturation0and255( ... ) 

\param Src The source 2D byte array to convolve. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >6.
\param columns Number of columns in source/destination array. Must be >6.
\param Kernel The 2D convolution kernel of size 7x7.
\param Divisor The divisor of the convolution sum. Must be >0.

Note: No implementation available for this function yet.

\return Returns true if filter was applied, false otherwise.
*/
bool SDL_imageFilterConvolveKernel7x7Divide(unsigned char *Src, unsigned char *Dest, int rows, int columns,
										   signed short *Kernel, unsigned char Divisor)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return false;

	if ((columns < 7) || (rows < 7) || (Divisor == 0))
		return false;

	/* No implementation yet */
	return false;
}

/*!
\brief Filter using ConvolveKernel9x9Divide: Dij = saturation0and255( ... ) 

\param Src The source 2D byte array to convolve. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >8.
\param columns Number of columns in source/destination array. Must be >8.
\param Kernel The 2D convolution kernel of size 9x9.
\param Divisor The divisor of the convolution sum. Must be >0.

Note: No implementation available for this function yet.

\return Returns true if filter was applied, false otherwise.
*/
bool SDL_imageFilterConvolveKernel9x9Divide(unsigned char *Src, unsigned char *Dest, int rows, int columns,
										   signed short *Kernel, unsigned char Divisor)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return false;

	if ((columns < 9) || (rows < 9) || (Divisor == 0))
		return false;

	/* No implementation yet */
	return false;
}

/*!
\brief Filter using ConvolveKernel3x3ShiftRight: Dij = saturation0and255( ... ) 

\param Src The source 2D byte array to convolve. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >2.
\param columns Number of columns in source/destination array. Must be >2.
\param Kernel The 2D convolution kernel of size 3x3.
\param NRightShift The number of right bit shifts to apply to the convolution sum. Must be <7.

Note: No implementation available for this function yet.

\return Returns true if filter was applied, false otherwise.
*/
bool SDL_imageFilterConvolveKernel3x3ShiftRight(unsigned char *Src, unsigned char *Dest, int rows, int columns,
											   signed short *Kernel, unsigned char NRightShift)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return false;

	if ((columns < 3) || (rows < 3) || (NRightShift > 7))
		return false;

	/* No implementation yet */
	return false;
}

/*!
\brief Filter using ConvolveKernel5x5ShiftRight: Dij = saturation0and255( ... ) 

\param Src The source 2D byte array to convolve. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >4.
\param columns Number of columns in source/destination array. Must be >4.
\param Kernel The 2D convolution kernel of size 5x5.
\param NRightShift The number of right bit shifts to apply to the convolution sum. Must be <7.

Note: No implementation available for this function yet.

\return Returns true if filter was applied, false otherwise.
*/
bool SDL_imageFilterConvolveKernel5x5ShiftRight(unsigned char *Src, unsigned char *Dest, int rows, int columns,
											   signed short *Kernel, unsigned char NRightShift)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return false;

	if ((columns < 5) || (rows < 5) || (NRightShift > 7))
		return false;

	/* No implementation yet */
	return false;
}

/*!
\brief Filter using ConvolveKernel7x7ShiftRight: Dij = saturation0and255( ... ) 

\param Src The source 2D byte array to convolve. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >6.
\param columns Number of columns in source/destination array. Must be >6.
\param Kernel The 2D convolution kernel of size 7x7.
\param NRightShift The number of right bit shifts to apply to the convolution sum. Must be <7.

Note: No implementation available for this function yet.

\return Returns true if filter was applied, false otherwise.
*/
bool SDL_imageFilterConvolveKernel7x7ShiftRight(unsigned char *Src, unsigned char *Dest, int rows, int columns,
											   signed short *Kernel, unsigned char NRightShift)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return false;

	if ((columns < 7) || (rows < 7) || (NRightShift > 7))
		return false;

	/* No implementation yet */
	return false;
}

/*!
\brief Filter using ConvolveKernel9x9ShiftRight: Dij = saturation255( ... ) 

\param Src The source 2D byte array to convolve. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >8.
\param columns Number of columns in source/destination array. Must be >8.
\param Kernel The 2D convolution kernel of size 9x9.
\param NRightShift The number of right bit shifts to apply to the convolution sum. Must be <7.

Note: No implementation available for this function yet.

\return Returns true if filter was applied, false otherwise.
*/
bool SDL_imageFilterConvolveKernel9x9ShiftRight(unsigned char *Src, unsigned char *Dest, int rows, int columns,
											   signed short *Kernel, unsigned char NRightShift)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return false;

	if ((columns < 9) || (rows < 9) || (NRightShift > 7))
		return false;

	/* No implementation yet */
	return false;
}

/* ------------------------------------------------------------------------------------ */

/*!
\brief Filter using SobelX: Dij = saturation255( ... ) 

\param Src The source 2D byte array to sobel-filter. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >2.
\param columns Number of columns in source/destination array. Must be >7.

Note: No implementation available for this function yet.

\return Returns true if filter was applied, false otherwise.
*/
bool SDL_imageFilterSobelX(unsigned char *Src, unsigned char *Dest, int rows, int columns)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL))
		return false;

	if ((columns < 8) || (rows < 3))
		return false;

	/* No implementation yet */
	return false;
}

/*!
\brief Filter using SobelXShiftRight: Dij = saturation255( ... ) 

\param Src The source 2D byte array to sobel-filter. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >2.
\param columns Number of columns in source/destination array. Must be >8.
\param NRightShift The number of right bit shifts to apply to the filter sum. Must be <7.

Note: No implementation available for this function yet.

\return Returns true if filter was applied, false otherwise.
*/
bool SDL_imageFilterSobelXShiftRight(unsigned char *Src, unsigned char *Dest, int rows, int columns,
									unsigned char NRightShift)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL))
		return false;
	if ((columns < 8) || (rows < 3) || (NRightShift > 7))
		return false;

	/* No implementation yet */
	return false;
}
