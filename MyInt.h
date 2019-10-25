#ifndef WIEWEL_MY_INT
#define WIEWEL_MY_INT
#include <iostream>

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
			std::cout << "\nInvalid location of " << i;
			return garbage;
		}
	}
	MyInt& operator=(int b);
	MyInt& operator=(const MyInt& b);
	MyInt operator+(const MyInt& b) const; //assummes both MyInts have same nDigits
};

#endif
