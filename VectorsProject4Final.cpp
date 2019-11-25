/*Name: Carlos Castillo
Class : CIS 161 ME1
Date : 25 October 2019
Program Name : Class Statistics Analyzer 
Program Explanation : This program reads 
student IDs and three quiz scores from a file. 
Then it calculates each students average and 
calculates the average of each quiz. It outputs
a header, the report, high scores, low scores,
and quiz averages to a file.*/
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

typedef vector<int> ivec; // ivec is an alias for a vector of integers
typedef vector<float> fvec;

void getdata(ivec &, ivec &, ivec &, ivec &); // function prototypes
void findstavg(const ivec &, const ivec &, const ivec &, fvec &);
int findhigh(const ivec &);
int findlow(const ivec &);
float findqzavg(const ivec &);
void printall(const ivec &, const ivec &, const ivec &, const ivec &, const fvec &, const int &, const int &, const int &, 
const int &, const int&, const int &, const float &, const float &, const float &);
void headings(ofstream &, const string &, const string &);
void report(ofstream &, const ivec &, const ivec &, const ivec &, const ivec &, const fvec &);
void hi_lo_avg(ofstream &, const int &,const int &,const int &,const int &,const int &,const int &, const float &,const float &,const float &);

int main()
{
	ivec student_IDs, quiz1_scores, quiz2_scores, quiz3_scores; // defined four vectors of integers
	fvec student_Avg; // defined one vector of floats
	int q1_high, q2_high, q3_high, q1_low, q2_low, q3_low;
	float qavg1, qavg2, qavg3;
	
	getdata(student_IDs, quiz1_scores, quiz2_scores, quiz3_scores);
	findstavg(quiz1_scores, quiz2_scores, quiz3_scores, student_Avg);
	q1_high = findhigh(quiz1_scores);
	q2_high = findhigh(quiz2_scores);
	q3_high = findhigh(quiz3_scores);
	q1_low = findlow(quiz1_scores);
	q2_low = findlow(quiz2_scores);
	q3_low = findlow(quiz3_scores);
	qavg1 = findqzavg(quiz1_scores);
	qavg2 = findqzavg(quiz2_scores);
	qavg3 = findqzavg(quiz3_scores);
	printall(student_IDs, quiz1_scores, quiz2_scores, quiz3_scores, student_Avg, q1_high, q2_high, q3_high, q1_low, q2_low, q3_low, qavg1, qavg2, qavg3);
	return 0;
}


/* This function is void because it returns no values.
It contains four parameters which are all vectors of integers.
They are all passed by reference.  This function opens
a file and reads in IDs and scores for each quiz from the file.
The vectors are given the values after they're read from the file.  
The file is closed at the end. */ 
void getdata(ivec &studID, ivec &q1, ivec &q2, ivec &q3)
{
	ifstream iFile("pr2data.txt"); // ifstream variable is defined here
	int id;
	int score1;
	int score2;
	int score3;
	
	if(!iFile) // checks if the file cannot be opened
		cout << "ERROR!!!" << endl;
	else
		while(iFile >> id) // reads values from the file to id
		{
			iFile >> score1 >> score2 >> score3;
			studID.push_back(id); // adds new element to the ID vector
			q1.push_back(score1); // adds new element to the quiz vector
			q2.push_back(score2);
			q3.push_back(score3);
		}
		
	iFile.close(); // closes the file to prevent data corruption
}


/* This function is void because it returns no values.
It contains four parameters.  There are three 
vectors of integers which are passed by const reference and
one vector of floats which is passed by reference.  This function
calculates each students average using the sum and number of quiz scores.  It 
stores each students average in the float vector. */
void findstavg(const ivec &q1, const ivec &q2, const ivec &q3, fvec &stAvg)
{
	int total;
	float avg;
	
	for(int count = 0; count < q1.size(); count++)
	{
		total = (q1[count] + q2[count] + q3[count]);
		avg = (total / 3.0);
		stAvg.push_back(avg); 	
	}	
}


/* This function is an integer type because
it returns an integer value called highest.  It contains
one parameter which is a vector of integers that is passed
by const reference.  This function sets up an initial
highest variable and then compares every element in 
the quiz vector to the highest variable in order to find
a new highest quiz value if there is one. */
int findhigh(const ivec &quiz)
{
	int highest;
	highest = quiz[0]; // sets the highest score to the first element
	
	for(int count = 1; count < quiz.size(); count++) 
	{
		if(quiz[count] > highest) // checks if elements in the vector are greater than highest variable
			highest = quiz[count]; // sets new highest value
	}
	
	return highest;	
}


