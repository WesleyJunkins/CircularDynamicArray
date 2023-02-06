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
        aSize = s;
        aCapacity = s;
        isReversed = false;
        frontIndex = 0;
        endIndex = s - 1;
    };

    //Copy Constructor
    CircularDynamicArray(const CircularDynamicArray& other)
    {
        array = new T[other.aCapacity];
        for(int i = 0; i < other.aCapacity; i++)
        {
            array[i] = other.array[i];
        }
        aSize = other.aSize;
        aCapacity = other.aCapacity;
        isReversed = other.isReversed;
        frontIndex = other.frontIndex;
        endIndex = other.endIndex;
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
    };

    ~CircularDynamicArray()
    {
        delete[] array;
    };

    T& operator[](int i)
    {
        if((i < 0) || (i > aSize - 1))
        {
            cout<<"ERROR: ["<<i<<"] is out of bounds for this array. Enter a value between 0 and "<<aSize - 1<<".\n";
            return returnReferenceValue;
        }
        else
        {
            if(isReversed == false)
            {
                return array[actualPosition(frontIndex + i)];
            }else
            {
                return array[actualPosition(frontIndex - i)];
            }
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
        array = new T[2];
        aSize = 0;
        aCapacity = 2;
    };

    T QuickSelect(int k)
    {
        T* tempArray = new T[aSize];
        int tempArraySize = 0;
        if(isReversed == false)
        {
            int startingIndex = actualPosition(frontIndex);
            for(int i = 0; i < aSize; i++)
            {
                tempArray[i] = array[actualPosition(startingIndex)];
                tempArraySize++;
                startingIndex++;
            }
        }else
        if(isReversed == true)
        {
            int startingIndex = actualPosition(frontIndex);
            for(int i = 0; i < aSize; i++)
            {
                tempArray[i] = array[actualPosition(startingIndex)];
                tempArraySize++;
                startingIndex--;
            }
        }

        T finalResult = select(tempArray, tempArraySize, k);
        delete[] tempArray;
        return finalResult;
    };

    T select(T tempArray[], int tempArraySize, int k)
    {
        int randomIndex = rand() % tempArraySize;
        T pivot = tempArray[randomIndex];
        T* L = new T[tempArraySize];
        T* E = new T[tempArraySize];
        T* G = new T[tempArraySize];
        int Lindex = 0;
        int Eindex = 0;
        int Gindex = 0;
        int Lsize = 0;
        int Esize = 0;
        int Gsize = 0;
        for(int i = 0; i < tempArraySize; i++)
        {
            if(tempArray[i] < pivot)
            {
                L[Lindex] = tempArray[i];
                Lindex++;
                Lsize++;
            }else
            if(tempArray[i] == pivot)
            {
                E[Eindex] = tempArray[i];
                Eindex++;
                Esize++;
            }else
            {
                G[Gindex] = tempArray[i];
                Gindex++;
                Gsize++;
            }
        }

        T recursiveResult;
        if(k <= Lsize)
        {
            recursiveResult = select(L, Lsize, k);
            delete[] L;
            delete[] E;
            delete[] G;
            return recursiveResult;
        }else
        if(k <= Lsize + Esize)
        {
            delete[] L;
            delete[] E;
            delete[] G;
            return pivot;
        }else
        {
            recursiveResult = select(G, Gsize, k - Lsize - Esize);
            delete[] L;
            delete[] E;
            delete[] G;
            return recursiveResult;
        }
    };

    void stableSort()
    {
        //When copying the SORTED array back into the original array, there are still values from the UNSORTED, UNWRAPPED array inside the array. These shouldn't be a problem since the user will not see this. These leftover elements will never be seen by the user since the user only sees from the front index to the back index.
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
        for(int i = 0; i < aSize; i++)
        {
            if(array[actualPosition(i)] == e)
            {
                return actualPosition(i);
            }
        }
        return -1;
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
    T returnReferenceValue;

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






































// int main()
// {
// //     CircularDynamicArray<int> myArray;
// //     cout<<"Size: "<<myArray.length()<<endl;
// //     cout<<"Capacity: "<<myArray.capacity()<<endl;
// //     //cout<<" "<<myArray.frontIndex<<" ";
// //     //cout<<" "<<myArray.endIndex<<" ";
// //     //myArray.reverse();
// //     myArray.addEnd(1);
// //     myArray.addEnd(2);
// //     myArray.addEnd(3);
// //     //myArray.delEnd();
// //     //myArray.reverse();
// //     myArray.addFront(0);
// //     myArray.addFront(-1);
// //     //myArray.reverse();
// //     //myArray.addFront(-2);
// //     myArray.reverse();
// //     myArray.addEnd(7);
// //     myArray.addEnd(8);
// //     myArray.delEnd();
// // //    myArray.addEnd(9);
// // //    myArray.addEnd(10);
// // //    myArray.addEnd(11);
// // //    myArray.addEnd(12);
// //     cout<<"Size2: "<<myArray.length()<<endl;
// //     cout<<"Capacity2: "<<myArray.capacity()<<endl;
// //     //myArray.reverse();
// //     cout<<"F: "<<myArray.fIndex()<<" ";
// //     cout<<"E: "<<myArray.eIndex()<<" ";
// //     //myArray.reverse();
// //     cout<<endl<<endl;
// //     for(int i = 0; i < 8; i++)
// //     {
// //         cout<<i<<": "<<myArray.at(i)<<endl;
// //     }
// //     cout<<endl<<endl;
// //     cout<<"Like the user sees it: "<<endl;
// //     myArray.print();
// // //    int currentIndex = myArray.frontIndex;
// // //    for(int i = 0; i < myArray.aSize; i++)
// // //    {
// // //        cout<<myArray.at(currentIndex)<<endl;
// // //        currentIndex++;
// // //    }
// //     return 0;







//     CircularDynamicArray<int> myArray;
//     myArray.addEnd(3);
//     myArray.addEnd(-1);
//     myArray.addEnd(7);
//     myArray.addEnd(5);
//     myArray.addEnd(23);
//     myArray.addEnd(46);
//     myArray.addFront(444);
//     //myArray.addFront(0);
//     //myArray.addFront(-13);
//     //myArray.reverse();
//     myArray.stableSort();
//     cout<<"FOUND"<<myArray.binSearch(5)<<endl;
//     cout<<"LinearSearchFound: "<<myArray.linearSearch(23)<<endl;
//     //cout<<"POSITION::: "<<myArray.binSearch(46)<<endl;

//     cout<<"F: "<<myArray.fIndex()<<" ";
//     cout<<"E: "<<myArray.eIndex()<<" ";

//     cout<<endl<<endl;
//     for(int i = 0; i < 8; i++)
//     {
//         cout<<i<<": "<<myArray.at(i)<<endl;
//     }

//     cout<<endl<<"Like the user sees it: "<<endl;
//     myArray.print();
//     return 0;
// }






















































void foo(CircularDynamicArray<int> x) {
	for (int i=0; i<x.length()/2; i++)
		x[i] = x[x.length()/2+i];
	// X => "6 7 8 9 10 15 19 6 7 8 9 10 15 19 11"
	for (int i=0; i< x.length();i++) cout << x[i] << " ";  cout << endl;
}

int main(){
	CircularDynamicArray<float> C(10);
    //cout<<"Length(size): "<<C.length()<<endl;
    //cout<<"Capacity: "<<C.capacity()<<endl;
	for (int i=0; i< C.length();i++) C[i] = i;
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// // C => "0 1 2 3 4 5 6 7 8 9"
	C.delFront();
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// // C => "1 2 3 4 5 6 7 8 9"
	C.delEnd();
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// // C => "1 2 3 4 5 6 7 8"
	C.addEnd(100.0);
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
    //cout<<"FRONTindex: "<<C.fIndex()<<endl;
    //cout<<"ENDindex: "<<C.eIndex()<<endl;
	// // C => "1 2 3 4 5 6 7 8 100"
	C.delFront();
	C.addEnd(200.0);
    for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// // C => "2 3 4 5 6 7 8 100 200"	

	C.addEnd(300.0);
	C.addEnd(400.0);
    for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// // C => "2 3 4 5 6 7 8 100 200 300 400"	
	
	C.reverse();
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// // C => "400 300 200 100 8 7 6 5 4 3 2"	
	
	C.delFront(); C.delFront();C.delEnd();
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// // C => "200 100 8 7 6 5 4 3"	

	C.reverse();
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// // C => "3 4 5 6 7 8 100 200"		

	// CircularDynamicArray<int> A,B;
	// for(int i=0; i<10;i++) A.addEnd(i);
	// B = A;
	// A.addEnd(15); A.addEnd(19);
	// // A => "0 1 2 3 4 5 6 7 8 9 15 19" 
	// cout << "Select is " << A.linearSearch(5) << endl;
	// // A => "0 1 2 3 4 5 6 7 8 9 15 19" Search => 5
	// cout << "Select is " << A.binSearch(12) << endl;
	// // A => "0 1 2 3 4 5 6 7 8 9 15 19" Search => -1
	// cout << "Select is " << A.binSearch(15) << endl;
	// // A => "0 1 2 3 4 5 6 7 8 9 15 19" Search => 10	
	// A.addFront(10); 
	// // A => "10 0 1 2 3 4 5 6 7 8 9 15 19"
	// cout << "Select is " << A.linearSearch(5) << endl;
	// // A => "10 0 1 2 3 4 5 6 7 8 9 15 19" Search => 6
	// cout << "Select is " << A.QuickSelect(3) << endl;
    // // Select => 2	
	// //	cout << "Select is " << A.WCSelect(12) << endl;
	// // Select => 15
	// A.stableSort();
	// // A => "0 1 2 3 4 5 6 7 8 9 10 15 19"
	// A.addEnd(11); A.addFront(1); A.addFront(2); A.addFront(3);
	// cout << "capacity is " << A.capacity() << endl;
	// // A => "3 2 1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"	  capacity => 32
	// A.delFront(); A.delFront();
	// // A => "1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"	  capacity => 32

	// foo(A);
	// for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;
	// // A => "1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"
	// for (int i=0; i< B.length();i++) cout << B[i] << " ";  cout << endl;
	// // B => "0 1 2 3 4 5 6 7 8 9"

    return 0;
}