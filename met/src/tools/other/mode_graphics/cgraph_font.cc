

////////////////////////////////////////////////////////////////////////


using namespace std;

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <cmath>

#include "cgraph_font.h"


////////////////////////////////////////////////////////////////////////


static const int alloc_inc = 30;

static const int total_predef_fonts = 34;


////////////////////////////////////////////////////////////////////////


static bool same_font(const CgFont &, const CgFont &);


////////////////////////////////////////////////////////////////////////


   //
   //  Code for class CgFont
   //


////////////////////////////////////////////////////////////////////////


CgFont::CgFont()

{

init_from_scratch();

}


////////////////////////////////////////////////////////////////////////


CgFont::~CgFont()

{

clear();

}


////////////////////////////////////////////////////////////////////////


CgFont::CgFont(const CgFont & p)

{

init_from_scratch();

assign(p);

}


////////////////////////////////////////////////////////////////////////


CgFont & CgFont::operator=(const CgFont & p)

{

if ( this == &p )  return ( * this );

assign(p);

return ( * this );

}


////////////////////////////////////////////////////////////////////////


void CgFont::init_from_scratch()

{

afm = (Afm *) 0;

face = 0;

// const char * c = getenv(cgraph_font_dir_env);
// 
// if ( ! c )  {
// 
//    cerr << "\n\n  CgFont::init_from_scratch() -> unable to get environment variable \""
//         << cgraph_font_dir_env << "\"\n\n";
// 
//    exit ( 1 );
// 
// }

gs_font_dir = CGRAPH_FONT_DIR ;

clear();

return;

}


////////////////////////////////////////////////////////////////////////


void CgFont::clear()

{

/*
if ( face )  {

   int error = FT_Done_Face(face);

   if ( error )  {

      cerr << "\n\n  CgFont::clear() -> trouble closing typeface \"" << short_pfb_name << "\"\n\n";

      exit ( 1 );

   }

   face = 0;
}
*/


full_pfb_name.clear();
short_pfb_name.clear();

full_afm_name.clear();
short_afm_name.clear();

ps_name.clear();

orig_ps_size = scaled_ps_size = 0.0;

if ( afm )  { delete afm;  afm = (Afm *) 0; }

ps_font_number = -1;


return;

}


////////////////////////////////////////////////////////////////////////


void CgFont::assign(const CgFont & p)

{

clear();

full_pfb_name  = p.full_pfb_name;
short_pfb_name = p.short_pfb_name;

full_afm_name  = p.full_afm_name;
short_afm_name = p.short_afm_name;

face = p.face;

ps_name = p.ps_name;

if ( p.afm )  {

   afm = new Afm;

   *afm = *(p.afm);

}

ps_font_number = p.ps_font_number;

orig_ps_size = p.orig_ps_size;
scaled_ps_size = p.scaled_ps_size;

return;

}


////////////////////////////////////////////////////////////////////////


void CgFont::dump(ostream & out, int depth) const

{

Indent prefix(depth);


out << prefix << "full_pfb_name  = ";

if ( full_pfb_name.length() == 0 )  out << "(nul)\n";
else                                out << '\"' << full_pfb_name << "\"\n";


out << prefix << "short_pfb_name = ";

if ( short_pfb_name.length() == 0 )  out << "(nul)\n";
else                                 out << '\"' << short_pfb_name << "\"\n";


out << prefix << "full_afm_name  = ";

if ( full_afm_name.length() == 0 )  out << "(nul)\n";
else                                out << '\"' << full_afm_name << "\"\n";


out << prefix << "short_afm_name = ";

if ( short_afm_name.length() == 0 )  out << "(nul)\n";
else                                 out << '\"' << short_afm_name << "\"\n";


out << prefix << "ps_name        = ";

if ( ps_name.length() == 0 )  out << "(nul)\n";
else                          out << '\"' << ps_name << "\"\n";


out << prefix << "ps_font_number = " << ps_font_number << "\n";

   //
   //  done
   //

out.flush();

return;

}


////////////////////////////////////////////////////////////////////////


void CgFont::set_by_number(int n)

{

clear();

if ( (n < 0) || (n >= total_predef_fonts) )  {

   cerr << "\n\n  CgFont::set_by_number(int) -> range check error\n\n";

   exit ( 1 );

}

char junk[256];

sprintf(junk, "%02d.afm", n);

short_afm_name = junk;

full_afm_name << gs_font_dir << '/' << gs_font_dir << '/' << short_afm_name;

if ( !file_exists(full_afm_name) )  {

   cerr << "\n\n  CgFont::set_by_number(int) -> can't find afm file \"" << full_afm_name << "\"\n\n";

   exit ( 1 );

}

afm = new Afm;

if ( !(afm->read(full_afm_name)) )  {

   cerr << "\n\n  CgFont::set_by_number(int) -> trouble reading afm file \"" << full_afm_name << "\"\n\n";

   exit ( 1 );

}

ps_name = afm->FontName;

ps_font_number = n;



   //
   //  done
   //

return;

}


////////////////////////////////////////////////////////////////////////


   //
   //  Code for class CgFontCollection
   //


////////////////////////////////////////////////////////////////////////


CgFontCollection::CgFontCollection()

{

init_from_scratch();

}


////////////////////////////////////////////////////////////////////////


