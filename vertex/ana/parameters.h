#ifndef GLOBAL_PARAMETERS_LOADED
#define GLOBAL_PARAMETERS_LOADED

// histos and parameters
#include "../src/common_info.h"

// analysis classes
#include "vertex.h"

// global variables
std::string DATA_PRINT = ".png";
std::string SIM_PRINT  = "_gsim.png";
std::string PRINT  = "none";

bool is_simulation = false;

const std::string data_pars_file = "vertex_par.txt";
const std::string gsim_pars_file = "vertex_par_gsim.txt";
const std::string data_root_file = "data_vertex.root";
const std::string gsim_root_file = "gsim_vertex.root";
std::string data_label     = "data";

// common histogram
chistos *H    = nullptr;
cpars   *Pars = nullptr;

// analysis classes - cannot be local to vertex.C
Vertex_CS *VertexCS = nullptr;

const int csize = 1200;   // common canvas size


#endif

