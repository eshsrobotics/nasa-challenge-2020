#include "matrix.h"
#include <iostream>
#include <cmath>

using std::sin;
using std::cos;
using std::tan;

const double deg_to_rad = M_PI/180;

Matrix::Matrix() {
    data = {0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0};
}



Matrix::Matrix(double a11, double a12, double a13, double a14,
               double a21, double a22, double a23, double a24,
               double a31, double a32, double a33, double a34,
               double a41, double a42, double a43, double a44) {
    data = {
        a11, a12, a13, a14,
        a21, a22, a23, a24,
        a31, a32, a33, a34,
        a41, a42, a43, a44
    };

}

Matrix operator*(Matrix m1, Matrix m2) {
    Matrix result;

    // "k" is the current position in the result array.
    for (int k = 0; k < 16; k += 1) {
        int m1_row = int(k/4);
        int m2_column = k%4;

        // "i" is the current position in the row and colunm we are multiplying
        for (int i = 0; i < 4; i += 1) {
            int m1_data_index = m1_row * 4 + i;
            int m2_data_index = m2_column + 4 * i;
            result.data[k] += m1.data[m1_data_index] * m2.data[m2_data_index];
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& s, Matrix m) {
    for (int i = 0; i < 16; i += 1) {
        if ((i + 1) % 4 == 0) {
            s << m.data[i] << ", \n";
        } else {
            s << m.data[i] << ", ";
        }
    }
    return s;
}

Vector operator*(Matrix m, Vector v) {
    double x = m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z + m.data[3] * 1;
    double y = m.data[4] * v.x + m.data[5] * v.y + m.data[6] * v.z + m.data[7] * 1;
    double z = m.data[8] * v.x + m.data[9] * v.y + m.data[10] * v.z + m.data[11] * 1;
    Vector result = Vector(x, y, z);
    return result;
}

Point operator*(Matrix m, Point p) {
    double x = m.data[0] * p.x + m.data[1] * p.y + m.data[2] * p.z + m.data[3] * 1;
    double y = m.data[4] * p.x + m.data[5] * p.y + m.data[6] * p.z + m.data[7] * 1;
    double z = m.data[8] * p.x + m.data[9] * p.y + m.data[10] * p.z + m.data[11] * 1;
    Point result = Point(x, y, z);
    return result;
}

Matrix translationMatrix(Vector v) {
    Matrix matrix(1, 0, 0, v.x,
                  0, 1, 0, v.y,
                  0, 0, 1, v.z,
                  0, 0, 0, 1);
    return matrix;
}

Matrix scalingMatrix(double xFactor, double yFactor, double zFactor) {
    Matrix matrix(xFactor, 0, 0, 0,
                  0, yFactor, 0, 0,
                  0, 0, zFactor, 0,
                  0, 0, 0, 1);
    return matrix;
}

Matrix scalingMatrix(double scaleFactor) {
    return scalingMatrix(scaleFactor, scaleFactor, scaleFactor);
}

Matrix xRotate(double thetaDeg) {
    double thetaRad = thetaDeg * deg_to_rad;
    return Matrix(1, 0, 0, 0,
                  0, cos(thetaRad), -sin(thetaRad), 0,
                  0, sin(thetaRad), cos(thetaRad), 0,
                  0, 0, 0, 1);

}

Matrix yRotate(double thetaDeg) {
    double thetaRad = thetaDeg * deg_to_rad;
    return Matrix(cos(thetaRad), 0, sin(thetaRad), 0,
                  0, 1, 0, 0,
                  -sin(thetaRad), 0, cos(thetaRad), 0,
                  0, 0, 0, 1);

}

Matrix zRotate(double thetaDeg) {
    double thetaRad = thetaDeg * deg_to_rad;
    return Matrix(cos(thetaRad), -sin(thetaRad), 0, 0,
                  sin(thetaRad), cos(thetaRad), 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1);

}
