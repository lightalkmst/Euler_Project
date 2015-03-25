// Euler_Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <time.h>

#define Print(n) PrintAns(n, ans);

void Solved();
void Problem1();
void Problem2();
void Problem3();
void Problem4();
void Problem5();
void Problem6();
void Problem7();
void Problem8();
void Problem9();
void Problem10();
//void Problem12();
//void Problem13();
//void Problem14();
//void Problem15();
void Problem16();
void Problem18();
void Problem20();
void Problem21();
void Problem23();
//void Problem24();
//void Problem25();
void Problem28();
void Problem29();
void Problem30();
void Problem31();
void Problem34();
void Problem39();
void Problem41(); // Incomplete
void Problem45();
void Problem52();
void Problem53();
void Problem58();
void Problem63();
void Problem66();

int total_solved = 0;

int main(int argc, _TCHAR* argv[]) {
	const bool RUN_ALL = true;
	void (*CURRENT_PROBLEM) (void) = Problem66;

	if (RUN_ALL) {
		Problem1();
		Problem2();
		Problem3();
		Problem4();
		Problem5();
		Problem6();
		Problem7();
		Problem8();
		Problem9();
		Problem10();
		Problem16();
		Problem18();
		Problem20();
		Problem21();
		Problem23();
		Problem28();
		Problem29();
		Problem30();
		Problem34();
		Problem39();
		Problem41();
		Problem52();
		Problem53();
		Problem58();
		Problem63();
		printf("%i problems solved total\n", total_solved);
	}
	else {
		// Problem I'm currently working on
		time_t start = time(NULL);
		CURRENT_PROBLEM();
		time_t end = time(NULL);
		double elapsed = difftime(end, start);
		printf("%u seconds spent to calculate the problem\n", elapsed);
	}

	{
		// Pause so that the results are legible
		// Waits for Enter
		fgetc(stdin);
	}
	return 0;
}

void PrintAns(int num, int ans) {
	printf("Problem %i:\n", num);
	printf("Answer: %i\n", ans);
	Solved();
}

void Solved() {
	total_solved++;
}

void Problem1() {
	/*
	Problem 1
	If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

	Find the sum of all the multiples of 3 or 5 below 1000.
	*/
	int ans = 0;
	int max = 999;
	int sum3 = (max / 3) * ((max / 3) + 1) * 3 / 2; // the triangle equation modified for the multiples of 3
	int sum5 = (max / 5) * ((max / 5) + 1) * 5 / 2; // the triangle equation modified for the multiples of 5
	int sum15 = (max / 15) * ((max / 15) + 1) * 15 / 2; // the triangle equation modified for the multiple of 15 to prevent double counting
	ans = sum3 + sum5 - sum15;
	PrintAns(1, ans);
}

void Problem2() {
	/*
	Problem 2
	Each new term in the Fibonacci sequence is generated by adding the previous two terms. By starting with 1 and 2, the first 10 terms
	will be:
	1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

	By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.
	*/
	int fib[2] = {1, 2};
	int ans = 0;
	for (; fib[1] < 4000000;) {
		if (fib[1] % 2 == 0)
			ans += fib[1];
		int t_sum = fib[0] + fib[1];
		fib[0] = fib[1];
		fib[1] = t_sum;
	}
	PrintAns(2, ans);
}

void Problem3() {
	/*
	Problem 3
	The prime factors of 13195 are 5, 7, 13 and 29.

	What is the largest prime factor of the number 600851475143 ?
	*/
	// Once a prime factor is found, you can divide it out
	// This makes future operations a little cheaper
	// Additionally, all composite factors will be ruled out
	int ans = -1;
	long long input = 600851475143;
	for (int n = 2; input > (long long) 1; n++) {
		if (input % (long long) n == 0) {
			input /= (long long) n;
			ans = (int) n;
			n--;
		}
	}
	PrintAns(3, ans);
}

void Problem4() {
	/*
	Problem 4
	A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 �
	99.

	Find the largest palindrome made from the product of two 3-digit numbers.
	*/
	// The product of two 3-digit numbers must be a 6-digit number
	// For each 3-digit number, find the largest 3-digit factor that gives a palindrome
	// That palindrome will be the largest palindrome from that 3-digit number
	int ans = -1;
	{
		int pal[1000] = {-1};
		for (int i = 999; i > 99; i--) {
			for (int i2 = 999; i2 > 99; i2--) {
				int t_prod = i * i2;
				if (t_prod / 100000 == t_prod % 10 && t_prod / 10000 % 10 == t_prod / 10 % 10 && t_prod / 1000 % 10 == t_prod / 100 % 10) {
					pal[i] = t_prod;
					break;
				}
			}
		}	
		for (int i = 100; i < 1000; i++) {
			if (pal[i] > ans)
				ans = pal[i];
		}
	}
	PrintAns(4, ans);
}

