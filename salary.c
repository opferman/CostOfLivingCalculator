/*
 *  Average Salary Calculator - Cost Of Living
 *
 *  Coderot - https://www.youtube.com/channel/UCMN9q8DbU0dnllWpVRvn7Cw  
 *
 *   Toby Opferman - 2019
 *
 *
 *   Simple program that will calculate for US the average amount of money after considering taxes, rent, etc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "taxtables.h"


/*
 * Internal Functions
 */
void Salary_Calculate(PSALARY_CALCULATION_PARAMS pSalaryParams);
int Salary_QueryStateTaxes(PSALARY_CALCULATION_PARAMS pSalaryParams, char *pszStateAbbrev);
float Salary_ComputeTaxes(PSALARY_CALCULATION_PARAMS pSalaryParams, PTAX_ENTRY pTaxTable);
float Salary_FicaEstimate(PSALARY_CALCULATION_PARAMS pSalaryParams);

int _cdecl main(int argc, char *argv[])
{
	SALARY_CALCULATION_PARAMS SalaryParams;
	int QuickExit;


   if (argc < 4 || argc > 6)
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
   else
   {
	   QuickExit = 0;
	   SalaryParams.Salary = atoi(argv[1]);

	   if (SalaryParams.Salary <= 0)
	   {
		   printf("Salary parameter incorrect %i, using default 100,000\n", SalaryParams.Salary);
		   SalaryParams.Salary = 100000;
	   }
	   else
	   {
		   if (SalaryParams.Salary > 5000000)
		   {
			   printf("Salary is %i? Yea right\n", SalaryParams.Salary);
			   QuickExit = 1;
		   }
		   else
		   {
			   printf("Salary %i\n", SalaryParams.Salary);
		   }		   
	   }

	   if (QuickExit == 0)
	   {
		   if (*argv[3] == 'M')
		   {
			   SalaryParams.TaxTableIndex = 0;
			   printf("Using Married tax table\n");
		   }
		   else
		   {
			   SalaryParams.TaxTableIndex = 1;
			   printf("Using Single tax table\n");
		   }

		   if (Salary_QueryStateTaxes(&SalaryParams, argv[2]) == 0)
		   {
			   SalaryParams.StateTaxes = 0.05f;
			   printf("The state '%s' is unknown, using a default flat tax rate value of 5%\n", argv[2]);
		   }

		   SalaryParams.OptionalMonthlyRent = 0;
		   SalaryParams.OptionalOtherExpenses = 0;

		   if (argc >= 5)
		   {
			   SalaryParams.OptionalMonthlyRent = atoi(argv[4]);
			   printf("Optional Montly Rent %i\n", SalaryParams.OptionalMonthlyRent);

			   if (argc >= 6)
			   {
				   SalaryParams.OptionalOtherExpenses = atoi(argv[5]);
				   printf("Optional Other Expenses %i\n", SalaryParams.OptionalOtherExpenses);
			   }
		   }

		   Salary_Calculate(&SalaryParams);
	   }
   }

   return 0;
}



float Salary_ComputeTaxes(PSALARY_CALCULATION_PARAMS pSalaryParams, PTAX_ENTRY pTaxTable)
{
	float TaxesComputed = 0.0f;
	float SalaryLeft;
	int NumbersRange;
	float DollarsToTax;

	SalaryLeft = (float)pSalaryParams->Salary;

	while (SalaryLeft != 0)
	{
		NumbersRange = pTaxTable->EndRange - pTaxTable->StartRange;

		if (SalaryLeft >= NumbersRange)
		{

			SalaryLeft -= ((float)NumbersRange);
			DollarsToTax = ((float)NumbersRange);
		}
		else
		{
			DollarsToTax = SalaryLeft;
			SalaryLeft = 0;
		}

		TaxesComputed += (DollarsToTax*pTaxTable->TaxPercentage);
		pTaxTable++;
	}

	return TaxesComputed;
}


