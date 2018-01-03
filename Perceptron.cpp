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

using namespace std;

/*
	Creating the class neuron
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

	//ifstream fConfiguration;

	//String to store a line
	string sLine;

	//Name of the file
	string sName;

	//char* to store the number from the txt
	string sNumber; 

	//Public functions of the class neuron
	public:

		//This is a constructor that gets executed when an object of the class
		//is created. That is why it is called the same
		//Neuron(ifstream &fConfiguration)
		//{

		//}
		//Void to get and set the values from the configuration.txt
		void get_values(int iN)
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

			//Counter to assing the value to a specefic Omega
			int iCounter = -1;

			//While there are lines
			while(getline(fConfiguration, sLine))
			{
				//Go throught the whole line char by char
				for(int i = 0; i < sLine.size(); i++)
				{
					//If it is not a space
					if(sLine[i] != ' ')
					{
						//Store that value in the string sNumber
						sNumber.append(sLine[i]);
						//cout << sNumber;

					}

					//Else if the counter is less than 3
					else if(iCounter < 3)
					{
						//If the counter is -1
						if(iCounter == -1)
						{
							//Convert the string  sLine into a float
							//and store it in the fUmbral
							//fUmbral = atof(sNumber);
						}

						//Else
						else
						{
							//Store it into the fArrOmega[iCounter]
							//fArrOmega[iCounter] = atof(sNumber);
							//cout << "fArrOmega[" << iCounter << "] is: " << fArrOmega[iCounter];
						}

						//Clean the string
						sNumber = '';
						//Increase the counter
						iCounter++;
					}
				}
			}

			//Close the file
			fConfiguration.close();
		}

		//Void to modify the values of the file configuration.txt
		//Use this after modyfing the values on the program
		//configuration.txt is just to store

		//Void to modify the values on the program
		
};

//Void to create all the objects

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
	for(int i = 0; i < iTotalNeurons; i++)
	{
		neuron[i].get_values(iCounter);
		cout << "Umbral is: " << neuron[i].fUmbral;

		if(iN < iArr[iCounter])
		{

			iN++;
		}

		else
		{
			iN = 1;
			iCounter++;
		}
		
	}
	
	//End
	return 0;
}



