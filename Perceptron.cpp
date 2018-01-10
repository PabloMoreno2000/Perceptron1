/*
	This code is a Perceptron, a type of neural network.
	Explanation of the project:

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

	In the file configuration.txt the values of the omegas and the umbral are stored.
	There is a line for each neuron, and a txt file per layer.

	Pablo Moreno
	04/01/2018
	Version 2.0
*/
#include<iostream>
#include<string>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//Declaring global variables
	//the desired result for the output neuron
	float fY;

using namespace std;
/*
	This function receives a line from the text
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
	return fResult;
}

/*
	Function to scale the values. The user will be able to type values bigger than 1,
	but the program should to the work by them, and we know that the neurons need a value
	between 0 and 1, so instead of having several cases and make a scale for each variable
	(That is how is made in a lot of perceptrons), lets make a scale for the whole set of data
	The bigger value will be 1, the smaller will be 0. So we first need the tree input values
	to scale them.

	Parameters:
		neuron[]		Array of the objects of the class Neuron
*/
void Scale(Neuron neuron[])
{
	//Variable to store the index of th maximum value
	int iMax;

	//Variable to store the index of the minimun value
	int iMin;

	//Both will first store the input value of the first neuron
	iMax = 0;
	iMin = iMax;
	
	//Search in the other two values
	for(int i = 1; i < 3; i++)
	{	
		//For the maximum
		if(neuron[i].fA > neuron[iMax].fA)
		{
			iMax = i;
		}

		//And for the minimum
		if(neuron[i].fA < neuron[iMin].fA)
		{
			iMin = i;
		}
	}

	//Scale them with the following formula
	for(int i = 0; i < 3; i++)
	{
		//Checking to not be dividing by 0
		if( neuron[iMax].fA != neuron[iMin].fA)
		{
			neuron[i].fA = (neuron[i].fA - neuron[iMin].fA) / (neuron[iMax].fA - neuron[iMin].fA);
		}
	
		//If this else is reached, that means, the three input values are equal
		else
		{
			neuron[i].fA = 1;	
		}
	}
}

/*
	Function that calculates the output "a" of each neuron
	and modify the variable fA of the current neuron

	Parameters:
		neuron[]		Array of objects of the class Neuron
		iArrNumber[]		Array with the number of neurons of each layer
		iArrSum[]		Array that stores the accumulative diferences of neurons per layer
		iK			The layer of the targeted neuron (counting from 0)
		iI			The position of the targeted neuron in the layer (counting from 0)
*/
void Output(Neuron neuron[], int iArrNumber[], int iArrSum[], int iK, int iI)
{
	//Variable to store the sum
	float iSum;
	
	//Variable to store the index of the neuron
	int iPos;


	//Determining the position of the neuron (counting from 0)
	iPos = iArrSum[iK] + iI;


	
	//Adding the output of each neuron in the last layer multiplied times the delta
	//In the first layer, we need to give some values
	if(iK == 0)
	{
		//Asking and receiving the values of the iPos neuron
		//This values should not be modified since its the input layer
		//Neither the umbral should be added
		cout << "Enter the value for the neuron #" << iPos + 1 << ": ";
		cin >> neuron[iPos].fA;

		//After receiving the value of the last input neuron
		if(iPos == 2)
		{
			//Scale them
			Scale(neuron);
		}
	}

	else
	{
		//The variable will start with the value of the umbral
		iSum = neuron[iPos].fUmbral;

		//Making the iteration to add up each neccesary value
		//The output of the neuron of the last layer times its omega
		for(int i = 0; i < iArrNumber[iK - 1]; i++)
		{
			iSum += neuron[iPos].fArrOmega[i] * neuron[iArrSum[iK - 1] + i].fA;
		}

		//After the loop, save the value
		neuron[iPos].fA = Sigmoid(iSum);
	}
}

