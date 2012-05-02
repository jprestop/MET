// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2012
// ** University Corporation for Atmospheric Research (UCAR)
// ** National Center for Atmospheric Research (NCAR)
// ** Research Applications Lab (RAL)
// ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

////////////////////////////////////////////////////////////////////////

#ifndef  __WAVELET_STAT_CONF_INFO_H__
#define  __WAVELET_STAT_CONF_INFO_H__

////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "vx_config.h"

#include "vx_data2d.h"
#include "vx_grid.h"
#include "vx_util.h"
#include "vx_cal.h"
#include "vx_math.h"
#include "vx_gsl_prob.h"
#include "vx_statistics.h"
#include "vx_stat_out.h"

////////////////////////////////////////////////////////////////////////

// Indices for the output flag types in the configuration file
static const int i_isc = 0;
static const int n_txt = 1;

// Text file type
static const STATLineType txt_file_type[n_txt] = {
   stat_isc
};

////////////////////////////////////////////////////////////////////////

class WaveletStatConfInfo {

   private:

      void init_from_scratch();

      // Counts based on the contents of the config file
      int n_vx;              // Number of fields to be verified
      int max_n_thresh;      // Maximum number of thresholds
      int n_tile;            // Number of tiles to apply
      int n_scale;           // Number of scales based on tile_dim

   public:

      // Wavelet-Stat configuration object
      MetConfig conf;

      // Store data parsed from the Grid-Stat configuration object
      ConcatString            model;              // Model name
      VarInfo **              fcst_info;          // Array of pointers for fcst VarInfo [n_vx]
      VarInfo **              obs_info;           // Array of pointers for obs VarInfo [n_vx]
      ThreshArray *           fcst_ta;            // Array for fcst thresholds [n_vx]
      ThreshArray *           obs_ta;             // Array for obs thresholds [n_vx]
      FieldType               mask_missing_flag;  // Mask missing data between fcst and obs
      GridDecompType          grid_decomp_flag;   // Method for grid decomposition
      int                     tile_dim;           // Tile dimension      
      NumArray                tile_xll;           // Array of lower-left x coordinates
      NumArray                tile_yll;           // Array of lower-left y coordinates
      Box                     pad_bb;             // Pad bouding box
      WaveletType             wvlt_type;          // Wavelet type
      int                     wvlt_member;        // Wavelet member k-value
      gsl_wavelet           * wvlt_ptr;           // GSL wavelet pointer
      gsl_wavelet_workspace * wvlt_work_ptr;      // GSL wavelet workspace
      STATOutputType          output_flag[n_txt]; // Flag for each output line type
      bool                    nc_pairs_flag;      // Flag for the output NetCDF pairs file
      bool                    ps_plot_flag;       // Flag for the output PostScript image file
      ConcatString            met_data_dir;       // MET data directory
      PlotInfo                fcst_raw_pi;        // Raw forecast plotting info
      PlotInfo                obs_raw_pi;         // Raw observation plotting info
      PlotInfo                wvlt_pi;            // Wavelet plotting
      ConcatString            output_prefix;      // String to customize output file name
      ConcatString            version;            // Config file version

      WaveletStatConfInfo();
     ~WaveletStatConfInfo();

      void clear();

      void read_config   (const char *, const char *);
      void process_config(GrdFileType, GrdFileType);
      void process_tiles (const Grid &);
      void center_tiles  (int, int);
      void pad_tiles     (int, int);

      // Dump out the counts
      int get_n_vx        () const;
      int get_max_n_thresh() const;
      int get_n_tile      () const;
      int get_tile_dim    () const;
      int get_n_scale     () const;

      // Compute the maximum number of output lines possible based
      // on the contents of the configuration file
      int n_isc_row ();
      int n_stat_row();
};

////////////////////////////////////////////////////////////////////////

inline int WaveletStatConfInfo::get_n_vx()         const { return(n_vx);          }
inline int WaveletStatConfInfo::get_max_n_thresh() const { return(max_n_thresh);  }
inline int WaveletStatConfInfo::get_n_tile()       const { return(n_tile);        }
inline int WaveletStatConfInfo::get_tile_dim()     const { return(tile_dim);      }
inline int WaveletStatConfInfo::get_n_scale()      const { return(n_scale);      }

////////////////////////////////////////////////////////////////////////

extern int get_pow2(double);

////////////////////////////////////////////////////////////////////////

#endif   /*  __WAVELET_STAT_CONF_INFO_H__  */

////////////////////////////////////////////////////////////////////////
