#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>

/*Variables*/
/*Employee structure*/
struct Employee
{
	unsigned int iEmployeeId;
	std::string strName;
	std::string strEMail;
	unsigned int iBasicSalary;
	unsigned int iPF;
	unsigned int iHealthInsurance;
};

/*Variables used for controlling the Widths of the fields for displaying the Employee records*/
const int iWidthTotal = 110;
const int iWidthEmpId = 10;
const int iWidthEmpName = 25;
const int iWidthEmpEmail = 25;
const int iWidthEmpBasic = 10;
const int iWidthEmpPF = 15;
const int iWidthEmpHltInc = 15;
const int iWidthEmpNet = 10;

/*Macros*/
#define EXIT (unsigned int)6
#define GETNETSALARY(basic, pf, healthinc)  basic-(pf+healthinc)

/*Function Prototypes*/
void printMenu();

//Reads the employee records from a Text file and return the number of records parsed
int readEmployeeRecords(std::vector<Employee>& v_emp, std::string fileName); 

//Prints the data read from the text file containing employee records in a specific format
void printEmployeeRecords(std::vector<Employee> v_emp);
void printSingleEmployeeRecord(std::vector<Employee> v_emp, unsigned int iIndex);

//Searches an Employee record
int searchEmployee(std::vector<Employee> v_emp, unsigned int iEmployeeId);

//Adds an Employee record to the Vector
void addEmployee(std::vector<Employee>& v_emp);

//Deletes an Employee record from a Vector
void deleteEmployee(std::vector<Employee>& v_emp);

//Save all records in the secondary memory
void saveEmployeeRecords(std::vector<Employee> v_emp, std::string strFileName);

void main()
{	
	unsigned int iUserOption;
	unsigned int iEmployeeId;
	unsigned int iEmpIndex = -1;
	std::string strFileName("records.txt");
	std::vector<Employee> v_emp;

	//Read Employee records and store the read data into a Vector
	int iCountEmployees = readEmployeeRecords(v_emp, strFileName);
	if (iCountEmployees >= 0)
	{
		std::cout << std::endl << "Total number of records read from the text file is " << iCountEmployees << std::endl;
	}	

	while (1)
	{
		printMenu();
		std::cin >> iUserOption;
		if (EXIT == iUserOption)
		{
			exit(1);
		}
		else
		{
			switch (iUserOption)
			{
			    case 1 : //Add Employee
					std::cout << "Selected option : Add Employee";
					addEmployee(v_emp);
				break;
				case 2 : //Print Employee reports 
					std::cout << "Selected option : Print Employee Reports";
					printEmployeeRecords(v_emp);
				break;
				case 3 : //Search Employee
					std::cout << "Selected option : Search Employee";
					std::cout << std::endl << std::endl <<"Enter Employee ID : ";
					std::cin >> iEmployeeId;
					iEmpIndex = searchEmployee(v_emp, iEmployeeId);
					if (-1 == iEmpIndex)
						std::cout << "Employee does not exist" << std::endl;
					else
					{
						std::cout << std::endl <<"Employee found. Details are as follows : ";
						printSingleEmployeeRecord(v_emp, iEmpIndex);
					}					    
				break;
				case 4 : //Delete Employee
					std::cout << "Selected option : Delete Employee records";
					deleteEmployee(v_emp);
				break;
				case 5 : //Save 
					std::cout << "Selected option : Save an employee record";
					saveEmployeeRecords(v_emp, strFileName);
				break;
			}
		}
	}
}//end main()

void printMenu()
{
	std::cout << std::endl << std::endl;
	std::cout << "1. Add Employee" << std::endl
		      << "2. Print Employee reports" << std::endl
		      << "3. Search Employee" << std::endl
		      << "4. Delete Employee" << std::endl
		      << "5. Save" << std::endl		
		      << "6. Exit" << std::endl
		      << "Your option: ";
}//end printMenu()

