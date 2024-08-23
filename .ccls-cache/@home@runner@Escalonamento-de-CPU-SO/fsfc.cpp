#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef struct{ // struct para de processos
  int t_retorno;
  int t_resposta;
  int t_espera;

  int t_chegada;
  int t_exec;
} processo;