void Problem5() {
	/*
	2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

	What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
	*/
	// Because there are composite numbers within the given range, I take the prime factorization of each
	// number to prevent double counting
	int primefactors[20] = {0};
	for (int n = 1; n <= 20; n++) {
		int t_n = n;
		for (int n2 = 2; n2 <= t_n; n2++) {
			int t_count = 0;
			for (; t_n % n2 == 0;) {
				t_n /= n2;
				t_count++;
			}
			if (primefactors[n2] < t_count)
				primefactors[n2] = t_count;
		}
	}
	int ans = 1;
	for (int i = 2; i < 20; i++) {
		if (primefactors[i] > 0) {
			ans *= i;
			primefactors[i]--;
			i--;
		}
	}
	PrintAns(5, ans);
}

void Problem6() {
	/*
	Problem 6
	The sum of the squares of the first ten natural numbers is,
	1^2 + 2^2 + ... + 10  ^ 2 = 385
	The square of the sum of the first ten natural numbers is,
	(1 + 2 + ... + 10)^2 = 55^2 = 3025
	Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 - 385 = 2640.

	Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
	*/

	// Brute force since the problem is not large enough to warrant a more sophisticated solution
	int sum_sq = 0;
	int sq_sum = 0;
	for (int i = 1; i <= 100; i++) {
		sum_sq += i * i;
		sq_sum += i;
	}
	sq_sum *= sq_sum;
	int ans = sq_sum - sum_sq;
	PrintAns(6, ans);
}

void Problem7() {
	/*
	Problem 7
	By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

	What is the 10 001st prime number?
	*/
	int ans = -1;
	int input = 10001;
	for (int i = 2; input; i++) {
		input--;
		for (int i2 = 2; i2 * i2 <= i; i2++) {
			if (i % i2 == 0) {
				input++;
				break;
			}
		}
		if (input == 0)
			ans = i;
	}
	PrintAns(7, ans);
}

void Problem8() {
	// Problem 8
	// Find the greatest product of five consecutive digits in the 1000-digit number.
	char input[] = "73167176531330624919225119674426574742355349194934"
		           "96983520312774506326239578318016984801869478851843"
				   "85861560789112949495459501737958331952853208805511"
				   "12540698747158523863050715693290963295227443043557"
				   "66896648950445244523161731856403098711121722383113"
				   "62229893423380308135336276614282806444486645238749"
				   "30358907296290491560440772390713810515859307960866"
				   "70172427121883998797908792274921901699720888093776"
				   "65727333001053367881220235421809751254540594752243"
				   "52584907711670556013604839586446706324415722155397"
				   "53697817977846174064955149290862569321978468622482"
				   "83972241375657056057490261407972968652414535100474"
				   "82166370484403199890008895243450658541227588666881"
				   "16427171479924442928230863465674813919123162824586"
				   "17866458359124566529476545682848912883142607690042"
				   "24219022671055626321111109370544217506941658960408"
				   "07198403850962455444362981230987879927244284909188"
				   "84580156166097919133875499200524063689912560717606"
				   "05886116467109405077541002256983155200055935729725"
				   "71636269561882670428252483600823257530420752963450";
	// Rather than brute force method, i will only calculate local maxima.
	// I will keep track of the digits in the window.
	// Whenever the window moves, one digit enters, another digit leaves.
	// Calculate current max when a digit smaller than the one leaving enters.
	int max = -1;
	int window = 5;
	for (int i = 1; i + window < (int) strlen(input); i++) {
		if ((int) (input[i - 1 + window] - input[i - 1]) < 0) {
			int temp = 1;
			for (int i2 = -1; i2 < window - 1; i2++) {
				temp *= (int) (input[i + i2] - '0');
			}
			max = temp > max ? temp : max;
		}
	}
	PrintAns(8, max);
}

void Problem9() {
	// Problem 9
	// A Pythagorean triplet is a set of three natural numbers, a < b < c
	// Where a^2 + b^2 = c^2
	// There is exactly one Pythagorean triplet where a + b + c = 1000

	// Find a * b * c

	// Because of the a < b < c constraint, we can stop searching early
	// and prevent recalculation of old
	int ans = -1;
	for (int a = 0; a < 333; a++) {
		for (int b = a + 1; b < (1000 - a) / 2; b++) {
			int c = 1000 - a - b;
			if (a * a + b * b != c * c) {
				continue;
			}
			ans = a * b * c;
			goto Solved;
		}
	}
Solved:;
	PrintAns(9, ans);
}

