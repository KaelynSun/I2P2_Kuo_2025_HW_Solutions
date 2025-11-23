#include <iostream>
#include <unordered_map>
using namespace std;

int main(){
    int testcases;
    cin >> testcases;
    while(testcases--){
        int n, k;
        int beautifulSequence = 0;
        cin >> n >> k;
        int array[n];
        for(int i = 0; i < n; i++){
            cin >> array[i];
        }

        unordered_map<long long, int> prefixSumCount;
        prefixSumCount[0] = 1;
        long long currentSum = 0;

        for(int i = 0; i < n; i++){
            currentSum += array[i];
            //if the prefixSumCount finds currentSum - k in the array then it exists, if it ends then it doesn't exist
            if(prefixSumCount.find(currentSum - k) != prefixSumCount.end()){
                beautifulSequence += prefixSumCount[currentSum - k];
            }
            prefixSumCount[currentSum]++;
        }
        cout << beautifulSequence << endl;
    }
    return 0;
}
