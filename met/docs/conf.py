# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import sys
sys.path.insert(0, os.path.abspath('.'))
print(sys.path)

# -- Project information -----------------------------------------------------

project = 'MET'
copyright = '2020, NCAR'
author = 'NCAR'

# the stable version, displayed on front page of PDF
version = '9.1'

# The full version, including alpha/beta/rc tags
release = f'{version}'

# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = ['sphinx.ext.autodoc','sphinx.ext.intersphinx']

# To enable PDF generation, set METPLUS_DOC_PDF environment variable
#  sphinx 2.4.2+ and rst2pdf packages are required
if os.environ.get('METPLUS_DOC_PDF'):
    extensions.append('rst2pdf.pdfbuilder')

# used for generating PDF
pdf_documents = [('index',
                  f'MET_Users_Guide_{version}',
                  f'MET User\'s Guide',
                  ('Tressa Fowler\\'
                   'John Halley Gotway\\'
                   'Randy Bullock\\'
                   'Kathryn Newman\\'
                   'Julie Prestopnik\\'
                   'Lisa Goodrich\\'
                   'Tara Jensen\\'
                   'Barbara Brown\\'
                   'Howard Soh\\'
                   'Tatiana Burek\\'
                   'Minna Win-Gildenmeister\\'
                   'George McCabe\\'
                   'David Fillmore\\'
                   'Paul Prestopnik\\'
                   'Eric Gilleland\\'
                   'Nancy Rehak\\'
                   'Paul Oldenburg\\'
                   'Anne Holmes\\'
                   'Lacey Holland\\'
                   'David Ahijevych\\'
                   'Bonny Strong\\'
                   )),]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store', 'Flowchart' ]

# Suppress certain warning messages
suppress_warnings = ['ref.citation']

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'
html_css_files = ['theme_override.css']


# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

# The name of an image file (relative to this directory) to place at the top
# of the sidebar.
html_logo = os.path.join('_static','met_logo_2019_09.png')

# -- Intersphinx control ---------------------------------------------------------------
intersphinx_mapping = {'numpy':("https://docs.scipy.org/doc/numpy/", None)}

numfig = True

numfig_format = {
    'figure': 'Figure %s',
}
