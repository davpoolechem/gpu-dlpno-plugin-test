#
#@BEGIN LICENSE
#
# GPU-accelerated density-fitted coupled-cluster, a plugin to:
#
# PSI4: an ab initio quantum chemistry software package
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


import psi4
import psi4.driver.p4util as p4util
from psi4.driver.procrouting import proc_util
from psi4.driver.p4util.exceptions import *

def run_gpu_dlpno_ccsd(name, **kwargs):
    lowername = name.lower()
    kwargs = p4util.kwargs_lower(kwargs)

    psi4.core.set_local_option("DLPNO", "GPU_PRINT_FROM", "PYTHON")

    # Compute a SCF reference, a wavefunction is return which holds the molecule used, orbitals
    # Fock matrices, and more
    #print('Attention! This SCF may be density-fitted.')
    ref_wfn = kwargs.get('ref_wfn', None)
    #if ref_wfn is None:
    #    ref_wfn = psi4.driver.scf_helper(name, **kwargs)
    
    if psi4.core.get_local_option("DLPNO", "GPU_PRINT_FROM") == "PYTHON": 
        print("Hi from David in Python! ๑(◕‿◕)๑ \n");  
    else:
        # Call the Psi4 plugin
        # Please note that setting the reference wavefunction in this way is ONLY for plugins
        gpu_dlpno = psi.core.plugin("gpu_dlpno_ccsd.so", ref_wfn)
