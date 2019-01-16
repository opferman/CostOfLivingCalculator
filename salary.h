/*
 * Salary Header File
 *
 */


#ifndef __SALARY_H__
#define __SALARY_H__

#include "taxtables.h"



typedef struct _SALARY_CALCULATION_PARAMS {
    int Salary;
    char *pszStateName;
    STATE_TAX_TYPE StateTaxType;
    float StateFlatTax;
    PTAX_ENTRY *pStateTaxTable;
    TAX_FILING_TYPE TaxFilingType;
    
} SALARY_CALCULATION_PARAMS, *PSALARY_CALCULATION_PARAMS;

typedef struct _SALARY_TAXES {

    float FederalTaxes;
    float Fica;
    float StateTaxes;

} SALARY_TAXES, *PSALARY_TAXES;

void Salary_CalculateTaxes(PSALARY_CALCULATION_PARAMS pSalaryParams, PSALARY_TAXES pSalaryTaxes);
int Salary_QueryStateTaxes(PSALARY_CALCULATION_PARAMS pSalaryParams, char *pszStateAbbrev);



#endif

 