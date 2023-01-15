#include <iostream>
#include <thread>
#include <vector>

void quicksort(std::vector<int> &vec, int left, int right) {
    if (left >= right) {
        return;
    }
    int pivot = vec[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (vec[i] < pivot) {
            i++;
        }
        while (vec[j] > pivot) {
            j--;
        }
        if (i <= j) {
            std::swap(vec[i], vec[j]);
            i++;
            j--;
        }
    }

    std::thread threads[8];
    int thread_count = 0;

    if (left < j && thread_count < 8) {
        threads[thread_count++] = std::thread(quicksort, std::ref(vec), left, j);
    }

    if (i < right && thread_count < 8) {
        threads[thread_count++] = std::thread(quicksort, std::ref(vec), i, right);
    }

    for (int i = 0; i < thread_count; i++) {
        threads[i].join();
    }
}

int main() {
    std::vector<int> vec = {5, 7, 1, 3, 2, 8, 6, 4};
    quicksort(vec, 0, vec.size() - 1);
    for (int i : vec) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    return 0;
}