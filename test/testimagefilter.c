/* 

TestImageFilter.c: test program for filter routines

(C) A. Schiffler, 2012-2014, zlib license
(C) Sylvain Beucler, 2013, zlib license

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#ifdef WIN32
#include <windows.h>
#endif
#include "SDL3_imageFilter.h"

#define SRC_SIZE 24

int total_count = 0;
int ok_count = 0;

char* append_number_to_string(char* text, const char* text_end, const char* fmt, unsigned char i);

void setup_src(unsigned char *src1, unsigned char *src2)
{
	int i;

	src1[0]=1;
	src1[2]=1; 
	src1[1]=4;
	src1[3]=3;
	src1[4]=33;
	for (i=5; i<14; i++) src1[i]=i;
	src1[14]=8;
	for (i=15; i<SRC_SIZE; i++) src1[i]=SDL_rand(255);

	src2[0]=1;
	src2[1]=3;
	src2[2]=3; 
	src2[3]=2;
	src2[4]=44;
	for (i=5; i<14; i++) src2[i]=14-i;
	src2[14]=10;
	for (i=15; i<SRC_SIZE; i++) src2[i]=src1[i];
}

void print_result(char *label, unsigned char *src1, unsigned char *src2, unsigned char *dst) 
{
	char number_str[256];
	const char* buf_end = number_str + 256;
	char* res;
	char blabel[80];
	int i;

	memset((void *)blabel, ' ', 80);
	blabel[strlen(label)+4]=0;

	SDL_Log(" ");
	res = number_str;
	res += SDL_snprintf(res, buf_end - res, "%s   pos   ", blabel);
	for (i = 0; i < SRC_SIZE; i++) {
		res = append_number_to_string(res, buf_end, "%2d ", i);
	}
	SDL_Log("%s", number_str);

	res = number_str;
	res += SDL_snprintf(res, buf_end - res, "%s   src1  ", blabel);
	for (i = 0; i < SRC_SIZE; i++){
		res = append_number_to_string(res, buf_end, "%02x ", src1[i]);
	}
	SDL_Log("%s", number_str);

	if (src2) {
		res = number_str;
		res += SDL_snprintf(res, buf_end - res, "%s   src2  ", blabel);
		for (i = 0; i < SRC_SIZE; i++) {
			res = append_number_to_string(res, buf_end, "%02x ", src2[i]);
		}
		SDL_Log("%s", number_str);
	}

	res = number_str;
	res += SDL_snprintf(res, buf_end - res, " %s      dest  ", label);
	for (i = 0; i < SRC_SIZE; i++) {
		res = append_number_to_string(res, buf_end, "%02x ", dst[i]);
	}
	SDL_Log("%s", number_str);
	SDL_Log("\n");
}

void print_line() 
{
	SDL_Log ("------------------------------------------------------------------------");
}

/* ----------- main ---------- */