void Problem10() {
	/*
	Problem 10
	The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

	Find the sum of all the primes below two million.
	*/
	long long ans = 0;
	for (int n = 2; n < 2000000; n++) {
		// Add all numbers
		ans += n;
		for (int n2 = 2; n2 * n2 <= n; n2++) {
			// Remove all composite numbers
			if (n % n2 == 0) {
				ans -= n;
				break;
			}
		}
	}
	printf("Problem 10\n");
	printf("Answer: %lli\n", ans);
	Solved();
}

void Problem16() {
	// Problem 16
	// 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26

	// What is the sum of the digits of 2^1000?
	
	// 2^1000 is definitely too large for a single int field, so use
	// an array to hold different orders of magnitude
	// When multiplying a value by 2, the change in number of digits
	// is at most 1 and at least 0, so 1000 places is definitely sufficient
	// I use int here, but a short or char array would use less room
	// but take more time
	int num[1000] = {1, 0}; // initialize as 1 = 2^0
	// Raise to the power of 1000
	for (int n = 0; n < 1000; n++) {
		int temp = 0;
		for (int i = 0; i < 1000; i++) {
			num[i] *= 2;
			num[i] += temp;
			temp = num[i] / 10;
			num[i] = num[i] % 10;
		}
	}
	// Add the digits
	int ans = 0;
	for (int i = 0; i < 1000; i++) {
		ans += num[i];
	}
	PrintAns(13, ans);
}

void Problem18() {
	/*
	By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
	   3
	  7 4
	 2 4 6
	8 5 9 3
	That is, 3 + 7 + 4 + 9 = 23.

	Find the maximum total from top to bottom of the triangle below:
	                            75
	                          95  64
	                        17  47  82
	                      18  35  87  10
	                    20  04  82  47  65
	                  19  01  23  75  03  34
	                88  02  77  73  07  63  67
	              99  65  04  28  06  16  70  92
	            41  41  26  56  83  40  80  70  33
	          41  48  72  33  47  32  37  16  94  29
	        53  71  44  65  25  43  91  52  97  51  14
	      70  11  33  28  77  73  17  78  39  68  17  57
	    91  71  52  38  17  14  91  43  58  50  27  29  48
	  63  66  04  68  89  53  67  30  73  16  69  87  40  31
	04  62  98  27  23  09  70  98  73  93  38  53  60  04  23
	NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. However, Problem 67, is the same 
	challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)
	*/
	// I use the unformatted pasted triangle as input for my code
	// I format it to my needs within the code
	char input[] = "75 "
                   "95 64 "
				   "17 47 82 "
				   "18 35 87 10 "
				   "20 04 82 47 65 "
				   "19 01 23 75 03 34 "
				   "88 02 77 73 07 63 67 "
				   "99 65 04 28 06 16 70 92 "
				   "41 41 26 56 83 40 80 70 33 "
				   "41 48 72 33 47 32 37 16 94 29 "
				   "53 71 44 65 25 43 91 52 97 51 14 "
				   "70 11 33 28 77 73 17 78 39 68 17 57 "
				   "91 71 52 38 17 14 91 43 58 50 27 29 48 "
				   "63 66 04 68 89 53 67 30 73 16 69 87 40 31 "
				   "04 62 98 27 23 09 70 98 73 93 38 53 60 04 23 ";
	int *triangle[15] = {NULL};
	for (int i = 0; i < 15; i++) {
		triangle[i] = new int[i]; // attempts to delete[] arrays at end cause crash. don't know why
	}
	{
		int row = 0;
		int col = 0;
		for (int i = 0; i * 3 < (int) strlen(input); i++) {
			triangle[row][col] = atoi(input + i * 3);
			col++;
			if (row < col) {
				row++;
				col = 0;
			}
		}
	}
	// Rather than brute force, I will solve this by going backwards.
	// In game theory, this is called finding the sub-game equilibria.
	// It works by ruling out all inferior choices given a superior one.
	for (int i = 14 - 1; i >= 0; i--) {
		for (int i2 = 0; i2 <= i; i2++) {
			triangle[i][i2] = triangle[i][i2] + std::max(triangle[i + 1][i2], triangle[i + 1][i2 + 1]);
		}
	}
	int ans = triangle[0][0];
	PrintAns(18, ans);
}

