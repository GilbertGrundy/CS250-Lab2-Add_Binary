/*
Name: Gilbert Grundy
Assignment: Lab #2
*/



#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

void get_num(char * &num);
bool check_binary(char * &num);
bool check_length(char * &num);
void print(char * &num);
char AND(char num1, char num2);
char OR(char num1, char num2);
char NOT(char num1);
char XOR(char num1, char num2);
char half_adder(char p, char q, char & sum_carry);
char full_adder(char num1, char num2, char & carry_in, char * sum_binary);
bool repeat();

int main()
{
	char * binary_num1;	//1st binary num to add
	char * binary_num2;	//2nd binary num to add
	char carry_in = '0';	//carries the carry
	char tempa, tempb;	//carries individual digits into the full adder
	char sum_binary[13];	//holds answer
	int a = 0;
	int b = 0;

	cout << "Gilbert Grundy CS250 Lab #2 \n\n";
	
	do{		
		cout << "What is the first number would you like to add?\n" << endl;

		get_num(binary_num1);

		while(!check_binary(binary_num1)) //checking the number is binary
		{
			cout << "Sorry, the number you gave was not a binary number";
			cout << "\n\nPlease try again.\n" << endl;
			if(binary_num1) delete [] binary_num1;
			get_num(binary_num1);
		};

		cout << "What is the second number would you like to add?" << endl;
	
		get_num(binary_num2);
	
		while(!check_binary(binary_num2)) //checking if the number is binary
		{
			cout << "Sorry, the number you gave was not a binary number.\n\nPlease try again.\n" << endl;
			if(binary_num2) delete [] binary_num2;
			get_num(binary_num2);
		};

		cout << "The numbers to be added are "; //display numbers
		print(binary_num1);
		cout << "and "; 
		print(binary_num2);
		cout << "\n\n";
	
		a = strlen(binary_num1);
		b = strlen(binary_num2);

		while((a> -1) || (b> -1))
		{
			--a;
			--b;
			tempa = binary_num1[a];
			tempb = binary_num2[b];

			if(!binary_num1[a]) tempa = '0';
			if(!binary_num2[b]) tempb = '0';
				
				//calling the adder
			carry_in = full_adder(tempa, tempb, carry_in, sum_binary);	
			cout << "\n";
		}

		cout << "The answer is: ";
	
		a = strlen(sum_binary);
		for(int i = -1; i < a; i= -1)
		{
			cout << sum_binary[a];
			if(!(a%4)) cout << " ";
			a = a - 1;
		}
		cout << endl;

		a = 0;	//deleting arrays for another go
		while(binary_num1[a])
		{
			binary_num1[a] = '\0';
			++a;
		}
		a = 0;
		while(binary_num2[a])
		{
			binary_num2[a] = '\0';
			++a;
		}
		
		a = 0;
		while(sum_binary[a])
		{
			sum_binary[a] = '\0';
			++a;
		}

	}while(repeat()); //do you want to repeat program?

	return 0;
}


//function to set the binary number
void get_num(char * &num)
{
	char temp[100];
	cin.get(temp,9, '\n');
	cin.ignore(100, '\n');

	num = new char[strlen(temp) + 1];
	strcpy(num, temp);

	return;
}

//function to check if the binary number is a binary number
bool check_binary(char * &num)
{
	if(!num) return false;
	int j = strlen(num);

	for (int i = 0; i < j; ++i)
	{
		if(num[i] != '0' && num[i] != '1' && num[i] != '\0') return false;
	}

	return true;
}


//prints the binary nummber, with spaces
void print(char * &num)
{
	int j = strlen(num);
	int k = strlen(num);

	for(int i = 0; i < j; i++)
	{
		cout << num[i];
		--k;
		if(!(k%4)) cout << " ";
	}
	return;
}


//And gate function
char AND(char num1, char num2)
{
	bool a = false; 
	bool b = false;
	if(num1 == '1') a = true;
	if(num2 == '1') b = true;

	if(a && b) return '1';
	return '0';
	
}

//Or gate function
char OR(char num1, char num2)
{
	bool a = false; 
	bool b = false;
	if(num1 == '1') a = true;
	if(num2 == '1') b = true;

	if(a || b) return '1';
	return '0';
}

//Not gate function
char NOT(char num1)
{
	if(num1 == '0') return '1';
	if(num1 == '1') return '0';
}

//Xor gate function
char XOR(char num1, char num2)
{
	bool a = false; 
	bool b = false;
	if(num1 == '1') a = true;
	if(num2 == '1') b = true;
	
	if(a != b) return '1';
	return '0';
}

//half adder function
char half_adder(char p, char q, char & sum, char & carry)
{
	carry = AND(p,q);
//	sum = AND(OR(p,q),NOT(AND(p,q)));
	sum = XOR(p,q);
	return carry;
}

//full adder function
char full_adder(char num1, char num2, char & carry_in, char * sum_binary)
{
	char sum = '0';
	char carry = '0';
	char temp_cout = '0';
	char temp_array[10];

	cout << "The bits are "	<< num1 << " and " << num2 << ". ";
	cout << "The carry in is " << carry_in << ". ";

		//call the half adder twice here
	temp_cout = half_adder(num1, num2, sum, carry);
	carry_in = half_adder(sum, carry_in, sum, carry);
	carry_in = OR(temp_cout, carry_in);
	cout << "The sum is " << sum << ". ";
	cout << "The carry out is " << carry_in << ". ";
	temp_array[0] = sum;
	strncat(sum_binary, temp_array, 1);

	return carry_in;
}


//function to check if the user would like to add bbinary 
//numbers again
bool repeat()
{
	char again;
	bool repeat = true;
	do
	{
		cout << "Would you like to add binary numbers again? y/n" << endl;

		cin >> again;
		cin.ignore(100, '\n');

		if(again == 'y' || again == 'Y') return true;
		if(again == 'n' || again == 'N') return false;
	}while(repeat);
}
