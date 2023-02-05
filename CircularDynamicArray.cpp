#include <iostream>
#include <string>
using namespace std;

template <typename T>
class CircularDynamicArray
{
    public:
    CircularDynamicArray() //DONE
    {
        array = new T[2];
        aSize = 0;
        aCapacity = 2;
        isReversed = false;
        frontIndex = 0;
        endIndex = 0;
    };

    CircularDynamicArray(int s) //DONE
    {
        array = new T[s];
        aSize = 0;
        aCapacity = s;
        isReversed = false;
        frontIndex = 0;
        endIndex = 0;
    };

    //Copy Constructor
    CircularDynamicArray(const CircularDynamicArray& other)
        :aSize(other.aSize), aCapacity(other.aCapacity) //This makes a shallow copy of the size and capacity.
    {
        
    };

    //Copy Assignment Operator
    CircularDynamicArray& operator=(const CircularDynamicArray& other)
    {
        if (this != &other) {
            T* newArray = new T[other.aCapacity];
            for (int i = 0; i < other.aSize; i++)
            {
                newArray[i] = other.array[i];
            }
            delete[] array;
            array = newArray;
            aSize = other.aSize;
            aCapacity = other.aCapacity;
            isReversed = other.isReversed;
            frontIndex = other.frontIndex;
            endIndex = other.endIndex;
        }
        return *this;
    }


    ~CircularDynamicArray()
    {
        delete[] array;
    };

    T& operator[](int i)
    {
        if((i < 0) || (i >= frontIndex + aSize))
        {
            cout<<"ERROR: ["<<i<<"] is out of bounds for this array. Enter a value between 0 and "<<i+frontIndex<<".\n";
            return returnReferenceValue;
        }
        else
        {
            //return the value at that position in the array.
            return array[frontIndex + i];
        };
    };

    void addEnd(T v)
    {
        if(aSize == aCapacity)
        {
            this->reallocate(aCapacity * 2);
        }
        if(isReversed == false)
        {
            if(aSize == 0)
            {
                array[actualPosition(endIndex)] = v;
                aSize++;
            }else
            {
                array[actualPosition(endIndex + 1)] = v;
                aSize++;
                endIndex = actualPosition(endIndex + 1);
            }
        }else
        if(isReversed == true)
        {
            if(aSize == 0)
            {
                array[actualPosition(endIndex)] = v;
                aSize++;
            }else
            {
                array[actualPosition(endIndex - 1)] = v;
                aSize++;
                endIndex = actualPosition(endIndex - 1);
            }
        };
    };

    void addFront(T v)
    {
        if(aSize == aCapacity)
        {
            this->reallocate(aCapacity * 2);
        }
        if(isReversed == false)
        {
            if(aSize == 0)
            {
                array[actualPosition(frontIndex)] = v;
                aSize++;
            }else
            {
                array[actualPosition(frontIndex - 1)] = v;
                aSize++;
                frontIndex = actualPosition(frontIndex - 1);
            }
        }else
        if(isReversed == true)
        {
            if(aSize == 0)
            {
                array[actualPosition(frontIndex)] = v;
                aSize++;
            }else
            {
                array[actualPosition(frontIndex + 1)] = v;
                aSize++;
                frontIndex = actualPosition(frontIndex + 1);
            }
        }
    };

    void delEnd()
    {
        if(aSize <= (int(aCapacity / 4)))
        {
            this->reallocate(int(aCapacity / 2));
        }
        if(isReversed == false)
        {
            if(aSize != 0)
            {
                endIndex = actualPosition(endIndex - 1);
                aSize--;
            }
        }else
        if(isReversed == true)
        {
            if(aSize != 0)
            {
                endIndex = actualPosition(endIndex + 1);
                aSize--;
            }
        }
    };