void Problem20() {
	/*
	Problem 20
	n! means n * (n - 1) * ... * 3 * 2 * 1
	For example, 10! = 10 * 9 * ... * 3 * 2 * 1 = 3628800,
	and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

	Find the sum of the digits in the number 100!
	*/
	
	// Similar solution and approach to number 16
	// 100! is definitely too large for a single int field, so use
	// an array to hold different orders of magnitude
	// When multiplying a value by another number, the maximum number of digits
	// is the total number of digits in both numbers, so 8 * 1 + 1 * 3 + 90 * 2 = 191
	// places is sufficient
	// I use int here, but a short or char array would use less room
	// but take more time
	int num[191] = {1, 0}; // initialize as 1
	// Raise to the power of 1000
	for (int n = 2; n < 100; n++) {
		int temp = 0;
		for (int i = 0; i < 191; i++) {
			num[i] *= n;
			num[i] += temp;
			temp = num[i] / 10;
			num[i] %= 10;
		}
	}
	// Add the digits
	int ans = 0;
	for (int i = 0; i < 191; i++) {
		ans += num[i];
	}
	PrintAns(20, ans);
}

void Problem21() {
	/*
	Problem 21
	Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
	If d(a) = b and d(b) = a, where a != b, then a and b are an amicable pair and each of a and b are called amicable numbers.
	For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55, and 110; therefore d(220) = 284.
	The Proper divisors of 284 are 1, 2, 4, 71, and 142; so d(284) = 220.

	Evaluate the sum of all the amicable numbers under 10000.
	*/

	// Pretty much brute-forcing here, but I try to make it efficient.
	int ans = 0;
	int divsum[10000] = {0};
	for (int i = 1; i < 10000; i++) {
		int t_divsum = 1;
		// End the search for divisors early
		for (int i2 = 2; i2 * i2 <= i; i2++) {
			if (i % i2 == 0) {
				t_divsum += i2;
				if (i2 * i2 != i)
					t_divsum += i / i2;
			}
		}
		divsum[i] = t_divsum;
		// Only check previously computed numbers
		// Since each numbers divisor sum must be equal to the other,
		// the search can be done as an O(1) direct search
		if (t_divsum < i && divsum[t_divsum] == i) {
			ans += i + t_divsum;
		}
	}
	PrintAns(21, ans);
}

void Problem23() {
	/*
	A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the
	proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
	A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.
	As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant
	numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant
	numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that
	cannot be expressed as the sum of two abundant numbers is less than this limit.

	Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
	*/

	// I'm gonna brute force this one too
	class Calc {
	public:
		static bool IsAbund(int n) {
			int t_divsum = 1;
			for (int i = 2; i * i <= n; i++) {
				if (n % i == 0) {
					t_divsum += i;
					if (i * i != n)
						t_divsum += n / i;
				}
			}
			return t_divsum > n;
		}

		static int BinSearch(int arr[], int hi, int n) {
			int low = 0;
			int mid = (hi + low) / 2;
			for (; hi >= low;) {
				mid = (hi + low) / 2;
				if (arr[mid] < n)
					low = mid + 1;
				else if (arr[mid] > n)
					hi = mid - 1;
				else
					return mid;
			}
			return -1;
		}
	};
	int abundnums[28124] = {-1};
	int abundindex = 0;
	for (int i = 1; i < 28124; i++) {
		if (Calc::IsAbund(i)) {
			abundnums[abundindex] = i;
			abundindex++;
		}
	}
	// Change to binary search on abundnums
	// Add up all numbers that are not the sum of two abundant numbers
	int ans = 0;
	for (int n = 1; n < 28124; n++) {
		// Add up all numbers
		ans += n;
		for (int i = 0; abundnums[i] * 2 <= n && abundnums[i] != -1; i++) {
			if (Calc::BinSearch(abundnums, abundindex, n - abundnums[i]) >= 0) {
				ans -= n;
				break;
			}
		}
	}
	PrintAns(23, ans);
}

void Problem28() {
	/*
	Problem 28
	Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:
	21 22 23 24 25
	20  7  8  9 10
	19  6  1  2 11
	18  5  4  3 12
	17 16 15 14 13
	It can be verified that the sum of the numbers on the diagonals is 101.

	What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
	*/
	// Each round of the spiral makes a square. This makes the calculated numbers very sequential.
	// The easiest to note is the top right corner of each layer as it is the last number in a square.
	int ans = 1; // initialize to 1 since that layer is special and has only one entry.
	for (int n = 2; n <= 501; n++) { // the spiral adds 2 to rows and cols for each iteration
		ans += (2 * n - 1) * (2 * n - 1); // top right corner
		ans += (2 * n - 1) * (2 * n - 1) - 2 * (n - 1); // top left corner
		ans += (2 * n - 1) * (2 * n - 1) - 4 * (n - 1); // bottom left corner
		ans += (2 * n - 1) * (2 * n - 1) - 6 * (n - 1); // bottom right corner
	}
	PrintAns(28, ans);
}

