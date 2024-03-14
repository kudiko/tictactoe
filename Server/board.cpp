#include "board.h"

#include <vector>
#include <tuple>
#include <stdexcept>

BoardVector::BoardVector(std::pair<int, int> dimensions) {
	if (dimensions.first < 0 || dimensions.second < 0) {
		throw std::invalid_argument("");
	}
	board_.resize(dimensions.first);
	for (std::vector<Mark>& row : board_) {
		row.resize(dimensions.second, Mark::EMPTY);
	}
	dimensions_ = dimensions;
}

// Returns 'true' if successful
bool BoardVector::Insert(std::pair<int, int> coord, Mark mark) {
	if (!CheckOutOfBounds(coord) && !CheckOccupied(coord)) {
		board_[coord.first][coord.second] = mark;
		return true;
	}
	return false;
}

bool BoardVector::ForceInsert(std::pair<int, int> coord, Mark mark) {
	if (!CheckOutOfBounds(coord)) {
		board_[coord.first][coord.second] = mark;
		return true;
	}
	return false;
}

bool BoardVector::Erase(std::pair<int, int> coord) {
	if (!CheckOutOfBounds(coord)) {
		board_[coord.first][coord.second] = Mark::EMPTY;
		return true;
	}
	return false;
}

Mark BoardVector::LookUp(std::pair<int, int> coord) const {
	if (!CheckOutOfBounds(coord)) {
		return board_[coord.first][coord.second];
	}
	return Mark::EMPTY;
}

void BoardVector::SetAllTiles(Mark mark) {
	for (std::vector<Mark>& row : board_) {
		for (Mark& current_mark : row) {
			current_mark = mark;
		}
	}
}

void BoardVector::ClearBoard() {
	this->SetAllTiles(Mark::EMPTY);
}

int BoardVector::GetFreeTilesCount() const {
	int output = 0;
	for (const std::vector<Mark>& row : board_) {
		for (const Mark& current_mark : row) {
			output += (current_mark == Mark::EMPTY) ? 1 : 0;
		}
	}
	return output;
}

std::pair<int, int> BoardVector::GetDimensions() const {
	return dimensions_;
}

[[nodiscard]] bool BoardVector::CheckOutOfBounds(std::pair<int, int> coord) const {
	if (coord.first >= 0 && coord.first < dimensions_.first) {
		if (coord.second >= 0 && coord.second < dimensions_.second) {
			return false;
		}
	}
	return true;
}

// Must not be out of bounds
[[nodiscard]] bool BoardVector::CheckOccupied(std::pair<int, int> coord) const {
	if (board_[coord.first][coord.second] == Mark::EMPTY) {
		return false;
	}
	return true;
}
