/*This Program is a simple calculator which is part of an application which is in development.
* This Application(in development) is a graph plotting app.
* Here only input and accurate output is only goal of this program.
* Proper calulator process is to be achieve.
*/



/*
* THE LESSIONS I LEARNT FROM THIS PROGRAM

* 1>  Each time check whether the resetting of values of variable is necessary or not.
*       Especially in a for loop and that purposefully  located in a recursion function.
*       This made a very big difference between a failure and success of my programme :)

* 2>  Learn to use recursion functions effectively
* 
*/

//All Header files

#include<iostream>
#include<vector>
#include<iomanip>
#include<math.h>

//Global Variables
short  count_LegalBrackets = 0;     //to count only the number of opening brackets in the equation
short count_NumberOfRecursions = 0;//to know the first function call

//Number Structure to store the number and its sign

struct Number
{
	long double data;
	bool sign;


	//Constructor
	Number()
	{
		data = 0.0;
		sign = true;
	}



	//Destructor
	~Number()
	{}
};


class CalculatorData
{
	Number num;
	char operation;


public://Constructors AND Destructors

	//Default Constructor
	CalculatorData()
	{
		num.data = 0.0;
		num.sign = 1;
		operation = ' ';
	}


	//Constructor only to define number
	CalculatorData(Number pNumber)
	{
		num = pNumber;
		operation = ' ';
	}


	//Constructor only to define operation
	CalculatorData(char pOperation)
	{
		num.data = 0;
		num.sign = 1;
		operation = pOperation;
	}
	

	//Destructor
	~CalculatorData()
	{}

public://Member Functions

	
	bool static GetTheEquation(std::vector<CalculatorData>& equation);      /*GetTheEquation as the
																		                                             name suggest fills up the 'equation' vector by the 
																		                                             input of user which is obviously is a equation

																		                                             It also checks for errors such as aplhabet
																		                                             other than *,/,+,-,%,^,any number and a variable
																		                                         */

	void static DisplayExpression(std::vector<CalculatorData>& equation);  //Only shows what's hiding any fishy in a expression i.e it displays the vector equation

	static bool DoMultiplicaion_Division(std::vector<CalculatorData>& equation);
	
	static bool DoAddition_Subtraction(std::vector<CalculatorData>& equation);

	static bool Simplifily_TheEquation(std::vector<CalculatorData>& equation);

	static bool CalculateNumberPowers(std::vector<CalculatorData>& equation);

	static bool DeleteRemainingExpression(std::vector<CalculatorData>& equation, int currentPosition, unsigned short manipulatePosition, bool withBrackets);  //it will delete the remaining expression after substuting ans
};



//Definations of class Member function