CgFontCollection::~CgFontCollection()

{

clear();

}


////////////////////////////////////////////////////////////////////////


CgFontCollection::CgFontCollection(const CgFontCollection & c)

{

init_from_scratch();

assign(c);

}


////////////////////////////////////////////////////////////////////////


CgFontCollection & CgFontCollection::operator=(const CgFontCollection & c)

{

if ( this == &c )  return ( * this );

assign(c);

return ( * this );

}


////////////////////////////////////////////////////////////////////////


void CgFontCollection::init_from_scratch()

{

e = (CgFont **) 0;

clear();

return;

}


////////////////////////////////////////////////////////////////////////


void CgFontCollection::clear()

{

if ( e )  {

   int j, error;

   for (j=0; j<Nalloc; ++j)  {

      if ( ! (e[j]) )  continue;

      error = FT_Done_Face(e[j]->face);

      if ( error )  {

         cerr << "\n\n  CgFontCollection::clear() -> trouble closing typeface \"" << e[j]->short_pfb_name << "\"\n\n";

         exit ( 1 );

      }

      e[j]->face = 0;

      if ( e[j] )  { delete e[j];  e[j] = (CgFont *) 0; }

   }

   delete [] e;  e = (CgFont **) 0;

}

Nelements = Nalloc = 0;

return;

}


////////////////////////////////////////////////////////////////////////


void CgFontCollection::dump(ostream & out, int depth) const

{

int j;
Indent prefix(depth);


out << prefix << "Nelements = " << Nelements << "\n";
out << prefix << "Nalloc    = " << Nalloc    << "\n";

for (j=0; j<Nelements; ++j)  {

   out << prefix << "\n";

   out << prefix << "Element # " << j << " ...\n";

   e[j]->dump(out, depth + 1);

}


   //
   //  done
   //

out.flush();

return;

}


////////////////////////////////////////////////////////////////////////


void CgFontCollection::extend(int n)

{

if ( n <= Nalloc )  return;

int j, k;
CgFont ** u = (CgFont **) 0;


k = n/alloc_inc;

if ( n%alloc_inc )  ++k;

n = k*alloc_inc;

u = new CgFont * [n];

if ( !u )  {

   cerr << "\n\n  CgFontCollection::extend(int) -> memory allocation error\n\n";

   exit ( 1 );

}

for (j=0; j<n; ++j)  u[j] = (CgFont *) 0;

if ( e )  {

   for (j=0; j<Nelements; ++j)  u[j] = e[j];

   delete [] e;  e = (CgFont **) 0;

}

e = u;  u = (CgFont **) 0;

Nalloc = n;

   //
   //  done
   //

return;

}


////////////////////////////////////////////////////////////////////////


void CgFontCollection::assign(const CgFontCollection & c)

{

clear();

if ( !(c.e) )  return;

extend(c.Nelements);

int j;

for (j=0; j<(c.Nelements); ++j)  {

   if ( c.e[j] )  {

      e[j] = new CgFont;

      *(e[j]) = *(c.e[j]);

   }

}

Nelements = c.Nelements;

   //
   //  done
   //

return;

}


////////////////////////////////////////////////////////////////////////


void CgFontCollection::add(const CgFont & f)

{

// if ( have_it(f) )  return;

extend(Nelements + 1);

e[Nelements] = new CgFont;

*(e[Nelements]) = f;

++Nelements;


return;

}


////////////////////////////////////////////////////////////////////////


void CgFontCollection::add_no_repeat(const CgFont & f)

{

if ( have_it(f) )  return;

extend(Nelements + 1);

e[Nelements] = new CgFont;

*(e[Nelements]) = f;

++Nelements;


return;

}


////////////////////////////////////////////////////////////////////////


bool CgFontCollection::have_it(const CgFont & f) const

{

int j;

for (j=0; j<Nelements; ++j)  {

   if ( same_font( *(e[j]), f ) )  return ( true );

}

return ( false );

}


////////////////////////////////////////////////////////////////////////


CgFont * CgFontCollection::lookup_by_ps_font_number(int n) const

{

int j;

for (j=0; j<Nelements; ++j)  {

   if ( e[j]->ps_font_number == n )  return ( e[j] );

}


return ( (CgFont *) 0 );

}


////////////////////////////////////////////////////////////////////////


CgFont * CgFontCollection::lookup_by_ps_name(const char * name) const

{

int j;

for (j=0; j<Nelements; ++j)  {

   if ( strcmp(e[j]->ps_name, name) == 0 )  return ( e[j] );

}


return ( (CgFont *) 0 );

}


////////////////////////////////////////////////////////////////////////


CgFont * CgFontCollection::operator[](int k) const

{

if ( (k < 0) || (k >= Nelements) )  {

   cerr << "\n\n  CgFont * CgFontCollection::operator[](int) const -> range check error\n\n";

   exit ( 1 );

}

return ( e[k] );

}


////////////////////////////////////////////////////////////////////////


   //
   //  Code for misc functions
   //


////////////////////////////////////////////////////////////////////////


bool same_font(const CgFont & a, const CgFont & b)

{

if ( strcmp(a.ps_name, b.ps_name) == 0 )  return ( true );

return ( false );

}


////////////////////////////////////////////////////////////////////////





