cmake_minimum_required(VERSION 3.30)
project(grapher CXX)
set(CMAKE_CXX_STANDART 23)

#ПОДКЛЮЧАЕМ ПЕРЕМЕННЫЕ
include(variables.cmake)

#ГРАФ
add_library(graph ${GRAPH})

#ДОСТИЖИМОСТЬ
add_library(achiveabler ${ACHIVE})
target_link_libraries(achiveabler PUBLIC graph)

#-------------------------------------------------
#РОУТЕР ДЕЙКСТРЫ
add_library(deikstrart ${DROUTER})
target_link_libraries(deikstrart PUBLIC graph)


#РОУТЕР ФЛОЙДА УОРШАЛЛА
add_library(floyd_warshallrt ${FLWROUTER})
target_link_libraries(floyd_warshallrt PUBLIC graph)

#--------------------------------------------------------------
#БИБЛИОТЕКА ГРАФИЧЕСКИХ ОБЬЕКТОВ И СТИЛИЗАЦЦИИ ПРОЕКТА
add_library(graphics ${GRAPHICS})

#БИБЛИОТЕКА ПРИНТЕРОВ SVG
add_library(svg_printers ${SVGPR})
target_link_libraries(svg_printers PUBLIC graphics deikstrart)

#БИБЛИОТЕКА ПРИНТЕРОВ В КОНСОЛЬ ГРАФА, ДОСТИЖИМОСТИ
add_library(console_gr_wgh_ach ${CNSL_GWA})
target_link_libraries(console_gr_wgh_ach PUBLIC graph)

#БИБЛИОТЕКА ПРИНТЕРА В КОНСОЛЬ ДЕЙКСТРЫ
add_library(console_deikstra ${CNSL_DEIKSTRA})
target_link_libraries(console_deikstra PUBLIC graph deikstrart)

add_library(AStar ${ASTAR})
#----------------------------------------------------------------
add_executable(grpx src/main.cpp)
target_link_libraries(grpx PUBLIC achiveabler svg_printers console_gr_wgh_ach AStar)


set(WAY_TO_INSTALL F:/COMPILESOFT/CUSTOMLIBS)
set(CMAKE_INSTALL_PREFIX ${WAY_TO_INSTALL})

install(TARGETS ${INSTALL_TARGETS} EXPORT GraphLibs
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
   INCLUDES DESTINATION include
)

install(EXPORT GraphLibs
   FILE GraphLibsConfig.cmake
   NAMESPACE GraphLibs::
   DESTINATION lib/cmake/GraphLib
)

install(FILES ${LIB_HEADERS} DESTINATION ${WAY_TO_INSTALL}/includes)
#cmake --build . --target install 
