#include "MyInt.h"

//prints entire array without formatting
void MyInt::printSimple() const
{
	//give right sign in front
	if(sign == negative)
		std::cout << "-";
	
	//start with highest power and print out the digits of the number
	for( int i = nDigits-1; i > -1; i--)
	{ std::cout << arr[i]; }			
}
//print only non-zero digits (excepting case where value is 0)
//and add in commas
void MyInt::printFancy() const
{
	//take care of sign printing
	if(sign == negative)
		std::cout << "-";
	
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
			std::cout << arr[i]; //put out the digit 
			//put a comma to separate categories like hundreds, thousands..
			if( i % 3 == 0 && i != 0)
			{
				std::cout << ",";
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
		std::cout << "\nThere was overflow.";
	
	return result;
}
