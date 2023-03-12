//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//int main() {
//
//    vector<float> example;
//
//    // assign 5 floats with value 10
//    example.assign(5, 10.0);
//
//    // print out the vector
//    for (int i = 0; i < example.size(); i++) {
//        cout << example[i] << endl;
//    }
//
//    // blank line outputted to terminal
//    cout << endl;
//
//    //multiply each value in the vector by 20
//    for (int i = 0; i < example.size(); i++) {
//        example[i] = 20 * example[i];
//    }
//
//    // print out the vector
//    for (int i = 0; i < example.size(); i++) {
//        cout << example[i] << endl;
//    }
//
//
//    return 0;
//}

#include <iostream>
#include <vector>

using namespace std;

int MathAndVector() {

    vector<int> exampleone(5);
    vector<int> exampletwo(5);
    vector<int> examplesum(5);

    exampleone[0] = 2;
    exampleone[1] = 6;
    exampleone[2] = 25;
    exampleone[3] = 1;
    exampleone[4] = 18;

    exampletwo[0] = 3;
    exampletwo[1] = 19;
    exampletwo[2] = 8;
    exampletwo[3] = 12;
    exampletwo[4] = 191;

    cout << "vector one ";

    // print out the first vector
    for (int i = 0; i < exampleone.size(); i++) {
        cout << exampleone[i] << " ";
    }

    // create a new line in the terminal
    cout << endl;

    cout << "vector two ";

    // print out the second vector
    for (int i = 0; i < exampletwo.size(); i++) {
        cout << exampletwo[i] << " ";
    }

    // create a new line in the terminal
    cout << endl;

    cout << "vector sum ";

    //add the vectors together
    for (int i = 0; i < exampleone.size(); i++) {
        examplesum[i] = exampleone[i] + exampletwo[i];
    }

    // print out the vector
    for (int i = 0; i < examplesum.size(); i++) {
        cout << examplesum[i] << " ";
    }

    // create a new line in the terminal
    cout << endl;

    return 0;
}