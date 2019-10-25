#include <iostream>
#include <vector>
#include "MyInt.h"
using namespace std;

MyInt MyIntFib(int n, int size);
MyInt MyIntFibHelper(int n, int size, vector<MyInt>& results);
long long LongLongFib(int n);
long long LongLongFibHelper(int n, vector<long long>& results);

int main(int argc, char* argv[])
{
	
	int size, input;
	cout << "\nHow many digits do you want for your fib number?\n> ";
	cin >> size;
	
	MyInt miFib(size); //my int fibonacci
	long long biFib = 0L; //built-in fibonacci
	
	bool go = true;
	
	while(go)
	{
	
		cout << "\nWhich fibonacchi number do you want? (enter -1 to quit) ";
		cin >> input;
		
		if(input > -1 ) //valid fibonacci number
		{
			//calculate the fibbonaccis
			miFib = MyIntFib(input, size);
			biFib = LongLongFib(input);
			
			cout << "\nHere is the fibonacci: ";
			miFib.printFancy();
			cout << "\n\nAs compared to: " << biFib;
		}
		else //user wishes to quit
		{
			go = false;
		}
	}
}

MyInt MyIntFib(int n, int size)
{
	//vector for memoizing fibonacci results
	static vector<MyInt> results;
	
	//get the base cases of the fibonacci sequence taken care of
	//only when the vector is empty
	if(results.size() < 1)
	{
		MyInt calc(size);
		calc = 0;
		results.push_back(calc);
		calc = 1;
		results.push_back(calc);
	}
	
	//calculate and return the result
	return MyIntFibHelper(n, size, results);
}
MyInt MyIntFibHelper(int n, int size, vector<MyInt>& results)
{
	//if we have calculated this before, return the result
	if( n < results.size() )
		return results[n];
	
	MyInt calc(size); //used to calculate the result
	
	//calculate the fibonacci number
	//no base cases in this function as they are implicitly
	//dealt with in the wrapper function
	calc = MyIntFibHelper(n-2, size, results) + 
	MyIntFibHelper(n-1, size, results);
	
	results.push_back(calc); //memoize the result
	
	//now that we have the calculation, return the result
	return calc;
}
//these two functions use the exact same logic as the ones with MyInt.
long long LongLongFib(int n)
{
	static vector<long long> results;
	
	if(results.size() < 1)
	{
		results.push_back(0L);
		results.push_back(1L);
	}
	
	return LongLongFibHelper(n, results);
}
long long LongLongFibHelper(int n, vector<long long>& results)
{
	if(n < results.size())
		return results[n];
	
	long long calc = 0L;
	
	calc = LongLongFibHelper(n-2, results) + 
	LongLongFibHelper(n-1, results);
	
	results.push_back(calc);
	
	return calc;
}
