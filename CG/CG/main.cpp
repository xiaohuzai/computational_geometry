#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include "base_geo_type.h"
#include "geometry_util.h"
#include "convex_hull.h"

using namespace pybind11::literals;

PYBIND11_MAKE_OPAQUE(std::vector<Point2D>);
PYBIND11_MODULE(CG, m) {
	m.doc() = "CG pybind11 plugin"; // optional module docstring

	// base_geo_type
	pybind11::class_<Point2D>(m, "Point2D")
		.def(pybind11::init<double, double>())
		.def("x", &Point2D::x)
		.def("y", &Point2D::y)
		.def("__repr__", [](const Point2D& p) {return "Point2D(" + std::to_string(p.x()) + ", " + std::to_string(p.y()) + ")"; });
	pybind11::bind_vector<std::vector<Point2D>>(m, "Point2DVector");

	// geometry_util
	m.def("to_left", &to_left, "p"_a, "q"_a, "s"_a);
	m.def("get_intersect", &get_intersect, "p0"_a, "p1"_a, "q0"_a, "q1"_a, "res"_a);
	m.def("counter_clockwise", &counter_clockwise, "p"_a, "q"_a, "r"_a);
	m.def("in_triangle", &in_triangle, "p"_a, "q"_a, "r"_a, "s"_a);
	m.def("in_convex_polygon", &in_convex_polygon, "extrem_points"_a, "pt"_a);
	m.def("calc_angle", &calc_angle, "v"_a);
	m.def("calc_angle_diff", &calc_angle_diff, "v1"_a, "v2"_a);
	m.def("sort_by_angle", &sort_by_angle, "p"_a, "points"_a);

	// convex_hull
	pybind11::class_<ConvexHull>(m, "convex_hull");
	pybind11::class_<ExtremEdgeAlgo, ConvexHull>(m, "ExtremEdgeAlgo")
		.def(pybind11::init<>())
		.def("gen_extrem_points", &ExtremEdgeAlgo::gen_extrem_points, "points"_a);
	pybind11::class_<IncrementalAlgo, ConvexHull>(m, "IncrementalAlgo")
		.def(pybind11::init<>())
		.def("gen_extrem_points", &IncrementalAlgo::gen_extrem_points, "points"_a);
	pybind11::class_<JarvisMarchAlgo, ConvexHull>(m, "JarvisMarchAlgo")
		.def(pybind11::init<>())
		.def("gen_extrem_points", &JarvisMarchAlgo::gen_extrem_points, "points"_a);
	pybind11::class_<GrahamScaneAlgo, ConvexHull>(m, "GrahamScaneAlgo")
		.def(pybind11::init<>())
		.def("gen_extrem_points", &GrahamScaneAlgo::gen_extrem_points, "points"_a);
}