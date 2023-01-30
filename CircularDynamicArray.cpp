#include <iostream>
#include <string>
using namespace std;

template <typename T>
class CircularDynamicArray
{
    public:

    T* array; //A pointer to the dynamic array.
    int aSize;
    int aCapacity;
    bool reverse;
    int frontIndex;
    int endIndex;

    CircularDynamicArray() //DONE
    {
        array = new T[2];
        aSize = 0;
        aCapacity = 2;
        reverse = false;
        frontIndex = 0;
        endIndex = 0;
    };

    CircularDynamicArray(int s) //DONE
    {
        array = new T[s];
        aSize = 0;
        aCapacity = s;
        reverse = false;
    };

    //Copy Constructor
    CircularDynamicArray(const CircularDynamicArray& other)
        :aSize(other.aSize), aCapacity(other.aCapacity) //This makes a shallow copy of the size and capacity.
    {

    };

    //Copy Assignment Operator


    ~CircularDynamicArray()
    {

    };

    T& operator[](/*int i*/)
    {

    };

    void addEnd(/*T v*/)
    {

    };

    void addFront(/*T v*/)
    {

    };

    void delEnd()
    {

    };

    void delFront()
    {

    };

    int length() //DONE
    {
        return aSize;
    };

    int capacity() //DONE
    {
        return aCapacity;
    };

    void clear() //DONE
    {
        delete[] array;
        T* array = new T[2];
        aSize = 0;
        aCapacity = 2;
    };

    T QuickSelect(/*int k*/)
    {

    };

    T WCSelect(/*int k*/)
    {

    };

    void stableSort()
    {

    };

    int linearSearch(/*T e*/)
    {

    };

    int binSearch(/*T e*/)
    {

    };

    void reverse()
    {
        if(reverse == true)
        {
            reverse = false;
        };
        else if(reverse == false)
        {
            reverse = true;
        };
    };





    private:

    void reallocate(int newCapacity) //Takes a parameter of the new capacity needed (provided by the caller). It then allocates a new array of that size, copies all elements over to it, and deletes the old array.
    {
        T* newArray = new T[newCapacity];
        if(newCapacity < aCapacity)
        {
            aSize = newCapacity;
        }
        for(int i = 0; i < aCapacity; i++)
        {
            newArray[i] = array[i];
            delete array[];                 //REWORK THIS WHOLE THING TO MAKE IT CIRCULAR!!!
            array = newArray;
            aCapacity = newCapacity;
        }
        
    };

    int actualPosition(int beforeMod)
    {
        int actualPosition = beforeMod%aCapacity;
        return actualPosition;
    }
};






































int main()
{
    return 0;
}