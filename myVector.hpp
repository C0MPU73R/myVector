/*
@filenaname: myVector.hpp
@author: C0MPU73R
*/
#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>
using namespace std;
template <typename C>
class myVector
{
public:
	myVector(int size = 0)
	{
		mVSize = size; //Create the initial size to be zero, this will be modified as elements are added and removed
		locations = new C[mVSize]; //Create the dynamic array
	}
	myVector(const myVector& rhs) //Parameterized constructor for a given rhs input of a myVector object that does not modify it, but 
		// merely prepares it for a deep copy operation
	{
		deepCopy(rhs); //this will make a deep copy
	}
	~myVector() // destruction, properly clean up any allocated memory on the heap that was used for objects created in the vector (dynamic array)
	{
		delete[] locations; //delete all allocated memory
		mVSize = 0; // Then reset the size of the vector to zero
	}
	myVector operator=(const myVector& rhs) // Overloaded assignment operator. If myVector equals another myVector, go ahead and delete our current locations, deep copy the myVector
		// that is passed in, then go ahead and return the instance of *this, being the new myVector itself that was created in the deep copy and copied
		// over all of the data that the rhs myVector had
	{
		delete[] locations;
		deepCopy(rhs);
		return *this;
	}
	C& operator[](int idx) // template type so that myVector can indeed be of any type, holding those specfic types of objects. They can even primitive data types such as ints, etc.
	{
		if (idx >= 0 && idx < mVSize) //Make sure that the index is in a valid range. We want to start at 0  and end at n, similar to that of an array or a sequence type.
		{
			return locations[idx];
		}
		else
		{
			throw std::out_of_range("Index out of range");
		}
	}
	int myVecSize() const
	{
		return mVSize;
	}
	//create pop
	void push(C element)
	{
		if (mVSize == 0)
		{
			this->mVSize = 1;
		}
		else
		{
			this->mVSize++;
		}
		myVector rhs = *this;
		this->locations = new C[mVSize];
		for (int idx = 0; idx < mVSize - 1; ++idx)
		{
			locations[idx] = rhs.locations[idx]; //fill vector besides new element.
		}
		//there should now be one space left for new added element.
		locations[mVSize - 1] = element;
	}
	void printMyVector() const
	{
		for (int idx = 0; idx < mVSize; ++idx)
		{
			cout << locations[idx] << endl;
		}
	}
private:
	int mVSize;
	C* locations = nullptr;
	void deepCopy(const myVector& rhs)
	{
		mVSize = rhs.mVSize;
		locations = new C[mVSize];
		for (int idx = 0; idx < mVSize; idx++)
		{
			this->locations[idx] = rhs.locations[idx];
		}
	}
};
#endif