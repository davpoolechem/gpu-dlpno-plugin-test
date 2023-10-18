#
#@BEGIN LICENSE
#
# v2RDM-CASSCF by A. Eugene DePrince III, a plugin to:
#
# Psi4: an open-source quantum chemistry software package
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#
#@END LICENSE
#

"""Plugin docstring.

"""
__version__ = '0.1'
__author__  = 'David Poole'

#=============================#
#== Define location of Psi4 ==# 
#=============================#
import os 
import sys
#psi4_sys_path = os.environ["PSI_DIR"] # hardcoded, to fix 
#sys.path.append(psi4_sys_path)

#=================================================#
#== Load Python-side functions from pymodule.py ==# 
#=================================================#
from .pymodule import *
#from .extras import test

#=========================================#
#== Load C++-side functions from pybind ==# 
#==  source files are in {plugdir}/src  ==#
#=========================================#
plugdir = os.path.split(os.path.abspath(__file__))[0]
sys.path.append(os.path.join(plugdir, "src"))
from .gpu_dlpno_ccsd import *

#==========================================#
#==           "plug in" to Psi4          ==#
#== this uses Psi4's libplugin interface ==#
#==========================================#
plugdir = os.path.split(os.path.abspath(__file__))[0]
sofile = plugdir + '/' + os.path.split(plugdir)[1] + '.so'
psi4.core.plugin_load(sofile)
