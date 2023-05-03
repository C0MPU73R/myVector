/*
@filenaname: myVector.hpp
@author: C0MPU73R
*/
#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>
using namespace std;
template <class C>
class myVector
{
public:
	myVector(int size = 0)
	{
		mVSize = size; //Create the initial size to be zero, this will be modified as elements are added and removed
		dyn_array = new C[mVSize]; //Create the dynamic array
	}
	myVector(const myVector& rhs) //Parameterized constructor for a given rhs input of a myVector object that does not modify it, but 
		// merely prepares it for a deep copy operation
	{
		deepCopy(rhs); //this will make a deep copy
	}
	~myVector() // destruction, properly clean up any allocated memory on the heap that was used for objects created in the vector (dynamic array)
	{
		delete[] dyn_array; //delete all allocated memory
		mVSize = 0; // Then reset the size of the vector to zero
	}
	myVector operator=(const myVector& rhs) // Overloaded assignment operator. If myVector equals another myVector, go ahead and delete our current locations, deep copy the myVector
		// that is passed in, then go ahead and return the instance of *this, being the new myVector itself that was created in the deep copy and copied
		// over all of the data that the rhs myVector had
	{
		delete[] dyn_array;
		deepCopy(rhs);
		return *this;
	}
	C& operator[](int idx) // template type so that myVector can indeed be of any type, holding those specfic types of objects. They can even primitive data types such as ints, etc.
	{
		if (idx >= 0 && idx < mVSize) //Make sure that the index is in a valid range. We want to start at 0  and end at n, similar to that of an array or a sequence type.
		{
			return dyn_array[idx]; // Return the object of type template at the specific index that the user wanted.
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
		this->dyn_array = new C[mVSize]; // create a brand new blank collection, of the new size that we need
		for (int idx = 0; idx < mVSize - 1; ++idx)
		{
			dyn_array[idx] = rhs.dyn_array[idx]; //fill vector besides new element. (Copy over all of the old elements from the rhs, keeping in mind not to yet fill
			// the last location as this is the one that is for the new element.
		}
		//there should now be one space left for new added element.
		dyn_array[mVSize - 1] = element;// go ahead and put that element in the last space in the dynamic array.
	}
	void printMyVector() const // Printing functionality for the myVector. This will print all of the elements in the dynamic array. If they are not primitive types, the information of the object will be printed.
	{
		for (int idx = 0; idx < mVSize; ++idx)
		{
			cout << dyn_array[idx] << endl;
		}
	}
private:
	int mVSize; // size of the dynamic array, type int.
	C* dyn_array = nullptr; // locations pointer of type template C, which will be used to create new template objects. Initially set it to nullptr upon creation.
	void deepCopy(const myVector& rhs) // The deep copy function. This is private due to its functionally being used by the API functions above. The overloaded assignment operator makes use of this the programmer can use at will.
	{
		mVSize = rhs.mVSize; // Take a const ref parameter of rhs, copy over rhs' current size.
		dyn_array = new C[mVSize]; // Create a new locations object of type C that will act as the dynamic array. TODO: Probably a bad name for this.
		for (int idx = 0; idx < mVSize; idx++)
		{
			this->dyn_array[idx] = rhs.dyn_array[idx]; // go ahead and copy over the the data from the rhs. This new dynamic array has the exact same size as the rhs, hence no indexing issues.
		}
	} // we now have a brand new dynamic array, with no shallow copies whatsoever, hence making use of this new myVector will not affect the rhs myVector that was passed in. They are completely differemt collections.
};
#endif