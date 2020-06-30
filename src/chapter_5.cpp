/*
 * chapter_5.hpp
 *
 *  Created on: Oct. 15, 2017
 *      Author: Pyrad
 * Description: Source file of chapter 5 String Problems
 *   Intention: Solutions for problems in Chapter 5[String Problems] of Code Interview Guide
 */



#include "chapter_5.hpp"
#include "chapter_5_tests.hpp"

#include <stdio.h>

namespace C5 {

// [TIME_STAMP] Start at 12:31, 2017/11/26

// --------------------------------------------------------------------------------------------------------------
// 5.1 Judge if two words are anagrams
void test_5_1() {
	const std::string str1("ambulence");
	const std::string str2("banana");
	printf("If %s and %s are anagrams: %s\n", str1.c_str(), str2.c_str(), if_two_words_are_anagrams(str1, str2) ? "Yes" : "No");
}

void test_5_2() {
	const std::string str1("A1CD2E33");
	const std::string str2("A-1BC--12");
	const std::string str3("A-1B--2C--D6E");
	printf("Sum of string %s is: %d\n", str1.c_str(), total_digits_sum_in_string(str1));
	printf("Sum of string %s is: %d\n", str2.c_str(), total_digits_sum_in_string(str2));
	printf("Sum of string %s is: %d\n", str3.c_str(), total_digits_sum_in_string(str3));
}


void test_5_3() {
	const std::string str("A0B00C000D0000E00000");
	printf("Remove 1 '0' in %s: %s\n", str.c_str(), remove_k_0_in_string(str, 1).c_str());
	printf("Remove 2 '0' in %s: %s\n", str.c_str(), remove_k_0_in_string(str, 2).c_str());
	printf("Remove 3 '0' in %s: %s\n", str.c_str(), remove_k_0_in_string(str, 3).c_str());
	printf("Remove 4 '0' in %s: %s\n", str.c_str(), remove_k_0_in_string(str, 4).c_str());
	printf("Remove 5 '0' in %s: %s\n", str.c_str(), remove_k_0_in_string(str, 5).c_str());
}

void test_5_4() {
	const std::string str1("ambulance");
	const std::string str2("lanceambu");
	printf("'%s' is or not rotated from '%s': %s\n", str1.c_str(), str2.c_str(), is_rotated_word(str1, str2) ? "Yes" : "No");
}

void test_5_5() {
	std::string str1("12abcabca4");
	std::string str2("12abccabcababc4");
	std::string str3("12abcababc4");

	const std::string from("abc");
	const std::string to("xyz");

	std::cout << str1 << " => " << replace_repeated_strings(str1, from, to) << std::endl;
	std::cout << str2 << " => " << replace_repeated_strings(str2, from, to) << std::endl;
	std::cout << str3 << " => " << replace_repeated_strings(str3, from, to) << std::endl;

	// printf("%s\n", str.c_str()); if str contains '\0', won't work

}

void test_5_7_1() {
	// a_1_b_1_d_1_a_2_b_2_c_2_d_3_e_1_f_2_g_1
	std::string str1("abdaabbccdddeffg");
	std::cout << string_successive_char_statistics(str1) << std::endl;

	std::string str2("a");
	std::cout << string_successive_char_statistics(str2) << std::endl;

	std::string str3("aa");
	std::cout << string_successive_char_statistics(str3) << std::endl;

	std::string str4("ab");
	std::cout << string_successive_char_statistics(str4) << std::endl;
}

void test_5_7_2() {
	// a_1_b_1_d_1_a_2_b_2_c_2_d_3_e_1_f_2_g_1
	// abdaabbccdddeffg
	std::string str("a_1_b_1_d_1_a_2_b_2_c_2_d_3_e_1_f_2_g_1");
	// std::cout << "Position " << 14 << " = >" << find_char_in_string_statistics_by_order(str, 14) << std::endl;
	for(std::size_t pos = 1; pos < 20; pos++) {
		// printf("current position: %d, pos);
		std::cout << "Position " << pos << " = >" << find_char_in_string_statistics_by_order(str, pos) << std::endl;
	}

}

void test_5_8() {
	const int num = 4;
	std::string test_strings[4] = {"ambulance", "zxzxyayaefefpqqp", "next", "woman"};
	for(int i = 0; i < num; i++) {
		printf("String '%s' has repeated chars: %s\n", test_strings[i].c_str(),  if_any_char_appear_only_once_use_heap_sort(test_strings[i]) ? "Yes" : "No");
	}
}

void test_5_9() {

}


void test_5_10_1() {
	const int SIZE = 30;
	char chars1[SIZE] = {'a', ' ', 'b', ' ', 'c', ' ', 'd', ' ', 'e', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	adjust_and_replace(chars1, SIZE, "XYZ");
	CU::print_char_array(chars1, SIZE);
}

void test_5_10_2() {
	const int SIZE = 30;
	char chars2[SIZE] = {'a', '*', 'b', '*', 'c', '*', 'd', '*', 'e', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	move_all_star_chars_to_front(chars2, SIZE);
	CU::print_char_array(chars2, SIZE);
}


void test_5_11() {
	std::string str("Nice to meet you!");
	reverse_all_words_in_string(str);

	str = std::string("Today   is    a   good day, isn't    it?");
	reverse_all_words_in_string(str);
}

void test_5_12_1() {
	const int SIZE = 30;
	const std::string ss[] = {"spam", "ham", "eggs", "bread", "toast", "apple", "garlic", "watermelon", "butter", "oil", \
								"milk", "banana", "oil", "suggar", "garlic", "onion", "pepper", "salt", "tomato", "oil", \
								"pork", "beef", "lamb", "potato", "leek", "carrot", "garlic", "celery", "carp", "bean"};
	const std::string item1("oil");
	const std::string item2("garlic");
	const std::string item3("eggs");
	const std::string item4("potato");

	const int ITEM_SIZE = 6;
	const std::string items[ITEM_SIZE] = {"oil", "garlic", "eggs", "potato", "noodle", "lobster"};

	std::vector<std::string> svec(CU::convert_to_string_vector(ss, SIZE));

	for(int i = 0; i < ITEM_SIZE; i++) {
		for(int j = i + 1; j < ITEM_SIZE; j++) {
			int mdist = min_dist_two_strings_in_string_array(svec, items[i], items[j]);
			printf("The minimum distance between '%s' and '%s' is: %d\n", items[i].c_str(), items[j].c_str(), mdist);
		}
	}
}

void test_5_12_2() {
	const int SIZE = 30;
	const std::string ss[] = {"spam", "ham", "eggs", "bread", "toast", "apple", "garlic", "watermelon", "butter", "oil", \
								"milk", "banana", "oil", "suggar", "garlic", "onion", "pepper", "salt", "tomato", "oil", \
								"pork", "beef", "lamb", "potato", "leek", "carrot", "garlic", "celery", "carp", "bean"};
	const std::string item1("oil");
	const std::string item2("garlic");
	const std::string item3("eggs");
	const std::string item4("potato");

	const int ITEM_SIZE = 6;
	const std::string items[ITEM_SIZE] = {"oil", "garlic", "eggs", "potato", "noodle", "lobster"};

	std::vector<std::string> svec(CU::convert_to_string_vector(ss, SIZE));
	std::vector<std::pair<std::string, std::string> > qvec;
	for(int i = 0; i < ITEM_SIZE; i++) {
		for(int j = i + 1; j < ITEM_SIZE; j++) {
			qvec.push_back(std::make_pair(items[i], items[j]));
		}
	}
	std::vector<int> results;

	records_relation rds(svec);
	rds.query_min_distance(qvec, results);
	printf("\n");
	CU::print_int_vector(results);
}

void test_5_13() {
	std::string test_string("good");
	std::string pstring(get_palindrome_adding_min_chars(test_string));

	printf("Original string: \t%s\n", test_string.c_str());
	printf("Palindrome string: \t%s\n", pstring.c_str());

	test_string = "ambulance";
	pstring = get_palindrome_adding_min_chars(test_string);
	printf("Original string: \t%s\n", test_string.c_str());
	printf("Palindrome string: \t%s\n", pstring.c_str());

	printf("\n");
}

void test_5_14() {
	std::string test_string("(())(())()()((()()))");
	int max_valid_substring_length = max_length_of_valid_parentheses_substring(test_string);
	if(max_valid_substring_length < 0) {
		printf("Error!\n");
	}

	test_string = "(())(())()()(((())";
	max_valid_substring_length = max_length_of_valid_parentheses_substring(test_string);
	if(max_valid_substring_length < 0) {
		printf("Error!\n");
	}

	test_string = "())(())()()(((())";
	max_valid_substring_length = max_length_of_valid_parentheses_substring(test_string);
	if(max_valid_substring_length < 0) {
		printf("Error!\n");
	}
}

void test_5_15() {
	std::string test_string("9*(3+2)-1");
	std::pair<int, int> res(get_formula_string_value(test_string, 0));
	printf("The result of '%s' is: %d\n", test_string.c_str(), res.first);

	test_string = "30+1+2*9";
	res = get_formula_string_value(test_string, 0);
	printf("The result of '%s' is: %d\n", test_string.c_str(), res.first);

	test_string = "30+(1+2)*9";
	res = get_formula_string_value(test_string, 0);
	printf("The result of '%s' is: %d\n", test_string.c_str(), res.first);

	test_string = "30+(2-1)*9";
	res = get_formula_string_value(test_string, 0);
	printf("The result of '%s' is: %d\n", test_string.c_str(), res.first);
}

void test_5_16() {
	int test_num = 10;
	printf("(n=%d)Total string number satisfying 1 at the left of 0: %d\n", test_num, total_string_number_one_before_zero(test_num));
	printf("(n=%d)Total string number satisfying 1 at the left of 0: %d\n", test_num, total_string_number_one_before_zero_space_saving(test_num));

	 test_num = 3;
	 printf("(n=%d)Total string number satisfying 1 at the left of 0: %d\n", test_num, total_string_number_one_before_zero(test_num));
	 printf("(n=%d)Total string number satisfying 1 at the left of 0: %d\n", test_num, total_string_number_one_before_zero_space_saving(test_num));
}

void test_5_17() {
	const int SIZE = 2;
	const std::string ss1[] = {"abc", "de"};
	const std::string ss2[] = {"b", "ba"};

	std::vector<std::string> svec1(CU::convert_to_string_vector(ss1, SIZE));
	printf("ss1 after concatenation: %s\n", concatenate_strings_min_dict_value(svec1).c_str());

	std::vector<std::string> svec2(CU::convert_to_string_vector(ss2, SIZE));
	printf("ss2 after concatenation: %s\n", concatenate_strings_min_dict_value(svec2).c_str());
}


void test_5_18() {
	std::string test_string("abcd");
	printf("The max length of substring without duplication for string %s is: %d\n", test_string.c_str(), max_substring_without_duplication(test_string));

	test_string = "aabcb";
	printf("The max length of substring without duplication for string %s is: %d\n", test_string.c_str(), max_substring_without_duplication(test_string));

}

void test_5_19() {
	std::string test_string("aaABCDEcBCg");
	int k = 7;
	printf("String is '%s', new type char at position %d is: %s\n", test_string.c_str(), k, new_type_char_at_position(test_string, k).c_str());

	k = 4;
	printf("String is '%s', new type char at position %d is: %s\n", test_string.c_str(), k, new_type_char_at_position(test_string, k).c_str());

	k = 10;
	printf("String is '%s', new type char at position %d is: %s\n", test_string.c_str(), k, new_type_char_at_position(test_string, k).c_str());
}

void test_5_20() {
	std::string str1("abcde");
	std::string str2("ac");
	printf("Shorteset length of substring in str1('%s') containing all chars in str2('%s') is: %d\n", str1.c_str(), str2.c_str(), shortest_substring_containing_another_string(str1, str2));

	str1 = "12345";
	str2 = "344";
	printf("Shorteset length of substring in str1('%s') containing all chars in str2('%s') is: %d\n", str1.c_str(), str2.c_str(), shortest_substring_containing_another_string(str1, str2));


	str1 = "acbfhcdefgfh";
	str2 = "cf";
	printf("Shorteset length of substring in str1('%s') containing all chars in str2('%s') is: %d\n", str1.c_str(), str2.c_str(), shortest_substring_containing_another_string(str1, str2));

	str1 = "cccacmkgdfeeeckf";
	str2 = "cf";
	printf("Shorteset length of substring in str1('%s') containing all chars in str2('%s') is: %d\n", str1.c_str(), str2.c_str(), shortest_substring_containing_another_string(str1, str2));

}

void test_5_21() {
	std::string test_string("ABA");
	printf("The min palindrome-paritioning times for string '%s' is: %d\n", test_string.c_str(), palindrome_partition(test_string));

	test_string = "ACDCDCDAD";
	printf("The min palindrome-paritioning times for string '%s' is: %d\n", test_string.c_str(), palindrome_partition(test_string));
}

void test_5_23() {
	Trie* a_trie = new Trie;

	a_trie->insert("abc");
	a_trie->insert("abcd");
	a_trie->insert("abd");
	a_trie->insert("b");
	a_trie->insert("bcd");
	a_trie->insert("efg");
	a_trie->insert("hik");

	std::string str("abc");
	printf("If '%s' exists in the trie: %s\n", str.c_str(), a_trie->search(str) ? "Yes" : "No");
	str = "k";
	printf("If '%s' exists in the trie: %s\n", str.c_str(), a_trie->search(str) ? "Yes" : "No");
	str = "hig";
	printf("If '%s' exists in the trie: %s\n", str.c_str(), a_trie->search(str) ? "Yes" : "No");
	str = "efg";
	printf("If '%s' exists in the trie: %s\n", str.c_str(), a_trie->search(str) ? "Yes" : "No");

	printf("Remove '%s' from trie...\n", str.c_str());
	a_trie->remove(str);
	printf("If '%s' exists in the trie: %s\n", str.c_str(), a_trie->search(str) ? "Yes" : "No");

	delete a_trie;
}

void test_5_all() {
	test_5_1();
	test_5_2();
	test_5_3();
	test_5_4();
	test_5_5();
	// test_5_6();
	test_5_7_1();
	test_5_7_2();
	test_5_8();
	test_5_9();
	test_5_10_1();
	test_5_10_1();
	test_5_11();
	test_5_12_1();
	test_5_12_2();
	test_5_13();
	test_5_14();
	test_5_15();
	test_5_16();
	test_5_17();
	test_5_18();
	test_5_19();
	test_5_20();
	test_5_21();
	// test_5_22();
	test_5_23();
}


// [TIME_STAMP] Stop at

} // namespace C5








































