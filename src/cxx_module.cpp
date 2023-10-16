#include "test.hpp"

#include "psi4/libpsi4util/process.h"
#include "psi4/libmints/wavefunction.h"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

using namespace psi

namespace py = pybind11;
using namespace pybind11::literals;

namespace psi {
namespace dlpno {

void export_gpu_dlpnoccsd(py::module& m) {
    m.def("say_hi", &say_hi, "Says hi from C++!");
}

PYBIND11_MODULE(gpu_dlpnoccsd, m) 
{
    m.doc() = "Python API of gpu_dlpnoccsd: a GPU-accelerated DLPNO-CCSD plugin to Psi4";
    export_gpu_dlpnoccsd(m);
}

} // namespace dlpno
} // namespace psi



