

// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2013
// ** University Corporation for Atmospheric Research (UCAR)
// ** National Center for Atmospheric Research (NCAR)
// ** Research Applications Lab (RAL)
// ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*




////////////////////////////////////////////////////////////////////////


#ifndef  __NETCDF_GRID_OUTPUT_H__
#define  __NETCDF_GRID_OUTPUT_H__


////////////////////////////////////////////////////////////////////////


#include <netcdf.hh>

#include "vx_grid.h"


////////////////////////////////////////////////////////////////////////


static const bool west_longitude_positive = false;


////////////////////////////////////////////////////////////////////////


extern void grid_output(const GridInfo &, NcFile * ncfile);


////////////////////////////////////////////////////////////////////////


#endif   /*  __NETCDF_GRID_OUTPUT_H__  */


////////////////////////////////////////////////////////////////////////



