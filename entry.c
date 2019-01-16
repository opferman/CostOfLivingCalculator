/*
 *  Average Salary Calculator - Cost Of Living
 *
 *  Checksum Error - https://www.youtube.com/channel/UCMN9q8DbU0dnllWpVRvn7Cw  
 *
 *   Toby Opferman - 2019
 *
 *
 *   Simple program that will calculate for US the average amount of money after considering taxes, rent, etc.
 *      Quick program in 2 hours, needs revised.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "salary.h"

#define MIN_SALARY 0
#define MAX_SALARY 4000000

typedef struct _OPTIONAL_PARAMETERS {
    int MonthlyRent;
    int OtherExpenses;

} OPTIONAL_PARAMETERS, *POPTIONAL_PARAMETERS;

typedef enum _ERROR_TYPE {
    ErrorInvalidSalary,
    ErrorInvalidState

} ERROR_TYPE, *PERROR_TYPE;


typedef enum _CMD_LINE_PARSE_STATE {

    CmdLneParse_Salary,
    CmdLneParse_State,
    CmdLneParse_FilingType,
    CmdLneParse_MonthlyRent,
    CmdLneParse_MonthlyExpenses,
    CmdLneParse_CompleteSuccess,
    CmdLneParse_CompleteFail

} CMD_LINE_PARSE_STATE, *PCMD_LINE_PARSE_STATE;

/*
 * Internal Functions
 */
void SalaryCalculator_DisplayCommandLineText(void);
int SalaryCalculator_ParseCommandLine(PSALARY_CALCULATION_PARAMS pSalaryParams, POPTIONAL_PARAMETERS pOptionalParameters, char **Args, int ArgcCount);
void SalaryCalculator_DisplaySalaryResults(PSALARY_CALCULATION_PARAMS pSalaryParams, PSALARY_TAXES pSalaryTaxes, POPTIONAL_PARAMETERS pOptionalParameters);
void SalaryCalculator_DisplayErrorString(ERROR_TYPE ErrorType);

/********************************************
*
* main
*
*   Program Entry Point
*
*
*******************************************/
int _cdecl main(int argc, char *argv[])
{
   SALARY_CALCULATION_PARAMS SalaryParams;
   SALARY_TAXES SalaryTaxes;
   OPTIONAL_PARAMETERS OptionalParameters;

   if (argc < 4 || argc > 6)
   {
       SalaryCalculator_DisplayCommandLineText();
   }
   else
   {
       if(SalaryCalculator_ParseCommandLine(&SalaryParams, &OptionalParameters, &argv[1], argc-1))
       {
           Salary_CalculateTaxes(&SalaryParams, &SalaryTaxes);
           SalaryCalculator_DisplaySalaryResults(&SalaryParams, &SalaryTaxes, &OptionalParameters);
       } 
    }

    return 0;
}


/********************************************
*
* SalaryCalculator_ParseCommandLine
*
*   Parse the command line.
*
*
*******************************************/
int SalaryCalculator_ParseCommandLine(PSALARY_CALCULATION_PARAMS pSalaryParams, POPTIONAL_PARAMETERS pOptionalParameters, char **Args, int ArgcCount)
{
    CMD_LINE_PARSE_STATE CmdLneState;
    int ReturnValue;

    CmdLneState = CmdLneParse_Salary;

    memset(pSalaryParams, 0, sizeof(SALARY_CALCULATION_PARAMS));
    memset(pOptionalParameters, 0, sizeof(OPTIONAL_PARAMETERS));

    while (CmdLneState != CmdLneParse_CompleteSuccess && CmdLneState != CmdLneParse_CompleteFail)
    {

        switch (CmdLneState)
        {
                case CmdLneParse_Salary:
                    pSalaryParams->Salary = atoi(Args[0]);
                    if (pSalaryParams->Salary <= MIN_SALARY || pSalaryParams->Salary >= MAX_SALARY)
                    {
                        SalaryCalculator_DisplayErrorString(ErrorInvalidSalary);
                        CmdLneState = CmdLneParse_CompleteFail;
                    }
                    else
                    {
                        Args++;
                        ArgcCount--;
                        CmdLneState++;
                    }
                    break;

                case CmdLneParse_State:
                    if (Salary_QueryStateTaxes(pSalaryParams, Args[0]) == 0)
                    {
                        SalaryCalculator_DisplayErrorString(ErrorInvalidState);
                        CmdLneState = CmdLneParse_CompleteFail;
                    }
                    else
                    {
                        Args++;
                        ArgcCount--;
                        CmdLneState++;
                    }
                    break;

                case CmdLneParse_FilingType:
                    if (*Args[0] == 'M')
                    {
                        pSalaryParams->TaxFilingType = TaxFilingMarried;
                    }
                    else
                    {
                        pSalaryParams->TaxFilingType = TaxFilingSingle;
                    }
                    Args++;
                    ArgcCount--;
                    CmdLneState++;
                    break;

                case CmdLneParse_MonthlyRent:
                    pOptionalParameters->MonthlyRent = atoi(Args[0]);
                    Args++;
                    ArgcCount--;
                    CmdLneState++;
                    break;

                case CmdLneParse_MonthlyExpenses:
                    pOptionalParameters->OtherExpenses = atoi(Args[0]);
                    Args++;
                    ArgcCount--;
                    CmdLneState++;
                    break;

        }

        if (ArgcCount == 0)
        {
            CmdLneState = CmdLneParse_CompleteSuccess;
        }
    }

    if (CmdLneState == CmdLneParse_CompleteSuccess)
    {
        ReturnValue = 1;
    }
    else
    {
        ReturnValue = 0;
    }

    return ReturnValue;
}


