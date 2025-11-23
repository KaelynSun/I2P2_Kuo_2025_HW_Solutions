#include <iostream>
#include <vector>
#include <stack>
using namespace std;

long long largestRectangle(vector <long long> & height){
    int n = height.size();
    stack<int> MonoStack;
    vector<int> left(n), right(n);
    long long maxArea = 0;

    for(int i = 0; i < n; ++i){
        /*
        !Monostack.empty() checks if the stack is not empty

        height[MonoStack.top()] >= height[i] checks if the current bar is shorter
        or equal to the bar that is at the top of the stack

        if both conditions are true, then please pop the top element from the stack,
        which means the bar cannot extend further right/left because height[i] is smaller

        */
        while(!MonoStack.empty() && height[MonoStack.top()] >= height[i]){
            MonoStack.pop();
        }
        left[i] = MonoStack.empty() ? -1 : MonoStack.top();
        MonoStack.push(i);

        /*
        this means if the stack is empty, then set the top to -1, as that means the bar (height[i])
        has no left boundary

        However, if it is not empty then the bar at the very top of the stack is it's boundary.
        */
    }

    // Clear the stack for reuse
    while (!MonoStack.empty()) MonoStack.pop();

    for(int i = n - 1; i >= 0; --i){
        while(!MonoStack.empty() && height[MonoStack.top()] >= height[i]){
            MonoStack.pop();
        }
        /*
        Difference for the right side is, if there no boundary
        then it's boundary is n (no limit, can extend to the end)
        */
        right[i] = MonoStack.empty() ? n : MonoStack.top();
        MonoStack.push(i);
    }

    for(int i = 0; i < n; ++i){
        long long width = right[i] - left[i] - 1;
        long long area = height[i] * width;
        if(area > maxArea){
            maxArea = area;
        }
    }

    return maxArea;
}

int main(){
    int testcase;
    cin >> testcase;

    while(testcase--){
        int n;
        cin >> n;
        vector<long long> height(n);

        for(int i = 0; i < n; ++i){
            cin >> height[i];
        }

        long long result = largestRectangle(height);
        cout << result << endl;
    }

    return 0;
}