int readEmployeeRecords(std::vector<Employee> &v_emp, std::string fileName)
{

	std::ifstream empRecords(fileName);
	if (true == empRecords.fail())
	{
		std::cout << "Error opening file " << fileName;
		return -1;
	}

	//Holds the count of the number of Employee records in the text file
	int count = 0;

	std::cout << "Parsing data ... " << std::endl;
	while (!empRecords.eof())
	{
		Employee emp_temp;

		unsigned int iEmployeeId;
		std::string strName;
		std::string strEMail;
		unsigned int iBasicSalary;
		unsigned int iPF;
		unsigned int iHealthInsurance;		

		std::string strLine;

		//Parse the next line from the file pointed to by the file handle "empRecords"		
		std::getline(empRecords, strLine);

		//Create a isstringstream object from the Parsed Line 
		std::istringstream issLine(strLine);

		//Parse the comma separated attributes in the line 
		std::string strTemp;

		//Variable that holds the position of the attribute being parsed for a single Employee
		unsigned int index = 0;

		while (std::getline(issLine, strTemp, ',')) {			
			if (0 == index) //Employee ID
			{
				emp_temp.iEmployeeId = atoi(strTemp.c_str());				
			}
			else if (1 == index) //Name 
			{
				emp_temp.strName = strTemp;				
			}
			else if (2 == index) //Basic 
			{
				emp_temp.iBasicSalary = stod(strTemp);				
			}
			else if (3 == index) //PF
			{
				emp_temp.iPF = stod(strTemp);				
			}
			else if (4 == index) //Health Insurance 
			{
				emp_temp.iHealthInsurance = stod(strTemp);				
			}
			else if (5 == index) //EMail ID
			{
				emp_temp.strEMail = strTemp;				
			}
			else
			{
				std::cout << std::endl << "Unexpected data in the text file containing employee records" << std::endl;
				std::cout << "Exiting ... " << std::endl;
				exit(1);
			}
			
			index += 1;			
		}		
		
		v_emp.push_back(emp_temp);
		count += 1;
		
	}//end outer while loop that parses the employee records in the text file line by line

	empRecords.close();
	return count;
}//readEmployeeRecords()

void printSingleEmployeeRecord(std::vector<Employee> v_emp, unsigned int iIndex)
{
	std::vector<Employee>::iterator it = v_emp.begin() + iIndex;
	std::cout << std::endl;
	std::cout << "** Employee ID : "<< it->iEmployeeId <<std::endl
		<< "** Employee Name : " << it->strName << std::endl
		<< "** Employee EMail : "<< it->strEMail << std::endl
		<< "** Basic Salary (in $) : " << it->iBasicSalary << std::endl
		<< "** PF (in $) : " << it->iPF << std::endl
		<< "** Health Insurace (in $) : "<< it->iHealthInsurance << std::endl
		<< "** Net Salary (in $) : " << GETNETSALARY(it->iBasicSalary, it->iPF, it->iHealthInsurance)
		<< std::endl;
}

void printEmployeeRecords(std::vector<Employee> v_emp)
{
	std::string strTemp(iWidthTotal, '-');
	unsigned int iTotalBasic=0, iTotalPF=0, iTotalHltInc=0, iTotalNet = 0;
	
	std::cout << std::endl << std::endl;

	std::cout << std::setw(iWidthEmpId) << std::left << "Emp Id"
		      << std::setw(iWidthEmpName) << std::left << "Name"
		      << std::setw(iWidthEmpEmail) << std::left << "EMail"
		      << std::setw(iWidthEmpBasic) << std::right << "Basic ($)"
		      << std::setw(iWidthEmpPF) << std::right << "PF ($)"
		      << std::setw(iWidthEmpHltInc) << std::right << "HltInc ($)"
		      << std::setw(iWidthEmpNet) << std::right << "Net ($)"
		      << std::endl;

	std::cout << std::setw(iWidthTotal) << strTemp << std::endl;
	
	for (std::vector<Employee>::iterator it = v_emp.begin(); it < v_emp.end();it++)
	{
		std::cout << std::setw(iWidthEmpId)     << std::left  << it->iEmployeeId
			      << std::setw(iWidthEmpName)   << std::left  << it->strName
			      << std::setw(iWidthEmpEmail)  << std::left  << it->strEMail
			      << std::setw(iWidthEmpBasic)  << std::right << std::setprecision(2) << std::fixed << it->iBasicSalary
			      << std::setw(iWidthEmpPF)     << std::right << std::setprecision(2) << std::fixed << it->iPF
			      << std::setw(iWidthEmpHltInc) << std::right << std::setprecision(2) << std::fixed << it->iHealthInsurance
			      << std::setw(iWidthEmpNet) << std::right << std::setprecision(2) << std::fixed << GETNETSALARY(it->iBasicSalary, it->iPF, it->iHealthInsurance)
			      << std::endl;	

		iTotalBasic += it->iBasicSalary;
		iTotalPF += it->iPF;
		iTotalHltInc += it->iHealthInsurance;
		iTotalNet += GETNETSALARY(it->iBasicSalary, it->iPF, it->iHealthInsurance);
	}

	std::cout << std::setw(iWidthTotal) << strTemp << std::endl;
	
	std::cout << std::setw(iWidthEmpId ) << std::left << "Total"
		<< std::setw(+iWidthEmpName + iWidthEmpEmail) << std::left << "In($)"		
		<< std::setw(iWidthEmpBasic) << std::right << iTotalBasic
		<< std::setw(iWidthEmpPF) << std::right << iTotalPF
		<< std::setw(iWidthEmpHltInc) << std::right << iTotalHltInc
		<< std::setw(iWidthEmpNet) << std::right << iTotalNet
		<< std::endl;

}//printEmployeeRecords()