    void delFront()
    {
        if(aSize <= (int(aCapacity / 4)))
        {
            this->reallocate(int(aCapacity / 2));
        }
        if(isReversed == false)
        {
            if(aSize != 0)
            {
                frontIndex = actualPosition(frontIndex + 1);
                aSize--;
            }
        }else
        if(isReversed == true)
        {
            if(aSize != 0)
            {
                frontIndex = actualPosition(frontIndex - 1);
                aSize--;
            }
        }
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

    void stableSort()
    {
        T* tempArray = new T[aSize];
        if(isReversed == false)
        {
            int startingIndex = actualPosition(frontIndex);
            for(int i = 0; i < aSize; i++)
            {
                tempArray[i] = array[actualPosition(startingIndex)];
                startingIndex++;
            }
        }else
        if(isReversed == true)
        {
            int startingIndex = actualPosition(frontIndex);
            for(int i = 0; i < aSize; i++)
            {
                tempArray[i] = array[actualPosition(startingIndex)];
                startingIndex--;
            }
        }
        int lowIndex = 0;
        int highIndex = aSize - 1;
        mergeSort(tempArray, lowIndex, highIndex);

        for(int i = 0; i < aSize; i++)
        {
            array[actualPosition(i)] = tempArray[actualPosition(i)];
        }
        if(isReversed == false)
        {
            frontIndex = 0;
            endIndex = actualPosition(aSize - 1);
        }else
        if(isReversed == true)
        {
            frontIndex = actualPosition(aSize - 1);
            endIndex = 0;
        }

        delete[] tempArray;
    };

    void mergeBack(T tempArray[], int lowIndex, int middleIndex, int highIndex)
    {
        int const leftSubArraySize = middleIndex - lowIndex + 1;
        int const rightSubArraySize = highIndex - middleIndex;

        T* leftSubArray = new T[leftSubArraySize];
        T* rightSubArray = new T[rightSubArraySize];

        for(int i = 0; i < leftSubArraySize; i++)
        {
            leftSubArray[i] = tempArray[lowIndex + i];
        }
        for(int i = 0; i < rightSubArraySize; i++)
        {
            rightSubArray[i] = tempArray[middleIndex + 1 + i];
        }

        int leftSubArrayStartingIndex = 0;
        int rightSubArrayStartingIndex = 0;
        int mergedArrayIndex = lowIndex;

        while((leftSubArrayStartingIndex < leftSubArraySize) && (rightSubArrayStartingIndex < rightSubArraySize))
        {
            if(leftSubArray[leftSubArrayStartingIndex] <= rightSubArray[rightSubArrayStartingIndex])
            {
                tempArray[mergedArrayIndex] = leftSubArray[leftSubArrayStartingIndex];
                leftSubArrayStartingIndex++;
            }else
            {
                tempArray[mergedArrayIndex] = rightSubArray[rightSubArrayStartingIndex];
                rightSubArrayStartingIndex++;
            }
            mergedArrayIndex++;
        }

        while(leftSubArrayStartingIndex < leftSubArraySize)
        {
            tempArray[mergedArrayIndex] = leftSubArray[leftSubArrayStartingIndex];
            leftSubArrayStartingIndex++;
            mergedArrayIndex++;
        }

        while(rightSubArrayStartingIndex < rightSubArraySize)
        {
            tempArray[mergedArrayIndex] = rightSubArray[rightSubArrayStartingIndex];
            rightSubArrayStartingIndex++;
            mergedArrayIndex++;
        }

        delete[] leftSubArray;
        delete[] rightSubArray;
    }

    void mergeSort(T tempArray[], int const lowIndex, int const highIndex)
    {
        if(lowIndex >= highIndex)
        {
            return;
        }

        int middleIndex = lowIndex + (highIndex - lowIndex) / 2;
        mergeSort(tempArray, lowIndex, middleIndex);
        mergeSort(tempArray, middleIndex + 1, highIndex);
        mergeBack(tempArray, lowIndex, middleIndex, highIndex);
    }

    int linearSearch(T e)
    {
        bool found = false;
        for(int i = 0; i < aSize; i++)
        {
            if(array[actualPosition(i) == e])
            {
                found = true;
                return actualPosition(i);
            }
        }
        if(found == false)
        {
            return -1;
        }
    };

    int binSearch(T e)
    {
        T* tempArray = new T[aSize];
        if(isReversed == false)
        {
            int startingIndex = actualPosition(frontIndex);
            for(int i = 0; i < aSize; i++)
            {
                tempArray[i] = array[actualPosition(startingIndex)];
                startingIndex++;
            }
        }else
        if(isReversed == true)
        {
            int startingIndex = actualPosition(frontIndex);
            for(int i = 0; i < aSize; i++)
            {
                tempArray[i] = array[actualPosition(startingIndex)];
                startingIndex--;
            }
        }
        int lowIndex = 0;
        int highIndex = aSize - 1;
        int binSearchIndex = splitSearch(e, tempArray, lowIndex, highIndex);
        delete[] tempArray;
        if(binSearchIndex == -1)
        {
            return -1;
        }else
        {
            if(isReversed == false)
            {
                return actualPosition(frontIndex + binSearchIndex);
            }else
            if(isReversed == true)
            {
                return actualPosition(endIndex + binSearchIndex);
            }
        }
        return binSearchIndex;
    };

    int splitSearch(T e, T tempArray[], int lowIndex, int highIndex)
    {
        while(lowIndex <= highIndex)
        {
            int middleIndex = (lowIndex + highIndex) / 2;
            if(tempArray[middleIndex] == e)
            {
                return middleIndex;
            }else
            if(e > tempArray[middleIndex])
            {
                lowIndex = middleIndex + 1;
            }else
            {
                highIndex = middleIndex - 1;
            }
        }
        return -1;
    };

    void reverse()
    {
        if(isReversed == true)
        {
            int tempIndex = frontIndex;
            frontIndex = endIndex;
            endIndex = tempIndex;
            isReversed = false;
        }
        else if(isReversed == false)
        {
            int tempIndex = frontIndex;
            frontIndex = endIndex;
            endIndex = tempIndex;
            isReversed = true;
        };
    };
    
    T at(int i)
    {
        return array[actualPosition(i)];
    };
    
    void print()
    {
        if(isReversed == false)
        {
            int currentIndex = frontIndex;
            for(int i = 0; i < aSize; i++)
            {
                cout<<array[actualPosition(currentIndex)]<<endl;
                currentIndex++;
            }
        }else
        if(isReversed == true)
        {
            int currentIndex = frontIndex;
            for(int i = 0; i < aSize; i++)
            {
                cout<<array[actualPosition(currentIndex)]<<endl;
                currentIndex--;
            }
        }
    };
    
    int fIndex()
    {
        return frontIndex;
    }
    
    int eIndex()
    {
        return endIndex;
    };





    private:
    T* array; //A pointer to the dynamic array.
    int aSize;
    int aCapacity;
    bool isReversed;
    int frontIndex;
    int endIndex;
    T* returnReferenceValue;

    void reallocate(int capacityNeeded) //Takes a parameter of the new capacity needed (provided by the caller). It then allocates a new array of that size, copies all elements over to it, and deletes the old array. DONE
    {
        if(isReversed == false)
        {
            T* newArray = new T[capacityNeeded];
            int currentIndex = frontIndex;
            for(int i = 0; i < aSize; i++)
            {
                newArray[i] = array[actualPosition(currentIndex)];
                currentIndex++;
            }
            delete[] array;
            array = newArray;
            aCapacity = capacityNeeded;
            frontIndex = 0;
            endIndex = aSize - 1;
            isReversed = false;
        }
        if(isReversed == true)
        {
            T* newArray = new T[capacityNeeded];
            int currentIndex = endIndex;
            for(int i = 0; i < aSize; i++)
            {
                newArray[i] = array[actualPosition(currentIndex)];
                currentIndex++;
            }
            delete[] array;
            array = newArray;
            aCapacity = capacityNeeded;
            endIndex = 0;
            frontIndex = aSize - 1;
            isReversed = true;
        }
    };

    int actualPosition(int beforeMod) //DONE
    {
        if(beforeMod < 0)
        {
            beforeMod = beforeMod + aCapacity;
        }
        int actualPosition = beforeMod%aCapacity;
        return actualPosition;
    }
};






































int main()
{
//     CircularDynamicArray<int> myArray;
//     cout<<"Size: "<<myArray.length()<<endl;
//     cout<<"Capacity: "<<myArray.capacity()<<endl;
//     //cout<<" "<<myArray.frontIndex<<" ";
//     //cout<<" "<<myArray.endIndex<<" ";
//     //myArray.reverse();
//     myArray.addEnd(1);
//     myArray.addEnd(2);
//     myArray.addEnd(3);
//     //myArray.delEnd();
//     //myArray.reverse();
//     myArray.addFront(0);
//     myArray.addFront(-1);
//     //myArray.reverse();
//     //myArray.addFront(-2);
//     myArray.reverse();
//     myArray.addEnd(7);
//     myArray.addEnd(8);
//     myArray.delEnd();
// //    myArray.addEnd(9);
// //    myArray.addEnd(10);
// //    myArray.addEnd(11);
// //    myArray.addEnd(12);
//     cout<<"Size2: "<<myArray.length()<<endl;
//     cout<<"Capacity2: "<<myArray.capacity()<<endl;
//     //myArray.reverse();
//     cout<<"F: "<<myArray.fIndex()<<" ";
//     cout<<"E: "<<myArray.eIndex()<<" ";
//     //myArray.reverse();
//     cout<<endl<<endl;
//     for(int i = 0; i < 8; i++)
//     {
//         cout<<i<<": "<<myArray.at(i)<<endl;
//     }
//     cout<<endl<<endl;
//     cout<<"Like the user sees it: "<<endl;
//     myArray.print();
// //    int currentIndex = myArray.frontIndex;
// //    for(int i = 0; i < myArray.aSize; i++)
// //    {
// //        cout<<myArray.at(currentIndex)<<endl;
// //        currentIndex++;
// //    }
//     return 0;







    CircularDynamicArray<int> myArray;
    myArray.addEnd(3);
    myArray.addEnd(-1);
    myArray.addEnd(7);
    myArray.addEnd(5);
    myArray.addEnd(23);
    myArray.addEnd(46);
    //myArray.addFront(0);
    //myArray.addFront(-13);
    myArray.reverse();
    myArray.stableSort();
    //cout<<"POSITION::: "<<myArray.binSearch(46)<<endl;

    cout<<"F: "<<myArray.fIndex()<<" ";
    cout<<"E: "<<myArray.eIndex()<<" ";

    cout<<endl<<endl;
    for(int i = 0; i < 8; i++)
    {
        cout<<i<<": "<<myArray.at(i)<<endl;
    }

    cout<<endl<<"Like the user sees it: "<<endl;
    myArray.print();
    return 0;
}





