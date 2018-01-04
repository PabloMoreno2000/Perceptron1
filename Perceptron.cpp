/*
	This code is a Perceptron, a type of neural network.
	The program does not know the mathematical functions neither the process.
	The goal for this network is to get the right value without knowing
	any of the functions. But here is the process anyways:
	I will introduce 3 random values and the addition of those three
	will be evaluated in the mathematical function 0.1x^2.
	If the value is equal or greater than 0, then that result will be used
	in the function 0.001x^3. Otherwise the  function that will be used wil be
	0.25x + 1.
	The result will be rounded up to the nearest integer if it is not a real number
	and if that result is even, the value of the output neuron will be 1, else a 0.

	In the file configuration.txt the values of the omegas and the umbral are stored
	a line for each neuron, and an "l" for an end of layer. There are 4 layers
*/
#include<iostream>
#include<string>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

using namespace std;
/*
	This functions receives a line from the text
	and change the "numbers" into numbers and then
	assigns the values to the variables of the neurons

	Parameters:
		sFloat		The string
		fUmbral		The umbral of the neuron
		fArrOmega[]	Array with the weights of the connections of the neurons
		iArrSpaces[]	Array with the index that stores a space

*/
void String_to_float(string &sFloat, float &fUmbral, float fArrOmega[], int iArrSpaces[])
{
	//iControl to help with the indexes of iArrSpaces
	int iControl = 0;

	//iCounter to control the chars of the sFloat
	int iCounter = 0;

	//Factor that will help while making the float
	float fFactor = 1;

	//Variable to store a number at a time
	float fNumber = 0;

	//Assigning the Umbral
	while(iCounter < iArrSpaces[iControl])
	{
		//Checking that we are not using the dot
		if(sFloat[iCounter] != '.')
		{
			//Converting the first "number" into a float
			fNumber += (sFloat[iCounter] - '0') * fFactor;

			//Changing the factor
			fFactor = fFactor/10;
		}

		//Increasing the counter
		iCounter++;
	}

	//Assigning the number to the Umbral
	fUmbral = fNumber;

	//iControl will increase
	iControl++;

	//The factor will be 1 again
	fFactor = 1;

	//Resetting the fNumber
	fNumber = 0;

	//Increasing the counter to not use the space
	iCounter++;

	//Assigning all the Omegas
	while(iCounter < sFloat.size())
	{
		//If iCounter position is less than iArrSpaces[iControl]
		if(iCounter < iArrSpaces[iControl])
		{
			//If the char is not a dot
			if(sFloat[iCounter] != '.')
			{
				//Add it to fNumber
				fNumber += (sFloat[iCounter] - '0') * fFactor;

				//Change the factor
				fFactor = fFactor / 10;
			}
		}

		//Else, if it is in the space
		else
		{
			//Assign the value of fNumber to fArrOmega[iControl - 1]
			//There are 3 Omegas and 4 values that iControl takes charge of
			//That is why there is a -1
			fArrOmega[iControl - 1] = fNumber;

			//Reset the factor
			fFactor = 1;

			//Reset fNumber
			fNumber = 0;

			//Increase iControl
			iControl++;
		}
				
		//Increase the counter
		iCounter++;
	}
}

/*
	Creating the class Neuron
	by default it will have 3 omegas, but some neurons
	only need 2
*/
class Neuron
{
	//Variables of the class neuron
	//fA is the output of the neuron
	public: float fUmbral;
	public: float fArrOmega[3];
	public: float fA;

	//Counter of iLine
	int iLineC;

	//There are 4 spaces per line(neuron)
	int iArrSpaces[4];

	//String to store a line
	string sLine;

	//Name of the file
	string sName;



	//Public functions of the class neuron
	public:

		//This is a constructor that gets executed when an object of the class
		//is created. That is why it is called the same
		Neuron()
		{
			iLineC = 0;
		}
		//Void to get and set the values from the configuration.txt
		void get_values(int iN, int iLine)
		{
			
			//Choosing the file name
			if(iN == 0)
			{
				sName = "configuration0.txt";

			}

			else if(iN == 1)
			{
				sName = "configuration1.txt";
			}

			else if(iN == 2)
			{
				sName = "configuration2.txt";

			}

			else if(iN == 3)
			{
				sName = "configuration3.txt";
			}


			//Opening the file configuration.txt
			ifstream fConfiguration(sName.c_str());

			//Counter to manage the indexes of iArrSpaces
			int iCounter;

			//While there are lines
			while(getline(fConfiguration, sLine))
			{
				//If we are in the line #iLine
				if(iLineC == iLine)
				{
					//iCounter will be 0
					iCounter = 0;

					//Get all the index whose char is a space
					for(int i = 0; i < sLine.size(); i++)
					{
						if(sLine[i] == ' ')
						{
							iArrSpaces[iCounter] = i;
							iCounter++;
						}
					}
			
					//Changing the values
					String_to_float(sLine, fUmbral, fArrOmega, iArrSpaces);
			/*
					cout << "Umbral is: " << fUmbral << endl;
					cout << "Omega1 is: " << fArrOmega[0] << endl;
					cout << "Omega2 is: " << fArrOmega[1] << endl;
					cout << "Omega3 is: " << fArrOmega[2] << endl;
			*/
				}

				
					//Increase iLineC
					iLineC++;
				
			}

			//Close the file
			fConfiguration.close();
		}

		//Void to modify the values of the file configuration.txt
		//Use this after modyfing the values on the program
		//configuration.txt is just to store

		//Void to modify the values on the program
		
};

/*
	Function that takes a number and evaluate it in the Sigmoid function.
	This function gives as a result a number between 0 and 1

	Parameters:
		fNumber		An input number

	Returns:
		fResult		The output
*/
float Sigmoid(float fNumber)
{
	//Variable to store the result
	float fResult;

	//Evaluating in the function
	fResult = 1 / (1 + pow(M_E, -fNumber));

	//Returning the result
}

int main()
{
	//iCounter to control a cycle
	int iCounter = 0;

	//Helping variable
	int iN = 0;


	//Array with the number of neuron per layer, including the one of the
	//input and the output
	int iArr[4] = {3, 2, 2, 1};

	int iTotalNeurons = iArr[0] + iArr[1] + iArr[2] + iArr[3];

	//Creating all the neurons
	Neuron neuron[iTotalNeurons];

	//Setting up the values for each neuron
	//I will make a loop for this later
	neuron[0].get_values(0, 0);
	neuron[1].get_values(0, 1);
	neuron[2].get_values(0, 2);
	neuron[3].get_values(1, 0);
	neuron[4].get_values(1, 1);
	neuron[5].get_values(2, 0);
	neuron[6].get_values(2, 1);
	neuron[7].get_values(3, 0);

	//End
	return 0;
}