//Fills up the vector by expression given by the user
bool CalculatorData::GetTheEquation(std::vector<CalculatorData>& equation)
{
	//Varibles      ***********************************************************************************************


	short currentPosition = 0;   //To know where the error occured in the equation

	Number buffer_ForInputData;     // This variable acts as a buffer to store numbre in vector
	char buffer_ForInputOperation = ' ';  //This variable acts as a buffer to store operator in vector

	short add_subtGroup = 0, multi_diviGroup = 0;   /*To store how many times these operation are
																		   putted between any two number (max size is ->
																		 add_subtGroup=1       and         multi_diviGroup=1.
																			*/


	bool noError = true;                              //For while statment to fill up the vector
	
	bool bracketSequence = false;        //to know the if there is a bracket between number and raised to the number operator

	bool addsubt_squence = false;              //To know squence of *,/,-,+ in between two numbers --> this varible groups addition and subtraction together
	bool multidivi_squence = false;               //To know squence of *,/,-,+ in between two numbers --> this varible groups multiplication and division together 
	
	bool raisedToApperence = false;           //To know raised to has apperaed and no number has appeared yet


	bool epi_sequence = false;                //to sequence of 'pi' and 'e' not to come one after the other
	
		short legalBrackets = 0;                 //To check whether all brackets end's up legally or not
	
	char peekInput = ' ';                       //To know in advance if it is char or number


	//gets the equation from the user **************************************************************************
	std::cout << "Enter the Equation    :       ";





	//Checks the equation for the errors ***********************************************************************

	while (noError)
	{

		//Operation error checking and filling vector         ---------------  OPERATOR SECTION   ------

		peekInput = std::cin.peek();


		
		if (peekInput == '\n')
		{
			if (equation[equation.size() - 1].operation == ' ' || equation[equation.size() - 1].operation == ')')
			{
				if (legalBrackets == 0)
					noError = false;
				else
				{
					std::cout << "\n\nError Brackets are not arranged in a standard manner \n";
					equation.clear();
					noError = false;
				}
			}
			else
			{
				std::cout << "\n\nError last term is a operator \n";
				equation.clear();
				noError = false;
			}
		}

		switch (peekInput)
		{
		case '(':case')':
		{
			bracketSequence = true;

			std::cin >> buffer_ForInputOperation;

			if (peekInput == '(')
			{
				count_LegalBrackets += 1;//because to solve one bracket two times the function is called so each time subtracting one from the variable 
				//so from the start we have to supply or add two in every call of above statement so to sync with the function below
				//i.e simplifily the equation
				legalBrackets++;
				//if (currentPosition == 1 && equation[currentPosition - 1].operation != ' ')
				//{
				//	std::cout << "\n\nError Operator \'+\' and  \'-\' does not come before the brackets without any aid of number\n\n";
				//	equation.clear();
				//	noError = false;
				//	break;
				//}
			}
			if (peekInput == ')')
			{
				legalBrackets--;
			}

			equation.push_back(buffer_ForInputOperation);

			currentPosition++;

			break;
		}
		case '^':
		{
			//keeps the count of raised to the number operator
			if (!raisedToApperence)
			{
				raisedToApperence = true;

				//check for operator before raise to operator 
				if (!addsubt_squence && !multidivi_squence)//it should not be a multiplcation or division or addition or subtraction sign
				{
					std::cin >> buffer_ForInputOperation;
					equation.push_back(buffer_ForInputOperation);
					currentPosition++;
					break;
				}
				else
				{
					std::cout << "Error----no operator must come before raise to the power operator\n";
					equation.clear();
					noError = false;
					break;
				}

			}
			else//so two or more raise to operator will not come together
			{
				std::cout << "Error no two raise to the power operator must come together\n";
				equation.clear();
				noError = false;
				break;
			}

			break;
		}

		case '/':case'*'://of type multi_diviGroup
		{
			//Checks whether multiplication and division sign occurs more than 1 time if so display error
			//between any two numbers(these numbers are consecutive,->one after another)
			
			epi_sequence = false;
			
			if (currentPosition != 0)
			{
				std::cin >> buffer_ForInputOperation;
			}
			else
			{
				std::cout << "\n\nError Operator \'*\' and  \'/\' does not come at starting of expression\n\n";
				equation.clear();
				noError = false;
				break;
			}
			//
			if (!addsubt_squence)
				multidivi_squence = true;
			else
			{
				std::cout << "\n\nError at position  ::  " << (currentPosition + 1) << "\n\n";
				equation.clear();
				noError = false;
				break;
			}

			//
			if (multi_diviGroup < 2)
			{
				multi_diviGroup++;
				if (multi_diviGroup >= 2)
				{
					std::cout << "\n\nError at position  ::  " << (currentPosition + 1) << "\n\n";
					equation.clear();
					noError = false;
					break;
				}
			}

			equation.push_back({ buffer_ForInputOperation });

			currentPosition++;                                 //keep track of position in the expression so as to point out error to user
			break;
		}
		
		case'-':case'+'://of type add_subtGroup
		{

			//Checks whether addition and subtraction sign occurs more than 1 time if so display error
			//between any two numbers(these numbers are consecutive,->one after another)
			std::cin >> buffer_ForInputOperation;

			addsubt_squence = true;

			epi_sequence = false;

			if (add_subtGroup < 2)
			{
				add_subtGroup++;
				if (add_subtGroup >= 2)
				{
					std::cout << "\n\nError at position  ::  " << (currentPosition + 1) << "\n\n";
					equation.clear();
					noError = false;
					break;
				}
			}

			equation.push_back({ buffer_ForInputOperation });
			currentPosition++;                                       //keep track of position in the expression so as to point out error to user
			break;
		}

		case 'e':case 'p':
		{
			
			std::cin >> buffer_ForInputOperation;
			
			

			if (buffer_ForInputOperation == 'e' && !epi_sequence)
			{
				equation.push_back({ buffer_ForInputOperation });
				equation[currentPosition].operation = ' ';
				equation[currentPosition].num.data = 2.71828;
			
				epi_sequence = true;
			}
			else if (buffer_ForInputOperation == 'p' && !epi_sequence)
			{
				equation.push_back({ buffer_ForInputOperation });
				equation[currentPosition].operation = ' ';
				equation[currentPosition].num.data = (22.0 / 7.0);
			
				epi_sequence = true;//to avoid pi and e coming one after the other
				//I would have checked the previous operation var to find it a sign
				// then only i would have assign value of e 
				//if not then displayed error
			}
			else
			{
				std::cout << "\nValue of pi and e cannot come together\n\n";
				equation.clear();
				noError = false;
				break;
			}

			//To know the sign of e and pi because it is a number so....................
				if (currentPosition >= 1)
				{
					if (equation[currentPosition - 1].operation == '-')//checks previous operator for - sign
					{
						equation[currentPosition].num.sign = 0;//assigns 0 for sign variable

						if (multidivi_squence && addsubt_squence) //any 9*-9 sun expression occurs - sign is deleted
						{
							if (equation[currentPosition - 1].operation == '-')equation[currentPosition].num.sign = 0;
							else if (equation[currentPosition - 1].operation == '+')equation[currentPosition].num.sign = 1;
							equation.erase(equation.begin() + (currentPosition - 1));
							currentPosition--;
						}
						else//else it is not 9*-9 so it will be 9-9 so below '-' sign is made positive i.e 9+9
						{
							equation[currentPosition - 1].operation = '+';
						}


						//if starter term is an operator
						if ((currentPosition - 1) == 0)//this checks for position at 0(zero) of vector for sign 
						{
							equation[currentPosition].num.sign = 0;
							equation.erase(equation.begin());//if '-' is found it is deleted 
							currentPosition--;//current position  resets
						}
					}
					else//assigns + sign if no - operator is before above number 
					{
						equation[currentPosition].num.sign = 1;//assigns 1 for sign variable

						if (multidivi_squence && addsubt_squence) //any 9*-9 sun expression occurs - sign is deleted
						{
							if (equation[currentPosition - 1].operation == '-')equation[currentPosition].num.sign = 0;
							else if (equation[currentPosition - 1].operation == '+')equation[currentPosition].num.sign = 1;
							equation.erase(equation.begin() + (currentPosition - 1));
							currentPosition--;
						}

						//For starter trem is any operator
						if ((currentPosition - 1) == 0)
						{
							equation[currentPosition].num.sign = 1;
							equation.erase(equation.begin());//if + is found it sis deleted 
							currentPosition--;
						}
					}
					/*if (multidivi_squence && addsubt_squence) //any 9*-9 sun expression occurs - sign is deleted
					{
						if (equation[currentPosition - 1].operation == '-')equation[currentPosition].num.sign = 0;
						else if (equation[currentPosition - 1].operation == '+')equation[currentPosition].num.sign = 1;
						equation.erase(equation.begin() + (currentPosition - 1));
						currentPosition--;
					}
					*/
				}

				//resets all conditions in operator side after ecah number and p and e
				addsubt_squence = false;
				multidivi_squence = false;
				multi_diviGroup = 0;
				add_subtGroup = 0;

				//reset bracket conditions
				bracketSequence = false;

				//reset raised to number conditions
				raisedToApperence = false;

			currentPosition++;
			break;
		}

		default:
		{
			switch (peekInput)
			{
			case '1':case'2':case'3':case'4':case'5':case'6':case'7':case'8':case'9':case'0':
			{
				std::cin >> buffer_ForInputData.data;
				buffer_ForInputData.data = buffer_ForInputData.data * 1.0;
				if (std::cin)
				{
					equation.push_back((buffer_ForInputData));        //Constructor only for number input

					//Down This is very important statement::  here numbers are assigined their sign
					//values which are according to the operator sign before them
					//whenn first trem has - or + sign that is also assigned to the number after it
					//and later it is deleted so remanins only the number at first
					//
					//
					//It does not removes the operator which is after the first position in the vector
					//so that remains as it is

					//IMPORTANT UPDATE ::  I cancelled the sign asignment i.e if - or + sign is 
					//in between two number after the starter trem it does not copy it as 
					//number sign variable which i have done before 
					//so now only starter operator is assign or an expression such as 9*-9
					//'-'sign is attach to 9 so expression becomes 9*9 where second 9 has - as it sign
					//and first 9 has + sign.

					if (currentPosition >= 1)
					{
						if (equation[currentPosition - 1].operation == '-')//checks previous operator for - sign
						{
							equation[currentPosition].num.sign = 0;//assigns 0 for sign variable
						
							if (multidivi_squence && addsubt_squence) //any 9*-9 sun expression occurs - sign is deleted
							{
								if (equation[currentPosition - 1].operation == '-')equation[currentPosition].num.sign = 0;
								else if (equation[currentPosition - 1].operation == '+')equation[currentPosition].num.sign = 1;
								equation.erase(equation.begin() + (currentPosition - 1));
								currentPosition--;
							}
							else//else it is not 9*-9 so it will be 9-9 so below '-' sign is made positive i.e 9+9
							{
								equation[currentPosition - 1].operation = '+';
							}
						

							//if starter term is an operator
							if ((currentPosition - 1) == 0)//this checks for position at 0(zero) of vector for sign 
							{
								equation[currentPosition].num.sign = 0;
								equation.erase(equation.begin());//if '-' is found it is deleted 
								currentPosition--;//current position  resets
							}
						}
						else//assigns + sign if no - operator is before above number 
						{
							equation[currentPosition].num.sign = 1;//assigns 1 for sign variable
							
							if (multidivi_squence && addsubt_squence) //any 9*-9 sun expression occurs - sign is deleted
							{
								if (equation[currentPosition - 1].operation == '-')equation[currentPosition].num.sign = 0;
								else if (equation[currentPosition - 1].operation == '+')equation[currentPosition].num.sign = 1;
								equation.erase(equation.begin() + (currentPosition - 1));
								currentPosition--;
							}

							//For starter trem is any operator
							if ((currentPosition - 1) == 0 && (equation[currentPosition-1].operation!='('))
							{
								equation[currentPosition].num.sign = 1;
								equation.erase(equation.begin());//if + is found it is deleted 
								currentPosition--;
							}
						}
						/*if (multidivi_squence && addsubt_squence) //any 9*-9 sun expression occurs - sign is deleted
						{		
							if (equation[currentPosition - 1].operation == '-')equation[currentPosition].num.sign = 0;
							else if (equation[currentPosition - 1].operation == '+')equation[currentPosition].num.sign = 1;
							equation.erase(equation.begin() + (currentPosition - 1));
							currentPosition--;
						}
						*/
					}

					//raise to the number operator checking
					if (currentPosition >= 3 && raisedToApperence)
					{
						if (multidivi_squence)//if multiplication or division appears then show error 
						{
							std::cout << "\n\nError at position  ::  " << (currentPosition) << "\n\n";
							equation.clear();
							noError = false;
							break;
						}
						else if (addsubt_squence)//if addition or subtraction appears the change the sign of number at current position and delete that operator
						{
							//(equation[currentPosition - 1].operation == '+') ? equation[currentPosition].num.sign = 1 : equation[currentPosition].num.sign = 0;
							equation.erase(equation.begin() + currentPosition - 1);
							currentPosition--;
						}
					}

					currentPosition++;                   //keep track of position in the expression so as to point out error to user
				}

			
				//Resets all the conditions for input of operators between numbers

			   //resets all conditions in operator side afet ecah number
				addsubt_squence = false;
				multidivi_squence = false;
				multi_diviGroup = 0;
				add_subtGroup = 0;

				//reset bracket conditions
				bracketSequence = false;
				
				//reset raised to number conditions
				raisedToApperence = false;

				break;
			}

			default://Error which is unusal in expression such as =,o instead of 0(zero),mainly unlogical errors in calculation
			{			
				if (noError)
				{
					std::cout << "\n\n\t\tERROR IN EXPRESSION AT POSITION   ::   "<<(currentPosition+1)<<"\n\n";
					equation.clear();
					noError = false;
				}
				break;
			}

			}

			break;
		}

		}

	}
	return true;
}


