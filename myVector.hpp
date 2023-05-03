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
			return locations[idx]; // Return the object of type template at the specific index that the user wanted.
		}
		else
		{
			throw std::out_of_range("Index out of range"); // Else, you are trying to return an element that is out of the scope, throw an error to the user

		}
	}
	int myVecSize() const // constant return, as we call this function to see what our current size is, we need not to modify it. That will be done as we add and remove objects from the collection
	{
		return mVSize;
	}
	//create pop
	void push(C element) //Create a "push" like function to add elements to the myVector of type template 'C'.
	{
		if (mVSize == 0) // if the size of the myVector is zero, this push is actually the first push, hence the size was originally zero, now it is one.
		{
			this->mVSize = 1;
		}
		else // else, the collection already had a size of greater than zero, hence go ahead and increase the size by one.
		{
			this->mVSize++;
		}
		myVector rhs = *this; // go ahead and create a myVector, call it rhs. Let it use the overloaded assignment operator that we created earlier to copy over the 'lhs' or current myVector. 
		// This assignment operator may look normal, but there is a lot going on behind the scene, this overloaded operator is making use of the overloaded operator
		// function, which in turn uses the deep copy function.
		this->locations = new C[mVSize]; // create a brand new blank collection, of the new size that we need
		for (int idx = 0; idx < mVSize - 1; ++idx)
		{
			locations[idx] = rhs.locations[idx]; //fill vector besides new element. (Copy over all of the old elements from the rhs, keeping in mind not to yet fill
			// the last location as this is the one that is for the new element.
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