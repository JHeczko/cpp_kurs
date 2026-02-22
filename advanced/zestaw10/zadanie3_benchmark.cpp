#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <numeric>
#include <chrono>

using namespace std;
using namespace std::chrono;

void benchmark(const string& name, function<void()> f) {
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    duration<double> diff = end - start;
    cout << name << ": " << diff.count() << " s\n";
}

int main() {
    const size_t SIZE = 100'000'000;
    vector<int> data(SIZE);
    iota(data.begin(), data.end(), 0);

    // 1. transform
    vector<int> out1(SIZE), out2(SIZE);
    benchmark("transform seq", [&] {
        transform(execution::seq, data.begin(), data.end(), out1.begin(),
                  [](int x) { return x * 2; });
    });
    benchmark("transform par", [&] {
        transform(execution::par, data.begin(), data.end(), out2.begin(),
                  [](int x) { return x * 2; });
    });

    // 2. for_each
    long long sum_seq = 0, sum_par = 0;
    benchmark("for_each seq", [&] {
        for_each(execution::seq, data.begin(), data.end(), [&](int x) {
            sum_seq += x % 10;
        });
    });
    benchmark("for_each par", [&] {
        mutex m;
        for_each(execution::par, data.begin(), data.end(), [&](int x) {
            lock_guard<mutex> lock(m);
            sum_par += x % 10;
        });
    });

    // 3. count_if
    benchmark("count_if seq", [&] {
        count_if(execution::seq, data.begin(), data.end(), [](int x) {
            return x % 2 == 0;
        });
    });
    benchmark("count_if par", [&] {
        count_if(execution::par, data.begin(), data.end(), [](int x) {
            return x % 2 == 0;
        });
    });

    // 4. sort
    vector<int> sort_seq = data;
    vector<int> sort_par = data;
    reverse(sort_seq.begin(), sort_seq.end());
    reverse(sort_par.begin(), sort_par.end());
    benchmark("sort seq", [&] {
        sort(execution::seq, sort_seq.begin(), sort_seq.end());
    });
    benchmark("sort par", [&] {
        sort(execution::par, sort_par.begin(), sort_par.end());
    });

    // 5. reduce
    benchmark("reduce seq", [&] {
        reduce(execution::seq, data.begin(), data.end(), 0LL);
    });
    benchmark("reduce par", [&] {
        reduce(execution::par, data.begin(), data.end(), 0LL);
    });

    return 0;
}
