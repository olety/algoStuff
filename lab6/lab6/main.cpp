/*
 Merge Sort Iteartive
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
    delete lowHalf;
    delete highHalf;
    
}

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
        exit(EXIT_FAILURE);
    if ( to == 0 )
        return 1;
    return base*power(base,to-1);
}


void iterative( int arr[], int size ){
    int sorted_ind = 0, ex = 0, i, j_prev, pwr, size_s = size;
    int *excludes = new int;
    for( i = 0; i < size; i++){
        excludes[i] = -1;
    }
    i=0;
    while ( size_s != 1 ){
        if ( size_s %2 != 0 )
            excludes[i] = 1;
        else
            excludes[i] = 0;
        size_s /= 2;
        i++;
    }
    ex = i;
    for ( i = 1; i < calcSteps(size); i++){
        pwr = power(2, i);
        j_prev = 0;
        for ( int j = pwr-1; j < size; j+= pwr ){
            merge(arr, j_prev, (j+j_prev)/2, j);
//            cout << j_prev << (j+j_prev)/2 << j << endl;
//            showArray(arr, size);
            j_prev = j+1;
        }
        showArray(arr, size);
    }
    
    sorted_ind = pow(2,ex)-1;
    
    for ( i = ex-1; i >= 0; i--)
    {
        if ( excludes[i] ){
            merge(arr, 0, sorted_ind, sorted_ind + pow(2,i));
//            cout << 0 << sorted_ind << sorted_ind+pow(2, i) << endl;
            showArray(arr, size);
            sorted_ind += pow(2,i);
        }
    }
    showArray(arr, size);
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
        
        if(isCommand(command,"MI")){
            int* arr = new int[value];
            for (int i = 0; i < value; i++){
                cin >> arr[i];
            }
            cout << "mergeSortIter" << endl;
            showArray(arr, value);
            mergeSort(arr, value);
            delete arr;
            continue;
        }
        cout << "wrong argument in test: " << command << endl;
    }
    return 0;
}
