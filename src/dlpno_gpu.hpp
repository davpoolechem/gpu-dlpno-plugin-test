#include <psi4/libdlpno/dlpno.h>

namespace psi {
namespace dlpno {

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
