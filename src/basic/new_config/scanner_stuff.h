

////////////////////////////////////////////////////////////////////////

   //
   //
   //

////////////////////////////////////////////////////////////////////////


#ifndef  __CONFIG_SCANNER_STUFF_H__
#define  __CONFIG_SCANNER_STUFF_H__


////////////////////////////////////////////////////////////////////////


static const int max_id_length = 256;


////////////////////////////////////////////////////////////////////////


enum Comparison {

   comparison_lt, 
   comparison_gt, 

   comparison_le, 
   comparison_ge, 

   no_comparison

};


////////////////////////////////////////////////////////////////////////


struct Number {

   bool is_int;

   int i;

   double d;

};


////////////////////////////////////////////////////////////////////////


#endif   /*  __CONFIG_SCANNER_STUFF_H__  */


////////////////////////////////////////////////////////////////////////


