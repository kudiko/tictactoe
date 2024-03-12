#pragma once

#include <vector>
#include <tuple>

enum class Mark {
	EMPTY,
	X,
	O
};

class Board {
public:

	virtual bool Insert(std::pair<int, int> coord, Mark mark) = 0;

	virtual bool ForceInsert(std::pair<int, int> coord, Mark mark) = 0;

	virtual bool Erase(std::pair<int, int> coord) = 0;

	virtual Mark LookUp(std::pair<int, int> coord) const = 0;

	virtual void SetAllTiles(Mark mark) = 0;

	virtual void ClearBoard() = 0;

	virtual int GetFreeTilesCount() const = 0;

	virtual std::pair<int, int> GetDimensions() const = 0;

};

class BoardVector : public Board {
public:

	BoardVector(std::pair<int, int> dimensions) {
		if (dimensions.first < 0 || dimensions.second < 0) {
			throw std::invalid_argument("");
		}
		board_.resize(dimensions.first);
		for (std::vector<Mark>& row : board_) {
			row.resize(dimensions.second, Mark::EMPTY);
		}
	}

	BoardVector() : BoardVector({ 3, 3 }) {}

	// Returns 'true' if successful
	bool Insert(std::pair<int, int> coord, Mark mark) override {
		if (!CheckOutOfBounds(coord) && !CheckOccupied(coord)) {
			board_[coord.first][coord.second] = mark;
			return true;
		}
		return false;
	}

	bool ForceInsert(std::pair<int, int> coord, Mark mark) override {
		if (!CheckOutOfBounds(coord)) {
			board_[coord.first][coord.second] = mark;
			return true;
		}
		return false;
	}

	bool Erase(std::pair<int, int> coord) override {
		if (!CheckOutOfBounds(coord)) {
			board_[coord.first][coord.second] = Mark::EMPTY;
			return true;
		}
		return false;
	}

	Mark LookUp(std::pair<int, int> coord) const override {
		if (!CheckOutOfBounds(coord)) {
			return board_[coord.first][coord.second];
		}
		return Mark::EMPTY;
	}

	void SetAllTiles(Mark mark) override {
		for (std::vector<Mark>& row : board_) {
			for (Mark& current_mark : row) {
				current_mark = mark;
			}
		}
	}

	void ClearBoard() override {
		this->SetAllTiles(Mark::EMPTY);
	}

	int GetFreeTilesCount() const override {
		int output = 0;
		for (const std::vector<Mark>& row : board_) {
			for (const Mark& current_mark : row) {
				output += (current_mark == Mark::EMPTY) ? 1 : 0;
			}
		}
		return output;
	}

	std::pair<int, int> GetDimensions() const override {
		return dimensions_;
	}

private:
	std::vector<std::vector<Mark>> board_;
	std::pair<int, int> dimensions_;

	[[nodiscard]] bool CheckOutOfBounds(std::pair<int, int> coord) const {
		if (coord.first >= 0 && coord.first < dimensions_.first) {
			if (coord.second >= 0 && coord.second < dimensions_.second) {
				return false;
			}
		}
		return true;
	}

	// Must not be out of bounds
	[[nodiscard]] bool CheckOccupied(std::pair<int, int> coord) const {
		if (board_[coord.first][coord.second] == Mark::EMPTY) {
			return false;
		}
		return true;
	}
};

class BoardBitset : public Board {
public:

private:
	int bits_per_tile = 0;

	int GetBitCountPerTile(int options_count) const {
		if (options_count <= 0) {
			return 0;
		}
		int output = 1;
		int num = 2;
		while (options_count > num) {
			++output;
			num *= 2;
		}
		return output;
	}
};