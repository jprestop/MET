

// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2016
// ** University Corporation for Atmospheric Research (UCAR)
// ** National Center for Atmospheric Research (NCAR)
// ** Research Applications Lab (RAL)
// ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*




////////////////////////////////////////////////////////////////////////


#ifndef  __LAMBERT_GRID_H__
#define  __LAMBERT_GRID_H__


////////////////////////////////////////////////////////////////////////


#include "grid_base.h"


////////////////////////////////////////////////////////////////////////


class LambertGrid : public GridRep {

      friend class Grid;

   private:

      LambertGrid();
     ~LambertGrid();
      LambertGrid(const LambertData &);

      void clear();

         //
         //
         //

      ConcatString Name;

      double Lat_LL;
      double Lon_LL;

      double Lon_orient;

      double Alpha;

      double Cone;

      double Bx;
      double By;

      int Nx;
      int Ny;

      double  f(double) const;
      double df(double) const;

      LambertData Data;

         //
         //  grid interface
         //

      void xy_to_uv(double x, double y, double & u, double & v) const;
      void uv_to_xy(double u, double v, double & x, double & y) const;

      double uv_closedpolyline_area(const double * u, const double * v, int n) const;
      double xy_closedpolyline_area(const double * x, const double * y, int n) const;

      void latlon_to_xy(double lat, double lon, double & x, double & y) const;

      void xy_to_latlon(double x, double y, double & lat, double & lon) const;

      double calc_area(int x, int y) const;

      int nx() const;
      int ny() const;

      ConcatString name() const;

      void dump(ostream &, int = 0) const;

      ConcatString serialize() const;

      GridInfo info () const;

      double rot_grid_to_earth(int x, int y) const;

      bool is_global() const;

      void shift_right(int);

      GridRep * copy() const;

};


////////////////////////////////////////////////////////////////////////


#endif   //  __LAMBERT_GRID_H__


////////////////////////////////////////////////////////////////////////



