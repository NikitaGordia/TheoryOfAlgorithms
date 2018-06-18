#include <iostream>
#include <fstream>

using namespace std;

#define endl "\n"

const int MAX_N = 1000;
const string OUTPUT_PATH = "/home/nikitagordia/CLionProjects/TA_Lab1/src/ip71_gordia_01_output.txt";
const string INPUT_PATH = "/home/nikitagordia/CLionProjects/TA_Lab1/Test/input_10.txt";

inline bool isEven(int x) {
    return x % 2 == 0;
}

inline bool compare(int x, int y) {
    if (isEven(x) && !isEven(y)) return false; else
        if (isEven(y) && !isEven(x)) return true; else
            if (isEven(x) && isEven(y)) return x > y; else
                return x < y;
}

inline void insert_sort(int* arr, int n) {
    int pos;
    for (int i = 1; i < n; i++) {
        pos = i - 1;
        while (pos >= 0 && compare(arr[pos], arr[pos + 1])) {
            swap(arr[pos], arr[pos + 1]);
            pos--;
        }
    }
}

int main() {
    int n, arr[MAX_N];
    string input_path;

    cin>>input_path;
    fstream input(input_path.c_str());

    if (!input.is_open()) {
        cout<<"File not found+"<<endl;
        return 0;
    }

    input>>n;
    for (int i = 0; i < n; i++)
        input>>arr[i];

    insert_sort(arr, n);

    fstream output(OUTPUT_PATH.c_str());

    if (!output.is_open()) {
        cout<<"Output file not found"<<endl;
        return 0;
    }

    for (int i = 0; i < n; i++)
        output<<arr[i]<<endl;

    cout<<"Done"<<endl;

    input.close();
    output.close();
    return 0;
}