/* ******************************************************
 * Name: Jasper Nelson
 * Wisc ID: 9073545106
 * OS: MAC
 * IDE (or text editor): Eclipse
 * Compiler: Eclipse
 * How long did the assignment take you to complete in minutes: 210
 * What other resources did you consult (copy and paste links below):
 * cplusplus.com
 * stackoverflow.com
*/ // ******************************************************

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int MAX_CLASS_SIZE = 100;
const int MAX_NUMBER_OF_ASSIGNMENTS = 100;

// do not change these prototypes.  Add your code to the function definitions below
void Read_Grade_File(string names[MAX_CLASS_SIZE][2], int scores[MAX_CLASS_SIZE][MAX_NUMBER_OF_ASSIGNMENTS], int *number_of_students, int *number_of_assignments, const string input_filename);
void Format_Case_Of_Names(string names[MAX_CLASS_SIZE][2], const int number_of_students);
void Compute_Total_And_Percent(int scores[MAX_CLASS_SIZE][MAX_NUMBER_OF_ASSIGNMENTS], int total[], float percent[], int number_of_students, int number_of_assignments);
void Write_Formatted_Grades(string names[MAX_CLASS_SIZE][2], int total[], float percent[], const int number_of_students, const string output_filename);

// There is no need to change main. However you are encouraged to write code
// to write data to the console to check the correctness of each of your functions as
// as you work.
int main() {
	string input_filename="unformatted_grades.txt";
	string output_filename="formatted_grades.txt";
	string names[MAX_CLASS_SIZE][2];
	int scores[MAX_CLASS_SIZE][MAX_NUMBER_OF_ASSIGNMENTS];
	int number_of_students=0;
	int number_of_assignments=0;
	int total[MAX_CLASS_SIZE];
	float percent[MAX_CLASS_SIZE];

	Read_Grade_File(names, scores, &number_of_students, &number_of_assignments, input_filename);
	Format_Case_Of_Names( names, number_of_students);
	Compute_Total_And_Percent( scores, total, percent, number_of_students, number_of_assignments);
	Write_Formatted_Grades(names, total, percent, number_of_students, output_filename);
	return 0;
}

// Add your code below to define these functions
// remember to add comments to each function to describe the
// 1) purpose, 2) input, and 3) output of the functions

/* Read_Grade_File opens and reads a file with the filename that is stored in input_filename.  It takes the data found
 * in the file and enters it into arrays to be accessed by other functions in the program
 *
 * input:
 * string names[][] - used to store the first and last name of each student
 * int scores[][] - used to store each students' score on each assignment
 * int *number_of_students - pointer to storage for the number of students in the class
 * int *number_of_assignments - pointer to the storage for the number of assignments per student
 * string input_filename - filename to be used as input for this program
 *
 * returns:
 * N/A
 */
void Read_Grade_File(string names[MAX_CLASS_SIZE][2], int scores[MAX_CLASS_SIZE][MAX_NUMBER_OF_ASSIGNMENTS], int *number_of_students, int *number_of_assignments, const string input_filename)
{
	ifstream grades;
	grades.open(input_filename); //open the input file
	if(grades.is_open())
	{
		if(grades.good())//check to make sure the file is opened properly and has data to input
		{
			string str;
			grades.ignore(19); //ignore variable name
			grades >> *number_of_students;//assign variable

			grades.ignore(23);//ignore variable name
			grades >> *number_of_assignments;//assign

			grades.ignore(256, '\n');//ignore the two end line characters
			grades.ignore(256, '\n');

			int i = 0;
			while(grades.eof() == false)//until bottom of file is reached
			{
				grades.ignore(256, ' ');//ignore up to first space, as names come after
				grades >> names[i][0];//assign variable
				grades >> names[i][1];
				for(int j = 0; j < *number_of_assignments; j++)
				{
					grades >> scores[i][j];//assign scores
				}
				i++;
			}

		}

	}
	grades.close(); //close file

}

/* Format_Case_Of_Names takes the names array filled by Read_Grade_File, transforms the entirety of each name to lowercase
 * and then changes the first letter in each name to uppercase.
 *
 * input:
 * string names[][] - used to store the first and last name of each student
 * int number_of_students - pointer to storage for the number of students in the class
 *
 * output:
 * N/A
 */
void Format_Case_Of_Names(string names[MAX_CLASS_SIZE][2], const int number_of_students)
{
	for(int k = 0; k < number_of_students; k++)
	{
		string first = names[k][0];
		string lowFirst;
		string last = names[k][1];
		string lowLast;
		char hld;
		for(int r = 1; r < first.length();r++)
		{
			hld = tolower(first[r]);//iterate through first omitting the 1st character
			lowFirst += hld; //create storage string of all lowercase letters for first name
		}
		for(int t = 1; t < last.length(); t++)
		{
			hld = tolower(last[t]);//iterate through last omitting the 1st character
			lowLast += hld; //create storage string of all lowercase letters for last name
		}
		first = toupper(first[0]); //capitalize first letter in each name
		last = toupper(last[0]);
		first += lowFirst; //add on lowercase letters following
		last += lowLast;
		names[k][0] = first; //update array
		names[k][1] = last;
	}
}

/* Compute_Total_And_Percent calculates each students total score and percentage of total points achieved and stores them
 * in arrays to be accessed by other methods.
 *
 * input:
 * int scores[][] - used to store each students' score on each assignment
 * int total[] - used to store each students' total score across all assignments
 * float percent[] - used to store each students' percentage of possible points earned
 * int *number_of_students - pointer to storage for the number of students in the class
 * int *number_of_assignments - pointer to the storage for the number of assignments per student
 *
 * output:
 * N/A
 */
void Compute_Total_And_Percent(int scores[MAX_CLASS_SIZE][MAX_NUMBER_OF_ASSIGNMENTS], int total[], float percent[], int number_of_students, int number_of_assignments)
{
	for(int f = 0; f < number_of_students; f++)
	{
		int maxPts = 10 * number_of_assignments; // calculate max possible pts
		for(int g = 0; g < number_of_assignments; g++)
		{
			total[f] += scores[f][g]; //sum over scores
			percent[f] = (double)total[f]/maxPts; //divide total by max points
		}
	}
}

/* Write_Formatted_Grades opens an output file and outputs information to the file in the format specified.
 *
 * input:
 * string names[][] - used to store the first and last name of each student
 * int total[] - used to store each students' total score across all assignments
 * float percent[] - used to store each students' percentage of possible points earned
 * int number_of_students - pointer to storage for the number of students in the class
 * string output_filename - name of the file to be created for output
 *
 * output:
 * A file named with the specified filename with the formatted grades inputted.
 */
void Write_Formatted_Grades(string names[MAX_CLASS_SIZE][2], int total[], float percent[], const int number_of_students, const string output_filename)
{
	ofstream write;
	write.open(output_filename); //opens a new file with the specified filename
	string build[number_of_students]; // used as a placeholder for the formatted name
	if(write.is_open())//check to see that the file opened correctly
	{
		int nameLength[number_of_students];
		for(int v = 0; v < number_of_students; v++)
		{
			nameLength[v] = names[v][1].length() + names[v][0].length(); //used to determine width
			build[v] = names[v][1] + ", " + names[v][0]; //create formatted name string
			write << build[v]; //output string
			write <<setw(20-nameLength[v])<< total[v]; //output total with appropriate spacing

			write << fixed;
			write << setw(7);
			write << setprecision(1);
			write << (double)percent[v] * 100 << endl;//output percentage with appropriate decimals
		}
		write << ends; //apply eof character
	}
	write.close();//close file
}

