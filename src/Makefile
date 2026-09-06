
INCLUDE_HEADERS = $(wildcard include/*.h)

GRAPH_SRC = $(wildcard Graph/*.cpp)
GRAPH_OBJECTS = $(GRAPH_SRC:.cpp=.o)

SRC_FILES = $(wildcard ./*.cpp)
SRC_OBJECTS = $(SRC_FILES:.cpp=.o)

ALGORITHMS_SRC = $(wildcard Algorithms/*.cpp)
ALGORITHMS_OBJECTS = $(ALGORITHMS_SRC:.cpp=.o)

TEST_SRC = $(wildcard tests/*.cpp)
TEST_OBJECTS = $(TEST_SRC:.cpp=.o)

TEST_FLAGS = -lgtest -lgmock -pthread
LCOV_FLAGS = --no-external --ignore-errors inconsistent,inconsistent

all: $(SRC_OBJECTS) s21_graph.a s21_graph_algorithms.a
	g++ $(FLAGS) $(SRC_OBJECTS) -L. -l:s21_graph.a -l:s21_graph_algorithms.a -o main
	./main

s21_graph.a: $(GRAPH_OBJECTS)
	@echo "Creating static library s21_graph.a"
	@ar rcs s21_graph.a $(GRAPH_OBJECTS)

s21_graph_algorithms.a: $(ALGORITHMS_OBJECTS)
	@echo "Creating static library s21_graph_algorithms.a"
	@ar rcs s21_graph_algorithms.a $(ALGORITHMS_OBJECTS)

%.o: %.cpp
	@g++ $(FLAGS) -c $< -o $@

FLAGS = -std=c++17 -Wall -Wextra -Werror -fPIC -fprofile-arcs -ftest-coverage

clean:
	@echo "Cleaning up..."
	@rm -f $(SRC_OBJECTS) $(GRAPH_OBJECTS) $(ALGORITHMS_OBJECTS) $(TEST_OBJECTS)
	@rm -f include.a s21_graph.a s21_graph_algorithms.a main test coverage.info
	@find . -type f \( -name '*.gcno' -o -name '*.gcda' -o -name '*.gcov' \) -delete
	@rm -rf out

test: $(TEST_OBJECTS) s21_graph.a s21_graph_algorithms.a
	g++ $(FLAGS) $(TEST_OBJECTS) -L. -l:s21_graph.a -l:s21_graph_algorithms.a -o test $(TEST_FLAGS)
	./test
gcov_report: clean test
	lcov $(LCOV_FLAGS) --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out
	google-chrome out/index.html
