#include <iostream>
#include <numeric>
#include <ctime>
using namespace std ;
int ** make_arr(int n)
{
    srand(time(0)) ;
    int ** arr = new int * [n] ;
    for (int i = 0 ; i < n ; i++){
        arr[i] = new int [n] ;
    }
    int c = 1 ;
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            arr[i][j] = c ;
            c++ ;
        }
    }
    arr[n-1][n-1] = 0 ;
    int arr2[n] ;
    for (int i = 0 ; i < n ; i++){
        arr2[i] = -1 ;
    }
    int a = 0 ;
    for(int k = 0 ; k < n;k++){
g :
        int r2 = rand() % n ;
        for (int i = 0 ; i < n ; i++){
            if (arr2[i] != r2 ){
                a++ ;
            }
        }
        if (a == n){
            arr2[k] = r2 ;
            a = 0 ;
        }
        else{
            a = 0 ;
            goto g ;
        }
        for(int m = 0 ; m < n ; m++){
            arr[r2][m] = arr[m][m] ; //For debugging
        }
        cout << endl;
    }
    return arr ;
}
int main ()
{
    int num ;
    cin >> num ;
    int ** arr = make_arr(num) ;
    for (int i = 0 ; i < num ; i++){
        for (int j = 0 ; j < num ; j++){
            cout << arr[i][j] << " " ;
        }
        cout << endl ;
    }
    return 0 ;
}
