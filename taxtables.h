/*
 * The Tax Tables
 *
 * Toby Opferman - 2019
 */


#ifndef _TAX_TABLES_H__
#define _TAX_TABLES_H__

typedef enum _STATE_TAX_TYPE {
    StateTaxInvalid,
    StateTaxNone,
    StateTaxFlat,
    StateTaxTable

} STATE_TAX_TYPE, *PSTATE_TAX_TYPE;

typedef enum _TAX_FILING_TYPE {
   TaxFilingMarried,
   TaxFilingSingle

} TAX_FILING_TYPE, *PTAX_FILING_TYPE;


typedef struct _TAX_ENTRY {
    int StartRange;
    int EndRange;
    float TaxPercentage;
} TAX_ENTRY, *PTAX_ENTRY;

typedef struct _STATE_TAX_LOOKUP_TABLE {
    char *pszStateName;
    char *pszStateAbbrev;
    STATE_TAX_TYPE StateTaxType;
    float StateFlatTax;
    PTAX_ENTRY *pTaxTable;
} STATE_TAX_LOOKUP_TABLE, *PSTATE_TAX_LOOKUP_TABLE;


extern TAX_ENTRY g_FederalTaxes2019[2][8];
STATE_TAX_LOOKUP_TABLE g_StateTaxLookupTable [];


#endif
