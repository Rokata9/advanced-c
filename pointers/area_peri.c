#include <stdio.h>

void areaPeri(double radius,
              double length,
              double breadth,
              double *cirArea,
              double *cirPeri,
              double *recArea,
              double *recPeri) {
    const double PI = 3.14;
    *recArea = length * breadth;
    *recPeri = 2 * (length + breadth);
    *cirArea = PI * radius * radius;
    *cirPeri = 2 * PI * radius;
}

int main() {
    double cirArea, cirPeri, recArea, recPeri;
    areaPeri(10, 5, 7, &cirArea, &cirPeri, &recArea, &recPeri);

    printf("Circle area: %f\n", cirArea);
    printf("Circle peri: %f\n", cirPeri);
    printf("Rect area: %f\n", recArea);
    printf("Rect peri: %f\n", recPeri);
}
