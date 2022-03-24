#pragma once

template <typename T>
class SortBox {
private:
	T* begin = nullptr;
	T* end = nullptr;
	T mem;
	
	static bool boolShowProc;

	HANDLE hConsole;

	clock_t sortInit(T* inp, const int size);
	//inline void putIn(T* ptr1, T* ptr2, const int size);
	inline void swap(T* ptr);
	inline void swap(T* ptr1, T* ptr2);
	inline bool compare(T* ptr, bool inverse);
	inline bool compare(T* ptr1, T* ptr2, bool inverse);
	void showArr(T* current);
	void showArr(T* current1, T* current2);

	int quickPart(T* inp, int lowPoint, int highPoint, bool inverse);
	void quickSort(T* inp, int lowPoint, int highPoint, bool inverse);

	void mergePart(T* inp, int left, int mid, int right, bool inverse);
	void mergeSort(T* inp, int lowPoint, int highPoint, bool inverse);


public:
	SortBox();
	~SortBox();

	int getDigit(T inp, int digit);

	static void showProc() { boolShowProc = !boolShowProc; }
	static void showProc(bool toBoolShowProc) { boolShowProc = toBoolShowProc; }

	bool checkIfSorted(bool inverse);

	// exchange sorts
	void bubble(T* inp, const int size, bool inverse = false);
	void cocktail(T* inp, const int size, bool inverse = false);
	void quick(T* inp, const int size, bool inverse = false);

	// insertion sorts
	void insertion(T* inp, const int size, bool inverse = false);

	// selection sorts
	void selection(T* inp, const int size, bool inverse = false);

	// merge sorts
	void merge(T* inp, const int size, bool inverse = false);

	// distribution sorts
	//void radix(T* inp, const int size, bool inverse = false);

	// joke sorts
	void bogo(T* inp, int size, bool inverse = false);


};