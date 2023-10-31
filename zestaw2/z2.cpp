#include <iostream>
#include <random>
#include <iostream>
#include <vector>
using namespace std;


void swap(vector<int>& v, int x, int y) {
    int temp = v[x];
    v[x] = v[y];
    v[y] = temp;

}

void quicksort(vector<int> &vec, int L, int R) {
    int i, j, mid, piv;
    i = L;
    j = R;
    mid = floor(L + (R - L) / 2);
    piv = vec[mid];

    while (i<R || j>L) {
        while (vec[i] < piv)
            i++;
        while (vec[j] > piv)
            j--;

        if (i <= j) {
            swap(vec, i, j); 
            i++;
            j--;
        }
        else {
            if (i < R)
                quicksort(vec, i, R);
            if (j > L)
                quicksort(vec, L, j);
            return;
        }
    }
}


/*int main() {
    vector<int> vec1;
    const int count = 10;

    for (int i = 0; i < count; i++) {
        vec1.push_back(1 + rand() % 100);
    }
    quicksort(vec1, 0, count - 1);

}*/
int main()
{
    std::vector<int> arr;
    int n;
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(1, 10000);
    std::cout << "Napisz jak wiele liczb chcesz miec" << "\n";
    while(true){
        std::cin >> n;
        if(n >= 0){
            break;
        }
        else{
            std::cout << "zly wybor ilosci liczb" << "\n";
        }
    }
    std::cout << "Przed posortowaniem: \n";
    for (int i = 0; i < n; ++i){
        arr.push_back(distrib(gen));
        std::cout << arr[i] << ' ';
        }
        //std::cout << '\n' << arr[1];
        std::cout << "\n";
    

	quicksort(arr, 0, n - 1);
    std::cout << "Po posortowaniu: \n";
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << " ";
	}

	return 0;
}