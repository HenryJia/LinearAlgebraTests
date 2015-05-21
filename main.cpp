#include <iostream>
#include <Eigen/Dense>
#include <chrono>
#include <lapackpp.h>
#include <armadillo>
#include <opencv2/opencv.hpp>

using namespace Eigen;
using namespace std;
using namespace arma;
using namespace cv;

double testEigen()
{
	auto start = chrono::steady_clock::now();
	MatrixXd a = MatrixXd::Random(300000, 80);
	MatrixXd b = MatrixXd::Random(80, 30);
	MatrixXd result(300000, 30);
	result = a * b;
	auto end = chrono::steady_clock::now();
	auto elapsed = end - start;
	return chrono::duration <double> (elapsed).count();
}

double testLapack()
{
	auto start = chrono::steady_clock::now();
	LaGenMatDouble a = LaGenMatDouble::rand(300000, 80);
	LaGenMatDouble b = LaGenMatDouble::rand(80, 30);
	LaGenMatDouble result(300000, 30);
	Blas_Mat_Mat_Mult(a, b, result, 1.0, 0.0);
	auto end = chrono::steady_clock::now();
	auto elapsed = end - start;
	return chrono::duration <double> (elapsed).count();
}

double testArmadillo()
{
	auto start = chrono::steady_clock::now();
	mat a = randu<mat>(300000, 80);
	mat b = randu<mat>(80, 30);
	mat c = a * b;
	auto end = chrono::steady_clock::now();
	auto elapsed = end - start;
	return chrono::duration <double> (elapsed).count();
}

double testOpenCV()
{
	auto start = chrono::steady_clock::now();
	RNG rng(0xFFFFFFFF);
	cv::Mat a(300000, 80, CV_32FC1);
	cv::Mat b(80, 30, CV_32FC1);
	cv::randu(a, 0.0, 1.0);
	cv::randu(b, 0.0, 1.0);
	cv::Mat c = a * b;
	auto end = chrono::steady_clock::now();
	auto elapsed = end - start;
	return chrono::duration <double> (elapsed).count();
}

int main()
{
	cout << "Eigen Start" << endl;
	cout << testEigen() << " s" << endl;
	cout << "Lapack Start" << endl;
	cout << testLapack() << " s" << endl;
	cout << "Armadillo Start" << endl;
	cout << testArmadillo() << " s" << endl;
	cout << "OpenCV Start" << endl;
	cout << testOpenCV() << " s" << endl;
	cout << "Finished, press enter to end" << endl;
	getchar();
}