/* This function is an integer type because
it returns an integer value called lowest.  It contains
one parameter which is a vector of integers that is passed
by const reference.  This function sets up an initial
lowest variable and then compares every element in 
the quiz vector to the lowest variable in order to find
a new lowest quiz value if there is one. */
int findlow(const ivec &quiz)
{
	int lowest;
	lowest = quiz[0]; // sets the lowest score to the first element
	
	for(int count = 1; count < quiz.size(); count++)
	{
		if(quiz[count] < lowest)  // checks if elements in the vector are less than lowest variable
			lowest = quiz[count]; // sets new lowest value
	}
	
	return lowest;
}


/*This function is a float type because it returns a float value 
called average.  It contains one parameter which is a vector of integers
that is passed by const reference.  This function calculates the 
average of a set of quizzes.  It uses the sum of the quiz scores
and the number of quizzes to find the average.*/
float findqzavg(const ivec &quiz)
{
	float avg;
	int total;
	total = 0;
	
	for(int count = 0; count < quiz.size(); count++)
	{
		total += quiz[count]; // adds quiz to the accumulator
	}
	
	avg = (total / static_cast<float>(quiz.size())); // avg is found by dividing total by the size of the quiz vector
	
	return avg;
}


/* This function is a void type because it returns no values.
It contains 14 paramters which are passed by const reference.  
This function calls one subfunction to display headings, a second
subfunction to display the class report, and a third subfunction to
display the highs, lows, and quiz averages for each quiz. All the
information is output to a file and the file is closed
at the end of the function*/
void printall(const ivec &ids, const ivec &q1, const ivec &q2, const ivec &q3, const fvec &stAvg, 
const int &high1, const int &high2, const int &high3, const int &low1, const int&low2, const int &low3, 
const float &qzavg1, const float &qzavg2, const float &qzavg3)
{
	ofstream outFile("ClassQuizReport.txt"); // defined ofstream variable 
	
	string report_header = "\t\tCIS Department - Fall 2019\t\t"; // defined two header string variables
	string report_header2 = "CIS 161 Class Statistics\n";
	
	headings(outFile, report_header, report_header2); 
	report(outFile, ids, q1, q2, q3, stAvg);
	hi_lo_avg(outFile, high1, high2, high3, low1, low2, low3, qzavg1, qzavg2, qzavg3);
	
	outFile.close();
}


/* This function is a void type because it doesn't return a value.
It contains three parameters.  The first parameter is an ofstream object
passed by reference.  The second and third paramters are strings that
are passed by const reference.  The function displays two headers to 
an output file. */ 
void headings(ofstream & oFile, const string &header, const string &header2)
{
	oFile << header << endl; // display the first header followed by the next header messages
	oFile << setw(42) << header2 << endl;
}


/* This function is a void because it doesn't return a value. 
It contains six parameters.  The first parameter is an ofstream object
that is passed by reference.  The other parameters are vectors of
integers and floats that are passed by const reference.  This function
outputs all student IDs, quiz 1 scores, quiz 2 scores, quiz 3 scores,
and student averages to a file.*/  
void report(ofstream & oFile, const ivec &ids, const ivec &q1, const ivec &q2, const ivec &q3, const fvec &stAvg)
{
	oFile << "Student\t\tQuiz 1\t\tQuiz 2\t\tQuiz 3\t\tAverage" << endl;	
	oFile << fixed << showpoint << setprecision(2); // formats the output
	for(int count = 0; count < ids.size(); count++)
		oFile << ids[count] << "\t\t" << q1[count] << "\t\t" << q2[count] << "\t\t" << q3[count] << "\t\t" << stAvg[count] << endl;	// display ids, quiz scores, student averages
}


/* This function is a void because it doesn't return a value.  It contains
10 parameters.  The first parameter is an ofstream type and it is passed
by reference.  Six parameters are int types passed by const reference.
Three parameters are float types passed by const reference.  This function
displays the highest scores, lowest scores, and quiz average of each quiz.*/
void hi_lo_avg(ofstream & oFile, const int &qhigh1,const int &qhigh2,const int &qhigh3,const int &qlow1,const int &qlow2,
const int &qlow3, const float &avg1,const float &avg2,const float &avg3)
{
	oFile << "\nHigh Score" << "\t" << qhigh1 << "\t\t" << qhigh2 << "\t\t" << qhigh3 << endl; // display highest scores
	oFile << "\nLow Score" << "\t" << qlow1 << "\t\t" << qlow2 << "\t\t" << qlow3 << endl; // display lowest scores
	oFile << "\nQuiz Average" << "\t" << avg1 << "\t\t" << avg2 << "\t\t" << avg3 << endl; // display each quiz average
}
