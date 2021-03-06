###########################
#         vulkan         #
###########################

set(INCLUDE_DIRECTORIES src/include)

set(SOURCE_FILES "")
set(FILES_PATH "src/src/")#file path from root
list(APPEND SOURCE_FILES "${FILES_PATH}utils.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems_menu.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}comparer.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}state_machine.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}message_writer.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}clock.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}fraction.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}splash_screen.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}main.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}definitions.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}poker_hand.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}graphs_and_grids.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}sdl_init.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_61_70.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_51_60.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_21_30.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_01_10.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_41_50.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_91_100.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_81_90.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_31_40.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_71_80.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_11_20.cpp")


set(HEADER_FILES "")
set(FILES_PATH "src/include/")#file path from root
list(APPEND HEADER_FILES "${FILES_PATH}enums.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}clock.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}defines.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}state_machine.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}fraction.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}hash.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}problems_menu.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}comparer.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}eulerproblems.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}splash_screen.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}message_writer.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}constants.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}utils.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}state_interface.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}graphs_and_grids.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}poker_hand.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}structs.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}sdl_init.hpp")