/********************************************
*
* SalaryCalculator_DisplayCommandLineText
*
*   Display program arguements
*
*
*******************************************/
void SalaryCalculator_DisplayCommandLineText(void)
{
   printf("Salary and Cost of Living Calculator \n");
   printf("salary [Salary] [State Abbrev] [M or S]  <Optional Monthly Rent>  <Optional Other Monthly Expenses>\n\n");
   printf("Example:\n");
   printf("        Salary  100000 CA S 1500 1000\n\n");
   printf("    Salary - Your yearly salary before taxes\n");
   printf("    State Abbrev - The state such as HI (Hawaii), WA (Washington), FL (Florida), CA (Califonria), etc.\n");
   printf("    M or S - M or Married filing Joinly or S for Single to calculate federal taxes.\n");
   printf("    Monthly Rent - Optionally supply the monthly rent since this program doesn't store rent averages for each city\n");
   printf("    Other Monthly Expenses - Optionally supply a consolidated monthly bills and/or food cost\n");
}


/********************************************
*
* SalaryCalculator_DisplayErrorString
*
*   Display error messages
*
*
*******************************************/
void SalaryCalculator_DisplayErrorString(ERROR_TYPE ErrorType)
{
    switch (ErrorType)
    {
        case ErrorInvalidSalary:
            printf("Error: Salary must be %i > Salary < %i\n", MIN_SALARY, MAX_SALARY);
            break;
        case ErrorInvalidState:
            printf("Error: Invalid state supplied.\n");
            break;
    }

}


/********************************************
*
* SalaryCalculator_DisplaySalaryResults
*
*   Display the Calculated Salary and expenses
*
*
*******************************************/
void SalaryCalculator_DisplaySalaryResults(PSALARY_CALCULATION_PARAMS pSalaryParams, PSALARY_TAXES pSalaryTaxes, POPTIONAL_PARAMETERS pOptionalParameters)
{
    double SalaryCalculation;
    double SalaryCalculationAfterTaxes;
    printf("Your salary is %i\n", pSalaryParams->Salary);
    printf("Federal Taxes: %1.2f\n", pSalaryTaxes->FederalTaxes);

    if (pSalaryParams->pStateTaxTable == NULL && pSalaryParams->StateTaxType == StateTaxTable)
    {
        printf("%s State Tax Tables are not available.\n", pSalaryParams->pszStateName);
    }
    else
    {
        printf("%s State Taxes: %1.2f\n", pSalaryParams->pszStateName, pSalaryTaxes->StateTaxes);
    }

    printf("FICA Taxes: %1.2f\n", pSalaryTaxes->Fica);
    printf("*************************************\n");

    SalaryCalculation = ((float)pSalaryParams->Salary) - pSalaryTaxes->FederalTaxes - pSalaryTaxes->StateTaxes - pSalaryTaxes->Fica;
    printf("Left after taxes: %1.2f\n\n", SalaryCalculation);

    SalaryCalculationAfterTaxes = SalaryCalculation;
    if (pOptionalParameters->MonthlyRent)
    {
        SalaryCalculationAfterTaxes = SalaryCalculationAfterTaxes - ((float)pOptionalParameters->MonthlyRent*12);
        printf(" Monthly Rent: %i", pOptionalParameters->MonthlyRent);
        printf("    Total Yearly: %i\n\n", pOptionalParameters->MonthlyRent * 12);
    }

    if (pOptionalParameters->OtherExpenses)
    {
        SalaryCalculationAfterTaxes = SalaryCalculationAfterTaxes - ((float)pOptionalParameters->OtherExpenses * 12);
        printf(" Monthly Expenses: %i", pOptionalParameters->OtherExpenses);
        printf("    Total Yearly: %i\n\n", pOptionalParameters->OtherExpenses * 12);
    }

    if (SalaryCalculationAfterTaxes != SalaryCalculation)
    {
        printf("  Final left: %1.2f\n", SalaryCalculationAfterTaxes);
    }
}