//Solve the brackets inside the equations
//This has to go from two different ways 
//First>> Brackets inside the brackets
//second>> brackets after the brackets
//PLEASE KEEP A EXTRA COPY OF EQUATION BEFORE PASSING IT AS AN ARGUEMENT TO BELOW FUNCTION
bool CalculatorData::Simplifily_TheEquation(std::vector<CalculatorData>& equation)
{
	
	count_NumberOfRecursions++;
	//solve the brackets
	
	//Position related inside the brackets and equation
	unsigned short manipulateExpression = 0;
	int currentPosition = 0;

	//Brackets related-------- this has to be reseted after complete solving of bracket i.e after every recusion function ended
	short legalBrackets = 0;
	bool isBracketAtStartingPosition = false;
	bool isThereAnyOperator_Before_OpeningBracket = false;
	bool isThereAnyOperator_After_ClosingBracket = false;

	//Temporary Equatin to store the content inside the brackets
	std::vector<CalculatorData>temporaryEquation;

	//int sizeOfTemporaryEquation = 0;


	//iterate through the expression
	for (currentPosition;currentPosition < equation.size();currentPosition++)
	{
		//put the equation in tempEquation if brackets are found
		if (legalBrackets > 0)
		{
			temporaryEquation.push_back(equation[currentPosition]);
		}

		//checks the opening of any brackets 
		if (equation[currentPosition].operation == '(')
		{
			if (currentPosition == 0)//for starting position brackets
			{
				isBracketAtStartingPosition = true;
				isThereAnyOperator_Before_OpeningBracket = false;
			}

			legalBrackets++;//keeps count of opening and closing of brackets

			if (legalBrackets == 1)
			{
				manipulateExpression = currentPosition;
				if (currentPosition != 0)
				{
					if (equation[currentPosition - 1].operation != ' ')//there is a operator before bracket
						isThereAnyOperator_Before_OpeningBracket = true;
					else//there is no operator before bracket
						isThereAnyOperator_Before_OpeningBracket = false;
				}
			}
		}

		//checks the closing of any brackets
		if (equation[currentPosition].operation == ')')
		{
			legalBrackets--;//keeps count of opening and closing of any brackets

			if (currentPosition == (equation.size() - 1) && legalBrackets==0)//checks last position
			{
				isThereAnyOperator_After_ClosingBracket = false;
			}

			if (legalBrackets == 0 && currentPosition < (equation.size() - 1))
			{
				if (equation[currentPosition + 1].operation != ' ')
				{
					if (equation[currentPosition + 1].operation == '(')//here '(' operator after closing bracket indicates that there will be multiplication between these brackets 
						isThereAnyOperator_After_ClosingBracket = false;//so taking that into account I intentionfully make '(' operator as a false one so program will not see it and inserts '*' sign instead of ')' in bracket we are in now
					else
						isThereAnyOperator_After_ClosingBracket = true;//if there is another sign instead of '(' then it is treated as operator in tne programme
				}
				else
					isThereAnyOperator_After_ClosingBracket = false;//there is no operator after the closing bracket neither a '(' opening bracket. so that's there is number
			}
		}

		if (legalBrackets == 0 && temporaryEquation.size() > 0)
		{
			

			//sizeOfTemporaryEquation = temporaryEquation.size();
			temporaryEquation.pop_back();
			Simplifily_TheEquation(temporaryEquation);

			if (count_LegalBrackets > 0)
				count_LegalBrackets--;//it is here because after every call to this function one bracket will be removed 
												   //no matter if it has one or not

			
			//=====================================================//

		//Now rearranging the equation vector because we have ans in temporaryEquation

		//Checks if Opening bracket is at starting position or not 
			if (isBracketAtStartingPosition)//Bracket is at starting position
			{
				//checks if temporaryEquation has one number or expression
				if (temporaryEquation.size() == 1) // it contains fully solved expression
				{
					//Put the answer at right position

					//checks if there is a operator before opening of  bracket usually operator will not be there 
					if (!isThereAnyOperator_Before_OpeningBracket)
					{
						equation[manipulateExpression] = temporaryEquation[0]; //Place the answer at the
																  // starting position instead of bracket
					}

					//checks if there is a operator after closing bracket
					if (isThereAnyOperator_After_ClosingBracket)//there is an operator after closing bracket
					{
						//so delete the remainig expression along with bracket in equation vector
						DeleteRemainingExpression(equation, currentPosition, manipulateExpression, true);

						//update the currentPosition
						currentPosition = manipulateExpression + 1;
					}
					else //there is not any operator after the closure of bracket
					{
						//so delete the remainig expression without bracket in equation vector
						DeleteRemainingExpression(equation, currentPosition, manipulateExpression, false);

						//update the currentPosition
						currentPosition = manipulateExpression + 1;

						//Now instead of closing bracket place a multiplication sign
						if (equation[currentPosition].operation == ')' && (currentPosition != equation.size() - 1))
						{
							if (currentPosition != equation.size() - 1)//if it is not the closer of bracket then put * sign instead of bracket
								equation[currentPosition].operation = '*';
							else
								equation.pop_back();//as current position is at last position there is no need of closing bracket because that bracket has been solve
						}
						else if (equation[currentPosition].operation == ')' && (currentPosition == equation.size() - 1))
						{
							equation.pop_back();//for the last bracket in end of equation where cureent position is at end of equation delete bracket
							currentPosition--; //update current position to previous place 
						
						}
						
					}
					
				}
				else if (temporaryEquation.size() > 1) // it contains partially solved expression
				{
					//to place the expression inside equation 
					//so size of temporaryEquation current size is needed

					manipulateExpression += 1; //to place the expression after the bracket

					for (int counter = 0; counter < temporaryEquation.size();counter++)//how many time to iterate
					{
						equation[manipulateExpression] = temporaryEquation[counter];
						manipulateExpression++;
					}

					//if there is a operator after the closing bracket or not; we have to preserve the breackets
					DeleteRemainingExpression(equation, currentPosition, manipulateExpression, false);

					//update the currentposition
					currentPosition = manipulateExpression;//currentPosition is on the closing bracket
					

				}
				else//i.e brackets are empty so delete them from equation vector
				{
					equation.erase(equation.begin() + currentPosition - 1);
					currentPosition--;
					equation.erase(equation.begin() + currentPosition);
					currentPosition--;
					
				}

				//resetting every thing except "currentposition" so that new values can be set
				legalBrackets = 0;
				isBracketAtStartingPosition = false;
				isThereAnyOperator_Before_OpeningBracket = false;
				isThereAnyOperator_After_ClosingBracket = false;
				temporaryEquation.clear();
			}
			else //bracket is at in the middle somewhere
			{
				//ckecks whether there is an operator before opening bracket
				if (isThereAnyOperator_Before_OpeningBracket)//there is an operator
				{
					if (temporaryEquation.size() == 1)//Completely solved equation
					{
						//there is an operator before opening bracket 
						//so delete the both opening and closing brackets
						equation[manipulateExpression] = temporaryEquation[0];

						if (isThereAnyOperator_After_ClosingBracket)//there is operator after closing bracket
						{
							//so delete the remainig expression along with bracket in equation vector
							DeleteRemainingExpression(equation, currentPosition, manipulateExpression, true);

							//update the currentPosition
							currentPosition = manipulateExpression + 1;
						}
						else//there is no operator after closing bracket
						{
							//so delete the remainig expression without bracket in equation vector
							DeleteRemainingExpression(equation, currentPosition, manipulateExpression, false);

							//update the currentPosition
							currentPosition = manipulateExpression + 1;

							//Now instead of closing bracket place a multiplication sign
							if (equation[currentPosition].operation == ')' && (currentPosition != equation.size() - 1))
							{
								if (currentPosition != equation.size() - 1)
									equation[currentPosition].operation = '*';
								else
									equation.pop_back();
							}
							else if (equation[currentPosition].operation == ')' && (currentPosition == equation.size() - 1))
							{
								equation.pop_back();
								currentPosition--; //update current position to previous place 
							}
						}

					}
					else if (temporaryEquation.size() > 1)//Partially solved equation
					{
						//to place the expression inside equation 
						//so size of original temporaryEquation is needed

						manipulateExpression += 1; //to place the expression after the bracket

						for (int counter = 0; counter < temporaryEquation.size();counter++)//how many time to iterate
						{
							equation[manipulateExpression] = temporaryEquation[counter];
							manipulateExpression++;
						}

						//if there is a operator after the closing bracket or not; we have to preserve the breackets
						DeleteRemainingExpression(equation, currentPosition, manipulateExpression, false);

						//update the currentposition
						currentPosition = manipulateExpression;//currentPosition is on the closing bracket

					}
					else//i.e brackets are empty so delete them from equation vector
					{
						equation.erase(equation.begin() + currentPosition - 1);
						currentPosition--;
						
						equation.erase(equation.begin() + currentPosition);
						currentPosition--;
					}


					//resetting every thing except "currentposition" so that new values can be set
					legalBrackets = 0;
					isBracketAtStartingPosition = false;
					isThereAnyOperator_Before_OpeningBracket = false;
					isThereAnyOperator_After_ClosingBracket = false;
					temporaryEquation.clear();
				}
				else//there is not a operator before opening bracket
				{
					if (temporaryEquation.size() == 1)//Completely solved equation
					{
						//instead of bracket place a * operator
						if (equation[manipulateExpression].operation == '(')
							equation[manipulateExpression].operation = '*';


						manipulateExpression++;  //to store the numbber at next place


						// so place the answer after the bracket
						equation[manipulateExpression] = temporaryEquation[0];

						//increment manipulateExpression on next place
						manipulateExpression++;

						if (isThereAnyOperator_After_ClosingBracket)
						{
							//delete all remaining places between manuplicate and currentposition
							DeleteRemainingExpression(equation, currentPosition, manipulateExpression, true);
						}
						else
						{
							//delete all remaining places between manuplicate and currentposition
							DeleteRemainingExpression(equation, currentPosition, manipulateExpression, false);

							//Now instead of closing bracket place a multiplication sign
							if (equation[currentPosition].operation == ')' && (currentPosition != equation.size() - 1))
							{
								if (currentPosition != equation.size() - 1)
									equation[currentPosition].operation = '*';
								else
									equation.pop_back();
							}
							else if (equation[currentPosition].operation == ')' && (currentPosition == equation.size() - 1))
							{
								equation.pop_back();
								currentPosition--; //update current position to previous place 
							}
						}

						//update current position
						currentPosition = manipulateExpression;


					}
					else if (temporaryEquation.size() > 1)//Partially solved equation
					{
						//to place the expression inside equation 
						//so size of original temporaryEquation is needed

						manipulateExpression += 1; //to place the expression after the bracket

						for (int counter = 0; counter < temporaryEquation.size();counter++)//how many time to iterate
						{
							equation[manipulateExpression] = temporaryEquation[counter];
							manipulateExpression++;
						}

						//if there is a operator after the closing bracket or not; we have to preserve the breackets
						DeleteRemainingExpression(equation, currentPosition, manipulateExpression, false);

						//update the currentposition
						currentPosition = manipulateExpression;//currentPosition is on the closing bracket

					}
					else//i.e brackets are empty so delete them from equation vector
					{
						equation.erase(equation.begin() + currentPosition - 1);
						currentPosition--;

						equation.erase(equation.begin() + currentPosition);
						currentPosition--;
						
					}
					//resetting every thing except "currentposition" so that new values can be set
					legalBrackets = 0;
					isBracketAtStartingPosition = false;
					isThereAnyOperator_Before_OpeningBracket = false;
					isThereAnyOperator_After_ClosingBracket = false;
					temporaryEquation.clear();
				}
			}
		}
	}
	
	

	//Do raised to the number
	CalculateNumberPowers(equation);


	//Do Multoplication and division
	DoMultiplicaion_Division(equation);


	//Do Addition and Subtraction
	DoAddition_Subtraction(equation);
			
	count_NumberOfRecursions--;

	return true;
}