int searchEmployee(std::vector<Employee> v_emp, unsigned int iEmployeeId)
{
	int iIndexFound = -1; //Index in the vector list where the searched Employee is located
	unsigned int iCurrIndex = 0;
	for (std::vector<Employee>::iterator it = v_emp.begin(); it < v_emp.end(); it++)
	{
		if (it->iEmployeeId == iEmployeeId)
		{
			iIndexFound = iCurrIndex;
			break;
		}

		iCurrIndex += 1;
	}

	return iIndexFound;
}//searchEmployee() ends here

void addEmployee(std::vector<Employee>& v_emp)
{
	Employee emp_temp;

	bool flag = true, abortAddEmployeeFlag = false;

	while (flag && !abortAddEmployeeFlag)
	{
		unsigned int iOption = 1; //Default option is to reenter a new employee record
		std::cout << std::endl << std::endl;
		std::cout << "New Employee ID = ";
		std::cin >> emp_temp.iEmployeeId;

		if (searchEmployee(v_emp, emp_temp.iEmployeeId) != -1) //Employee ID exists already
		{
			std::cout << "Employee with ID " << emp_temp.iEmployeeId << " already exists " << std::endl << std::endl
				<< "Enter" << std::endl
				<< "1 - Re-enter a new employee ID" << std::endl
				<< "0 - Exit adding an Employee record" << std::endl
				<< "Your option : ";
			std::cin >> iOption;

			if (0 == iOption)
				abortAddEmployeeFlag = true;
		}
		else
		{
			flag = false;
		}		
	}//Employee ID loop 

	if (abortAddEmployeeFlag)
	{
		return;
	}
	else //Prompt user to enter more attributes regarding the new Employee if the "abortAddEmployeeFlag" flag is not asserted
	{
		//Clear the cin buffer before prompting the user for a string 
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n'); //Flush out all newline characters in the cin buffer

		std::cout << "Employee Name = ";
		std::cin >> emp_temp.strName;

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "Employee EMail = ";
		std::cin >> emp_temp.strEMail;

		std::cout << "Basic Salary (in $) = ";
		std::cin >> emp_temp.iBasicSalary;

		std::cout << "PF (in $) = ";
		std::cin >> emp_temp.iPF;

		std::cout << "Health Insurance (in $) = ";
		std::cin >> emp_temp.iHealthInsurance;

		v_emp.push_back(emp_temp);
	}

}// addEmployee()

void deleteEmployee(std::vector<Employee>& v_emp)
{
	unsigned int iEmployeeId;
	unsigned int iUserOption;
	std::cout << std::endl << "Enter Employee ID of the employee to be deleted : ";
	std::cin >> iEmployeeId;

	int iEmpIndex = searchEmployee(v_emp, iEmployeeId);

	if (iEmpIndex == -1) //Employee ID not found 
	{
		std::cout << "Employee with ID = " << iEmployeeId << " not found" << std::endl;
		return;
	}
	else
	{
		std::cout << std::endl <<"Are you sure that you want to delete the following record ? " ;
		printSingleEmployeeRecord(v_emp, iEmpIndex);
		std::cout << std::endl << "Enter" << std::endl
			      << "1 - Delete" << std::endl
			      << "0 - Exit without deleting" << std::endl
			      << "Your option : ";
		std::cin >> iUserOption;

		if (0 == iUserOption)
		{
			return;
		}
		else
		{
			v_emp.erase(v_emp.begin()+iEmpIndex);
		}
	}
}//deleteEmployee()

void saveEmployeeRecords(std::vector<Employee> v_emp, std::string strFileName)
{
	std::ofstream fout(strFileName);
	if (fout.fail() == true)
	{
		std::cout << "Error opening file " << strFileName;
		return ;
	}
	
	for(std::vector<Employee>::iterator it = v_emp.begin() ;  it < v_emp.end(); ++it)
	{
		fout << it->iEmployeeId << ','
			<< it->strName << ','
			<< it->iBasicSalary << ','
			<< it->iPF << ','
			<< it->iHealthInsurance << ','
			<< it->strEMail;

		if (it != (v_emp.end() - 1))
		{
			fout << std::endl;
		}
	}
	fout.close();
}//saveEmployeeRecord()