void Problem29() {
	/*
	Problem 29
	Consider all integer combinations of a^b for 2 <= a <= 5 and 2 <= b <= 5:
	2^2 = 4, 2^3 = 8, 2^4 = 16, 2^5 = 32
	3^2 = 9, 3^3 = 27, 3^4 = 81, 3^5 = 243
	4^2 = 16, 4^3 = 64, 4^4 = 256, 4^5 = 1024
	5^2 = 25, 5^3 = 125, 5^4 = 625, 5^5 = 3125
	If they are then placed in numerical order, with any repeats removed, we get the following sequence of 15 distinct terms:
	4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 243, 256, 625, 1024, 3125

	How many distinct terms are in the sequence generated by a^b for 2 <= a <= 100 and 2 <= b <= 100?
	*/
	// The numbers that will be created through this fashion are too large to be held by the commputer
	// Instead, I will hold the prime factorization of the numbers and compare those to determine equivalency
	class PowerEntry {
	private:
		int b;
		int p;
		PowerEntry *next;
	public:
		PowerEntry(int b, int p) {
			this->b = b;
			this->p = p;
			next = NULL;
		}

		~PowerEntry() {
			if (next != NULL)
				delete next;
		}

		bool IsEqual(PowerEntry *other) {
			if (other == NULL) {
				return false;
			}
			if (this->b == -1)
				return next->IsEqual(other);
			if (other->b == -1)
				return IsEqual(other->next);
			if (b == other->b && p == other->p) {
				if (next == NULL && other->next == NULL)
					return true;
				return next->IsEqual(other->next);
			}
			return false;
		}

		void Add(int b, int p) {
			PowerEntry *curr = this;
			PowerEntry *prev = NULL;
			for (; curr != NULL; curr = curr->next) {
				if (curr->b == b) {
					curr->p += p;
					return;
				}
				prev = curr;
			}
			prev->next = new PowerEntry(b, p);
		}

		void Multiply(int m) {
			for (PowerEntry *curr = this; curr != NULL; curr = curr->next) {
				curr->p *= m;
			}
		}

		PowerEntry *Clone() {
			PowerEntry *t_ret = new PowerEntry(b, p);
			if (next != NULL)
				t_ret->next = next->Clone();
			else 
				t_ret->next = NULL;
			return t_ret;
		}

		void Merge(PowerEntry *other, bool free = false) {
			for (PowerEntry *o_curr = other; o_curr != NULL;) {
				this->Add(o_curr->b, o_curr->p);
				if (free) {
					PowerEntry *t_o_curr = o_curr;
					o_curr = o_curr->next;
					t_o_curr->next = NULL;
				}
				else {
					o_curr = o_curr->next;
				}
			}
		}
	};
	PowerEntry *arr_root[10000] = {NULL}; // max 99 * 99 numbers if no dups
	for (int i = 0; i < 10000; i++) {
		arr_root[i] = NULL;
	}
	for (int a = 2; a <= 100; a++) {
		// Prime factors of a
		PowerEntry *root_a = new PowerEntry(-1, -1);
		int t_a = a;
		for (int n = 2; t_a > 1; n++) {
			if (t_a % n == 0) {
				t_a /= n;
				root_a->Add(n, 1);
				n--;
			}
		}
		for (int b = 2; b <= 100; b++) {
			// Prime factors of b
			PowerEntry *root_b = root_a->Clone();
			root_b->Multiply(b);
			// Check if in main array
			bool found = false;
			int i = 0;
			for (; arr_root[i] != NULL; i++) {
				if (root_b->IsEqual(arr_root[i])) {
					found = true;
					break;
				}
			}
			if (!found) {
				arr_root[i] = root_b;
			}
			else {
				delete root_b;
			}
		}
		delete root_a;
	}
	int ans = 0;
	for (int i = 0;; i++) {
		if (arr_root[i] == NULL) {
			ans = i;
			break;
		}
		delete arr_root[i];
	}
	PrintAns(29, ans);
}

void Problem30() {
	/*
	Problem 30
	Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:
	1634 = 1^4 + 6^4 + 3^4 + 4^4
	8208 = 8^4 + 2^4 + 0^4 + 8^4
	9474 = 9^4 + 4^4 + 7^4 + 4^4
	As 1 = 1^4 is not a sum it is not included.
	The sum of these numbers is 1634 + 8208 + 9474 = 19316.

	Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
	*/
	// Pretty much brute force is all I've got here
	int pow[10] = {0, 1, 32, 243, 1024, 3125, 7776, 16807, 32768, 59049};
	int ans = 0;
	for (int i = 2; i <= 999999; i++) {
		int t_sum = 0;
		for (int t_i = i; t_i > 0; t_i /= 10) {
			t_sum += pow[t_i % 10];
		}
		if (t_sum == i) {
			ans += i;
		}
	}
	PrintAns(30, ans);
}

