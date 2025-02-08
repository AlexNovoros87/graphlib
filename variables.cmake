#graph
set(GRAPH
src//free/structs.h
src/free/freefoo.h
src/free/graphfree.cpp
src/graph/graph.h
src/graph/graph.cpp 
)
#achiveabler
set(ACHIVE
src/achiveabler/achiveabler.h
src/achiveabler/achiveabler.cpp
)
#deikstrart
set(DROUTER
src/routers/deikstrarouter.h
src/routers/deikstrarouter.cpp
)
#floyd_warshallrt
set(FLWROUTER 
src/routers/floydwarshall.h
src/routers/floydwarshall.cpp
)

#graphics
set(GRAPHICS
src/graphics/functions_interfaces.h #
src/graphics/free_and_shape.cpp
src/graphics/def_configurator.h     #
src/graphics/def_configurator.cpp
src/graphics/drawable_shapes.h      #
src/graphics/circles_and_text.cpp
src/graphics/other_shapes.cpp 
src/graphics/shape_modificators.h   #
src/graphics/shape_modificators.cpp
)
#svg_printers
set(SVGPR 
src/svg_printers/svg_printers.h
src/svg_printers/graph_printer.cpp
)

#console_gr_wgh_ach
set(CNSL_GWA
src/console_printers/graph_achive_border.h
src/console_printers/graph_achive_border.cpp
)

#console_deikstra
set(CNSL_DEIKSTRA
src/console_printers/deikstra_printer.h
src/console_printers/deikstra_printer.cpp
)


set(ASTAR 
  src/free/freefoo.h
  src/AStar/astardeclare.h
  src/AStar/astarsupport.h
  src/AStar/astarfoo.cpp
  src/AStar/astarmap.cpp
  src/AStar/designastar.cpp
          
)

set(INSTALL_TARGETS
graph
achiveabler
deikstrart
floyd_warshallrt
graphics
svg_printers
console_gr_wgh_ach
console_deikstra
AStar
)

set(LIB_HEADERS
src/AStar/astardeclare.h
src/AStar/astarsupport.h
src//free/structs.h
src/free/freefoo.h
src/graph/graph.h
src/achiveabler/achiveabler.h
src/routers/deikstrarouter.h
src/routers/floydwarshall.h
src/graphics/functions_interfaces.h #
src/graphics/def_configurator.h     #
src/graphics/drawable_shapes.h      #
src/graphics/shape_modificators.h   #
src/svg_printers/svg_printers.h
src/console_printers/graph_achive_border.h
src/console_printers/deikstra_printer.h
)