void Salary_Calculate(PSALARY_CALCULATION_PARAMS pSalaryParams)
{
	float SalaryLeftOver;
	float FederalTaxes;
	float StateTaxes;
	float FicaTaxes;

	printf("Your salary is %i\n", pSalaryParams->Salary);
	
	FederalTaxes = Salary_ComputeTaxes(pSalaryParams, &g_FederalTaxes2019[pSalaryParams->TaxTableIndex][0]);
	printf("Your federal taxes are %1.2f\n", FederalTaxes);

	FicaTaxes = Salary_FicaEstimate(pSalaryParams);
	printf("Your FICA taxes are %1.2f\n", FicaTaxes);



	StateTaxes = 0;
	if (pSalaryParams->StateTaxes)
	{
		StateTaxes = pSalaryParams->StateTaxes*pSalaryParams->Salary;
	}
	else
	{
		if (pSalaryParams->pStateTaxTable)
		{
			StateTaxes = Salary_ComputeTaxes(pSalaryParams, pSalaryParams->pStateTaxTable[pSalaryParams->TaxTableIndex]);
		}
	}



	printf("Your state taxes are %1.2f\n", StateTaxes);

	printf("Your monthly rent is %i or %1.2f yearly\n", pSalaryParams->OptionalMonthlyRent, pSalaryParams->OptionalMonthlyRent*12.0f);
	printf("Your other montly expenses are is %i or %1.2f yearly\n", pSalaryParams->OptionalOtherExpenses, pSalaryParams->OptionalOtherExpenses*12.0f);

	SalaryLeftOver = ((float)pSalaryParams->Salary) - FederalTaxes - FicaTaxes - StateTaxes - (pSalaryParams->OptionalMonthlyRent*12.0f) - (pSalaryParams->OptionalOtherExpenses*12.0f);
	printf("What you have left over is %1.2f\n", SalaryLeftOver);

}


int Salary_QueryStateTaxes(PSALARY_CALCULATION_PARAMS pSalaryParams, char *pszStateAbbrev)
{
	int Succeeded = 0;
	int Index;

	Index = 0;

	/*
	 * Try No-Tax states
	 */
	while (g_NoTaxStates[Index] && Succeeded == 0)
	{
		if (_strcmpi(pszStateAbbrev, g_NoTaxStates[Index]) == 0)
		{
			printf("No income tax state\n");
			Succeeded = 1;
			pSalaryParams->pStateTaxTable = NULL;
			pSalaryParams->StateTaxes = 0;
		}
		Index++;
	}

	/*
	* Try Flat Rate Tax states
	*/
	if (Succeeded == 0)
	{
		Index = 0;

		/*
		* Try No-Tax states
		*/
		while (g_FlatStateTaxes[Index].pszStateAbbrev != NULL && Succeeded == 0)
		{
			if (_strcmpi(pszStateAbbrev, g_FlatStateTaxes[Index].pszStateAbbrev) == 0)
			{
				printf("Flat Tax State %1.2f\n", g_FlatStateTaxes[Index].Taxes);
				Succeeded = 1;
				pSalaryParams->pStateTaxTable = NULL;
				pSalaryParams->StateTaxes = g_FlatStateTaxes[Index].Taxes;
			}
			Index++;
		}

	}

	/*
	* Try Tax Table states
	*/
	if (Succeeded == 0)
	{
		Index = 0;

		/*
		* Try No-Tax states
		*/
		while (g_StateTaxTables[Index].pszStateAbbrev != NULL && Succeeded == 0)
		{
			if (_strcmpi(pszStateAbbrev, g_StateTaxTables[Index].pszStateAbbrev) == 0)
			{
				if (g_StateTaxTables[Index].pTaxTable == NULL)
				{
					printf("Tax Table State, however no taxes will be used since we currently do not have the table for this state.\n");
				}
				else
				{
					printf("Tax Table State, using state tax table.\n");
				}
				
				Succeeded = 1;
				pSalaryParams->pStateTaxTable = g_StateTaxTables[Index].pTaxTable;
				pSalaryParams->StateTaxes = 0;
			}
			Index++;
		}

	}
	return Succeeded;
}

float Salary_FicaEstimate(PSALARY_CALCULATION_PARAMS pSalaryParams)
{
	/* TODO: Not Implemented */
	printf("** FICA not implemented **\n");

	return 0;
}

/*
Alabama -    AL
Alaska -     AK
Arizona -    AZ
Arkansas -   AR
California - CA
Colorado -   CO
Connecticut -CT
Delaware -   DE
Florida -    FL
Georgia -    GA
Hawaii -     HI
Idaho -      ID
Illinois -   IL
Indiana -    IN
Iowa -       IA
Kansas -     KS
Kentucky -   KY
Louisiana -  LA
Maine -      ME
Maryland -   MD
MassachusettsMA
Michigan -   MI
Minnesota -  MN
Mississippi -MS
Missouri -   MO
Montana -    MT
Nebraska -   NE
Nevada -     NV
New HampshireNH
New Jersey - NJ
New Mexico - NM
New York -   NY
North CarolinNC
North Dakota ND
Ohio -       OH
Oklahoma -   OK
Oregon -     OR
Pennsylvania PA
Rhode Island RI
South CarolinSC
South Dakota SD
Tennessee -  TN
Texas -      TX
Utah -       UT
Vermont -    VT
Virginia -   VA
Washington - WA
West VirginiaWV
Wisconsin -  WI
Wyoming -    WY
*/