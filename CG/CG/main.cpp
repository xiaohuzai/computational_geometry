#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include "base_geo_type.h"
#include "geometry_util.h"

PYBIND11_MAKE_OPAQUE(std::vector<Point2D>);
PYBIND11_MODULE(CG, m) {
	m.doc() = "CG pybind11 plugin"; // optional module docstring

	pybind11::class_<Point2D>(m, "Point2D")
		.def(pybind11::init<double, double>())
		.def("x", &Point2D::x)
		.def("y", &Point2D::y)
		.def("__repr__", [](const Point2D& p) {return "Point2D(" + std::to_string(p.x()) + ", " + std::to_string(p.y()) + ")"; });
	pybind11::bind_vector<std::vector<Point2D>>(m, "Point2DVector");

	m.def("to_left", &to_left);
	m.def("get_intersect", &get_intersect);
}