void Problem31() {
	/*
	Problem 31
	In England the currency is made up of pound, �, and pence, p, and there are eight coins in general circulation:
	1p, 2p, 5p, 10p, 20p, 50p, �1 (100p) and �2 (200p).
	It is possible to make �2 in the following way:
	1ף1 + 1�50p + 2�20p + 1�5p + 1�2p + 3�1p

	How many different ways can �2 be made using any number of coins?
	*/
	// Simple problem to brute force
	int ans = 0;
	for (int i = 0; i * 200 <= 200; i++) {
		for (int i1 = 0; i * 200 + i1 * 100 <= 200; i1++) {
			for (int i2 = 0; i * 200 + i1 * 100 + i2 * 50 <= 200; i2++) {
				for (int i3 = 0; i * 200 + i1 * 100 + i2 * 50 + i3 * 20 <= 200; i3++) {
					for (int i4 = 0; i * 200 + i1 * 100 + i2 * 50 + i3 * 20 + i4 * 10 <= 200; i4++) {
						for (int i5 = 0; i * 200 + i1 * 100 + i2 * 50 + i3 * 20 + i4 * 10 + i5 * 5 <= 200; i5++) {
							for (int i6 = 0; i * 200 + i1 * 100 + i2 * 50 + i3 * 20 + i4 * 10 + i5 * 5 + i6 * 2 <= 200; i6++) {
								ans++; // any sum of the other coins can be filled out using the 1p coins
							}
						}
					}
				}
			}
		}
	}
	PrintAns(31, ans);
}

