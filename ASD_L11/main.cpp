#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <functional>
#include "aho-corasick.h"

std::string random_string(int length, const std::string& alphabet)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, alphabet.size() - 1);

	std::string result;
	result.reserve(length);

	for (int i = 0; i < length; ++i)
	{
		result += alphabet[dis(gen)];
	}

	return result;
}

std::string bad(int length)
{
	return std::string(length, 'a');
}

std::string good(int length)
{
	const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	return random_string(length, alphabet);
}

std::string average(int length)
{
	const std::string pattern = "aabbaabbccdd";
	std::string result;
	result.reserve(length);

	while (result.size() < static_cast<size_t>(length))
	{
		result += pattern;
	}

	return result.substr(0, length);
}

int main()
{
	{
		std::ofstream outfile("bad.csv");
		if (!outfile.is_open()) throw std::exception("Проблемы с файлом");

		outfile << "Длина,Время(мс),Сравнения\n";

		AhoCorasick ac;

		ac.add_pattern("aaa");
		ac.add_pattern("aa");
		ac.add_pattern("a");

		ac.build_links();

		for (int length = 1000; length <= 50000; length += 1000)
		{
			std::string text = bad(length);

			ac.reset();

			auto start = std::chrono::high_resolution_clock::now();
			auto matches = ac.search(text);
			auto end = std::chrono::high_resolution_clock::now();

			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			int comparisons = ac.compares();

			outfile << length << "," << duration << "," << comparisons << "\n";
		}
	}
	{
		std::ofstream outfile("average.csv");
		if (!outfile.is_open()) throw std::exception("Проблемы с файлом");

		outfile << "Длина,Время(мс),Сравнения\n";

		AhoCorasick ac;

		ac.add_pattern("aaa");
		ac.add_pattern("aa");
		ac.add_pattern("a");

		ac.build_links();

		for (int length = 1000; length <= 50000; length += 1000)
		{
			std::string text = average(length);

			ac.reset();

			auto start = std::chrono::high_resolution_clock::now();
			auto matches = ac.search(text);
			auto end = std::chrono::high_resolution_clock::now();

			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			int comparisons = ac.compares();

			outfile << length << "," << duration << "," << comparisons <<"\n";
		}
	}
	{
		std::ofstream outfile("good.csv");
		if (!outfile.is_open()) throw std::exception("Проблемы с файлом");

		outfile << "Длина,Время(мс),Сравнения\n";

		AhoCorasick ac;

		ac.add_pattern("aaa");
		ac.add_pattern("aa");
		ac.add_pattern("a");
		int pattern_count = 3;

		ac.build_links();

		for (int length = 1000; length <= 50000; length += 1000)
		{
			std::string text = good(length);

			ac.reset();

			auto start = std::chrono::high_resolution_clock::now();
			auto matches = ac.search(text);
			auto end = std::chrono::high_resolution_clock::now();

			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			int comparisons = ac.compares();

			outfile << length << "," << duration << "," << comparisons << "\n";
		}
	}
}