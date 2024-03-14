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

	virtual ~Board() = default;

};

class BoardVector : public Board {
public:

	BoardVector(std::pair<int, int> dimensions);

	BoardVector() : BoardVector({ 3, 3 }) {}

	// Returns 'true' if successful
	bool Insert(std::pair<int, int> coord, Mark mark) override;

	bool ForceInsert(std::pair<int, int> coord, Mark mark) override;

	bool Erase(std::pair<int, int> coord) override;

	Mark LookUp(std::pair<int, int> coord) const override;

	void SetAllTiles(Mark mark) override;

	void ClearBoard() override;

	int GetFreeTilesCount() const override;

	std::pair<int, int> GetDimensions() const override;

	virtual ~BoardVector() = default;

private:
	std::vector<std::vector<Mark>> board_;
	std::pair<int, int> dimensions_;

	[[nodiscard]] bool CheckOutOfBounds(std::pair<int, int> coord) const;

	// Must not be out of bounds
	[[nodiscard]] bool CheckOccupied(std::pair<int, int> coord) const;
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