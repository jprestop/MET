

////////////////////////////////////////////////////////////////////////


#ifndef  __VX_GDATA_UTIL_H__
#define  __VX_GDATA_UTIL_H__


////////////////////////////////////////////////////////////////////////


#include <netcdf.hh>

#include "vx_util/long_array.h"


////////////////////////////////////////////////////////////////////////


static const int vx_gdata_star = -12345;


////////////////////////////////////////////////////////////////////////


extern int get_int_var(NcFile *, const char * var_name, int index);

extern bool args_ok(const LongArray &);


////////////////////////////////////////////////////////////////////////


#endif   /*  __VX_GDATA_UTIL_H__  */


////////////////////////////////////////////////////////////////////////


