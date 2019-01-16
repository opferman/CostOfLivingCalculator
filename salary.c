/*
 *  Salary Library
 *
 *  Checksum Error - https://www.youtube.com/channel/UCMN9q8DbU0dnllWpVRvn7Cw  
 *
 *   Toby Opferman - 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "salary.h"
#include "taxtables.h"


/*
 * Internal Functions
 */
float Salary_Internal_ComputeTaxes(PSALARY_CALCULATION_PARAMS pSalaryParams, PTAX_ENTRY pTaxTable);
float Salary_Internal_FicaEstimate(PSALARY_CALCULATION_PARAMS pSalaryParams);


/********************************************
 *
 * Salary_Internal_ComputeTaxes
 *
 *   Use the supplied tax table to compute taxes
 *   and return the amount of taxes.
 *
 *******************************************/
float Salary_Internal_ComputeTaxes(PSALARY_CALCULATION_PARAMS pSalaryParams, PTAX_ENTRY pTaxTable)
{
    float TaxesComputed = 0.0f;
    float SalaryLeft;
    int NumbersRange;
    float DollarsToTax;

	SalaryLeft = ((float)pSalaryParams->Salary);

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

/********************************************
*
* Salary_CalculateTaxes
*
*   Calculate all taxes based on the salary
*   
*
*******************************************/
void Salary_CalculateTaxes(PSALARY_CALCULATION_PARAMS pSalaryParams, PSALARY_TAXES pSalaryTaxes)
{

    pSalaryTaxes->FederalTaxes = Salary_Internal_ComputeTaxes(pSalaryParams, &g_FederalTaxes2019[pSalaryParams->TaxFilingType][0]);
    pSalaryTaxes->Fica = Salary_Internal_FicaEstimate(pSalaryParams);

    switch (pSalaryParams->StateTaxType)
    {
        case StateTaxNone:
            pSalaryTaxes->StateTaxes = 0;
            break;
    
        case StateTaxFlat:
            pSalaryTaxes->StateTaxes = pSalaryParams->StateFlatTax*((float)pSalaryParams->Salary);
            break;

        case StateTaxTable:
            if (pSalaryParams->pStateTaxTable)
            {
                pSalaryTaxes->StateTaxes = Salary_Internal_ComputeTaxes(pSalaryParams, pSalaryParams->pStateTaxTable[pSalaryParams->TaxFilingType]);
            }
            else
            {
                pSalaryTaxes->StateTaxes = 0; /* Missing Tax Table */
            }
            break;
    }
}

/********************************************
*
* Salary_QueryStateTaxes
*
*   Updates the tax information.
*
*
*******************************************/
int Salary_QueryStateTaxes(PSALARY_CALCULATION_PARAMS pSalaryParams, char *pszStateAbbrev)
{
    int Succeeded = 0;
    int Index;

    Index = 0;

    while (g_StateTaxLookupTable[Index].pszStateAbbrev != NULL && Succeeded == 0)
    {
        if (_strcmpi(pszStateAbbrev, g_StateTaxLookupTable[Index].pszStateAbbrev) == 0)
        {
            Succeeded = 1;

			pSalaryParams->pszStateName = g_StateTaxLookupTable[Index].pszStateName;
			pSalaryParams->StateFlatTax = g_StateTaxLookupTable[Index].StateFlatTax;
			pSalaryParams->StateTaxType = g_StateTaxLookupTable[Index].StateTaxType;
            pSalaryParams->pStateTaxTable = g_StateTaxLookupTable[Index].pTaxTable;
        }
        Index++;
    }

    return Succeeded;
}



/********************************************
*
* Salary_Internal_FicaEstimate
*
*   Calculates the FICA Taxes
*
*
*******************************************/
float Salary_Internal_FicaEstimate(PSALARY_CALCULATION_PARAMS pSalaryParams)
{
    /* TODO: Not Implemented */

    return 0.0f;
}

