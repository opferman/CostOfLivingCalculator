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





/*
 * Individual State Tax Tables - TODO: Need to create one for each state.
 */

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
* State Tax Look up
*/

STATE_TAX_LOOKUP_TABLE g_StateTaxLookupTable[] = {
{ "Alabama"       , "AK" , StateTaxNone,  0.0f, NULL },
{ "Alaska"		  ,	"AL" , StateTaxTable, 0.0f, NULL },
{ "Arizona"		  ,	"AZ" , StateTaxTable, 0.0f, NULL },
{ "Arkansas"	  ,	"AR" , StateTaxTable, 0.0f, NULL },
{ "California"	  ,	"CA" , StateTaxTable, 0.0f, &g_CaliforniaTaxTable[0] },
{ "Colorado"	  ,	"CO" , StateTaxFlat,  0.0463f, NULL },
{ "Connecticut"	  ,	"CT" , StateTaxTable, 0.0f, NULL },
{ "Delaware"	  ,	"DE" , StateTaxTable, 0.0f, NULL },
{ "Florida"		  ,	"FL" , StateTaxNone,  0.0f, NULL },
{ "Georgia"		  ,	"GA" , StateTaxTable, 0.0f, NULL },
{ "Hawaii"		  ,	"HI" , StateTaxTable, 0.0f, NULL },
{ "Idaho"		  ,	"ID" , StateTaxTable, 0.0f, NULL },
{ "Illinois"	  ,	"IL" , StateTaxFlat,  0.0495f, NULL },
{ "Indiana"		  ,	"IN" , StateTaxFlat,  0.0323f, NULL },
{ "Iowa"		  ,	"IA" , StateTaxTable, 0.0f, NULL },
{ "Kansas"		  ,	"KS" , StateTaxTable, 0.0f, NULL },
{ "Kentucky"	  ,	"KY" , StateTaxTable, 0.0f, NULL },
{ "Louisiana"	  ,	"LA" , StateTaxTable, 0.0f, NULL },
{ "Maine"		  ,	"ME" , StateTaxTable, 0.0f, NULL },
{ "Maryland"      ,	"MD" , StateTaxTable, 0.0f, NULL },
{ "Massachusetts" ,	"MA" , StateTaxTable, 0.0f, NULL },
{ "Michigan"	  ,	"MI" , StateTaxFlat,  0.051f, NULL },
{ "Minnesota"	  ,	"MN" , StateTaxTable, 0.0f, NULL },
{ "Mississippi"	  ,	"MS" , StateTaxTable, 0.0f, NULL },
{ "Missouri"	  ,	"MO" , StateTaxTable, 0.0f, NULL },
{ "Montana"		  ,	"MT" , StateTaxTable, 0.0f, NULL },
{ "Nebraska"	  ,	"NE" , StateTaxTable, 0.0f, NULL },
{ "Nevada"		  ,	"NV" , StateTaxNone,  0.0f, NULL },
{ "New Hampshire" ,	"NH" , StateTaxTable, 0.0f, NULL },
{ "New Jersey"	  ,	"NJ" , StateTaxTable, 0.0f, NULL },
{ "New Mexico"	  ,	"NM" , StateTaxTable, 0.0f, NULL },
{ "New York"	  ,	"NY" , StateTaxTable, 0.0f, NULL },
{ "North Carolina",	"NC" , StateTaxFlat,  0.05499f, NULL },
{ "North Dakota"  ,	"ND" , StateTaxTable, 0.0f, NULL },
{ "Ohio"		  ,	"OH" , StateTaxTable, 0.0f, NULL },
{ "Oklahoma"	  ,	"OK" , StateTaxTable, 0.0f, NULL },
{ "Oregon"		  ,	"OR" , StateTaxTable, 0.0f, NULL },
{ "Pennsylvania"  ,	"PA" , StateTaxFlat,  0.0307f, NULL },
{ "Rhode Island"   ,"RI" , StateTaxTable, 0.0f, NULL },
{ "South Carolina" ,"SC" , StateTaxTable, 0.0f, NULL },
{ "South Dakota"   ,"SD" , StateTaxNone,  0.0f, NULL },
{ "Tennessee"	   ,"TN" , StateTaxTable, 0.0f, NULL },
{ "Texas"		   ,"TX" , StateTaxNone,  0.0f, NULL },
{ "Utah"		   ,"UT" , StateTaxFlat,  0.0f, NULL },
{ "Vermont"		   ,"VT" , StateTaxTable, 0.0f, NULL },
{ "Virginia"	   ,"VA" , StateTaxTable, 0.0f, NULL },
{ "Washington"	   ,"WA" , StateTaxNone,  0.0f, NULL },
{ "West Virginia"  ,"WV" , StateTaxTable, 0.0f, NULL },
{ "Wisconsin"	   ,"WI" , StateTaxTable, 0.0f, NULL },
{ "Wyoming"		   ,"WY" , StateTaxNone,  0.0f, NULL },
{ NULL, NULL, StateTaxInvalid,  0.0f, NULL }

};				   





















































