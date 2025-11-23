#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
using namespace std;

int findNearest(const set<int>& portals, int x){
    auto iter = portals.lower_bound(x);
    /* lower_bound(x) here does not mean lower bound mathematically,
    lower_bound(int) in c++ means to return the first value that is NOT less than x
    returns an iterator that is >= x
    if all the portals are > x, then just return end(?)
    */
    int nearest = -1;
    int minDistance = INT_MAX;
    /* INT_MAX is the largest possible integer value. We use this so that any real distance
    we compute will be smaller, ensuring the first comparison to work properly
    */
    if(iter != portals.end()){
        // if the iterator is valid, compute the distance to x
        // portals.end() refers to a dummy end that signals that no match is found
        int distance = abs(*iter - x);

        //since iter is an iterator (a pointer), we dereference it with *iter to get the actual value
        if(distance < minDistance || (distance == minDistance && *iter < nearest)){
            minDistance = distance;
            nearest = *iter;
        }
    }

    if(iter != portals.begin()){
        //portals.begin() refers to the first portal in the set
        /* checks if iter is not at the first portal, there might be a portal before
        that is closer to the x coordinate (of the person)

        if iter is at the beginning, decrementing it would be invalid

        distance = how far the individual is from their nearest portal
        minDistance = the smallest distance found so far (initially INT_MAX)
        nearest = the coordinate of the nearest portal so far
        *iter = the actual coordinate of the current portal being checked
        */
        --iter;
        int distance = abs(*iter - x);
        if(distance < minDistance ||(distance == minDistance && *iter < nearest)){
        // distance < minDistance Checks if the current portal is strictly closer than the previous current
        // distance == minDistance && *iter < nearest, distance is the same but check for smaller coordinate
            minDistance = distance;
            nearest = *iter;
        }
    }
    return nearest;
}
int main(){
    int n, m;
    cin >> n >> m;
    vector<int>portalCoord(n);
    for(int i = 0; i < n; ++i){
        cin >> portalCoord[i];
    }
    sort(portalCoord.begin(), portalCoord.end());
    set<int>availablePortal(portalCoord.begin(), portalCoord.end());

    for(int i = 0; i < m; ++i){
        int start, destination;
        cin >> start >> destination;

        int nearestStart = findNearest(availablePortal, start);
        int nearestDestination = findNearest(availablePortal, destination);

        if(nearestStart == nearestDestination || (abs(nearestStart - start) + abs(nearestDestination - destination)) >= abs(start - destination)){
            /*
            if walking from our x,y coordinate to the nearest portal's x,y coordinate takes a lot more walking then just directly walking from point A to b
            then we just walk (no need for portals, very mafan)
            */
            cout << "walk\n";
        } else{
            cout << nearestStart << " " << nearestDestination << "\n";
            availablePortal.erase(nearestStart);
            availablePortal.erase(nearestDestination);
        }
    }

    return 0;
}
