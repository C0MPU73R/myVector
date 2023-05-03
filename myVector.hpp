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
	~myVector()
	{
		delete[] locations; //delete all allocated memory
		mVSize = 0;
	}
	myVector operator=(const myVector& rhs)
	{
		delete[] locations;
		deepCopy(rhs);
		return *this;
	}
	C& operator[](int idx)
	{
		if (idx >= 0 && idx < mVSize) //check if in range
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