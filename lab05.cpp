#include <iostream>
#include <ctime>
#include <vector>

double f(double c, double d, double x) {
	return (c * x + d);
}

double x_rand(double xMin, double xMax) {
	double x = (double)rand() / RAND_MAX;
	return xMin + x * (xMax - xMin);
}

double calc_c_mnk(int N, double sum_x, double sum_y, double sum_xy, double sum_xx) {
	return (N * sum_xy - sum_x * sum_y) / (N * sum_xx  - sum_x * sum_x);
}

double calc_d_mnk(int N, double sum_x, double sum_y, double c_) {
	return (sum_y - c_ * sum_x) / N;
}


int main() {
	srand(time(0));
	double a = 0;
	double b = 10;
	double c = -500; //mnk
	double d = 200; //mnk
	int N = 24;
	int A = 1000;
	double error = 0;
	double x_step = (b - a) / N;
	double x_point = 0;

	std::vector<std::pair<double, double>> y_vec;
	std::vector<std::pair<double, double>> y_vec_error;
	for (int i = 0; i <= N; i++) {
		x_point = a + i * x_step;
		y_vec.push_back(std::make_pair(x_point, f(c, d, x_point)));
		error = A * x_rand(-0.5, 0.5);
		y_vec_error.push_back(std::make_pair(x_point, f(c, d, x_point) + error));
	}

	double sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0;

	for (auto& el : y_vec) {
		sum_x += el.first;
		sum_y += el.second;
		sum_xy += el.first * el.second;
		sum_xx += el.first * el.first;
		std::cout << "X = " << el.first << " " << "Y = " << el.second << std::endl;
	}

	double c_ = calc_c_mnk(N, sum_x, sum_y, sum_xy, sum_xx);
	double d_ = calc_d_mnk(N, sum_x, sum_y, c_);
	std::cout << "Without noise: " << c_ << " " << d_ << std::endl;

	sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0;

	for (auto& el : y_vec_error) {
		sum_x += el.first;
		sum_y += el.second;
		sum_xy += el.first * el.second;
		sum_xx += el.first * el.first;
		std::cout << "X = " << el.first << " " << "Y = " << el.second << std::endl;
	}

	 c_ = calc_c_mnk(N, sum_x, sum_y, sum_xy, sum_xx);
	 d_ = calc_d_mnk(N, sum_x, sum_y, c_);

	std::cout << "With noise: " << c_ << " " << d_ << std::endl;
}
