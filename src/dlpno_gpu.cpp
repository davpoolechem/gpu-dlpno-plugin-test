#include "dlpno_gpu.hpp"

namespace psi {
namespace dlpno { 

DLPNOCCSD_GPU::DLPNOCCSD_GPU(SharedWavefunction ref_wfn, Options& options) : DLPNOCCSD(ref_wfn, options) { common_init() }
DLPNOCCSD_GPU::~DLPNOCCSD_GPU() {}

void DLPNOCCSD_GPU::common_init() {
  printf("Hi from David in C++! ๑(◕‿◕)๑ \n");  
}

double DLPNOCCSD_GPU::compute_energy() { return 0.0; }

} // namespace dlpno 
} // namespace psi4 


