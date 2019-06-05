/////////////////////////////////////////////////////////////////////////
// Workshop 7: Algorithms
// File: DataTable.h
// Date: July 16, 2018
// Author: Ricky Zaman
// Id: 121942171
// Email: rzaman6@myseneca.ca
// Implemented everything in the headerfile because using class template 
/////////////////////////////////////////////////////////////////////////
#pragma once 

#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>
#include<iomanip>
#include<functional>

namespace w7 {

	template<class T>
	class DataTable {
		std::vector<T>x, y;
		int fwidth;
		int noDecimals; 

	public:
		DataTable():fwidth(0), noDecimals(0) {

		}

		DataTable(std::ifstream& in, int width, int decimals):fwidth(width),noDecimals(decimals) {
			T nx, ny;
			if (in.is_open()) {
				while (!in.eof()) {
					in >> nx;
					x.push_back(nx);
					in >> ny;
					y.push_back(ny);
				}
			}
		}


		T mean() const {
			T result = std::accumulate(y.begin(), y.end(), (T)0) / (T)y.size();
			return result; 
		}

		T sigma() const {
			T mavg = mean(); 
			T sum = 0; 
			T result; 

			for (size_t i = 0; i < y.size(); i++) {
				sum += (y.at(i) - mavg)*(y.at(i) - mavg);   //multiply by itself to model squared
			}
			result = sqrt(sum / ((T)y.size() - 1)); 
			return result; 
		}

		T median() const {
			std::vector<T> temp = y;
			sort(temp.begin(), temp.end()); //didn't use std::sort because it switches to qsort

			return temp[temp.size() / 2];
		}

		void regression(T& slope, T& y_intercept) const {
			T SX = std::accumulate(x.begin(), x.end(), (T)0);   //SX= Sum of X
			T SY = std::accumulate(y.begin(), y.end(), (T)0); //SY= Sum of Y
			T SXX = std::inner_product(x.begin(), x.end(), x.begin(), (T)0); //SXX= sum of (X)(X)
			T SXY = std::inner_product(x.begin(), x.end(), y.begin(), (T)0); //SXY= sum of (X)(Y)
			T size = y.size(); 

			slope = ((size*SXY) - (SX*SY)) / ((size*SXX) - (SX*SX));
			y_intercept = (SY - (slope*SX)) / size;
		}

		void display(std::ostream& os) const {
			os << std::setw(fwidth) << std::right << "x";
			os << std::setw(fwidth) << std::right << "y" << std::endl;

			for (int i = 0; i < x.size(); i++) {
				os << std::setw(fwidth) << std::fixed << std::setprecision(noDecimals) << x[i];
				os << std::setw(fwidth) << std::fixed << std::setprecision(noDecimals) << y[i] << std::endl;
			}
		}
	};

	template<class T>
	std::ostream& operator<<(std::ostream& os, const DataTable<T> &data) {
		data.display(os);
		return os; 
	}


}