/*
	Void that completes a whole iteration,
	when it is called, the outputs of each neuron are gotten in
	order until the output neuron. Its result will be displayed

	Parameters:
		neuron[]		Array of objects of the class Neuron
		iArrNumber[]		Array with the number of neurons of each layer
		iArrSum[]		Array that stores the accumulative diferences of neurons per layer
*/
void Iteration(Neuron neuron[], int iArrNumber[], int iArrSum[])
{
	//Calling the Output void for each neuron
	//In this case, I use instruction by instruction instead of a loop because I would have needed more variables
	//And even more lines of code, knowing that this Perceptron only has 8 neurons.

	//1st layer(input)
	Output(neuron, iArrNumber, iArrSum, 0, 0);
	Output(neuron, iArrNumber, iArrSum, 0, 1);
	Output(neuron, iArrNumber, iArrSum, 0, 2);

	//2nd layer
	Output(neuron, iArrNumber, iArrSum, 1, 0);
	Output(neuron, iArrNumber, iArrSum, 1, 1);

	//3rd layer
	Output(neuron, iArrNumber, iArrSum, 2, 0);
	Output(neuron, iArrNumber, iArrSum, 2, 1);

	//4th layer(output)
	Output(neuron, iArrNumber, iArrSum, 3, 0);

	//Displaying the result
	cout << "The result of the output neuron is: " << neuron[7].fA;
}

/*
	Function to obtain the fourth delta. The deltas will help us to modify the omegas
	in order to train the neural net and reduce the error. In this case the fourth delta
	will help us to modify the omegas(or the umbrals) that connect the third with the fourth layer.

	Parameters:
		neuron[]		Array of objects of the class Neuron
		
	Returns:
		fFourthDelta		float value with the result needed to modify an omega or an umbral of the third layer
*/
float FourthDelta(Neuron neuron[])
{
	//Variable to store the result
	float fFourthDelta = 0;

	//Array that shows how many neurons we need to add up if we want to go to the next layer
	int iArrSum[4] = {0, 3, 5, 7};

	//Calculating the result
	{
		fFourthDelta = fY * (1 - fY) * -(neuron[iArrSum[3]].fA - fY);
	}
}

/*
	Function to return the Third Delta. This delta is obtained when we want to derivate the error
	with respect to an omega that is connecting the second and third layer. Or an umbral of the third
	layer

	Parameters:
		neuron[]		Array of objects of the class Neuron
		iJ			Neuron number from where the connection starts(counting from 1)
		iI			Neuron number from where the connection finishes(Counting from 1)
		
	Returns:
		fThirdDelta		The value of the third delta
*/
float ThirdDelta(Neuron neuron[], int iJ, int iI)
{
	//Variable to store the result
	float fThirdDelta = 0;

	//Array that shows how many neurons we need to add up if we want to go to the next layer
	int iArrSum[4] = {0, 3, 5, 7};

	//Array with the number of neurons per layer(counting from 1)
	int iArrN[4] = {3, 2, 2, 1};

	//Calculating the result
	//First we make the necessary loop to obtain the right result
	//The loop is not neccesary thanks to the net structure, but I will leave it in case
	//of a future moditication
	for(int i = iArrSum[3]; i < iArrSum[3] + iArrN[3]; i++)
	{
		fThirdDelta += neuron[iArrSum[3]].fArrOmega[iI - 1] * FourthDelta(neuron);
	}

	//Then we multiply that result times the other values
	fThirdDelta *= neuron[iArrSum[2] + iI - 1].fA * (1 - neuron[iArrSum[2] + iI - 1].fA);

	//Returning the result
	return fThirdDelta;
}

/*
	Function to get the second delta. The second delta will be used later to change
	any value of an omega between the first and the second layer, or an umbral of the
	second layer.

	Parameters:
		neuron[]	Array of objects of the class Neuron
		iJ		Neuron# (1 - 3), first layer
		iK		Neuron# (1 - 2), second layer

	Returns:
		fSecondDelta	The value of the second delta
*/
float SecondDelta(Neuron neuron[], int iJ, int iK)
{
	//Declaring the variable to store the result
	float fSecondDelta = 0;

	//Array that shows how many neurons we need to add up if we want to go to the next layer
	int iArrSum[4] = {0, 3, 5, 7};

	//Array with the number of neurons per layer(counting from 1)
	int iArrN[4] = {3, 2, 2, 1};

	//Making the summation
	for(int i = 0; i < iArrN[2]; i++)
	{
		fSecondDelta += neuron[iArrSum[2] + i].fArrOmega[iK - 1] * ThirdDelta(neuron, i + 1, iArrN[3]);
	}

	//Multypling times the other values
	fSecondDelta *= neuron[iArrSum[1] + iK - 1].fA * (1 - neuron[iArrSum[1] + iK - 1].fA);

	//Returning the result
	return fSecondDelta;
}

