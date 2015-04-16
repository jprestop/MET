

////////////////////////////////////////////////////////////////////////


// ** Copyright UCAR (c) 1992 - 2015
// ** University Corporation for Atmospheric Research (UCAR)
// ** National Center for Atmospheric Research (NCAR)
// ** Research Applications Lab (RAL)
// ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

////////////////////////////////////////////////////////////////////////


#ifndef  __MODE_EXECUTIVE_H__
#define  __MODE_EXECUTIVE_H__


////////////////////////////////////////////////////////////////////////


#include <iostream>

#include "netcdf.hh"

#include "vx_data2d.h"
#include "vx_data2d_factory.h"
#include "data2d_factory_utils.h"
#include "vx_shapedata.h"
#include "vx_grid.h"
#include "vx_util.h"
#include "vx_nc_util.h"
#include "vx_cal.h"
#include "vx_grid.h"
#include "vx_math.h"
#include "vx_statistics.h"

#include "vx_color.h"
#include "vx_ps.h"
#include "vx_pxm.h"
#include "vx_render.h"
#include "vx_plot_util.h"

#include "mode_ps_file.h"

////////////////////////////////////////////////////////////////////////


static const int n_cts = 3;


////////////////////////////////////////////////////////////////////////


enum ObjPolyType {
   FcstSimpBdyPoly  = 0,
   ObsSimpBdyPoly   = 1,
   FcstSimpHullPoly = 2,
   ObsSimpHullPoly  = 3,
   FcstClusHullPoly = 4,
   ObsClusHullPoly  = 5
};


////////////////////////////////////////////////////////////////////////


class ModeExecutive {

   private:

      void init_from_scratch();

   public:

      ModeExecutive();
     ~ModeExecutive();

      void clear();

      void init();

         //
         // Input configuration files
         //

      ConcatString default_config_file;
      ConcatString match_config_file;
      ConcatString merge_config_file;

         //
         // Input files
         //

      ConcatString fcst_file;
      ConcatString obs_file;
      Met2dDataFile * fcst_mtddf;
      Met2dDataFile * obs_mtddf;

      TTContingencyTable cts[n_cts];

      ModeFuzzyEngine engine;
      Grid grid;
      Box xy_bb;
      ConcatString out_dir;
      double data_min, data_max;

      ShapeData Fcst_sd, Obs_sd;

      void setup_fcst_obs_data();
      void do_conv_thresh();
      void do_match_merge();

      void process_masks(ShapeData &, ShapeData &);
      void process_output();

      void plot_engine();

      void compute_ct_stats();

      void build_outfile_name(const char *, ConcatString &);
      void write_obj_stats();
      void write_obj_netcdf(const ModeNcOutInfo &);
      void write_poly_netcdf(NcFile *);
      void write_poly_netcdf(NcFile *, const ObjPolyType);
      void write_ct_stats();

};


////////////////////////////////////////////////////////////////////////


#endif   /*  __MODE_EXECUTIVE_H__  */


/////////////////////////////////////////////////////////////////////////

