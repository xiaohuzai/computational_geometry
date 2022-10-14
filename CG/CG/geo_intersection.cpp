#include "geo_intersection.h"
#include "geometry_util.h"
#include <algorithm>
#include <queue>
#include <list>
#include <iostream>

std::vector<Point2D> BentleyOttmanAlgo::get_intersection(const std::vector<Segment2D>& segs) {
	std::priority_queue<Event_, std::vector<Event_>, std::greater<Event_>> events_;
	for (int i = 0, size = static_cast<int>(segs.size()); i < size; ++i) {
		events_.emplace(segs[i].start(), 0, std::pair<int, int>{ i, -1 });
		events_.emplace(segs[i].end(), 1, std::pair<int, int>{ i, -1 });
	}
	auto sweep_line = 0.0;
	auto sweep_line_status = std::list<LineSegment_>{};
	auto marked = std::vector<std::vector<char>>(segs.size(), std::vector<char>(segs.size(), 0));
	for (size_t i = 0; i < segs.size(); ++i) {
		for (size_t j = 0; j < segs.size(); ++j) {
			marked[i][j] = 1;
		}
	}
	auto res = std::vector<Point2D>{};
	while (!events_.empty()) {
		auto front_event = events_.top();
		events_.pop();
		sweep_line = front_event.p_.x();
		sweep_line_status.sort([&](const auto& l, const auto& r) {
			return l.get_y_by_x(sweep_line) > r.get_y_by_x(sweep_line);
			});
		if (front_event.type_ == 0) {
			auto cur_line_segment = LineSegment_{ front_event.index_.first , segs[front_event.index_.first] };
			auto next = std::find_if(sweep_line_status.begin(), sweep_line_status.end(), [&](const auto& s) {
				return s.get_y_by_x(sweep_line) < front_event.p_.y();
				});
			if (next != sweep_line_status.end() && marked[next->index_][front_event.index_.first] == 0) {
				marked[next->index_][front_event.index_.first] = 1;
				marked[front_event.index_.first][next->index_] = 1;
				auto intersect_pt = Point2D{};
				if (get_intersect(segs[front_event.index_.first].start(),
					segs[front_event.index_.first].end(),
					next->segment_.start(),
					next->segment_.end(),
					intersect_pt)) {
					res.push_back(intersect_pt);
					events_.emplace(intersect_pt, 2, std::pair<int, int>{front_event.index_.first, next->index_ });
				}
			}
			auto prev = std::find_if(sweep_line_status.rbegin(), sweep_line_status.rend(), [&](const auto& s) {
				return s.get_y_by_x(sweep_line) > front_event.p_.y();
				});
			if (prev != sweep_line_status.rend() && marked[prev->index_][front_event.index_.first] == 0) {
				marked[prev->index_][front_event.index_.first] = 1;
				marked[front_event.index_.first][prev->index_] = 1;
				auto intersect_pt = Point2D{};
				if (get_intersect(segs[front_event.index_.first].start(),
					segs[front_event.index_.first].end(),
					prev->segment_.start(),
					prev->segment_.end(),
					intersect_pt)) {
					res.push_back(intersect_pt);
					events_.emplace(intersect_pt, 2, std::pair<int, int>{ prev->index_, front_event.index_.first});
				}
			}
			sweep_line_status.emplace(next, LineSegment_{ front_event.index_.first , segs[front_event.index_.first] });
		}
		else if (front_event.type_ == 1) {
			auto cur_itr = std::find_if(sweep_line_status.begin(), sweep_line_status.end(), [&](const auto& l) {
				return l.index_ == front_event.index_.first;
				});
			if (cur_itr == sweep_line_status.end()) {
				continue;
			}
			auto prev = cur_itr;
			if (cur_itr != sweep_line_status.begin()) {
				--prev;
			}
			else {
				prev = sweep_line_status.end();
			}
			auto next = cur_itr;
			++next;
			if (prev != sweep_line_status.end() && next != sweep_line_status.end() && marked[prev->index_][next->index_] == 0) {
				marked[prev->index_][next->index_] = 1;
				marked[next->index_][prev->index_] = 1;
				auto intersect_pt = Point2D{};
				if (get_intersect(prev->segment_.start(), prev->segment_.end(),
					next->segment_.start(), next->segment_.end(), intersect_pt)) {
					res.push_back(intersect_pt);
					events_.emplace(intersect_pt, 2, std::pair<int, int>{ prev->index_, next->index_});
				}
			}
			sweep_line_status.erase(cur_itr);
		}
		else if (front_event.type_ == 2) {
			auto prev = std::find_if(sweep_line_status.begin(), sweep_line_status.end(), [&](const auto& l) {
				return l.index_ == front_event.index_.first;
				});
			auto next = std::find_if(sweep_line_status.begin(), sweep_line_status.end(), [&](const auto& l) {
				return l.index_ == front_event.index_.second;
				});
			if (prev == sweep_line_status.end() || next == sweep_line_status.end()) {
				std::cout << "prev_itr or next_itr are empty!" << std::endl;
			}

			auto nearby = std::vector<std::list<LineSegment_>::iterator>{};
			auto prev_prev = prev;
			if (prev_prev == sweep_line_status.begin()) {
				prev_prev = sweep_line_status.end();
			}
			else {
				--prev_prev;
			}
			nearby.push_back(prev_prev);
			auto prev_next = prev;
			prev_next++;
			nearby.push_back(prev_next);
			auto next_prev = next;
			if (next_prev == sweep_line_status.begin()) {
				next_prev = sweep_line_status.end();
			}
			else {
				--next_prev;
			}
			nearby.push_back(next_prev);
			auto next_next = next;
			next_next++;
			nearby.push_back(next_next);
			for (const auto& i : nearby) {
				if (i != sweep_line_status.end() && marked[next->index_][i->index_] == 0) {
					marked[next->index_][i->index_] = 1;
					marked[i->index_][next->index_] = 1;
					auto intersect_pt = Point2D{};
					if (get_intersect(i->segment_.start(), i->segment_.end(),
						next->segment_.start(), next->segment_.end(), intersect_pt)) {
						res.push_back(intersect_pt);
						events_.emplace(intersect_pt, 2, std::pair<int, int>{ i->index_, next->index_});
					}
				}
				if (i != sweep_line_status.end() && marked[prev->index_][i->index_] == 0) {
					marked[prev->index_][i->index_] = 1;
					marked[i->index_][prev->index_] = 1;
					auto intersect_pt = Point2D{};
					if (get_intersect(prev->segment_.start(), prev->segment_.end(), i->segment_.start(),
						i->segment_.end(), intersect_pt)) {
						res.push_back(intersect_pt);
						events_.emplace(intersect_pt, 2, std::pair<int, int>{ prev->index_, i->index_});
					}
				}
			}
		}
	}
	return res;
}