bool CalculatorData::DeleteRemainingExpression(std::vector<CalculatorData>& equation, int currentPosition, unsigned short manipulatePosition, bool withBrackets)
{
	if (withBrackets)// delete brackets first and last when ans from inside the bracket is only a number
	{
		for (int counter = 0;counter < currentPosition - manipulatePosition;counter++)
		{
			equation.erase(equation.begin() + manipulatePosition + 1);
		}
	}
	else// do not delete first and endind bracket because ans from inside the bracket is not a number but an expression
	{
		for (int counter = 0;counter < (currentPosition - manipulatePosition-1); counter++)
		{
			equation.erase(equation.begin() + manipulatePosition + 1);
		}
	}

	return true;
}


//displays the whole equation for the sake of error and any correction
void CalculatorData::DisplayExpression(std::vector<CalculatorData>& equation)
{	
	if (equation.size() > 0)
	{

		std::cout << "\n\n Size on Expression  :  " << equation.size();
		std::cout << "\n";
		std::cout << "\t\t\tANSWER\n\n\n";
		for (int i = 0;i < equation.size();i++)
		{
			/*switch (equation[i].operation)
			{
			case' ':
			{
				std::cout << "\t\t" << equation[i].num.data << "\t\t\t\t" << equation[i].num.sign << "\t\t\t\t" << equation[i].operation << "\n\n";
			}
			default:
				std::cout << "\t\t" << "No......" << "\t\t\t\t" << equation[i].num.sign << "\t\t\t\t" << equation[i].operation << "\n\n";
				break;
			}*/

			long double Answer = equation[i].num.data; //the Answer variable is not define multiple times in a for loop 
			//but insted same variable is over-written i.e valuse changes but memory location remains the same
			//unless and untill variable name is same


			if (equation[i].num.sign == 0)
				Answer = 0 - Answer;

			std::cout  << "\t\t\t" << Answer;
		

		}
	}  
}


