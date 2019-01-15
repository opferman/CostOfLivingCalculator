/*
 * Tax Tables Globals
 *
 *  Toby Opferman
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "taxtables.h"

#define TAX_LIMIT_INFINTE 1000000000
/*
 * Table Indexes are 0 for Married and 1 for Single.
 */

TAX_ENTRY g_FederalTaxes2019[2][8] = {
{
	{ 0,     19400,    .1f},
	{ 19400, 78950,    .12f},
	{ 78950, 168400,   .22f},
	{ 1658400, 321450, .24f},
	{ 321450, 408200,  .32f},
	{ 408200, 612350,  .35f},
	{ 612350, TAX_LIMIT_INFINTE, .37f},
	{ 0, 0, 0.0f }
},
{
	{ 0,     9700,    .1f },
	{ 9700, 39475,    .12f },
	{ 39475, 84200,   .22f },
	{ 84200, 160725, .24f },
	{ 160725, 204100,  .32f },
	{ 204100, 510300,  .35f },
	{ 510300, TAX_LIMIT_INFINTE, .37f },
	{ 0, 0, 0.0f }
} };

/* TODO: Combine to 1 table, add full state name and enumeration on the tax type (Flat, None or Table).  Write single tax decode function and binary sort. */

STATE_TAXES g_FlatStateTaxes[] = {
{	"CO", .0463f },
{	"IL", .0495f },
{	"IN", .0323f },
{	"MA",.051f},
{	"MI",.051f},
{	"NC",.05499f},
{	"PA",.0307f},
{	"UT",.05f},
{ NULL, 0.0f }
};

char *g_NoTaxStates[] =
{
	{ "AK"},
	{ "WA"},
	{ "TX"},
	{ "NV"},
	{ "SD"},
	{ "WY"},
	{ "FL"},
	{ NULL }
};

/* Tax tables are being used as exclusive (i.e. <= max range instead of < max range, this may skew the results minorly for some states. */

TAX_ENTRY g_CaliforniaTaxTableMarried[] =
{
	{ 0        ,     16030, 0.01f },
	{ 16030		 , 38002, 0.02f },
	{ 38002    , 	  59978, 0.04f },
	{ 59978	,	  83258, 0.06f },
	{ 83258	,	  105224, 0.08f },
	{ 105224	,	  537500, 0.093f },
	{ 537500	,	  644998,  0.103f },
	{ 644998	,	  1000000, 0.113f },
	{ 1000000	,	  1074996, 0.123f },
	{ 1074996,       TAX_LIMIT_INFINTE, 0.133f },
	{ 0,0,0.0f }
};

TAX_ENTRY g_CaliforniaTaxTableSingle[] =
{
	{ 0, 8015, 0.01f },
	{ 8015		 ,  19001   , 0.02f },
	{ 19001    , 	29989   , 0.04f },
	{ 29989    ,    41629	  , 0.06f },
	{ 41629	  ,	    52612	  , 0.08f },
	{ 52612	  ,	    268750 , 0.093f },
	{ 268750	,	322499 ,  0.103f },
	{ 322499	,	537498 , 0.113f },
	{ 537498	,	1000000 , 0.123f },
	{ 1000000,       TAX_LIMIT_INFINTE, 0.133f },
	{ 0,0,0.0f }
};

PTAX_ENTRY g_CaliforniaTaxTable[] = {
	{&g_CaliforniaTaxTableMarried[0]},
	{&g_CaliforniaTaxTableSingle[0]}
};


/*
 * TODO: Create the tax tables for each state.
 */
STATE_TAX_TABLES g_StateTaxTables[] =
{
	{ "AL", NULL},
	{ "AZ",NULL },
	{ "AR",NULL },
	{ "CA", &g_CaliforniaTaxTable[0] },
	{ "CT",NULL },
	{ "DE",NULL },
	{ "GA",NULL },
	{ "HI",NULL },
	{ "ID",NULL },
	{ "IA",NULL },
	{ "KS",NULL },
	{ "KY",NULL },
	{ "LA",NULL },
	{ "ME",NULL },
	{ "MD",NULL },
	{ "MN",NULL },
	{ "MS",NULL },
	{ "MO",NULL },
	{ "MT",NULL },
	{ "NE",NULL },
	{ "NH",NULL },
	{ "NJ",NULL },
	{ "NM",NULL },
	{ "NY",NULL },
	{ "ND",NULL },
	{ "OH",NULL },
	{ "OK",NULL },
	{ "OR",NULL },
	{ "RI",NULL },
	{ "SC",NULL },
	{ "TN",NULL },
	{ "VT",NULL },
	{ "VA",NULL },
	{ "WV",NULL },
	{ "WI",NULL },
	{ NULL, NULL }
};