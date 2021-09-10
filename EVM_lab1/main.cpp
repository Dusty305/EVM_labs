#include <iostream>
#include <string>
using namespace std;

#define LD_SIZE sizeof(long double)
#define UC_SIZE sizeof(unsigned char)

union LongDoubleBits
{
	long double ld;
	struct
	{
		unsigned char bits_arr[LD_SIZE];
	};
};

void printUCharBin(unsigned char uc);
void printLDoubleBin(long double ld);

unsigned char changeUChar(unsigned char uc, const int number, const int value);
unsigned char changeUCharBits(unsigned char uc);
long double changeLDoubleBits(long double ld);

int main()
{
	unsigned char uc = 124;
	printUCharBin(uc);
	cout << endl;

	long double ld = 15.375;
	printLDoubleBin(ld);
	cout << endl;

	changeUCharBits(uc);
	changeLDoubleBits(ld);

	return 0;
}

void printUCharBin(unsigned char uc)
{
	for (int i = UC_SIZE * 8 - 1; i >= 0; i--)
		cout << ((uc >> i) & 1);
}

void printLDoubleBin(long double ld)
{
	LongDoubleBits ld_bin = { ld };

	for (int i = LD_SIZE - 1; i >= 0; i--)
		printUCharBin(ld_bin.bits_arr[i]);
}

unsigned char changeUChar(unsigned char uc, const int number, const int value)
{
	int bit = (uc >> number) & 1;
	if (bit != value)
		uc += bit ? -(1 << number) : (1 << number);
	return uc;
}

unsigned char changeUCharBits(unsigned char uc)
{
	int size, number, value;

	cout << "The initial number: " << (int)uc << endl
		<< "Binary representation of the number: ";
	printUCharBin(uc);

	cout << endl << "Write how many bits you want to change: ";
	cin >> size;
	for (int i = 0; i < size; i++) {
		cout << i + 1 << ". Write the number (7...0) of a bit you want to change and its value: ";
		cin >> number >> value;

		uc = changeUChar(uc, number, value);
	}

	cout << "Changed number: " << (int)uc << endl
		<< "Binary representation of the number: ";
	printUCharBin(uc);
	cout << endl;

	return uc;
}

long double changeLDoubleBits(long double ld)
{
	int size, number, value;
	LongDoubleBits ld_bits = { ld };

	cout << "The initial number: " << ld << endl
		<< "Binary representation of the number: ";
	printLDoubleBin(ld);

	cout << endl << "Write how many bits you want to change: ";
	cin >> size;
	for (int i = 0; i < size; i++) {
		cout << i + 1 << ". Write the number (" + to_string(LD_SIZE * 8 - 1) + "...0) of a bit you want to change and its value: ";
		cin >> number >> value;

		ld_bits.bits_arr[number / 8] = changeUChar(ld_bits.bits_arr[number / 8], number % 8, value);
	}

	cout << "Changed number: " << ld_bits.ld << endl
		<< "Binary representation of the number: ";
	printLDoubleBin(ld_bits.ld);
	cout << endl;

	return ld_bits.ld;
}