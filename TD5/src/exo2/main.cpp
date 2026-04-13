#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <fstream>

// QUESTION 1

enum class Direction { 
    Haut, 
    Droite, 
    Bas, 
    Gauche 
};

Direction turn_right(Direction dir) {
    switch (dir) {
        case Direction::Haut:   return Direction::Droite;
        case Direction::Droite: return Direction::Bas;
        case Direction::Bas:    return Direction::Gauche;
        case Direction::Gauche: return Direction::Haut;
        default: return dir;
    }
}

struct Position {
    int x {};
    int y {};

    bool operator==(Position const& other) const {
        return x == other.x && y == other.y;
    }

    Position& operator+=(Position const& b) {
        x += b.x;
        y += b.y;
        return *this;
    }

    Position& operator+=(Direction dir) {
        if (dir == Direction::Haut)   y -= 1;
        else if (dir == Direction::Bas)    y += 1;
        else if (dir == Direction::Gauche) x -= 1;
        else if (dir == Direction::Droite) x += 1;
        return *this;
    }
};

std::ostream& operator<<(std::ostream& os, Position const& p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

Position operator+(Position p, Direction dir) {
    p += dir; 
    return p;
}

// QUESTION 2

namespace std {
    template <>
    struct hash<Position> {
        std::size_t operator()(const Position& pos) const {
            return std::hash<int>{}(pos.x) ^ (std::hash<int>{}(pos.y) << 1);
        }
    };
}

struct Input_Map {
    std::unordered_set<Position> filled_positions;
    int width {};
    int height {};
    Position start_pos {};
    Direction start_dir { Direction::Haut };
};

Input_Map parse_input(std::istream& input_stream) {
    Input_Map map;
    int row = 0;
    int max_col = 0;

    for (std::string line{}; std::getline(input_stream, line, '\n') && line != "";) {
        for (int col = 0; col < static_cast<int>(line.size()); ++col) {
            char cell = line[col];

            if (cell == '#') {
                map.filled_positions.insert(Position{col, row});
            } 
            else if (cell == '^' || cell == 'v' || cell == '<' || cell == '>') {
                map.start_pos = Position{col, row};
                
                switch (cell) {
                    case '^':
                        map.start_dir = Direction::Haut;
                        break;
                    case 'v':
                        map.start_dir = Direction::Bas;
                        break;
                    case '<':
                        map.start_dir = Direction::Gauche;
                        break;
                    case '>':
                        map.start_dir = Direction::Droite;
                        break;
                }
            }
            if (col > max_col) max_col = col;
        }
        row++;
    }
    map.width = max_col + 1;
    map.height = row;
    return map;
}

bool is_obstacle(Position const& target, std::unordered_set<Position> const& obstacles) {
    return obstacles.count(target) > 0;
}

// QUESTION 3

struct WalkResult {
    Position final_position;
    size_t steps_taken;
    std::unordered_set<Position> visited_positions;
};

WalkResult simulate_guard(Input_Map const& map) {
    Position current_pos = map.start_pos;
    Direction current_dir = map.start_dir;
    
    std::unordered_set<Position> visited;
    visited.insert(current_pos);
    
    size_t steps = 0;

    while (true) {
        Position next_pos = current_pos + current_dir;

        if (next_pos.x < 0 || next_pos.x >= map.width || 
            next_pos.y < 0 || next_pos.y >= map.height) {
            return {current_pos, steps, visited};
        }

        if (is_obstacle(next_pos, map.filled_positions)) {
            current_dir = turn_right(current_dir);
        } else {
            current_pos = next_pos;
            visited.insert(current_pos);
            steps++;
        }
    }
}

// QUESTION 4

struct GuardState {
    Position pos;
    Direction dir;

    bool operator==(GuardState const& other) const {
        return pos == other.pos && dir == other.dir;
    }
};

namespace std {
    template <>
    struct hash<GuardState> {
        std::size_t operator()(const GuardState& s) const {
            return std::hash<Position>{}(s.pos) ^ (std::hash<int>{}(static_cast<int>(s.dir)) << 16);
        }
    };
}

bool predict_loop(Input_Map const& map) {
    Position current_pos = map.start_pos;
    Direction current_dir = map.start_dir;
    
    std::unordered_set<GuardState> history;

    while (true) {
        if (history.count({current_pos, current_dir})) {
            return true;
        }
        history.insert({current_pos, current_dir});

        Position next_pos = current_pos + current_dir;

        if (next_pos.x < 0 || next_pos.x >= map.width || 
            next_pos.y < 0 || next_pos.y >= map.height) {
            return false;
        }

        if (is_obstacle(next_pos, map.filled_positions)) {
            current_dir = turn_right(current_dir);
        } else {
            current_pos = next_pos;
        }
    }
}

int count_loops(Input_Map const& base_map, std::unordered_set<Position> const& original_path) {
    int loops_found = 0;

    for (Position const& p : original_path) {
        if (p == base_map.start_pos) continue;

        Input_Map modified_map = base_map;
        modified_map.filled_positions.insert(p);

        if (predict_loop(modified_map)) {
            loops_found++;
        }
    }
    return loops_found;
}

int main() {

    // QUESTION 1
    Position pos{2, 3};
    Direction d = Direction::Haut;

    std::cout << "\nTest question 1 :" << std::endl;
    std::cout << pos << " + Haut = " << (pos + d) << std::endl;
    pos += turn_right(d); 
    std::cout << "Apres tourne a droite et avance : " << pos << " (attendu: (3, 3))" << std::endl;
    std::cout << "Test egalite : " << (pos == Position{3, 3} ? "OK" : "ERREUR") << std::endl;

    // QUESTION 2 et 3 (première carte de test)
    std::stringstream ss("....#\n.....\n..^..\n.#...\n");
    Input_Map data = parse_input(ss);

    std::cout << "\nTest question 2 :" << std::endl;
    std::cout << "Garde : " << data.start_pos << std::endl; 
    std::cout << "Obstacles : " << data.filled_positions.size() << std::endl; 
    std::cout << "Taille carte : " << data.width << "x" << data.height << std::endl;

    WalkResult result = simulate_guard(data);
    std::cout << "\nTest question 3 :" << std::endl;
    std::cout << "Position finale : " << result.final_position << std::endl;
    std::cout << "Positions visitees : " << result.visited_positions.size() << std::endl;

    // QUESTION 3.3 (carte d'exemple : 41 positions)
    std::string example_map = 
        "....#.....\n"
        ".........#\n"
        "..........\n"
        "..#.......\n"
        ".......#..\n"
        "..........\n"
        ".#..^.....\n"
        "........#.\n"
        "#.........\n"
        "......#...\n";

    ss = std::stringstream(example_map); 
    data = parse_input(ss);
    result = simulate_guard(data);

    std::cout << "\nTest Carte d'exemple :" << std::endl;
    std::cout << "Position finale : " << result.final_position << std::endl;
    std::cout << "Nombre de pas : " << result.steps_taken << std::endl;
    std::cout << "Positions visitees : " << result.visited_positions.size() << std::endl;

    if (result.visited_positions.size() == 41) {
        std::cout << "RESULTAT : OK" << std::endl;
    } else {
        std::cout << "RESULTAT : ERREUR (Attendu 41, obtenu " << result.visited_positions.size() << ")" << std::endl;
    }

    std::ifstream file("input_guard_patrol.txt"); 
    if (file.is_open()) {
        data = parse_input(file);
        result = simulate_guard(data);
        std::cout << "RESULTAT FINAL : " << result.visited_positions.size() << std::endl;

        // QUESTION 4 (nb boucles)
        std::cout << "Calcul des boucles :" << std::endl;
        int loops_found = 0;
        
        for (Position const& p : result.visited_positions) {
            if (p == data.start_pos) continue;

            Input_Map modified_map = data;
            modified_map.filled_positions.insert(p);

            if (predict_loop(modified_map)) {
                loops_found++;
            }
        }

        std::cout << "Nombre de boucles possibles : " << loops_found << std::endl;
    }

    return 0;
}