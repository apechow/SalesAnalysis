/*
 Array of structures: Insertion Sort
 Name: Annabella Chow
 IDE: VIsual Studio Code
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

// global constant definition: array capacity
const int MAX_PEOPLE = 30;

// structure definition
/* Write the definition of the Sales structure with the following fields:
- name, a string
- amount, and integer 
*/
struct Sales {
    string name;
    int amount;
};

// function prototypes
void readSalesData(string fileName, Sales list[], int &size);
void insertSort(Sales list[], int size);
double detCommissionPercent(int);
double detAmountEarned(int);
void showSalesData(Sales list[], int size);
void saveSalesData(string fileName, Sales list[], int size);


int main()
{
    // array definition
    Sales list[MAX_PEOPLE];
    
    // other variables
    int noPeople;           // actual size of arrays
    string filename;
    
    // function calls
    cout << "Enter input file name: ";
    cin >> filename;
    readSalesData(filename + ".txt", list, noPeople);
    insertSort(list, noPeople);

    string answer;
    cout << "\nShow Report(Y/N)? ";
    cin >> answer;
    if (answer == "y" || answer == "Y") {
        cout << endl;
        showSalesData(list, noPeople);
    }
    saveSalesData(filename + "_report.txt", list, noPeople);
    return 0;
}
//Function reads file of sales data and puts into an array
void readSalesData(string fileName, Sales list[], int &size) {
    int count = 0; //initialize var

    ifstream inFile(fileName); // open file

    //checks if file open
    if (!inFile) {
        cout << "Error opening the input file: " << fileName << ".\n";
        exit(EXIT_FAILURE); //exit code if no file opened
    }

    while (inFile >> list[count].amount) {//reads file until end of file
        //first input reading is amount

        if (count > 29) { //end program if more than 30 lines
            cout << "The array is full and there's more data in the file.\n";
            cout << "The program ends here!\n";
            exit(EXIT_FAILURE);
        }
        inFile.ignore();
        getline(inFile, list[count].name, ';'); //read names
        count += 1; //keep count of how many lines
    }

    size = count; //updates size of list
    inFile.close(); //close file
}

//Function sorts array in descending order by amount.
void insertSort(Sales list[], int size) {
    for (int current = 1; current < size; current++){
        Sales temp = list[current]; //copies current structure

        int walk = current - 1;
        while (walk >= 0 && temp.amount > list[walk].amount) { 
            //runs while loop to keep shifting struct in array to right if fulfill conditions
            list[walk + 1] = list[walk]; //shifts struct in array to the right
            walk--; //updates walk
        }
        list[walk + 1] = temp; // puts original array in new place
    }
}

/*~*~*~*~*~*~
 This function determines the commision percent based on the following table:
    Sales        Commission
   $0 - 1000        3%
 1001 - 5000        4.5%
 5001 - 10,000      5.25%
 over 10,000        6%
*~*/
double detCommissionPercent(int sales)
{
    double commission = 0;
    
    if (sales == 0 || sales < 1001) {
        commission = 3;
    }
    else if (sales < 5001) {
        commission = 4.5;
    }
    else if (sales < 10001) {
        commission = 5.25;
    }
    else if (sales > 10000) {
        commission = 6;
    }
    return commission;
}

/*~*~*~*~*~*~
 This function determines the amount earned:
 it calls the detCommisionPercent) function.
*~*/
double detAmountEarned(int sales)
{
    double amountEarned = 0;
    //calls func to determine percentage
    double commissionPercentage = detCommissionPercent(sales); 
    amountEarned = sales * commissionPercentage / 100; //divide by 100 to get decimal
    
    return amountEarned;
}

//Func shows sales data including amount sold, name, commission percent, and amount earned
void showSalesData(Sales list[], int size) {
    double commissionPercentage;
    double commissionEarned;
    cout << "Sorted List:\n";

    for(int i = 0; i < size; i++) {//run for loop to see all on array
        cout << "$" << setw(6) << right << list[i].amount;
        cout << " " << list[i].name << ", ";

        //calls func to cal comission percent
        commissionPercentage = detCommissionPercent(list[i].amount); 
        //calls func to cal comission earned
        commissionEarned = detAmountEarned(list[i].amount); 

        cout << commissionPercentage << "% ($" << commissionEarned << ")\n";
    }
}

//func saves sales data to .txt file
void saveSalesData(string fileName, Sales list[], int size) {
    ofstream outFile(fileName); //open output file
    for (int i = 0; i < size; i++) {//writes array into file through for loop
        outFile << list[i].amount << " " << list[i].name << ";\n";
    }

    outFile.close(); //close file
    cout << "The Sales Report has been saved to \"" << fileName << "\"\n";
}