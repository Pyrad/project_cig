/*
 * smart_pointer_test.cpp
 *
 *  Created on: Dec 25th, 2017
 *      Author: Pyrad
 */


#ifndef USE_DEPRECATED_FEATURES
#define USE_DEPRECATED_FEATURES 0
#endif // USE_DEPRECATED_FEATURES

#include<stdio.h>
#include "smart_pointer_test.hpp"

// ----Smart Pointers----
//1. std::auto_ptr
//2. boost::scoped_ptr
//3. boost::shared_ptr
//4. boost::scoped_array
//5. boost::shared_array
//6. boost::weak_ptr
//7. boost:: intrusive_ptr

// std::auto_ptr
#include<memory>
// boost::scoped_ptr
// boost::shared_ptr
// boost::scoped_array
// boost::weak_ptr
#include<boost/smart_ptr.hpp>

namespace smart_pointer_test {

#if USE_DEPRECATED_FEATURES
void test_std_autoptr() {
	std::auto_ptr<Simple> my_memory(new Simple(1));
	if(my_memory.get()) {
		my_memory->PrintSomething();
		my_memory.get()->info_extend = "Addition";
		my_memory->PrintSomething();
		(*my_memory).info_extend += " other";
		my_memory->PrintSomething();
	}
}

void test_std_autoptr_1() {
	std::auto_ptr<Simple> my_memory(new Simple(1));
	if(my_memory.get()) {
		std::auto_ptr<Simple> my_memory2;
		my_memory2 = my_memory;
		my_memory2->PrintSomething();
		if(my_memory.get()) {
			my_memory->PrintSomething();
		} else {
			printf("Now pointer 'my_memory' is EMPTY!\n");
		}
	}
}

void test_std_autoptr_2() {
	std::auto_ptr<Simple> my_memory(new Simple(1));
	std::auto_ptr<Simple> my_memory1(new Simple(2));

	// If we want to release a big chunk of memory immediately
	// Better use '->reset' other than just use '->release'
	// Because the use of '->release' will cause memory leakage(MLK)
	if(my_memory.get()) {
		my_memory.reset();
	}

	// Or you can use '->release' and 'delete' together
	// Since '->release' just give in administration authority
	if(my_memory1.get()) {
		Simple *p = my_memory1.release();
		delete p;
	}
}
#endif // USE_DEPRECATED_FEATURES


void test_scoped_ptr() {
	boost::scoped_ptr<Simple> my_memory(new Simple(1));
	if(my_memory.get()) {
		my_memory->PrintSomething();
		my_memory.get()->info_extend = "Addition";
		my_memory->PrintSomething();
		(*my_memory).info_extend += " other";
		my_memory->PrintSomething();

		// boost::scoped_ptr has NO member function 'release()'

		// If Simple has no overloaded function 'operator='
		// then assignment will be a compilation error!
		// If Simple has no overloaded copy constructor
		// then it is illegal to use copy assignment
		// std::auto_ptr<Simple> my_memory2;
		// my_memory2 = my_memory;
	}
}

// boost::shared_ptr supports arguments copying, passing
void test_shared_ptr(boost::shared_ptr<Simple> memory) {
	memory->PrintSomething();
	printf("test_shared_ptr UseCount: %ld\n\n", memory.use_count());
}

void test_shared_ptr_wrapper() {
	boost::shared_ptr<Simple> my_memory(new Simple(1));
	if(my_memory.get()) {
		my_memory->PrintSomething();
		my_memory.get()->info_extend = "Addition";
		my_memory->PrintSomething();
		(*my_memory).info_extend += " other";
		my_memory->PrintSomething();
	}

	printf("test_shared_ptr_wrapper UseCount: %ld\n", my_memory.use_count());
	test_shared_ptr(my_memory);
	printf("test_shared_ptr_wrapper UseCount: %ld\n", my_memory.use_count());
}

void test_scoped_array() {
	printf("*****Running test_scoped_array*****\n");
	boost::scoped_array<Simple> my_memory(new Simple[10]);
	for(int i = 0; i < 10; i++) {
		my_memory[i].SetNumber(i+1);
	}
	if(my_memory.get()) {
		my_memory[0].PrintSomething();
		my_memory.get()[0].info_extend = "Addition";
		my_memory[0].PrintSomething();
		// Since no 'operator*' overloaded, so error using '*'
		// (*my_memory)[0].info_extend += " other";

		// No 'release' function
		// my_memory[0].release();

		// No overloaded assignment function 'operator='
		// boost::scoped_array<Simple> my_memory2;
		// my_memory2 = my_memory;
	}
}

void test_shared_array(boost::shared_array<Simple> memory) {
	printf("test_shared_array UseCount: %ld\n", memory.use_count());
}

void test_shared_array_wrapper() {
	printf("*****Running test_shared_array*****\n");

	boost::shared_array<Simple> my_memory(new Simple[10]);
	for(int i = 0; i < 10; i++) {
		my_memory[i].SetNumber(i+10);
	}
	if(my_memory.get()) {
		my_memory[0].PrintSomething();
		my_memory.get()[0].info_extend = "Addition";
		my_memory[0].PrintSomething();
		my_memory[1].PrintSomething();
		my_memory.get()[1].info_extend = "Addition";
		my_memory[1].PrintSomething();
	}
	printf("test_shared_array_wrapper UseCount: %ld\n", my_memory.use_count());
	test_shared_array(my_memory);
	printf("test_shared_array_wrapper UseCount: %ld\n", my_memory.use_count());
}

void test_weak_ptr() {
	printf("*****Running test_weak_ptr*****\n");

	boost::weak_ptr<Simple> my_memory_weak;
	boost::shared_ptr<Simple> my_memory(new Simple(1));
	boost::shared_ptr<Simple> my_memory2;


	printf("test_weak_ptr boost::shared_ptr UseCount: %ld\n", my_memory.use_count());
	my_memory_weak = my_memory;
	printf("test_weak_ptr boost::shared_ptr UseCount: %ld\n", my_memory.use_count());
	my_memory2 = my_memory;
	printf("test_weak_ptr boost::shared_ptr UseCount: %ld\n", my_memory.use_count());

}

void test_alpha_beta() {
	printf("*****Running test_alpha_beta*****\n");

	boost::shared_ptr<alpha> pa(new alpha("Fox"));
	printf("p UseCount: %ld\n", pa.use_count());
	beta pb("Deer", pa);
	printf("p UseCount: %ld\n", pa.use_count());
	pb.print_ptr_count();
}


void run_smart_pointer_test() {
#if USE_DEPRECATED_FEATURES
	test_std_autoptr();
	test_std_autoptr_1();
	test_std_autoptr_2();
#endif // USE_DEPRECATED_FEATURES

	test_scoped_ptr();

	test_shared_ptr_wrapper();

	test_scoped_array();

	test_shared_array_wrapper();

	test_weak_ptr();

	test_alpha_beta();
}


} // smart_pointer_test
