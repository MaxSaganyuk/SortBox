#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "sortbox.h"

template <typename T>
SortBox<T>::SortBox() {
    begin = nullptr;
    end = nullptr;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(0));
}

template <typename T>
SortBox<T>::~SortBox() {

}

template <typename T>
clock_t SortBox<T>::sortInit(T* inp, int size) {
    begin = inp;
    end = inp + size;
    clock_t time;
    time = clock();

    return time;
}

template <typename T>
void SortBox<T>::showArr(T* current) {
    for (T* ptr = begin; ptr != end; ++ptr) {
        if (current == ptr || current + 1 == ptr) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        else SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        
        std::cout << *ptr << ' ';
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

template<typename T>
void SortBox<T>::showArr(T* current1, T* current2) {
    for (T* ptr = begin; ptr != end; ++ptr) {
        if (current1 == ptr || current2 == ptr) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        else SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

        std::cout << *ptr << ' ';
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

template <typename T>
inline bool SortBox<T>::compare(T* ptr, bool inverse) {
    return (inverse ? (*ptr < *(ptr + 1)) : (*ptr > *(ptr + 1)));
}

template <typename T>
inline bool SortBox<T>::compare(T* ptr1, T* ptr2, bool inverse) {
    return (inverse ? (*ptr1 < *ptr2) : (*ptr1 > *ptr2));
}

template <typename T>
bool SortBox<T>::checkIfSorted(bool inverse) {
    bool done = true;
    for (T* ptr = begin; ptr != (end - 1); ++ptr) {
        if (compare(ptr, inverse)) {
            done = false;
            break;
        }
    }

    return done;
}

template <typename T>
inline void SortBox<T>::swap(T* ptr) {
    mem = *ptr;
    *ptr = *(ptr + 1);
    *(ptr + 1) = mem;
}

template <typename T>
inline void SortBox<T>::swap(T* ptr1, T* ptr2) {
    mem = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = mem;
}

/*
template <typename T>
inline void SortBox<T>::putIn(T* ptr1, T* ptr2, const int size) {

}
*/


template <typename T>
void SortBox<T>::bubble(T* inp, const int size, bool inverse) {

    clock_t time = sortInit(inp, size);

    bool done = false;

    while (!checkIfSorted(inverse)) {
        for (T* ptr = begin; ptr != (end - 1); ++ptr) {
            if (boolShowProc) showArr(ptr);

            if (compare(ptr, inverse)) swap(ptr);

            if (boolShowProc) {
                std::cout << "| ";
                showArr(ptr);
                std::cout << '\n';
            }
        }
    }

    std::cout << "Sorting took " << (long double)(time) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

template <typename T>
void SortBox<T>::cocktail(T* inp, const int size, bool inverse) {
    
    clock_t time = sortInit(inp, size);

    int beginD = 0;
    int endD = 0;

    bool done = false;
    int type;

    while (!checkIfSorted(inverse)) {
        type = 0;
        for (T* ptr = begin + beginD; type != 2;) {
            if (boolShowProc) showArr(ptr);

            if (compare(ptr, inverse)) swap(ptr);

            if (boolShowProc) {
                std::cout << "| ";
                showArr(ptr);
                std::cout << '\n';
            }
            
            if (type == 0) {
                ++ptr;
                if (ptr == end - 1 - endD) {
                    type = 1;
                    --ptr;
                }
            }
            else if (type == 1) {
                if (ptr == begin + beginD) {
                    type = 2;
                    ++beginD;
                    ++endD;
                }
                --ptr;
            }
        }
        if(beginD > endD) break;
    }
    std::cout << "Sorting took " << (long double)(time) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

template <typename T>
int SortBox<T>::quickPart(T* inp, int lowPoint, int highPoint, bool inverse) {
    T* pivot = begin + highPoint;

    int i = lowPoint - 1;

    for (T* ptr = begin + lowPoint; ptr != begin + highPoint; ++ptr) {
        if (compare(pivot, ptr, inverse)) {
            ++i;
            if (boolShowProc) showArr(begin + i, ptr);
            swap(ptr, begin + i);
            if (boolShowProc) {
                std::cout << "| ";
                showArr(begin + i, ptr);
                std::cout << '\n';
            }
        }
    }
    swap(begin + i + 1, begin + highPoint);

    return (i + 1);

}

template <typename T>
void SortBox<T>::quickSort(T* inp, int lowPoint, int highPoint, bool inverse) {
    if (lowPoint < highPoint) {
        int part = quickPart(inp, lowPoint, highPoint, inverse);

        quickSort(inp, lowPoint, part - 1, inverse);
        quickSort(inp, part + 1, highPoint, inverse);
    }
}

template <typename T>
void SortBox<T>::quick(T* inp, const int size, bool inverse) {

    clock_t time = sortInit(inp, size);

    quickSort(inp, 0, size - 1, inverse);

    std::cout << "Sorting took " << (long double)(time) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

template <typename T>
void SortBox<T>::insertion(T* inp, const int size, bool inverse) {

    clock_t time = sortInit(inp, size);

    for (T* ptr = begin + 1; ptr != end - 1; ++ptr) {
        if (boolShowProc) showArr(ptr);

        if (compare(ptr, inverse)) {
            swap(ptr);

            if (boolShowProc) {
                std::cout << "| ";
                showArr(ptr);
                std::cout << '\n';
            }

            if (ptr != begin) ptr -= 2;
        }
        else if (boolShowProc) {
            std::cout << "| ";
            showArr(ptr);
            std::cout << '\n';
        }

    }

    std::cout << "Sorting took " << (long double)(time) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

template <typename T>
void SortBox<T>::selection(T* inp, const int size, bool inverse){

    clock_t time = sortInit(inp, size);

    T* memP;

    for (T* mainPtr = begin; mainPtr != end; ++mainPtr) {
        memP = nullptr;
        for (T* ptr = mainPtr; ptr != end; ++ptr) {
            if (!memP || compare(memP, ptr, inverse)) memP = ptr;
            if (boolShowProc) showArr(memP, ptr);
            std::cout << '\n';
        }
        if (memP) swap(mainPtr, memP);
    }

    std::cout << "Sorting took " << (long double)(time) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

template <typename T>
void SortBox<T>::mergePart(T* inp, int left, int mid, int right, bool inverse) {
    const int subLeft = mid - left + 1;
    const int subRight = right - mid;
   
    T* leftInp = new T[subLeft];
    T* rightInp = new T[subRight];

    T* ptr;
    T* ptrLeft = leftInp;
    T* ptrRight = rightInp;

    for (ptr = inp; ptr != begin + subLeft; ++ptr, ++ptrLeft) *ptrLeft = *(ptr + left);
    for (ptr = inp; ptr != begin + subRight; ++ptr, ++ptrRight) *ptrRight = *(ptr + mid + 1);

    int leftInpIndex  = 0;
    int rightInpIndex = 0;
    int resInpIndex   = left;

    while (leftInpIndex < subLeft && rightInpIndex < subRight) {
        if (compare(rightInp + rightInpIndex, leftInp + leftInpIndex, inverse)) {
            *(inp + resInpIndex) = *(leftInp + leftInpIndex);
            ++leftInpIndex;
        }
        else {
            *(inp + resInpIndex) = *(rightInp + rightInpIndex);
            ++rightInpIndex;
        }
        ++resInpIndex;
    }

    while (leftInpIndex < subLeft) {
        *(inp + resInpIndex) = *(leftInp + leftInpIndex);
        ++leftInpIndex;
        ++resInpIndex;
    }
    while (rightInpIndex < subRight) {
        *(inp + resInpIndex) = *(rightInp + rightInpIndex);
        ++rightInpIndex;
        ++resInpIndex;
    }

}

template <typename T>
void SortBox<T>::mergeSort(T* inp, int lowPoint, int highPoint, bool inverse) {
    if (lowPoint < highPoint) {
        int mid = lowPoint + ((highPoint - lowPoint) / 2);

        mergeSort(inp, lowPoint, mid, inverse);
        mergeSort(inp, mid + 1, highPoint, inverse);

        mergePart(inp, lowPoint, mid, highPoint, inverse);
    }
}

template <typename T>
void SortBox<T>::merge(T* inp, const int size, bool inverse) {
    
    clock_t time = sortInit(inp, size);

    mergeSort(inp, 0, size - 1, inverse);

    std::cout << "Sorting took " << (long double)(time) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

template <typename T>
int SortBox<T>::getDigit(T inp, int digit) {
    int res = 0;
    int digitAmount = 0;
    T tempInp = inp;

    for (digitAmount = 0; inp >= pow(10, digitAmount); ++digitAmount);
    //std::cout << digitAmount << std::endl;
    digitAmount -= 1;
    if (digit >= digitAmount + 1) return 0;

    while(digitAmount >= digit) {
        res = 0;
        while (tempInp >= pow(10, digitAmount)){
            tempInp -= pow(10, digitAmount);

            ++res;
        }
        --digitAmount;
    }

    return res;

}

/*
template <typename T>
void SortBox<T>::radix(T* inp, const int size, bool inverse) {
    
    clock_t time = sortInit(inp, size);

    int i = 0;
    int digitInNum = 0;

    while (digitInNum < 4) {
        i = 0;
        for (int digit = 0; digit < 10; ++digit) {
            for (T* ptr = begin + i; ptr != end; ++ptr) {
                if (digit == getDigit(*ptr, digitInNum)) {
                    if (*ptr != *(begin + i)) {
                        putIn(ptr, begin + i, size);
                    }
                    ++i;
                    ptr = begin + i - 1;
                }
            }
        }
        ++digitInNum;
    }

    std::cout << "Sorting took " << (long double)(time) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

*/

template <typename T>
void SortBox<T>::bogo(T* inp, const int size, bool inverse) {
    
    clock_t time = sortInit(inp, size);

    int currentRand;
    while (!checkIfSorted(inverse)) {
        for (T* ptr = begin; ptr != end; ++ptr) {
            if (boolShowProc) showArr(ptr);

            currentRand = rand() % size;
            swap(ptr, begin + currentRand);

            if (boolShowProc) {
                std::cout << "| ";
                showArr(ptr);
                std::cout << '\n';
            }
        }
    }
    std::cout << "Sorting took " << (long double)(time) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

template <typename T>
bool SortBox<T>::boolShowProc = false;

template <typename T>
T* generateArr(int sizeOfInp) {
    T* arr = new T[(const int)(sizeOfInp)];

    for (int i = 0; i < sizeOfInp; ++i) {
        arr[i] = rand() % sizeOfInp;
    }

    return arr;

}

int main(){
    srand(time(0));

    int sizeOfInp;
    std::cin >> sizeOfInp;

    int* inp = generateArr<int>(sizeOfInp);

    //SortBox<int>::showProc(true);
    SortBox<int> s;
    //s.bubble(inp, sizeOfInp);
    //s.insertion(inp, sizeOfInp);
    //s.cocktail(inp, sizeOfInp);
    //s.bogo(inp, sizeOfInp);
    //s.selection(inp, sizeOfInp);
    //s.quick(inp, sizeOfInp);
    //s.merge(inp, sizeOfInp);
    //s.radix(inp, sizeOfInp);
    //std::cout << s.getDigit(125454, 44);

    std::cout << '\n';
    for (int n = 0; n < sizeOfInp; n++) std::cout << inp[n] << ' ';
}