//do power problems that is number raised to something
bool CalculatorData::CalculateNumberPowers(std::vector<CalculatorData>& equation)
{
	if (equation.size() > 2)
	{
		for (int currentPosition = 0;currentPosition < equation.size();currentPosition++)
		{

			if (equation[currentPosition].operation == '^')
			{
				long double number = 0.0, power = 0.0, answer = 0.0;

				if (equation[currentPosition + 1].operation == ' ')//there is a number 
				{
					//Modify the power variable
					(equation[currentPosition + 1].num.sign == 1) ? power = equation[currentPosition + 1].num.data : power = 0.0 - equation[currentPosition + 1].num.data;
						
					//Modify the number variable
					(equation[currentPosition - 1].num.sign == 1) ? number = equation[currentPosition - 1].num.data : number = 0.0 - equation[currentPosition - 1].num.data;

					//Now perform power operation
					answer = powl(number, power);

					//Modify the equation vector with the answer
					if (answer >= 0)//it is greater than or equal zero
					{
						equation[currentPosition - 1].num.data = answer;
						equation[currentPosition - 1].num.sign = 1;
					}
					else//it is less than 0
					{
						equation[currentPosition - 1].num.data = 0.0 - answer;
						equation[currentPosition - 1].num.sign = 0;
					}

					equation.erase(equation.begin() + currentPosition);
					equation.erase(equation.begin() + currentPosition);
					currentPosition--;
					currentPosition--;
				}
				else if (equation[currentPosition + 2].operation == ' ' && equation[currentPosition + 1].operation != ' ')
				{//there is number and addition or subraction sign between ^ and numbers

					if (equation[currentPosition + 1].operation == '+')
					{
						equation.erase(equation.begin() + currentPosition + 1);
						
						//Modify the power variable
						(equation[currentPosition + 1].num.sign == 1) ? power = equation[currentPosition + 1].num.data : power = 0.0 - equation[currentPosition + 1].num.data;

						//Modify the number variable
						(equation[currentPosition - 1].num.sign == 1) ? number = equation[currentPosition - 1].num.data : number = 0.0 - equation[currentPosition - 1].num.data;
					
						//Now perform power operation
						answer = powl(number, power);

						//Modify the equation vector with the answer
						if (answer >= 0)//it is greater than or equal zero
						{
							equation[currentPosition - 1].num.data = answer;
							equation[currentPosition - 1].num.sign = 1;
						}
						else//it is less than 0
						{
							equation[currentPosition - 1].num.data = 0.0 - answer;
							equation[currentPosition - 1].num.sign = 0;
						}

						equation.erase(equation.begin() + currentPosition);
						equation.erase(equation.begin() + currentPosition);
						currentPosition--;
						currentPosition--;
					
					}
					else if (equation[currentPosition + 1].operation == '-')
					{
						//change the sign of number next to next ^ so if it is positive make it negative and 
						//if it is negative make it positive
						(equation[currentPosition + 2].num.sign == 1) ? equation[currentPosition + 2].num.sign = 0 : equation[currentPosition + 2].num.sign = 1;

						//after modifying the sign delete the sign
						equation.erase(equation.begin() + currentPosition + 1);


						//then after that it is same as original sequence 3^3
						//so..............

						//Modify the power variable
						(equation[currentPosition + 1].num.sign == 1) ? power = equation[currentPosition + 1].num.data : power = 0.0 - equation[currentPosition + 1].num.data;

						//Modify the number variable
						(equation[currentPosition - 1].num.sign == 1) ? number = equation[currentPosition - 1].num.data : number = 0.0 - equation[currentPosition - 1].num.data;

						//Now perform power operation
						answer = powl(number, power);

						//Modify the equation vector with the answer
						if (answer >= 0)//it is greater than or equal zero
						{
							equation[currentPosition - 1].num.data = answer;
							equation[currentPosition - 1].num.sign = 1;
						}
						else//it is less than 0
						{
							equation[currentPosition - 1].num.data = 0.0 - answer;
							equation[currentPosition - 1].num.sign = 0;
						}

						equation.erase(equation.begin() + currentPosition);
						equation.erase(equation.begin() + currentPosition);
						currentPosition--;
						currentPosition--;
					}
				}
					CalculateNumberPowers(equation);//recurrsion of function to solve other ^ operators
			}
		}
	}
	return true;
}


