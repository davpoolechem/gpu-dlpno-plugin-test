/*
 *@BEGIN LICENSE
 *
 * v2RDM-CASSCF, a plugin to:
 *
 * Psi4: an open-source quantum chemistry software package
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Copyright (c) 2014, The Florida State University. All rights reserved.
 * 
 *@END LICENSE
 *
 */

#include "dlpno_gpu.hpp"

#include <psi4/libplugin/plugin.h>
#include <psi4/psi4-dec.h>
#include <psi4/liboptions/liboptions.h>
#include <psi4/libpsio/psio.hpp>
#include <psi4/libciomr/libciomr.h>
#include <psi4/libpsi4util/process.h>

INIT_PLUGIN

namespace psi { 
namespace dlpno {

extern "C" PSI_API
int read_options(std::string name, Options& options)
{
    if (name == "DLPNO"|| options.read_globals()) {
        /*- where do I say hi from? -*/ 
        options.add_str("GPU_PRINT_FROM", "PYTHON");
    } 

    return true;
}

extern "C" PSI_API
SharedWavefunction gpu_dlpno_ccsd(SharedWavefunction ref_wfn, Options& options)
{
    // Note that if this function was integrated into Psi4 we would not be using P::e.wavefunction
    // Instead everything would be explicitly passed
    auto wfn = std::make_shared<DLPNOCCSD_GPU>(ref_wfn, options);
    wfn->compute_energy();

    return wfn;
}

} // namespace dlpno
} // namespace psi

