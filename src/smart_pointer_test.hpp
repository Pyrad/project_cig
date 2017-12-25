/*
 * smart_pointer_test.hpp
 *
 *  Created on: 2017 Dec 25
 *      Author: Pyrad
 */

#ifndef SMART_POINTER_TEST_HPP_
#define SMART_POINTER_TEST_HPP_

#include <iostream>
#include<boost/smart_ptr.hpp>


namespace smart_pointer_test {

void run_smart_pointer_test();

class Simple {
public:
	Simple(int param = 0) {
		number = param;
		std::cout << "Simple: " << number << std::endl;
	}

	~Simple() {
		std::cout << "~Simple: " << number << std::endl;
	}

	void PrintSomething() {
		std::cout << "PrintSomething: " << info_extend.c_str() << std::endl;
	}

	void SetNumber(int n) {
		number = n;
	}

	std::string info_extend;
	int number;
};

class alpha {
public:
	alpha(): m_str("alpha") {}
	alpha(const std::string& s): m_str(s) {}

	~alpha() {
		printf("Deleting alpha\n");
	}

	std::string m_str;
};

class beta {
public:
	beta(): m_str("alpha") {}
	beta(const std::string& s): m_str(s) {}
	beta(const std::string& s, boost::shared_ptr<alpha> p): m_str(s), m_ptr(p) {}

	~beta() {
		printf("Deleting beta, m_ptr UseCount: %ld\n", m_ptr.use_count());
	}


	void print_ptr_count() {
		printf("[class beta] get_ptr_count m_ptr useCount: %ld\n", m_ptr.use_count());
	}

	std::string m_str;
	boost::shared_ptr<alpha> m_ptr;
};


} // smart_pointer_test


#endif /* SMART_POINTER_TEST_HPP_ */
