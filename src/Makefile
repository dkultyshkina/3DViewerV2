G++ = g++ -std=c++17
CHECKFLAGS = -Wall -Werror -Wextra
SRC = Model/Facade.cc Model/FacadeOperationResult.cc Model/FileReader.cc Model/Model.cc Model/MovedModel.cc Model/RotatedModel.cc Model/ScaledModel.cc Model/OffsetScene.cc
OBJ = $(SRC:%.cc=%.o)
OS = $(shell uname -s)

TEST_DIR = tests
BUILD_DIR = ../build
DOCS_DIR = Docs
COVERAGE_DIR = Coverage

TEST_SRC = $(TEST_DIR)/test.cc
TEST_LIBS = -lgtest -pthread

ifeq ($(OS), Darwin)
	NAME_APP=3DViewerV2.app
else
	NAME_APP=3DViewerV2
endif

all: clean tests

tests: clean unpack_obj
	$(G++) $(TEST_SRC) $(SRC) $(CHECKFLAGS) $(TEST_LIBS) -o test
	./test

clean:
	@echo "Cleanup is in progress..."
	@rm -rf Archive_3DViewerV2 test.dSYM
	@rm -rf *.css .DS_Store
	@rm -rf *.html *.gcda *.gcno *.a test
	@rm -rf *.tgz fsanityze.out
	@rm -rf test_output gcov_test report
	@rm -rf $(BUILD_DIR) $(DOCS_DIR) $(COVERAGE_DIR)
	@echo "Cleanup is done."

dvi: doxygen
	open ./$(DOCS_DIR)/html/annotated.html

install:
	@rm -rf $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)
	@echo "Installing..."
	@cd $(BUILD_DIR)/ && qmake ../src && make
	@echo "Install completed"
	@rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/moc_*
	@rm $(BUILD_DIR)/ui_* $(BUILD_DIR)/Makefile $(BUILD_DIR)/.qmake.stash

uninstall:
	rm -rf $(BUILD_DIR)

dist: install
	rm -rf Archive_3DViewerV2/
	mkdir Archive_3DViewerV2/
	mkdir Archive_3DViewerV2/src
	cp -r ./$(BUILD_DIR)/$(NAME_APP) Archive_3DViewerV2/src/
	tar cvzf Archive_3DViewerV2.tgz Archive_3DViewerV2/
	rm -rf Archive_3DViewerV2/

gcov_report: clean unpack_obj
	@mkdir -p $(COVERAGE_DIR)
	$(G++) --coverage $(TEST_SRC) $(SRC) $(CHECKFLAGS) $(TEST_LIBS) -o $(COVERAGE_DIR)/gcov_test $(shell pkg-config --libs --cflags check)
	@./$(COVERAGE_DIR)/gcov_test
	gcovr -r . --html --html-details -d $(COVERAGE_DIR) -o $(COVERAGE_DIR)/3DViewerV2.html
	@rm -rf $(COVERAGE_DIR)/*.gcno $(COVERAGE_DIR)/gcov_test
	open ./$(COVERAGE_DIR)/3DViewerV2.html

clang:
	clang-format -style=google -i Model/*.cc
	clang-format -style=google -i Model/*.h
	clang-format -style=google -i View/*.cc
	clang-format -style=google -i View/*.h
	clang-format -style=google -i Controller/*.cc
	clang-format -style=google -i Controller/*.h
	clang-format -style=google -i tests/*.cc

clang-format:
	clang-format -style=google -n Model/*.cc View/*.cc Controller/*.cc tests/*.cc
	clang-format -style=google -n Model/*.h View/*.h Controller/*.h

doxygen:
	@rm -rf $(DOCS_DIR)
	doxygen Doxyfile
	@echo "Documentation created ($(PWD)/$(DOCS_DIR)/html/annotated.html)."

fsanitize:
	$(G++) $(TEST_SRC) $(SRC)  $(CHECKFLAGS) -g -fsanitize=address,undefined $(TEST_LIBS) -o test
	@./test

valgrind: tests
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

unpack_obj:
	@rm -rf $(TEST_DIR)/obj*.obj
	@tar -xvf $(TEST_DIR)/obj_test.tar -C ./$(TEST_DIR)
