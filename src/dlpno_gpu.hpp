#include <psi4/libdlpno/dlpno.h>

#ifndef DLPNO_CCSD
#define DLPNO_CCSD

namespace psi {
namespace dlpno {

class DLPNOCCSD;

class DLPNOCCSD_GPU : public DLPNOCCSD { 
public:
  DLPNOCCSD_GPU(SharedWavefunction ref_wfn, Options& options);
  ~DLPNOCCSD_GPU() override;

  double compute_energy() override;

private:
  void common_init();
};

} // namespace dlpno
} // namespace psi4


#endif
