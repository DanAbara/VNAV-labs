#include <iostream>
#include <Eigen/Dense>

int main() {
    Eigen::MatrixXd A(2,2);
    A(0,0) = 1.5;
    A(0,1) = 2.05;
    A(1,0) = -2.3;
    A(1,1) = -0.4;
    std::cout << A << std::endl;
}
