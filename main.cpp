#include "polyline.h"

template<typename T>
Polyline<T> createIsoscelesTriangle(double sideLength, double vertexAngle) {
    Polyline<T> triangle(3);
    triangle[0] = Point<T>(0, 0); 
    triangle[1] = Point<T>(sideLength, 0);

    // Третья точка рассчитывается по вершине угла и стороне
    T x3 = static_cast<T>(sideLength * std::cos(vertexAngle));
    T y3 = static_cast<T>(sideLength * std::sin(vertexAngle));
    triangle[2] = Point<T>(x3, y3);

    return triangle;
}


int main() {
    Point<int> p1(1, 2);
    Polyline<int> poly1(p1);
    std::cout << "Polyline 1:\n";
    poly1.print();

    Polyline<int> poly2(3);
    poly2[0] = Point<int>(1, 2);
    poly2[1] = Point<int>(2, 3);
    poly2[2] = Point<int>(4, 5);
    std::cout << "\nPolyline 2:\n";
    poly2.print();

    Polyline<float> poly3(4, 0.0f, 10.0f);
    std::cout << "\nPolyline 3 (with random points):\n";
    poly3.print();

    Polyline<int> poly4 = poly1 + poly2;
    std::cout << "\nConcatenated Polyline 4 (Polyline 1 + Polyline 2):\n";
    poly4.print();

    poly4 += Point<int>(3, 4);
    std::cout << "\nPolyline 4 after adding point (3, 4):\n";
    poly4.print();

    Polyline<int> poly5 = Point<int>(-1, -1) + poly4;
    std::cout << "\nPolyline 5 after adding point (-1, -1) at the beginning:\n";
    poly5.print();
    std::cout << "Length of Polyline 5: " << poly5.length() << "\n";


    std::cout << "\n-----------------------------------------------------------------------------\n";
    double sideLength = 5.0;
    double angle = PI / 3;
    Polyline<double> triangle = createIsoscelesTriangle<double>(sideLength, angle);
    std::cout << "\nTriangle Polyline:";
    triangle.print();
    std::cout << "Length of Triangle Polyline: " << triangle.length() << "\n";


    std::cout << "\n-----------------------------------------------------------------------------\n";
    std::cout << "\nCopy constructor: " << "\n";
    Polyline<int> poly6(3);
    poly6[0] = Point<int>(10, 10);
    poly6[1] = Point<int>(20, 20);
    poly6[2] = Point<int>(30, 30);
    std::cout << "\nPolyline 6:\n";
    poly6.print();

    
    Polyline<int> poly6Copy(poly6);
    std::cout << "\nCopy of Polyline 6 (poly6Copy):\n";
    poly6Copy.print();

    
    poly6 += Point<int>(40, 40);
    std::cout << "\nPolyline 6 after adding point (40, 40):\n";
    poly6.print();

    std::cout << "\nCopy of Polyline 6 (poly6Copy) after modifying Polyline 6:\n";
    poly6Copy.print();


    Point<int> p7(1, 2);
    Polyline<int> poly7(p1);

    Polyline<int> poly8(3);
    poly8[0] = Point<int>(1, 2);
    poly8[1] = Point<int>(2, 3);
    poly8[2] = Point<int>(4, 5);

    Polyline<int> poly9(poly8);  

    std::cout << "\n-----------------------------------------------------------------------------\n";
    std::cout << "\nTesting equality and inequality operators:\n";
    std::cout << "Polyline 7:\n";
    poly7.print();
    std::cout << "Polyline 8:\n";
    poly8.print();
    std::cout << "Polyline 9 (copy of Polyline 2):\n";
    poly9.print();

    std::cout << "\npoly8 == poly9: " << (poly8 == poly9 ? "True" : "False") << "\n";  // Ожидается True
    std::cout << "poly7 == poly8: " << (poly7 == poly8 ? "True" : "False") << "\n";    // Ожидается False
    std::cout << "poly7 != poly8: " << (poly7 != poly8 ? "True" : "False") << "\n";    // Ожидается True

   
    Polyline<double> poly10(2);
    poly10[0] = Point<double>(1.000001, 2.000001);
    poly10[1] = Point<double>(3.0, 4.0);

    Polyline<double> poly11(2);
    poly11[0] = Point<double>(1.000002, 2.000002); 
    poly11[1] = Point<double>(3.0, 4.0);

    std::cout << "\nPolyline 10:\n";
    poly10.print();
    std::cout << "Polyline 11:\n";
    poly11.print();

  
    std::cout << "\npoly10 == poly11: " << (poly10 == poly11 ? "True" : "False") << "\n";  // Ожидается True (с учетом epsilon)
    std::cout << "poly10 != poly11: " << (poly10 != poly11 ? "True" : "False") << "\n";    // Ожидается False (с учетом epsilon)

    
    poly11[1] = Point<double>(3.1, 4.1);
    std::cout << "\nModified Polyline 5:\n";
    poly11.print();

    std::cout << "\npoly10 == poly11: " << (poly10 == poly11 ? "True" : "False") << "\n";  // Ожидается False
    std::cout << "poly10 != poly11: " << (poly10 != poly11 ? "True" : "False") << "\n";    // Ожидается True


    // Тестирование с типом int
    Polyline<int> polyInt;
    polyInt += Point<int>(1, 2);
    polyInt += Point<int>(3, 4);
    std::cout << "\n-----------------------------------------------------------------------------\n";
    std::cout << "\nPolyline<int> length: " << polyInt.length() << std::endl;
    polyInt.print();

    // Тестирование с типом float
    Polyline<float> polyFloat;
    polyFloat += Point<float>(1.1f, 2.2f);
    polyFloat += Point<float>(3.3f, 4.4f);
    std::cout << "Polyline<float> length: " << polyFloat.length() << std::endl;
    polyFloat.print();

    // Тестирование с типом double
    Polyline<double> polyDouble;
    polyDouble += Point<double>(1.11, 2.22);
    polyDouble += Point<double>(3.33, 4.44);
    std::cout << "Polyline<double> length: " << polyDouble.length() << std::endl;
    polyDouble.print();

    // Тестирование с типом std::complex<float>
    Polyline<std::complex<float>> polyComplexFloat;
    polyComplexFloat += Point<std::complex<float>>(std::complex<float>(1.1f, 2.2f), std::complex<float>(3.3f, 4.4f));
    polyComplexFloat += Point<std::complex<float>>(std::complex<float>(5.5f, 6.6f), std::complex<float>(7.7f, 8.8f));
    std::cout << "Polyline<std::complex<float>> length: " << polyComplexFloat.length() << std::endl;
    polyComplexFloat.print();

    // Тестирование с типом std::complex<double>
    Polyline<std::complex<double>> polyComplexDouble;
    polyComplexDouble += Point<std::complex<double>>(std::complex<double>(1.11, 2.22), std::complex<double>(3.33, 4.44));
    polyComplexDouble += Point<std::complex<double>>(std::complex<double>(5.55, 6.66), std::complex<double>(7.77, 8.88));
    std::cout << "Polyline<std::complex<double>> length: " << polyComplexDouble.length() << std::endl;
    polyComplexDouble.print();

    // Проверка оператора сложения двух ломаных
    Polyline<int> polyInt2;
    polyInt2 += Point<int>(5, 6);
    Polyline<int> polyIntCombined = polyInt + polyInt2;
    std::cout << "Combined Polyline<int> length: " << polyIntCombined.length() << std::endl;
    polyIntCombined.print();

    return 0;
}


