#include "sjf.h"

typedef struct{ // struct para de processos
  int t_retorno;
  int t_resposta;
  int t_espera;

  int t_chegada;
  int t_pico;
  int t_termino;
  int t_restante;
} processo;

processo& menorProcesso(vector<processo>& VecProcessos, int tempo_atual){
  int indice_menor = -1;  // Índice do processo com menor tempo de pico
  int menor_tempo_pico = INT_MAX; // Inicializa com um valor grande

  for (int i = 0; i < VecProcessos.size(); i++) {
      if (VecProcessos[i].t_restante > 0 && VecProcessos[i].t_pico < menor_tempo_pico && VecProcessos[i].t_chegada <= tempo_atual) {
          menor_tempo_pico = VecProcessos[i].t_pico;
          indice_menor = i;
      }
  }

  if (indice_menor != -1) {
      return VecProcessos[indice_menor];  // Retorna o processo com menor tempo de pico
  } else {
      throw std::runtime_error("Nenhum processo restante encontrado.");  // Lida com o caso onde não há processos com t_restante > 0
  }
  
}

void sjf(void){

  vector<processo> processos; // vetor de processos
  processo auxiliar; // auxiliar para processos

  ifstream file( "processos.txt" ); // lendo arquivo
  if(!file){
    cerr <<"Erro ao abrir o arquivo" << endl;
  }

  while(file >> auxiliar.t_chegada >> auxiliar.t_pico){ 
    processos.push_back(auxiliar); // armazenando processos
  }

  file.close();
  
  int tempo_total_exec = 0;
  
  for(int i = 0; i < processos.size(); i++){
    tempo_total_exec += processos[i].t_pico;
    processos[i].t_restante = processos[i].t_pico;
  }
  
  
  int tempo_atual = 0;
  for( ;tempo_atual < tempo_total_exec; tempo_atual++){
    processo& processo_atual = menorProcesso(processos,tempo_atual);
    
    processo_atual.t_restante--;
  
    if(processo_atual.t_restante == 0){
      processo_atual.t_termino = tempo_atual + 1;
      cout << "Processo terminou em: " << processo_atual.t_termino << endl;
    }
  }
  /*
  for(int i=0; i<processos.size(); i++){
    cout << "Processo " << i+1 << ": " << endl;
    cout << "\tT chegada: " << processos[i].t_chegada << endl;
    cout << "\tT pico: " << processos[i].t_pico << endl;
    cout << "\tT termino: " << processos[i].t_termino << endl;
  }
  */
}
 //cout << "Tempo restante do processo: " << processo_atual.t_restante << endl;