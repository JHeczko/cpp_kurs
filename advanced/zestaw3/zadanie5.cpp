# include <iostream>
#include <set>

using namespace std;

int main(){
	std::set<int, greater_equal<int> > myset = {12,3,4,5,5,123,4,431,2,123};

	for (auto el : myset){
     cout << el << endl;
	}
}