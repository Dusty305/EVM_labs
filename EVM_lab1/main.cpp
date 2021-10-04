#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
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
	int uc;
	string emptyStr;

	cout << "======Unsigned char======\n";

	do
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "\nWrite first num(unsigned char 0..255): " << endl;
        cin >> uc;
        getline(cin, emptyStr);

    } while (cin.fail() || !emptyStr.empty() || uc > 255 || uc < 0);
	
	(unsigned char)uc;
	
	cout << "\n";
	changeUCharBits(uc);

	cout << "\n======Long double======\n";
	long double ld;
	do
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "\nWrite second num(long double): " << endl;
        cin >> ld;
        getline(cin, emptyStr);

    } while (cin.fail() || !emptyStr.empty());

	cout << "\n";
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
	string emptyStr;

	cout << "The initial number: " << (int)uc << endl
		<< "Binary representation of the number: ";
	printUCharBin(uc);


	do
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << endl << "Write how many bits you want to change(0..8): ";
        cin >> size;
        getline(cin, emptyStr);

    } while (cin.fail() || !emptyStr.empty() || size > 8 || size < 0);


	for (int i = 0; i < size; i++) {
		do
    	{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << i + 1 << ". Write the number (7...0) of a bit you want to change and its value: ";
			cin >> number >> value;
			getline(cin, emptyStr);
    	} while (cin.fail() || !emptyStr.empty() || number > 7 || number < 0 || value < 0 || value > 1);


		uc = changeUChar(uc, number, value);
	}

	cout << "---Result---\n";
	cout << "Changed number: " << (int)uc << endl
		<< "Binary representation of the number: ";
	printUCharBin(uc);
	cout << endl;

	return uc;
}

long double changeLDoubleBits(long double ld)
{
	int size, number, value;
	string emptyStr;
	LongDoubleBits ld_bits = { ld };

	cout << "The initial number: " << ld << endl
		<< "Binary representation of the number: ";
	printLDoubleBin(ld);


	do
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << endl << "Write how many bits you want to change: ";
        cin >> size;
        getline(cin, emptyStr);

    } while (cin.fail() || !emptyStr.empty());

	for (int i = 0; i < size; i++) {
		do
    	{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << i + 1 << ". Write the number (" + to_string(LD_SIZE * 8 - 1) + "...0) of a bit you want to change and its value: ";
			cin >> number >> value;
			getline(cin, emptyStr);
    	} while (cin.fail() || !emptyStr.empty() || number > (LD_SIZE * 8 - 1) || number < 0 || value < 0 || value > 1);

		ld_bits.bits_arr[number / 8] = changeUChar(ld_bits.bits_arr[number / 8], number % 8, value);
	}

	cout << "---Result---\n";
	cout << "Changed number: " << ld_bits.ld << endl
		<< "Binary representation of the number: ";
	printLDoubleBin(ld_bits.ld);
	cout << endl;

	return ld_bits.ld;
}