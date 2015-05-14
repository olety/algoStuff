#include<iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <sys/time.h>
#include <chrono>

using namespace std;
void swap( int&a, int&b ){
    int temp = a;
    a = b;
    b = temp;
};

class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const {
        return chrono::duration_cast<second_>
        (clock_::now() - beg_).count(); }
    
private:
    typedef chrono::high_resolution_clock clock_;
    typedef chrono::duration<double, std::ratio<1> > second_;
    chrono::time_point<clock_> beg_;
};

void showArray( int arr[], int size ){
    for (int i = 0; i < size; i++){
        cout << arr[i] << ",";
    }
    cout << endl;
};

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
       // showArray(arr, size);
    }
};

void bubbleSort( int arr[], int size ){
    for ( int j = 0; j < size - 1; j++ ){
        for ( int i = size - 1; i > j; i-- ){
            if ( arr[i] < arr[i-1] ){
                swap(arr[i-1],arr[i]);
            }
        }
        //showArray(arr, size);
    }
};

void merge( int array[], int p, int q, int r){
    int* lowHalf = new int[q-p+1];
    int* highHalf = new int[r-(q+1)+1]; // r-q-1+1 = r-q
    
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
   // showArray(arr, size);
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

int main2(){
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
        
        if(isCommand(command,"BS")){
            int* arr = new int[value];
            for (int i = 0; i < value; i++){
                cin >> arr[i];
            }
            cout << "bubbleSort" << endl;
            showArray(arr, value);
            bubbleSort(arr, value);
            delete arr;
            continue;
        }
        
        if(isCommand(command,"IS")){
            int* arr = new int[value];
            for (int i = 0; i < value; i++){
                cin >> arr[i];
            }
            cout << "insertSort" << endl;
            showArray(arr, value);
            insertSort(arr, value);
            delete arr;
            continue;
        }
    
        if(isCommand(command,"MS")){
            int* arr = new int[value];
            for (int i = 0; i < value; i++){
                cin >> arr[i];
            }
            cout << "mergeSort" << endl;
            showArray(arr, value);
            mergeSort(arr, value);
            showArray(arr, value);
            delete arr;
            continue;
        }
        cout << "wrong argument in test: " << command << endl;
    }
    return 0;
}

void parseIn ( FILE &in, int arr[]){
    char string[2048];
    int i = 0;
    while ( fscanf(&in, "%s", string) != EOF ){
        arr[i] = stoi(string);
        i++;
    }
}

void outdata ( FILE &out, const char*s, double time ){
    cout << "printing data " << s << endl;
    printf( "execution time of %s is %f.\n", s, time);
}

void bsort( FILE &out, Timer tmr, int arr[], int size, const char* s){
    tmr.reset();
    bubbleSort(arr, size);
    double t = tmr.elapsed();
    outdata( out,"bsort 10",t);
}

int main ( void ){
    
    FILE *out = fopen("res.txt", "w+");
    FILE *in100 = fopen("inverse100.txt", "r");
    FILE *in10k = fopen("inverse10k.txt", "r");
    FILE *in100k = fopen("inverse100k.txt", "r");
    
    
    int *arr100b = new int[100];
    int *arr100i = new int[100];
    int * arr100m = new int[100];
    
    
    int *arr10kb = new int[10000];
    int *arr10ki = new int[10000];
    int * arr10km = new int[10000];
    
    int *arr100kb = new int[100000];
    int *arr100ki = new int[100000];
    int * arr100km = new int[100000];
    
    
    Timer tmr;
    double t = 0;
    
//    parsing files
    
    parseIn(*in100, arr100b);
    parseIn(*in100, arr100i);
    parseIn(*in100, arr100m);
    
    parseIn(*in10k, arr10kb);
    parseIn(*in10k, arr10ki);
    parseIn(*in10k, arr10km);
    
    parseIn(*in100k, arr100kb);
    parseIn(*in100k, arr100ki);
    parseIn(*in100k, arr100km);
    
    
    
    tmr.reset();
    bubbleSort(arr100b, 100);
    t = tmr.elapsed();
    outdata( *out,"bsort 100",t);
    
    tmr.reset();
    bubbleSort(arr10kb, 10000);
    t = tmr.elapsed();
    outdata( *out,"bsort 10k",t);
    
    tmr.reset();
    bubbleSort(arr100kb, 100000);
    t = tmr.elapsed();
    outdata( *out,"bsort 100k",t);
    
//    tmr.reset();
//    bubbleSort(arrmilb, 1000000);
//    t = tmr.elapsed();
//    cout << "exec time of bsort 1mil " <<   << endl;
    
//    insert sort
    
    tmr.reset();
    insertSort(arr100i, 100);
    t = tmr.elapsed();
    outdata( *out, "insort 100", t );
    
    tmr.reset();
    insertSort(arr10ki, 10000);
    t = tmr.elapsed();
    outdata( *out, "insort 10k", t );
    
    tmr.reset();
    insertSort(arr100ki, 100000);
    t = tmr.elapsed();
    outdata( *out, "insort 100k", t );
    
//    merge sort
    
    tmr.reset();
    mergeSort(arr100m, 100);
    t = tmr.elapsed();
    outdata( *out, "msort 100", t );
    
    tmr.reset();
    mergeSort(arr10km, 10000);
    t = tmr.elapsed();
    outdata( *out, "msort 10k", t );
    
    tmr.reset();
    mergeSort(arr100km, 100000);
    t = tmr.elapsed();
    outdata( *out, "msort 100k", t );
    
    
    return 0;
}
