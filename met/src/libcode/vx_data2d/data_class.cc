

   // *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
   // ** Copyright UCAR (c) 1992 - 2012
   // ** University Corporation for Atmospheric Research (UCAR)
   // ** National Center for Atmospheric Research (NCAR)
   // ** Research Applications Lab (RAL)
   // ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
   // *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*




////////////////////////////////////////////////////////////////////////


using namespace std;

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cmath>

#include "vx_log.h"
#include "indent.h"
#include "data_class.h"

////////////////////////////////////////////////////////////////////////


   //
   //  Code for class Met2dData
   //


////////////////////////////////////////////////////////////////////////


Met2dData::Met2dData()

{

mtdd_init_from_scratch();

}


////////////////////////////////////////////////////////////////////////


Met2dData::~Met2dData()

{


}


////////////////////////////////////////////////////////////////////////


void Met2dData::mtdd_init_from_scratch()

{


return;

}


////////////////////////////////////////////////////////////////////////


   //
   //  Code for class Met2dDataFile
   //


////////////////////////////////////////////////////////////////////////


Met2dDataFile::Met2dDataFile()

{

mtddf_init_from_scratch();

}


////////////////////////////////////////////////////////////////////////


Met2dDataFile::~Met2dDataFile()

{

mtddf_clear();

}


////////////////////////////////////////////////////////////////////////


void Met2dDataFile::mtddf_init_from_scratch()

{

_Grid = (Grid *) 0;

return;

}


////////////////////////////////////////////////////////////////////////


void Met2dDataFile::mtddf_clear()

{

// mttd_clear();

if ( _Grid )  { delete _Grid;  _Grid = (Grid *) 0; }

Filename.clear();

return;

}


////////////////////////////////////////////////////////////////////////


void Met2dDataFile::dump(ostream & out, int depth) const

{

Indent prefix(depth);

out << prefix << "File = ";

if ( Filename.empty() )  out << "(nul)\n";
else                     out << '\"' << Filename << "\"\n";

out << prefix << "Grid = ";

if ( _Grid )  {

   out << '\n';

   _Grid->dump(out, depth + 1);

} else out << "(nul)\n";
   
   //
   //  done
   //

out.flush();

return;

}


////////////////////////////////////////////////////////////////////////


const Grid & Met2dDataFile::grid() const

{

if ( ! _Grid )  {

   mlog << Error << "\nMet2dDataFile::grid() -> no grid defined!\n\n";

   exit ( 1 );

}

return ( *_Grid );

}


////////////////////////////////////////////////////////////////////////