//do Multiplication and division because these came under same level
bool CalculatorData::DoMultiplicaion_Division(std::vector<CalculatorData>& equation)
{
	//iterate through the expression and see's whether the * or / appears or not if so calculates 
	//it and again call's itself so to check whether any * and / operations ar remaining or not
	//if not returns true and the end of for loop 
	//so each call after returning true is returned true thus coming out of function
	//such architecture of function is called recurrsion function---- function calling to itself.......
	
	if (equation.size() > 2)
	{
		for (int currentPosition = 0;currentPosition < equation.size();currentPosition++)
		{
			if (equation[currentPosition].operation == '*')//checks for * sign between two consective numbers
			{
				//data i.e calculated number is stored in currentPosition-1 location
				if (equation[currentPosition - 1].operation == ' ' && equation[currentPosition + 1].operation == ' ')
					equation[currentPosition - 1].num.data = equation[currentPosition - 1].num.data * equation[currentPosition + 1].num.data;

				//sign of number is calculated according to double implication i.e (p->q)^(q->p)
				equation[currentPosition - 1].num.sign = (!equation[currentPosition - 1].num.sign || equation[currentPosition + 1].num.sign) && (!equation[currentPosition + 1].num.sign || equation[currentPosition - 1].num.sign);

				//deletes two positions
				equation.erase(equation.begin() + currentPosition);
				equation.erase(equation.begin() + currentPosition);

				return CalculatorData::DoMultiplicaion_Division(equation);
				//possibility that * appears more 
				//than once so call itself again to ensure all * 
				//operation is over so exit for loop and retursn true
			}
			else if (equation[currentPosition].operation == '/')//checks for / sign between two consective numbers
			{
				//data i.e calculated number is stored in currentPosition-1 location
				if (equation[currentPosition - 1].operation == ' ' && equation[currentPosition + 1].operation == ' ')
					equation[currentPosition - 1].num.data = equation[currentPosition - 1].num.data / equation[currentPosition + 1].num.data;

				//sign of number is calculated according to double implication i.e (p->q)^(q->p)
				equation[currentPosition - 1].num.sign = (!equation[currentPosition - 1].num.sign || equation[currentPosition + 1].num.sign) && (!equation[currentPosition + 1].num.sign || equation[currentPosition - 1].num.sign);

				//deletes two positions
				equation.erase(equation.begin() + currentPosition);
				equation.erase(equation.begin() + currentPosition);

				return CalculatorData::DoMultiplicaion_Division(equation);
				//possibility that / appears more 
			   //than once so call itself again to ensure all * 
			   //operation is over so exit for loop and retursn true
			}
		}
	}
	else if (equation.size() <= 2 && equation.size() != 0)//removes unrequired data from the equation
	{
		if (equation[0].operation != ' ')
		{
			if (equation[0].operation == '-' || equation[0].operation == '+')//ckecks if first position resides to - or +
			{//other than + or - it will bedeleted without any modification

			 //because implication code works on booleans so operator - on one side makes equation[0].num.sign=0
			//and operators *,/,+,(,) on other side makes equation[0].num.sign=1 i.e positive

				(equation[0].operation == '-') ? equation[0].num.sign = 0 : equation[0].num.sign = 1;

				if (equation[1].operation == ' ')//having the number so modification can take place
				{
					equation[1].num.sign = (!equation[1].num.sign || equation[0].num.sign) && (!equation[0].num.sign || equation[1].num.sign);

				}
			}
			equation.erase(equation.begin());
		}
		else if ( equation.size() == 2)
		{
			if (equation[1].operation != ' ')
				equation.erase(equation.begin() + 1);
		}
		else
		{
			if (equation.size() == 2)
			{
				equation.erase(equation.begin());
				equation.erase(equation.begin());
			}
		}
	}
	return true; // return true when all * and / sign operation is over
}


