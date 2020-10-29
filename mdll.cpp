#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

struct complex {
    double r;
    double i;
    complex(double r, double i) : r(r), i(i) {}
    complex operator*(const complex& c) {
        complex prod {r*c.r+-i*c.i, r*c.i+i*c.r};
        return prod;
    }
    complex operator+(const complex& c) {
        complex sum {r+c.r, i+c.i};
        return sum;
    }
    double mag() {
        return sqrt(r*r+i*i);
    }
};

complex iter(complex num, int numIter) {
    complex curr {0,0};
    for (int i=0; i<numIter; i++) 
        curr=(curr*curr)+num;
    return curr;
}

int main() {
    const float imgWid {1751};
    const float imgHei {1000};
    FILE *img = fopen("C://Users//Eric//Desktop//ppmMandel.ppm", "wb");
    char buffer[]  {'P', '6', '\n',
                    '1', '7', '5', '1', ' ', '1', '0', '0', '0', '\n',
                    '2', '5', '5', '\n'};
    int len {sizeof(buffer)/sizeof(buffer[0])};
    fwrite(buffer,1,len,img);
    for (double i=1; i>-1; i-=0.002) {
        for (double r=-2.75; r<0.75; r+=0.002) {
            complex c {r,i};
            if (iter(c,5).mag()<100) {
                char b[] {0,0,0};
                fwrite(b,1,3,img);
            }
            else {
                unsigned char b[] {255,255,255};
                fwrite(b,1,3,img);
            }    
        }
        if (int((i-1)/0.002)%50==0) cout << i << endl;
    }
}

// convert P6 ppm to jpg:
// from PIL import Image
// Image.open("___.ppm").save("___.jpg")