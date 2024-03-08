#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int crossingChecker(int* shapex, int* shapey, int verts, int x, int y);

int main(int argc, char* argv[])
{
    fstream inFile(argv[1]);
    int* xverts;
    int* yverts;
    int size, crossings = 0;
    int xcord = atoi(argv[2]);
    int ycord = atoi(argv[3]);

    string word;

    // Parses the text file word by word until empty
    while (inFile >> word) {
        // Creates an array that contains the vertices of either the main shape or the cut
        if (word == "OUTLINE" || word == "CUT") {
            inFile >> word;
            try {
                size = stoi(word);
                xverts = new int[size];
                yverts = new int[size];
                for (int i = 0; i < size; i++) {
                    inFile >> word;
                    xverts[i] = stoi(word);
                    inFile >> word;
                    yverts[i] = stoi(word);
                }
                //Counts the amount of lines the point crosses and adds it to the total crosses
                crossings += crossingChecker(xverts, yverts, size, xcord, ycord);
            }
            catch (...) {
                cout << "Invalid Coordinates";
            }
        }
        else {
            cout << "File in wrong format";
        }

    }
    inFile.close();

    //Determines if points is in the shape based on the amount or lines it has crossed
    if (crossings % 2 == 0) {
        cout << "Point " << xcord << "," << ycord << " is OUTSIDE the shape";
        return 0;
    }
    else {
        cout << "Point " << xcord << "," << ycord << " is INSIDE the shape";
        return 1;
    }
}

//Counts the amount of perpendicular lines of the shape this point would cross
int crossingChecker(int* shapex, int* shapey, int verts, int x, int y) {
    int c = 0;
    for (int i = 0, j = verts - 1; i < verts; j = i++) {
        if (((shapey[i] > y) != (shapey[j] > y)) && (shapex[i] > x) && (shapex[j])) {
            c += 1;
        }
    }
    return c;
}