int main(int argc, char *argv[])
{
	unsigned char src1[SRC_SIZE], src2[SRC_SIZE], dstm[SRC_SIZE], dstc[SRC_SIZE];
    int size = 2*1024*1024;
    unsigned char *t1 = (unsigned char *)SDL_malloc(size);
	unsigned char *t2 = (unsigned char *)SDL_malloc(size);
	unsigned char *d = (unsigned char *)SDL_malloc(size);

	/* Set a default seed to make random consistent to test */
	SDL_srand(1234);

	/* Initialize to make valgrind happy */
	for (int i = 0; i < size; i++) {
		/* use more random lower-order bits (int->char) */
		t1[i] = SDL_rand(255); t2[i] = SDL_rand(255); d[i] = SDL_rand(255);
	}

	SDL_Init(0);

	/* SDL_imageFilter Test */
	SDL_Log("TestImageFilter\n\n");
	SDL_Log("Testing an array of %u bytes\n\n", SRC_SIZE);
	print_line();

	/* First batch of tests, using a second byte array filter */
	{
		#define FUNC(f) { #f, SDL_imageFilter ## f }

		struct func {
			char* name;
			int (*f)(unsigned char*, unsigned char*, unsigned char*, unsigned int);
		};

		struct func funcs[] = {
			FUNC(BitAnd),
			FUNC(BitOr),
			FUNC(Add),
			FUNC(AbsDiff),
			FUNC(Mean),
			FUNC(Sub),
			FUNC(Mult),
			FUNC(MultNor),
			FUNC(MultDivby2),
			FUNC(MultDivby4),
			FUNC(Div),
		};

		for (int k = 0; k < sizeof(funcs)/sizeof(struct func); k++) {
			int i;
			setup_src(src1, src2);

			funcs[k].f(src1, src2, dstc, SRC_SIZE);
			print_result(funcs[k].name, src1, src2, dstc);

			Uint64 start = SDL_GetTicks();
			for (i = 0; i < 50; i++) {
				funcs[k].f(t1, t2, d, size);
			}
			SDL_Log(" Speed test (%d x %dk byte array): %lums\n", i, size/1024, SDL_GetTicks() - start);
			print_line();
		}
	}

	/* Second batch bit negation */
	{
		Uint64 start;
		int i;
		char call[1024];
		SDL_snprintf(call, 1024, "BitNegation");
		
		setup_src(src1, src2);
		SDL_imageFilterBitNegation(src1, dstc, SRC_SIZE);
		print_result(call, src1, NULL, dstc);

		start = SDL_GetTicks();
		for (i = 0; i < 50; i++) {
			SDL_imageFilterBitNegation(t1, d, size);
		}
		SDL_Log(" Speed test (%d x %dk byte array): %lums\n", i, size/1024, SDL_GetTicks() - start);
		print_line();
	}

	/* Third batch, all that use one additional C constant */
	{
#undef FUNC
#define FUNC(f, c) { #f, SDL_imageFilter ## f, c }
		struct func {
			char* name;
			int (*f)(unsigned char*, unsigned char*, unsigned int, unsigned char);
			unsigned char arg;
		};

		struct func funcs[] = {
			FUNC(AddByte,                3),
			FUNC(AddByteToHalf,          3),
			FUNC(SubByte,                3),
			FUNC(ShiftRight,             1),
			FUNC(ShiftRightUint,         4),
			FUNC(MultByByte,             3),
			FUNC(ShiftLeftByte,          3),
			FUNC(ShiftLeft,              3),
			FUNC(ShiftLeftUint,          4),
			FUNC(BinarizeUsingThreshold, 9),
		};

		int k;
		for (k = 0; k < sizeof(funcs)/sizeof(struct func); k++) {
			Uint64 start;
			int i;
			char call[1024];
			SDL_snprintf(call, 1024, "%s(%u)", funcs[k].name, funcs[k].arg);
			setup_src(src1, src2);

			funcs[k].f(src1, dstc, SRC_SIZE, funcs[k].arg);
			print_result(call, src1, NULL, dstc);

			start = SDL_GetTicks();
			for (i = 0; i < 50; i++) {
				funcs[k].f(t1, d, size, funcs[k].arg);
			}
			SDL_Log(" Speed test (%d x %dk byte array): %lums\n", i, size/1024, SDL_GetTicks() - start);
			print_line();
		}
    }

	/* Fourth batch, ones that use two constants*/
	{
#undef FUNC
#define FUNC(f, c1, c2) { #f, SDL_imageFilter ## f, c1, c2 }
		struct func {
			char* name;
			int (*f)(unsigned char*, unsigned char*, unsigned int, unsigned char, unsigned char);
			unsigned char arg1, arg2;
		};
		struct func funcs[] = {
			FUNC(ShiftRightAndMultByByte, 1, 3),
			FUNC(ClipToRange, 3, 8),
		};
		
		int k;
		for (k = 0; k < sizeof(funcs)/sizeof(struct func); k++) {
			Uint64 start;
			int i;
			char call[1024];
			SDL_snprintf(call, 1024, "%s(%u,%u)", funcs[k].name, funcs[k].arg1, funcs[k].arg2);

			setup_src(src1, src2);

			funcs[k].f(src1, dstc, SRC_SIZE, funcs[k].arg1, funcs[k].arg2);
			print_result(call, src1, NULL, dstc);

			start = SDL_GetTicks();
			for (i = 0; i < 50; i++) {
				funcs[k].f(t1, d, size, funcs[k].arg1, funcs[k].arg2);
			}
			SDL_Log(" Speed test (%d x %dk byte array): %lums\n", i, size/1024, SDL_GetTicks() - start);
			print_line();
		}
	}

	/* Fith batch, NormalizeLinear */
	{
		Uint64 start;
		int i;
		char call[1024];
		SDL_snprintf(call, 1024, "NormalizeLinear(0, 33, 0, 255)");
		
		setup_src(src1, src2);

		SDL_imageFilterNormalizeLinear(src1, dstc, SRC_SIZE, 0,33, 0,255);
		print_result(call, src1, NULL, dstc);

		start = SDL_GetTicks();
		for (i = 0; i < 50; i++) {
			SDL_imageFilterNormalizeLinear(t1, d, size, 0,33, 0,255);
		}
		SDL_Log(" Speed test (%d x %dk byte array): %lums\n", i, size/1024, SDL_GetTicks() - start);
		print_line();
	}


	/* Sixth batch: Uint addition functions */
	{
#undef FUNC
#define FUNC(f, b, c) { #f, SDL_imageFilter ## f, b, c }
		struct func {
			char* name;
			int (*f)(unsigned char*, unsigned char*, unsigned int, unsigned int, unsigned int);
			unsigned int arg1;
			unsigned int arg2;
		};
		struct func funcs[] = {
			FUNC(AddUint,       4, 0x01020304),
			FUNC(SubUint,       4, 0x01020304),
		};
		
		int k;
		for (k = 0; k < sizeof(funcs)/sizeof(struct func); k++) {
			Uint64 start;
			int i;
			char call[1024];
			SDL_snprintf(call, 1024, "%s(%u, %u)", funcs[k].name, funcs[k].arg1, funcs[k].arg2);
			
			setup_src(src1, src2);

			funcs[k].f(src1, dstc, SRC_SIZE, funcs[k].arg1, funcs[k].arg2);
			print_result(call, src1, NULL, dstc);

			start = SDL_GetTicks();
			for (i = 0; i < 50; i++) {
				funcs[k].f(t1, d, size, funcs[k].arg1, funcs[k].arg2);
			}
			SDL_Log(" Speed test (%d x %dk byte array): %lums\n", i, size/1024, SDL_GetTicks() - start);
			print_line();
		}
	}

	SDL_Log("Result: %i of %i passed OK.\n", ok_count, total_count);

	SDL_Quit();
	SDL_free(d);
	SDL_free(t2);
	SDL_free(t1);

	exit(0);
}

char* append_number_to_string(char* text, const char* text_end, const char* fmt, unsigned char i)
{
	if (text >= text_end)
	{
		//Do not keep incrementing return pointer if its already past the end
		return text;
	}

	char* cur = text;
	cur += SDL_snprintf(cur, text_end - cur, fmt, i);
	return cur;
}