/*
	Void to ask some neccesary values in order to modify an Omega

	Parameters:
		iLayer		Variable to store the layer of the umbral or the group of omegas
		iOmegaS		Variable to store the #neuron from where the omega starts
		iOmegaE		Variable to store the #neuron from where the omega ends
*/
void OmegaGetValues(int &iLayer, int &iOmegaS, int &iOmegaE)
{
	//Asking which of the three groups
	cout << "Which one of the three groups of Omegas do you want to modify?";
	cin >> iLayer;

	//Asking the #neuron of the left layer
	cout <<"Enter the number of the neuron of the layer " << iLayer << " from where the omega comes out: ";
	cin >> iOmegaS;

	//Asking the #neuron of the right layer
	cout << "Enter the number of the neuron of the layer " << iLayer + 1 << " where the omega ends: ";
	cin >> iOmegaE;

}

/*
	Void to change the value of the Omega in the program

	Parameters:
		neuron[]	Array of objects of the class Neuron
		iLayer		Variable to store the layer of the umbral or the group of omegas
		iOmegaS		Variable to store the #neuron from where the omega starts
		iOmegaE		Variable to store the #neuron from where the omega ends
		fRate		Variable to control how much the omega or the umbral will change	
*/
void OmegaChangeValue(Neuron neuron[],int iLayer, int iOmegaS, int iOmegaE, float fRate)
{
	//Array that will help us to have less code, the number of the layer
	//is used as the index in order to know how much we need to add up
	int iArrSum[4] = {0, 3, 5, 7};

	//Variable to store the result of the delta
	float fD;

	//If it is from the first group
	if(iLayer == 1)
	{
		fD = SecondDelta(neuron, iOmegaS, iOmegaE);
	}		

	//If it is from the second group
	else if(iLayer = 2)
	{
		fD = ThirdDelta(neuron, iOmegaS, iOmegaE);
	}
	//If it is from the third group
	else
	{
		fD = FourthDelta(neuron);
	}

	//Printing fD
	//cout << "fD is: " << fD;

	//Printing the value
	cout << "Before the process it was: " << neuron[iArrSum[iLayer] + iOmegaE -1].fArrOmega[iOmegaS - 1];

	//Changing the process
	neuron[iArrSum[iLayer] + iOmegaE -1].fArrOmega[iOmegaS - 1] = neuron[iArrSum[iLayer] + iOmegaE - 1].fArrOmega[iOmegaS - 1] - fRate * fD;

	//Printing the value
	cout << endl << "After the process it is: " << neuron[iArrSum[iLayer] + iOmegaE -1].fArrOmega[iOmegaS - 1] << endl;
}

/*
	Void to ask some neccesary values in order to modify an Umbral

	Parameters:
		iLayer		Variable to store the layer of the umbral or the group of omegas
		iOmegaS		Variable to store the #neuron that has the umbral
*/
void UmbralGetValues(int &iLayer, int &iOmegaS)
{
	//Asking the number of layer
	cout << "In which layer the umbral is? ";
	cin >> iLayer;

	//Asking the number of neuron in that layer
	cout << "What is the position of the neuron in that layer that has the umbral? ";
	cin >> iOmegaS;
}

/*
	Void to change the value of the umbral in the program

	Parameters:
		neuron[]	Array of objects of the class Neuron
		iLayer		Variable to store the layer of the umbral
		iOmegaS		Variable to store the #neuron where the umbral is
		fRate		Variable to control how much the omega or the umbral will change	
*/
void OmegaChangeValue(Neuron neuron[], int iLayer, int iOmegaS, float fRate)
{
	//Array that will help us to have less code, the number of the layer
	//is used as the index in order to know how much we need to add up
	int iArrSum[4] = {0, 3, 5, 7};

	//Variable to store the return of the delta function
	float fD;

	//It is important to remember that the input neurons have not a umbral
	
	//If it is from the second layer
	if(iLayer == 2)
	{

	}

	//or from the third
	else if(iLayer == 3)
	{

	}

	//or the last
	else
	{

	}

	//Making the operation
	neuron[iArrSum[iLayer - 1] + iOmegaS - 1].fUmbral = neuron[iArrSum[iLayer -1] + iOmegaS - 1].fUmbral - fRate * fD;
}

