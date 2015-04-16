/*
 Merge Sort Iterative
 0 | 1 | 2 | 3 | 4 | 5 [ 6
   m       m       m
 
 0 1 | 2 3 [ 4 5 [ 6
     m
 
 0 1 2 3 | 4 5 [ 6
         m
 
 0 1 2 3 4 5 | 6
             m
 */
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

void showArray( int arr[], int size ){
    for (int i = 0; i < size; i++){
        cout << arr[i] << ",";
    }
    cout << endl;
};

void merge( int array[], int p, int q, int r){
    int* lowHalf = new int[q-p+1];
    int* highHalf = new int[r-q];
    
    int k = p;
    int i;
    int j;
    for (i = 0; k <= q; i++, k++) {
        lowHalf[i] = array[k];
    }
    for (j = 0; k <= r; j++, k++) {
        highHalf[j] = array[k];
    }
    
    k = p;
    i = 0;
    j = 0;
    
    while ( i <= (q-p) && j <= (r-q-1)){
        if ( lowHalf[i] < highHalf[j] ) {
            array[k] = lowHalf[i];
            i++;
        }else {
            array[k] = highHalf[j];
            j++;
        }
        k++;
    }
    
    while ( i <= (q-p) ){
        array[k] = lowHalf[i];
        k++;
        i++;
    }
    while ( j <= (r-q-1) ){
        array[k] = highHalf[j];
        k++;
        j++;
    }
    delete[] lowHalf;
    delete[] highHalf;
    
}

void insertSort( int arr[], int size ){
    int i,j,k,elem;
    for ( i = size-2; i >=0; i--){
        j = size-1;
        elem = arr[i];
        while ( j>i && elem <= arr[j] )
            j--;
        for ( k = i; k < j; k ++){
            arr[k] = arr[k+1];
        }
        arr[j] = elem;
        showArray(arr, size);
    }
};

void bubbleSort( int arr[], int size ){
    for ( int j = 0; j < size - 1; j++ ){
        for ( int i = size - 1; i > j; i-- ){
            if ( arr[i] < arr[i-1] ){
                swap(arr[i-1],arr[i]);
            }
        }
        showArray(arr, size);
    }
};



int isPow2 ( int n ){
    int k = 2;
    while ( k <= n ){
        if ( n == k ){
            return true;
        }
        k *= 2;
    }
    return false;
}

int calcSteps ( int n ){
    int i = 0;
    while ( n>0 ){
        n /= 2;
        i++;
    }
    return i;
}

int power ( int base, int to ){
    if ( to < 0 )
        return -1;
    if ( to == 0 )
        return 1;
    return base*power(base,to-1);
}


void iterative( int arr[], int size ){
    int ex = 0, i, j=0, j_prev=0, pwr;
     for ( i = 1; i < calcSteps(size); i++){
        pwr = power(2, i);
        if ( (size-ex)%pwr != 0 ){
            ex += power(2,i-1);
        }
        j_prev = 0;
        for (  j = pwr-1; j < size; j+= pwr ){
            merge(arr, j_prev, (j+j_prev)/2, j);
            j_prev = j+1;
        }
         if ( ex > power(2,i-1) ){
             merge(arr, size-ex, size-ex+power(2,i-1)-1, size-1);
         }
         showArray(arr, size);
    }
    if ( ex != 0 ){
        merge(arr, 0, j_prev-1, size-1);
        showArray(arr, size);
    }
}
    
void mergeSortArr ( int arr[], int p, int r){
    if ( r > p ){
        int q = (r+p)/2;
        mergeSortArr(arr, p, q);
        mergeSortArr(arr, q+1, r);
        merge(arr,p,q,r);
    }
}

void mergeSort( int arr[], int size ){
    mergeSortArr(arr,0,size-1);
    //iterative(arr, size);
    showArray(arr, size);
};

void mergeSortI( int arr[], int size ){
    //mergeSortArr(arr,0,size-1);
    iterative(arr, size);
    //showArray(arr, size);
};

void showBool(bool val){
    if(val)
        cout << "true" << endl;
    else
        cout << "false" << endl;
}

bool isCommand(const string command,const char *mnemonic){
    return command==mnemonic;
}



int main(){
    string line;
    string command;
    int value;
    int* arr = NULL;
    //cout << "START" << endl;
    while(true){
        getline(cin,line);
        std::stringstream stream(line);
        stream >> command;
        if(line=="" || command[0]=='#')
        {
            // ignore empty line and comment
            continue;
        }
        
        // copy line on output with exclamation mark
        //cout << "!" << line << endl;;
        
        // change to uppercase
        command[0]=toupper(command[0]);
        command[1]=toupper(command[1]);
        
        // zero-argument command
        if(isCommand(command,"HA")){
            cout << "END OF EXECUTION" << endl;
            break;
        }
        //one-arg command
        stream >> value;
        if(isCommand(command,"BS")){
            arr = new int[value];
            for (int i = 0; i < value; i++){
                cin >> arr[i];
            }
            cout << "bubbleSort" << endl;
            showArray(arr, value);
            bubbleSort(arr, value);
            delete[] arr;
            continue;
        }
        
        if(isCommand(command,"IS")){
            arr = new int[value];
            for (int i = 0; i < value; i++){
                cin >> arr[i];
            }
            cout << "insertSort" << endl;
            showArray(arr, value);
            insertSort(arr, value);
            delete[] arr;
            continue;
        }
        
        if(isCommand(command,"MS")){
            arr = new int[value];
            for (int i = 0; i < value; i++){
                cin >> arr[i];
            }
            cout << "mergeSort" << endl;
            showArray(arr, value);
            mergeSort(arr, value);
            delete[] arr;
            continue;
        }
        
        if(isCommand(command,"MI")){
            arr = new int[value];
            for (int i = 0; i < value; i++){
                cin >> arr[i];
            }
            cout << "mergeSortIter" << endl;
            showArray(arr, value);
            mergeSortI(arr, value);
            delete[] arr;
            continue;
        }
        cout << "wrong argument in test: " << command << endl;
    }
    return 0;
}
