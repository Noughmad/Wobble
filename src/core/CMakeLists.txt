set(Wobble_SRCS common.cpp
    type.cpp 
    identifier.cpp
    class.cpp
    view.cpp 
    project.cpp
    input.cpp
    output.cpp
)

wobble_add_library(WobbleCore ${Wobble_SRCS})
target_link_libraries(WobbleCore ${QT_QTCORE_LIBRARY})
