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
    
    for (int i = 0; i < VecProcessos.size(); i++) { // Percorre o vetor de processos em busca do menor tempo de pico
        if (VecProcessos[i].t_restante > 0 && VecProcessos[i].t_pico < menor_tempo_pico && VecProcessos[i].t_chegada <= tempo_atual) {
            menor_tempo_pico = VecProcessos[i].t_pico;
            indice_menor = i;
        }
    }

    if (indice_menor != -1) {
        return VecProcessos[indice_menor];  // Retorna o processo com menor tempo de pico
    }else {
        static processo vazio;
        vazio.t_restante = 0;
        return vazio; // Lida com o caso onde não há processos com t_restante > 0
    }
}

void sjf(void){
    
    vector<processo> processos; // Vetor de processos
    processo auxiliar; // Auxiliar para processos
    
    ifstream file( "processos.txt" ); // Lendo arquivo
    
    if(!file){
        cerr <<"Erro ao abrir o arquivo" << endl;
        return;
    }
    
    while(file >> auxiliar.t_chegada >> auxiliar.t_pico){ 
        processos.push_back(auxiliar); // Armazenando processos
    }
    
    file.close();
    
    int tempo_total_exec = 0;
    
    for(int i = 0; i < processos.size(); i++){
        tempo_total_exec += processos[i].t_pico;       // Calcula o tempo total de exec
        processos[i].t_restante = processos[i].t_pico; // Iguala o tempo restante ao tempo de pico
    }

    int tempo_atual = 0;
    size_t index = 0; // Um contador de processos
    
    while(tempo_atual < tempo_total_exec){
        
        while (index < processos.size() && processos[index].t_chegada <= tempo_atual) { // A cada processo chegado aumenta o index
            index++;
        }
        
        processo& processo_atual = menorProcesso(processos,tempo_atual); // Procura o menor processo e armazena em processo_atual
        
        if (processo_atual.t_restante == 0) { // Se o processo retornado é fictício, ou seja o processo_atual retornou o processo
            if (index < processos.size()) {  //  vazio com t_restante = 0
                tempo_atual = processos[index].t_chegada;
                continue;
            }
            break;
        }
        processo_atual.t_resposta = tempo_atual - processo_atual.t_chegada;
        
        tempo_atual += processo_atual.t_restante;
        processo_atual.t_restante = 0;
        processo_atual.t_termino = tempo_atual;
        
        processo_atual.t_retorno = processo_atual.t_termino - processo_atual.t_chegada;
        processo_atual.t_espera = processo_atual.t_termino - processo_atual.t_chegada - processo_atual.t_pico; // ou
        //processo_atual.t_espera = processo_atual.t_retorno - processo_atual.t_pico;

    }
    
    // Imprimindo resultados
    float espera_med, retorno_med, resposta_med;
    espera_med = retorno_med = resposta_med = 0;
    
    for(int i=0; i<processos.size(); i++){
        espera_med+= processos[i].t_espera;
        retorno_med+= processos[i].t_retorno;
        resposta_med+= processos[i].t_resposta;
    }
    cout << fixed << setprecision(1);
    cout << "SJF " << retorno_med/processos.size() <<" " << resposta_med/processos.size() << " " << espera_med/processos.size() << endl;
}
