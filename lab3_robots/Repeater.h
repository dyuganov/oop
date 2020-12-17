#pragma once

#include "Map.h"
#include "Environment.h"

#include <set>
#include <map>
#include <vector>
using std::pair;
using std::vector;

class Repeater {
private:
	vector<pair<Coordinates, Object>> changes;
	vector<Coordinates> robotsPositions;

	Coordinates offsetForSync = { 0, 0 }; // x, y

	bool isEqual(const Coordinates& l, const Coordinates& r) const noexcept {
		if ((l.x == r.x) && (l.y == r.y)) {
			return true;
		}
		else {
			return false;
		}
	}

public:
	Repeater() = default;
	~Repeater() = default;

	// makes this cell empty
	void NotifyDefuse(const Coordinates& coords) {
		changes.push_back({ coords, Object::empty });
	}

	void NotifyScan(const vector<pair<Coordinates, Object>>& objects) noexcept {
		for (const auto& item : objects) {
			this->changes.push_back(item);
		}
	}

	// makes this cell empty
	void NotifyCollect(const Coordinates& coords) noexcept {
		changes.push_back({coords, Object::empty});
	}

	// add new coords
	void NotifyRobotCreated(const Coordinates& coords) noexcept {
		robotsPositions.push_back(coords);
	}

	// delete coords
	void NotifyRobotDeleted(const Coordinates& coords) {
		for (size_t i = 0; i < robotsPositions.size(); ++i) {
			if (isEqual(robotsPositions.at(i), coords)) {
				robotsPositions.erase(robotsPositions.begin() + i);
				return;
			}
		}
	}

	// delete old coords, add new
	void NotifyMove(const Coordinates& prevCoords, const Coordinates& newCoords) {
		if (!robotsPositions.empty()) {
			for (size_t i = 0; i < robotsPositions.size(); ++i) {
				if (isEqual(robotsPositions.at(i), prevCoords)) {
					robotsPositions.erase(robotsPositions.begin() + i);
					break;
				}
			}
			robotsPositions.push_back(newCoords);
		}
		else {
			throw exception("Notify move error. There are no robots positions in repeater.");
		}
	}

	// Check that there is no other robot in this position
	bool isEmptyCell(const Coordinates& coords) const noexcept {
		for (const auto& i : robotsPositions) {
			if (isEqual(i, coords)) return false;
		}
		return true;
	}

	vector<pair<Coordinates, Object>> getMapUpdates() {
		vector<pair<Coordinates, Object>> res(changes);
		changes.clear();
		return res;
	}

	void DeleteElem(const size_t& idx) {
		if (idx >= this->changes.size() || idx < 0) {
			throw exception("Can't delete this element in changes vector");
		}
		this->changes.erase(changes.begin() + idx);
	}

	bool isAlone() {
		return !robotsPositions.size();
	}
};
