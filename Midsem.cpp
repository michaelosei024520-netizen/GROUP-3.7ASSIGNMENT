#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

class EmployeePayroll
{
private:
    string employeeID;
    string employeeName;
    string department;

    double basicSalary;
    double allowance;
    double deduction;

    double grossSalary;
    double netSalary;

    string salaryStatus;

public:

    void setEmployeeDetails()
    {
        cout << "Enter Employee ID: ";
        cin >> employeeID;

        cin.ignore();

        cout << "Enter Employee Name: ";
        getline(cin, employeeName);

        cout << "Enter Department: ";
        getline(cin, department);

        cout << "Enter Basic Salary: ";
        cin >> basicSalary;

        cout << "Enter Allowance: ";
        cin >> allowance;

        cout << "Enter Deduction: ";
        cin >> deduction;
    }

    bool validateDetails()
    {
        if (basicSalary < 0 || allowance < 0 || deduction < 0)
        {
            return false;
        }
        return true;
    }

    void calculateGrossSalary()
    {
        grossSalary = basicSalary + allowance;
    }

    void calculateNetSalary()
    {
        netSalary = grossSalary - deduction;
    }

    void checkSalaryStatus()
    {
        if (deduction > grossSalary)
        {
            salaryStatus = "Review Required";
        }
        else
        {
            salaryStatus = "Ready for Payment";
        }
    }

    void displayPayrollReport()
    {
        cout << "\n========== PAYROLL REPORT ==========\n";

        cout << "Employee ID: " << employeeID << endl;
        cout << "Employee Name: " << employeeName << endl;
        cout << "Department: " << department << endl;
        cout << fixed << setprecision(2);
        cout << "Gross Salary: GHS " << grossSalary << endl;
        cout << "Net Salary: GHS " << netSalary << endl;
        cout << "Status: " << salaryStatus << endl;
    }

    void savePayrollReport(ofstream &file)
    {
        file << "Employee ID: " << employeeID << endl;
        file << "Employee Name: " << employeeName << endl;
        file << "Department: " << department << endl;
        file << fixed << setprecision(2);
        file << "Gross Salary: GHS " << grossSalary << endl;
        file << "Net Salary: GHS " << netSalary << endl;
        file << "Status: " << salaryStatus << endl;
        file << "-----------------------------------" << endl;
    }

    double getNetSalary()
    {
        return netSalary;
    }
};

int main()
{
    cout << "=========================================\n";
    cout << " SIMPLE PAYROLL MANAGEMENT SYSTEM\n";
    cout << "=========================================\n";

    int numberOfEmployees;

    cout << "Enter number of employees: ";
    cin >> numberOfEmployees;

    vector<EmployeePayroll> employees(numberOfEmployees);

    ofstream report("payroll_report.txt");

    double totalSalary = 0;

    for (int i = 0; i < numberOfEmployees; i++)
    {
        cout << "\nEmployee " << i + 1 << endl;

        employees[i].setEmployeeDetails();

        if (!employees[i].validateDetails())
        {
            cout << "Invalid payroll record!\n";
            continue;
        }

        employees[i].calculateGrossSalary();
        employees[i].calculateNetSalary();
        employees[i].checkSalaryStatus();

        employees[i].displayPayrollReport();
        employees[i].savePayrollReport(report);

        totalSalary += employees[i].getNetSalary();
    }

    report.close();

    cout << "\n=========================================\n";
    cout << "Total Employees Processed: " << numberOfEmployees << endl;
    cout << "Total Net Salary: GHS " << fixed << setprecision(2) << totalSalary << endl;
    cout << "Payroll report saved to payroll_report.txt" << endl;
    cout << "=========================================\n";

    return 0;
}