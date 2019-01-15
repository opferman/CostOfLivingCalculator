/*
 * The Tax Tables
 *
 * Toby Opferman - 2019
 */


#ifndef _TAX_TABLES_H__
#define _TAX_TABLES_H__

typedef struct _TAX_ENTRY {
	int StartRange;
	int EndRange;
	float TaxPercentage;
} TAX_ENTRY, *PTAX_ENTRY;

typedef struct _STATE_TAX_TABLES {
	char *pszStateAbbrev;
	PTAX_ENTRY *pTaxTable;
} STATE_TAX_TABLES, *PSTATE_TAX_TABLES;


typedef struct _SALARY_CALCULATION_PARAMS {
	int Salary;
	float StateTaxes;
	PTAX_ENTRY *pStateTaxTable;
	int OptionalMonthlyRent;
	int OptionalOtherExpenses;
	int TaxTableIndex;
} SALARY_CALCULATION_PARAMS, *PSALARY_CALCULATION_PARAMS;

typedef struct _STATE_TAXES {
	char *pszStateAbbrev;
	float Taxes;
} STATE_TAXES, *PSTATE_TAXES;


extern TAX_ENTRY g_FederalTaxes2019[2][8];
extern STATE_TAXES g_FlatStateTaxes[];
extern char *g_NoTaxStates[];
extern STATE_TAX_TABLES g_StateTaxTables[];


#endif
