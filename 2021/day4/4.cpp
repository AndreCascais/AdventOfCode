#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include <vector>

using Board = std::vector<std::vector<int>>;

struct BoardCell
{
    int row;
    int col;
    int boardNumber;
};

std::vector<int> readDraw()
{
    std::string line{};
    std::getline(std::cin, line);
    std::replace(line.begin(), line.end(), ',', ' ');
    std::istringstream stream(line);
    std::vector<int> draw((std::istream_iterator<int>(stream)),
                          std::istream_iterator<int>());
    return draw;
}

std::vector<Board> readBoards()
{
    std::string line{};
    int nBoards = 0;
    std::vector<Board> boards;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            boards.resize(boards.size() + 1);
            ++nBoards;
            continue;
        }
        std::istringstream stream(line);
        std::vector<int> row((std::istream_iterator<int>(stream)),
                             std::istream_iterator<int>());
        boards[nBoards - 1].emplace_back(std::move(row));
    };
    return boards;
}

std::unordered_multimap<int, BoardCell> constructNumberMap(
    std::vector<Board> boards)
{
    int nBoards = boards.size();
    int nRows = boards[0].size();
    int nCols = boards[0][0].size();

    std::unordered_multimap<int, BoardCell> numberMap;
    for (int boardNumber = 0; boardNumber != nBoards; ++boardNumber) {
        for (int row = 0; row < nRows; ++row) {
            for (int col = 0; col < nCols; ++col) {
                numberMap.emplace(boards[boardNumber][row][col],
                                  BoardCell{ row, col, boardNumber });
            }
        }
    }
    return numberMap;
}

auto sumBoard = [](const auto& board) {
    int sum = 0;
    for (const auto& row : board) {
        for (auto number : row) {
            sum += number;
        }
    }
    return sum;
};

int getWinner(std::vector<Board> boards,
              const std::unordered_multimap<int, BoardCell>& numberMap,
              const std::vector<int>& draw,
              int winnerPosition)
{
    int nBoards = boards.size();
    int nRows = boards[0].size();
    int nCols = boards[0][0].size();

    std::vector<std::vector<int>> rows(nBoards, std::vector<int>(nRows));
    std::vector<std::vector<int>> cols(nBoards, std::vector<int>(nCols));

    std::vector<int> winners{};
    int winnerBoard;
    int winnerNumber;

    for (const auto& number : draw) {
        auto [matchesBegin, matchesEnd] = numberMap.equal_range(number);
        for (auto match = matchesBegin; match != matchesEnd; ++match) {
            const auto [row, col, board] = match->second;
            if (std::find(winners.begin(), winners.end(), board) != winners.end()) {
                continue;
            }
            boards[board][row][col] = 0;
            if (++rows[board][row] == nRows || ++cols[board][col] == nCols) {
                winnerBoard = board;
                winnerNumber = number;
                winners.emplace_back(winnerBoard);
            }
        }
        if (winners.size() == winnerPosition) {
            break;
        }
    }

    return sumBoard(boards[winnerBoard]) * winnerNumber;
}

int main()
{
    auto draw = readDraw();
    auto boards = readBoards();
    auto numberMap = constructNumberMap(boards);

    std::cout << "sum * number for first board:"
              << getWinner(boards, numberMap, draw, 1) << '\n';
    std::cout << "sum * number for last board:"
              << getWinner(boards, numberMap, draw, boards.size()) << '\n';
}