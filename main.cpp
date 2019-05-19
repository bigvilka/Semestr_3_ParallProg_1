#include <iostream>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <omp.h>
#include <vector>
#include <iterator>

using namespace std;

template <typename TElement>
void SetRandom(vector<TElement> *arr)
{
	typename vector<TElement>::iterator ptr = arr->begin();
	for (int i = 0; i < arr->size(); i++)
	{
		*ptr = rand();
		ptr++;
	}
}

template <typename TElement>
void GetCopy(vector<TElement> *from, vector<TElement> *to)
{
	for (int i = 0; i < from->size(); i++)
		to->push_back(from->at(i));
}

template <typename TElement>
void oddEvenSorting(vector<TElement> *arr)
{
	for (int i = 0; i < arr->size(); i++)
	{
		if (i % 2 == 0)
			for (typename vector<TElement>::iterator ptr = arr->begin(); ptr < arr->end(); ptr += 2)
            {
				if (*ptr > *(ptr + 1))
					swap(*ptr, *(ptr + 1));
            }
            else
                for (typename vector<TElement>::iterator ptr = arr->begin() + 1; ptr < arr->end() - 1; ptr += 2)
                {
                    if (*ptr > *(ptr + 1))
                        swap(*ptr , *(ptr + 1));
                }
	}
}

template <typename TElement>
void ParallelOddEvenSort(vector<TElement> *arr)
{
	#pragma omp parallel for
	for (int i = 0; i < arr->size(); i++)
	{
		if (i % 2 == 0)
			for (typename vector<TElement>::iterator ptr = arr->begin(); ptr < arr->end(); ptr += 2)
            {
				if (*ptr > *(ptr + 1))
					swap(*ptr, *(ptr + 1));
            }
            else
                for (typename vector<TElement>::iterator ptr = arr->begin() + 1; ptr < arr->end() - 1; ptr += 2)
                {
                    if (*ptr > *(ptr + 1))
                        swap(*ptr , *(ptr + 1));
                }
	}
}

double GetTime(function<void()> foo)
{
	double start_time = clock();
	foo();
	double end_time = clock();

	return (end_time - start_time) / CLOCKS_PER_SEC;
}

int main()
{
	setlocale(0, "Russian");

	omp_set_num_threads(4);

	cout << "Введите длину" << endl;
	int length;
	cin >> length;
	vector<int> sequence(length);
	SetRandom<int>(&sequence);

	vector<int> copy_seq(0);
	GetCopy(&sequence, &copy_seq);

	for (int i = 0; i < sequence.size(); i++)
		cout << sequence.at(i) << " ";
    cout << endl;

	double time = GetTime([&sequence]() { oddEvenSorting<int>(&sequence); });
	cout << "Время работы: " << time << endl;
	time = GetTime([&copy_seq]() { ParallelOddEvenSort<int>(&copy_seq); });
	cout << "Время работы Parallel: " << time << endl;

	return 0;
}
