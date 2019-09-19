#include <iostream>
#include <vector>

using namespace std;

const bool positive = true;
const bool negative = false;

class MyInt
{
private: 
	
	short* arr; //array to hold digits of the number
	int nDigits;//value keep track of how many digits the number has
	bool sign; //boolean to keep track if number is positive or negative
	
	//deallocates dynamic memory
	void destroy()
	{
		delete[] arr;
	}
	//sets all indices of array to 0
	void initializeArray()
	{
		for(int i = 0; i < nDigits; i++)
			arr[i] = 0;
	}

public:
	
	MyInt() //default constructor
		:arr(new short[100]), nDigits(100), sign(positive)
	{ initializeArray(); }
	MyInt(int nD) //constructor to manually set number of digits
		:arr(new short[nD]), nDigits(nD), sign(positive)
	{ initializeArray(); }
	MyInt(const MyInt& b) //copy constructor
		:arr(new short[b.getNDigits()]), nDigits(b.getNDigits()), sign(b.getSign())
	{ 
		//copy over the array from the copied MyInt into this object's array
		for(int i = 0; i < nDigits; i++)
			arr[i] = b[i];
	}
	~MyInt() //destructor
	{ destroy(); }
	
	int getNDigits() const
	{ return nDigits; }
	bool getSign() const
	{ return sign; }
	
	void reset()
	{
		sign = positive; //positive sign
		initializeArray();
	}
	//prints entire array without formatting
	void printSimple() const;
	//print only non-zero digits (excepting case where value is 0)
	//and add in commas
	void printFancy() const;
	
	short operator[](const int i) const
	{
		if( i >= 0 && i < nDigits ) //i is in range
			return arr[i];
		else
			return -1; //error
	}
	short& operator[](const int i)
	{
		static short garbage;
		if( i >= 0 && i < nDigits )
			return arr[i];
		else
		{
			cout << "\nInvalid location of " << i;
			return garbage;
		}
	}
	MyInt& operator=(int b);
	MyInt& operator=(const MyInt& b);
	MyInt operator+(const MyInt& b) const; //assummes both MyInts have same nDigits
};

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

//prints entire array without formatting
void MyInt::printSimple() const
{
	//give right sign in front
	if(sign == negative)
		cout << "-";
	
	//start with highest power and print out the digits of the number
	for( int i = nDigits-1; i > -1; i--)
	{ cout << arr[i]; }			
}
//print only non-zero digits (excepting case where value is 0)
//and add in commas
void MyInt::printFancy() const
{
	//take care of sign printing
	if(sign == negative)
		cout << "-";
	
	bool printDig = false;
	
	//start at the end of the array so that we
	//print the highest powers first and works our
	//way down to the 1s place
	for( int i = nDigits - 1; i > -1; i--)
	{
		if(!printDig) //haven't come up with a digit to print yet
		{
			
			//we are either at our first non-zero value or the last index
			//of the array so we start printing the values
			if( arr[i] != 0 || i == 0 )
				printDig = true;
		}
		
		if(printDig)
		{
			cout << arr[i]; //put out the digit 
			//put a comma to separate categories like hundreds, thousands..
			if( i % 3 == 0 && i != 0)
			{
				cout << ",";
			}
		}
	}
}
MyInt& MyInt::operator=(int b)
{
	//clear out the array first.
	reset(); 
	
	int i = 0;
	bool keepAdding = true;
	
	while(keepAdding)
	{
		arr[i] = b % 10; //get single digit
		b /= 10; //go down to next digit
		i++; //be ready to do next position
		if( b == 0 ) //no more digits to add
			keepAdding = false;
	}
	
	return *this;
}
MyInt& MyInt::operator=(const MyInt& b)
{
	//avoid self-assignment
	if(this != &b)
	{
		reset(); //clear previous info
		
		if( b.getNDigits() > nDigits ) //equalling a larger number
		{
			//resize array
			destroy();
			nDigits = b.getNDigits();
			arr = new short[nDigits];
		}
		
		sign = b.getSign(); //set sign
		
		//copy numbers over
		
		int bNDigits = b.getNDigits(); //get number of digits in b
		for(int i = 0; i < bNDigits; i++)
		{
			arr[i] = b[i];
		}
	}
	
	return *this;
}
//this operator assumes both MyInts have the same number of digits
MyInt MyInt::operator+(const MyInt& b) const
{
	MyInt result(nDigits);
	short carry = 0; //used for carry
	short val;
	
	for(int i = 0; i < nDigits; i++)
	{
		val = carry + arr[i] + b[i]; //create a value for this index
		carry = val / 10; //we only want the 1's digit. An overflow goes to the next power
		result[i] = val % 10; //put value of 1's place digit into array
	}
	
	//let user know if addition is inaccurate due to overflow
	if( carry != 0 )
		cout << "\nThere was overflow.";
	
	return result;
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