//do Addition and Subtraction because these came under same level
bool CalculatorData::DoAddition_Subtraction(std::vector<CalculatorData>& equation)
{
	if (equation.size() > 2)
	{
		for (int currentPosition = 0;currentPosition < equation.size();currentPosition++)
		{
			if (equation[currentPosition].operation == '-')//operation is subtraction
			{
				if (equation[currentPosition - 1].operation == ' ' && equation[currentPosition + 1].operation == ' ')
				{
					//first modify the sign of second number
					(equation[currentPosition + 1].num.sign == 1) ? equation[currentPosition + 1].num.sign = 0 : equation[currentPosition + 1].num.sign = 1;

					//all below will be same as for addition so no problem
					//necessary was that of changing the sign of second number
					//that was done in above line

					//checks whether sign is same or not
					if (equation[currentPosition - 1].num.sign == equation[currentPosition + 1].num.sign)
					{
						//as sign is same whether -,- or +,+ addition is done
						equation[currentPosition - 1].num.data = equation[currentPosition - 1].num.data + equation[currentPosition + 1].num.data;

						//sign is same so assigning  for precaution
						equation[currentPosition - 1].num.sign = equation[currentPosition + 1].num.sign;


						equation.erase(equation.begin() + currentPosition);
						equation.erase(equation.begin() + currentPosition);
					}
					else if (equation[currentPosition - 1].num.sign != equation[currentPosition + 1].num.sign)//for different signs
					{
						//assigning it's sign----- because sign has to calculated before any changes to 
						//original numbers

						//Getting a bigger number sign going
						if (equation[currentPosition - 1].num.data > equation[currentPosition + 1].num.data)
						{
							//assigning same sign
							equation[currentPosition - 1].num.sign = equation[currentPosition - 1].num.sign;
						}
						else if (equation[currentPosition - 1].num.data < equation[currentPosition + 1].num.data)
						{
							//assigning the sign of greater number
							equation[currentPosition - 1].num.sign = equation[currentPosition + 1].num.sign;
						}
						else if (equation[currentPosition - 1].num.data == equation[currentPosition + 1].num.data)
						{
							// for equal numbers sign will be positive
							equation[currentPosition - 1].num.sign = 1;
						}

						//as sign is different subtraction is done whether -,+ or +,- 
						equation[currentPosition - 1].num.data = equation[currentPosition - 1].num.data - equation[currentPosition + 1].num.data;

						//as above is done in O.S in standard manner i.e sign is saign along with number 
						//I knowing that intentionfully making it positive number if it is negative
						//REASON  :::  because at the end of calculation one number is produce in
						//Number variable so it will have a sign of itself
						//Second mainly because i have not coded to have a number it's natural sign
						//assign to it because it's of no importance because sign member data is
						//taken into consideration when calculating any vaue whether by * or -or +or /

						//SO.................
						if (equation[currentPosition - 1].num.data < 0)
							equation[currentPosition - 1].num.data = 0 - equation[currentPosition - 1].num.data;


						equation.erase(equation.begin() + currentPosition);
						equation.erase(equation.begin() + currentPosition);

					}
				}
				
				return DoAddition_Subtraction(equation);
			}
			else if (equation[currentPosition].operation == '+')// operation is addition
			{
				if (equation[currentPosition - 1].operation == ' ' && equation[currentPosition + 1].operation == ' ')
				{
					//checks whether sign is same or not
					if (equation[currentPosition - 1].num.sign == equation[currentPosition + 1].num.sign)
					{
						//as sign is same whether -,- or +,+ addition is done
						equation[currentPosition - 1].num.data = equation[currentPosition - 1].num.data + equation[currentPosition + 1].num.data;

						//sign is same so assigning  for precaution
						equation[currentPosition - 1].num.sign = equation[currentPosition + 1].num.sign;


						equation.erase(equation.begin() + currentPosition);
						equation.erase(equation.begin() + currentPosition);
					}
					else if (equation[currentPosition - 1].num.sign != equation[currentPosition + 1].num.sign)//for different signs
					{
						//assigning it's sign----- because sign has to calculated before any changes to 
						//original numbers

						//Getting a bigger number sign going
						if (equation[currentPosition - 1].num.data > equation[currentPosition + 1].num.data)
						{
							//assigning same sign
							equation[currentPosition - 1].num.sign = equation[currentPosition - 1].num.sign;
						}
						else if (equation[currentPosition - 1].num.data < equation[currentPosition + 1].num.data)
						{
							//assigning the sign of greater number
							equation[currentPosition - 1].num.sign = equation[currentPosition + 1].num.sign;
						}
						else if (equation[currentPosition - 1].num.data == equation[currentPosition + 1].num.data)
						{
							// for equal numbers sign will be positive
							equation[currentPosition - 1].num.sign = 1;
						}

						//as sign is different subtraction is done whether -,+ or +,- 
						equation[currentPosition - 1].num.data = equation[currentPosition - 1].num.data - equation[currentPosition + 1].num.data;

						//as above is done in O.S in standard manner i.e sign is saign along with number 
						//I knowing that intentionfully making it positive number if it is negative
						//REASON  :::  because at the end of calculation one number is produce in
						//Number variable so it will have a sign of itself
						//Second mainly because i have not coded to have a number it's natural sign
						//assign to it because it's of no importance because sign member data is
						//taken into consideration when calculating any vaue whether by * or -or +or /

						//SO.................
						if (equation[currentPosition - 1].num.data < 0)
							equation[currentPosition - 1].num.data = 0 - equation[currentPosition - 1].num.data;


						equation.erase(equation.begin() + currentPosition);
						equation.erase(equation.begin() + currentPosition);

					}

				}


				return DoAddition_Subtraction(equation);
			}

		}
	}
	else if (equation.size() <= 2 && equation.size()!=0)//removes unrequired data from the equation
	{
		if (equation[0].operation != ' ')
		{
			if (equation[0].operation == '-' || equation[0].operation == '+')//ckecks if first position resides to - or +
			{//other than + or - it will bedeleted without any modification
				
			 //because implication code works on booleans so operator - on one side makes equation[0].num.sign=0
				//and operators *,/,+,(,) on other side makes equation[0].num.sign=1 i.e positive
				
				(equation[0].operation == '-') ? equation[0].num.sign = 0 : equation[0].num.sign = 1;

				if (equation[1].operation == ' ')//having the number so modification can take place
				{
					equation[1].num.sign = (!equation[1].num.sign || equation[0].num.sign) && (!equation[0].num.sign || equation[1].num.sign);

				}
			}
			equation.erase(equation.begin());
		}
		else if (equation.size() == 2)
		{
			if (equation[1].operation != ' ')
				equation.erase(equation.begin() + 1);
		}
		else
		{
			if (equation.size() == 2)
			{
				equation.erase(equation.begin());
				equation.erase(equation.begin());
			}
		}
	}
	return true;
}


//Main Function
int main()
{
	std::vector<CalculatorData>expression;
  
	CalculatorData::GetTheEquation(expression);

	CalculatorData::Simplifily_TheEquation(expression);
	CalculatorData::DisplayExpression(expression);

	std::cout << "\n\n\n\n";
	return 0;
}