void Problem34() {
	/*
	Problem 34
	145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
	Find the sum of all numbers which are equal to the sum of the factorial of their digits.

	Note: as 1! = 1 and 2! = 2 are not sums they are not included.
	*/
	// Same as problem 30
	int fact[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
	// 9! = 362880 so the biggest eligible number is 7 digits
	int ans = 0;
	for (int i = 3; i <= 9999999; i++) {
		int t_sum = 0;
		for (int t_i = i; t_i > 0; t_i /= 10) {
			t_sum += fact[t_i % 10];
		}
		if (t_sum == i) {
			ans += i;
		}
	}
	PrintAns(34, ans);
}

void Problem39() {
	/*
	Problem 39
	If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.
	{20,48,52}, {24,45,51}, {30,40,50}

	For which value of p <= 1000, is the number of solutions maximised?
	*/
	// Brute force
	int ans = 0;
	int max = 0;
	for (int p = 1; p <= 1000; p++) {
		int t_count = 0;
		for (int c = p / 3; c < p; c++) {
			for (int b = c - 1; b < c && b > 1; b--) {
				int a = p - c - b;
				if (a > b)
					continue;
				if (a * a + b * b == c * c)
					t_count++;
			}
		}
		if (t_count > max) {
			max = t_count;
			ans = p;
		}
	}
	PrintAns(39, ans);
}

void Problem41(){
	/*
	Problem 41
	We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.

	What is the largest n-digit pandigital prime that exists?
	*/
	class Calc {
	public:
		static int Pand(int d, int n) {
			int *digits = new int[d];
			for (int i = 0; i < d; i++) {
				digits[i] = i + 1;
			}
			int ret = 0;
			for (; d > 0; d--) {
				ret *= 10;
				ret += digits[n % d];
				for (int i = n % d; i < d - 1; i++) {
					digits[i] = digits[i + 1];
				}
				n /= d;
			}
			delete [] digits;
			return ret;
		}

		static int Fact(int n) {
			int ret = 1;
			for (; n > 1; n--)
				ret *= n;
			return ret;
		}

		static bool IsPrime(int n) {
			for (int i = 2; i * i <= n; i++)
				if (n % i == 0)
					return false;
			return true;
		}
	};
	int ans = 0;
	for (int i = 9; i > 0; i--) {
		for (int curr = Calc::Fact(i) - 1; curr >= 0; curr--) {
			int curr1 = Calc::Pand(i, curr);
			if (Calc::IsPrime(curr1) && curr1 > ans) {
				ans = curr1;
			}
		}
	}
	PrintAns(41, ans);
}

void Problem45() {
	// Incomplete : unsigned long long too small
	// Solve equations mathematically
	return;
	/*
	Problem 45
	Triangle, pentagonal, and hexagonal numbers are generated by the following formulae:
	Triangle	  Tn=n(n+1)/2	    1, 3, 6, 10, 15, ...
	Pentagonal	  Pn=n(3n-1)/2  	1, 5, 12, 22, 35, ...
	Hexagonal	  H_n=n(2n-1)	    1, 6, 15, 28, 45, ...
	It can be verified that T285 = P165 = H143 = 40755.

	Find the next triangle number that is also pentagonal and hexagonal.
	*/

	// Only calculate next term when necessary
	// Once a term is passed, it won't be found again, so only need to store current number
	class Calc {
	public:
		static long long Tri(int n) {
			return n * (n + 1) / 2;
		}

		static long long Pen(int n) {
			return n * (3 * n - 1) / 2;
		}

		static long long Hex(int n) {
			return n * (2 * n - 1);
		}
	};
	int n_tri = 286;
	int n_pen = 165;
	int n_hex = 143;
	// Instead of recalculating when we need it, which will be many times per value, store latest value
	unsigned long long curr_tri = Calc::Tri(n_tri);
	unsigned long long curr_pen = Calc::Pen(n_pen);
	unsigned long long curr_hex = Calc::Hex(n_hex);
	int ans = 0;
	for (; curr_tri != curr_pen || curr_tri != curr_hex; curr_tri = Calc::Tri(++n_tri)) {
		for (; curr_pen < curr_tri; curr_pen = Calc::Pen(++n_pen));
		for (; curr_hex < curr_tri; curr_hex = Calc::Hex(++n_hex));
	}
	ans = (int) curr_tri;
	PrintAns(45, ans);
}

void Problem52() {
	/*
	Problem 52
	It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.

	Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
	*/
	int ans = 0;
	for (int i = 1; ans == 0; i++) {
		int digits[6][10] = {{0}};
		for (int i1 = 0; i1 < 6; i1++) {
			for (int t_i = i * (i1 + 1); t_i > 0; t_i /= 10) {
				digits[i1][t_i % 10]++;
			}
		}
		bool failed = false;
		for (int i1 = 0; i1 < 5; i1++) {
			for (int i2 = 0; i2 < 10; i2++) {
				if (digits[i1][i2] != digits[i1 + 1][i2])
					failed = true;
			}
		}
		if (!failed)
			ans = i;
	}
	PrintAns(52, ans);
}

void Problem53() {
	/*
	Problem 53
	There are exactly ten ways of selecting three from five, 12345:
	123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
	In combinatorics, we use the notation, 5C3 = 10.
	In general, nCr = n!/(r!(n-r)!), where r <= n, n! = n*(n-1)*...*3*2*1 and 0! = 1.
	It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.

	How many, not necessarily distinct, values of nCr, for 1 <= n <= 100, are greater than one-million?
	*/
	class Calc {
	public:
		static long long Fact(int n) {
			long long ret = 1;
			for (; n > 1; n--)
				ret *= n;
			return ret;
		}

		static long long FactI(int n, int n2) {
			long long ret = 1;
			for (; n > n2; n--)
				ret *= n;
			return ret;
		}
	};
	int ans = 0;
	for (int n = 1; n <= 100; n++) {
		for (int r = 0; r <= n; r++) {
			int max = std::max(r, n - r);
			int min = std::min(r, n - r);
			double val = 1;
			for (int i = 0; i + max + 1 <= n || min - i > 1; i++) {
				if (i + max + 1 <= n)
					val *= (double) (i + max + 1);
				if (min - i > 1)
					val /= (double) (min - i);
			}
			if (val > (double) 1000000)
				ans++;
		}
	}
	PrintAns(53, ans);
}

void Problem56() {
	/*
	Problem 56
	A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost unimaginably large: one followed by two-hundred zeros. Despite their size, the sum of the digits in each number is only 1.

	Considering natural numbers of the form, ab, where a, b < 100, what is the maximum digital sum?
	*/
	int num[3268] = {0};
	int max = -1;
	for (int a = 1; a < 100; a++) {
		for (int b = 1; b < 100; b++) {
			// Setup
			num[0] = 1;
			for (int i = 1; i < 3268; i++)
				num[i] = 0;
			// Compute number and digits
			for (int t_b = 0; t_b < b; t_b++) {
				int t_rem = 0;
				for (int i = 0; i < 3268 && (num[i] > 0 || t_rem > 0); i++) {
					num[i] *= a;
					num[i] += t_rem;
					t_rem = num[i] / 1000;
					num[i] %= 1000;
				}
			}
			// Add up the digits
			int t_sum = 0;
			for (int i = 0; i < 3268; i++) {
				t_sum += num[i] % 10;
				t_sum += num[i] / 10 % 10;
				t_sum += num[i] / 100 % 10;
			}
			if (t_sum > max)
				max = t_sum;
		}
	}
	int ans = max;
	PrintAns(56, ans);
}

void Problem58() {
	/*
	Problem 58
	Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side length 7 is formed.
	37 36 35 34 33 32 31
	38 17 16 15 14 13 30
	39 18  5  4  3 12 29
	40 19  6  1  2 11 28
	41 20  7  8  9 10 27
	42 21 22 23 24 25 26
	43 44 45 46 47 48 49
	It is interesting to note that the odd squares lie along the bottom right diagonal, but what is more interesting is that 8 out of the 13 numbers lying along both diagonals are prime; that is, a ratio of 8/13 = 62%.

	If one complete new layer is wrapped around the spiral above, a square spiral with side length 9 will be formed. If this process is continued, what is the side length of the square spiral for which the ratio of primes along both diagonals first falls below 10%?
	*/
	class Calc {
	public:
		static bool IsPrime(int n) {
			for (int i = 2; i * i <= n; i++)
				if (n % i == 0)
					return false;
			return true;
		}
	};
	int num = 3;
	int den = 5;
	int ans = 0;
	for (int i = 2; num * 10 >= den; i++) {
		int t_n = 2 * i + 1;
		for (int i2 = 0; i2 < 4; i2++) {
			den++;
			if (Calc::IsPrime(t_n * t_n - i2 * i * 2))
				num++;
		}
		ans = i * 2 + 1;
	}
	PrintAns(58, ans);
}

void Problem63() {
	/*
	Problem 63
	The 5-digit number, 16807=7^5, is also a fifth power. Similarly, the 9-digit number, 134217728=8^9, is a ninth power.

	How many n-digit positive integers exist which are also an nth power?
	*/
	int num[50] = {0};
	int count = 0;
	for (int b = 1; b < 10; b++) {
		// Reset the number
		num[0] = 1;
		for (int i = 1; i < 50; i++) {
			num[i] = 0;
		}
		// Raise to the power
		for (int p = 1; ; p++) {
			int t_rem = 0;
			for (int i = 0; i < 49; i++) {
				num[i] *= b;
				num[i] += t_rem;
				t_rem = num[i] / 10;
				num[i] %= 10;
			}
			// Check length
			int t_dig = -1;
			for (int i = 49; i >= 0; i--) {
				if (num[i] > 0) {
					t_dig = i + 1;
					break;
				}
			}
			// Check if valid
			if (t_dig == p) {
				count++;
			} else if (t_dig < p) {
				break;
			}
		}
	}
	int ans = count;
	Print(63);
}

void Problem66() {
	return; // Incomplete: read up on Pell's equations and chakravala method
	/*
	Problem 66
	Consider quadratic Diophantine equations of the form:
	x^2 � Dy^2 = 1
	For example, when D=13, the minimal solution in x is 649^2 � 13 * 180^2 = 1.
	It can be assumed that there are no solutions in positive integers when D is square.
	By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain the following:
	3^2 � 2 * 2^2 = 1
	2^2 � 3 * 1^2 = 1
	9^2 � 5 * 4^2 = 1
	5^2 � 6 * 2^2 = 1
	8^2 � 7 * 3^2 = 1
	Hence, by considering minimal solutions in x for D <= 7, the largest x is obtained when D = 5.

	Find the value of D <= 1000 in minimal solutions of x for which the largest value of x is obtained.
	*/
	class Calc {
	public:
		static long long Sqrt(long long n) {
			/*
			if (n==0) 
				return n;  
			double dividend = n;  
			double val = n;
			double last = 0;
			for (int i = 0; i < 100 && abs(val - last) > 1e-3; i++) {
				last = val;
				val = (val + dividend / val) * 0.5;  
			}
			return (long long) val;
			*/
			/*
			if (n < 2)
				return 1;
			double hi = n / 2;
			long long low = 1;
			long long mid = (hi + low) / 2;
			for (; ; ) {
				mid = (hi + low) / 2;
				if (mid * mid > n)
					hi = mid - 1;
				else if ((mid + 1) * (mid + 1) <= n)
					low = mid + 1;
				else
					return mid;
			}
			*/
			
			for (long long i = 1; ; i++) {
				if (i * i > n)
					return i - 1;
			}
			
		}
	};
	long long max = 0;
	// Stuck at certain numbers
	for (long long d = 2; d <= 1000; d++) {
		printf("%i\n", d);
		if (Calc::Sqrt(d) * Calc::Sqrt(d) == d) {
			continue;
		}
		for (long long x = Calc::Sqrt(d); ; x++) {
			long long y = std::max((long long) 1, (long long) Calc::Sqrt((x * x - 1) / d));
			long long t_r = x * x - d * y * y;
			if (t_r == 1) {
				if (x > max)
					max = x;
				break;
			}
			
			/*
			for (long long y = std::max((long long) 1, Calc::Sqrt(x * x / d)); ; y++) {
				long long t_r = x * x - d * y * y;
				if (t_r == 1) {
					if (x > max)
						max = x;
					goto End;
				}
				else if (t_r < 0)
					break;
			}
			*/
		}
		End:;
	}
	int ans = max;
	Print(66);
}