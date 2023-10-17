#include "test.hpp"

#include "psi4/libpsi4util/process.h"
#include "psi4/libmints/wavefunction.h"

#include <pybind11.h>
#include <numpy.h>
#include <stl.h>

using namespace psi;

namespace py = pybind11;
using namespace pybind11::literals;

namespace psi {
namespace dlpno {

void export_gpu_dlpno_ccsd(py::module& m) {
    m.def("say_hi", &say_hi, "Says hi from C++!");
}

PYBIND11_MODULE(gpu_dlpno_ccsd, m) 
{
    m.doc() = "Python API of gpu_dlpno_ccsd: a GPU-accelerated DLPNO-CCSD plugin to Psi4";
    export_gpu_dlpno_ccsd(m);
}

} // namespace dlpno
} // namespace psi



