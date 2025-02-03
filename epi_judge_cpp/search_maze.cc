#include <istream>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
enum class Color { kWhite, kBlack };
struct Coordinate {
  bool operator==(const Coordinate& that) const {
    return x == that.x && y == that.y;
  }

  int x, y;
};

static const std::vector<std::pair<int,int>> dirs{
  {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

bool find_path(
  const vector<vector<Color>>& maze,
  const Coordinate& e,
  const Coordinate& curr,
  vector<Coordinate>& curr_path,
  vector<vector<bool>>& visited
) {
  visited[curr.x][curr.y] = true;
  curr_path.emplace_back(curr);

  if (curr == e) {
    // path found
    return true;
  }

  for (const auto& dir : dirs) {
    Coordinate neigh{curr.x + dir.first, curr.y + dir.second};
    if (neigh.x < 0 || neigh.x >= maze.size() ||
        neigh.y < 0 || neigh.y >= maze[0].size()) {
      continue;
    }
    if (visited[neigh.x][neigh.y] || maze[neigh.x][neigh.y] == Color::kBlack) {
      continue;
    }
    if (find_path(maze, e, neigh, curr_path, visited)) {
      // found a path via curr -> neigh
      return true;
    }
  }

  // path not found via curr
  curr_path.pop_back();
  return false;
}

vector<Coordinate> SearchMaze(vector<vector<Color>> maze, const Coordinate& s,
                              const Coordinate& e) {
  vector<vector<bool>> visited(
    maze.size(), vector<bool>(maze[0].size(), false)
  );
  vector<Coordinate> curr_path{};
  find_path(maze, e, s, curr_path, visited);
  return curr_path;
}

namespace test_framework {
template <>
struct SerializationTrait<Color> : SerializationTrait<int> {
  using serialization_type = Color;

  static serialization_type Parse(const json& json_object) {
    return static_cast<serialization_type>(
        SerializationTrait<int>::Parse(json_object));
  }
};
}  // namespace test_framework

namespace test_framework {
template <>
struct SerializationTrait<Coordinate> : UserSerTrait<Coordinate, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {};
  }

  static std::vector<int> GetMetrics(const Coordinate& x) { return {}; }
};
}  // namespace test_framework

bool PathElementIsFeasible(const vector<vector<Color>>& maze,
                           const Coordinate& prev, const Coordinate& cur) {
  if (!(0 <= cur.x && cur.x < maze.size() && 0 <= cur.y &&
        cur.y < maze[cur.x].size() && maze[cur.x][cur.y] == Color::kWhite)) {
    return false;
  }
  return cur == Coordinate{prev.x + 1, prev.y} ||
         cur == Coordinate{prev.x - 1, prev.y} ||
         cur == Coordinate{prev.x, prev.y + 1} ||
         cur == Coordinate{prev.x, prev.y - 1};
}

bool SearchMazeWrapper(TimedExecutor& executor,
                       const vector<vector<Color>>& maze, const Coordinate& s,
                       const Coordinate& e) {
  vector<vector<Color>> copy = maze;

  auto path = executor.Run([&] { return SearchMaze(copy, s, e); });

  if (path.empty()) {
    return s == e;
  }

  if (!(path.front() == s) || !(path.back() == e)) {
    throw TestFailure("Path doesn't lay between start and end points");
  }

  for (size_t i = 1; i < path.size(); i++) {
    if (!PathElementIsFeasible(maze, path[i - 1], path[i])) {
      throw TestFailure("Path contains invalid segments");
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "maze", "s", "e"};
  return GenericTestMain(args, "search_maze.cc", "search_maze.tsv",
                         &SearchMazeWrapper, DefaultComparator{}, param_names);
}