/*
	This is the main.
	here some important variables are declared and important functions
	and instructions are performed in order to create the neurons
	and assign the values for each one.

	Parameters:
		none

	Returns:
		0
*/
int main()
{
	//Array with the number of neuron per layer, including the one of the
	//input and the output
	int iArrNumber[4] = {3, 2, 2, 1};

	//Array that will help us to have less code, the number of the layer
	//is used as the index in order to know how much we need to add up
	int iArrSum[4] = {0, 3, 5, 7};

	//Variable to store the total number of neurons
	int iTotalNeurons = iArrNumber[0] + iArrNumber[1] + iArrNumber[2] + iArrNumber[3];

	//Variable to store the layer of the umbral or the group of omegas
	int iLayer;

	//Variable to store the #neuron from where the omega starts
	int iOmegaS;

	//Variable to store the #neuron from where the omega ends
	int iOmegaE;

	//Target to modify, could be an Omega or an Umbral
	int iTarget;

	//Variable to continue or stop the program
	char cContinue = '8';

	//Variable to control how much the omega or the umbral will change
	float fRate = 0.2;

	//Variable to control what is going to be displayed
	bool bControl = true;


	//Creating all the neurons
	Neuron neuron[iTotalNeurons];

	//Setting up the values for each neuron
	//In this case, I use instruction by instruction instead of a loop because I would have needed more variables
	//And even more lines of code, knowing that this Perceptron only has 8 neurons.
	neuron[0].get_values(0, 0);
	neuron[1].get_values(0, 1);
	neuron[2].get_values(0, 2);
	neuron[3].get_values(1, 0);
	neuron[4].get_values(1, 1);
	neuron[5].get_values(2, 0);
	neuron[6].get_values(2, 1);
	neuron[7].get_values(3, 0);
	
	//The welcome
	cout << "Welcome to the Perceptron" << endl;

	//Displaying the menu
	cout << endl << "MENU:";
	cout << endl << "Press O to modify an Omega";
	cout << endl << "Press U to modify an Umbral";
	cout << endl << "Press R to change the learning rate(bigger than 0, less than 1), right now it's " << fRate;
	cout << endl << "Press E to exit";
	cout << endl << "Press any other key to continue" << endl;


	//Making the process
	do
	{
		if(bControl)
		{
			//Ask the desired result
			do
			{
				cout << "Enter the desired result for the output neuron(Beetwen 0 and less than 1): ";
				cin >> fY;
			}while(!(fY < 1 && fY >= 0));

			//Making the Iteration
			Iteration(neuron, iArrNumber, iArrSum);

			//Changing bControl
			bControl = false;
		}


		//If the user selects an omega
		if(cContinue == 'O' || cContinue == 'o')
		{
			//Asking values
			OmegaGetValues(iLayer, iOmegaS, iOmegaE);

			//Changing the omega value
			OmegaChangeValue(neuron, iLayer, iOmegaS, iOmegaE, fRate);
		}
			
		

		//Modyfing an Umbral
		else if(cContinue == 'U' || cContinue == 'u')
		{
			//Asking the values
			//UmbralGetValues(iLayer, iOmegaS);

			//Changing the umbral value
			//UmbralChangeValue(neuron, iLayer, iOmegaS, fRate);
		}
	

		//With any other key, an iteration will be made again
		//I will check the next condition to prevent displaying errors
		//After the first iteration
		else if(cContinue != '8')
		{
			bControl = true;
		}

		//To prevent some possible displaying errors, make bControl false here too
		bControl = false;

		//Asking him what he/she wants to do next
		cout << endl << "Great, now please select an option from the menu: ";
		cin >> cContinue;


	}//while te user does not type an e or a E
	while(!(cContinue == 'e' || cContinue == 'E'));

	//End
	return 0;
}
