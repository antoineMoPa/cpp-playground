#include <iostream>
#include <iterator>

using namespace std;

void my_sort(int * arr, int size){
    
}

int main(int argc, char ** argv){
    cout << "Hello !" << endl;

    // Plain array
    int arr [] = {0,5,4,3,7,3,8,2,9};
    
    my_sort(arr, sizeof(arr)/sizeof(int));
    
    // Print values, method 1
    for(int i = 0; i < sizeof(arr)/sizeof(int); i++){
        cout << arr[i];
        if(i != sizeof(arr)/sizeof(int) - 1){
            cout << ", ";
        } else {
            cout << endl;
        }
    }

    // Print values, method 1
    for(int i = 0; i < sizeof(arr)/sizeof(int); ++i){
        cout << arr[i];
        if(i != sizeof(arr)/sizeof(int) - 1){
            cout << ", ";
        } else {
            cout << endl;
        }
    }

    {
        int i = 0;
        int j = 10;
        
        j += ++i;
        
        cout << i << endl;
        cout << j << endl;
    }

    {
        int i = 0;
        int j = 10;
        
        j += i++;
        
        cout << i << endl;
        cout << j << endl;
    }

    
    return 0;
}
