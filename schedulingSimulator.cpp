#include <bits/stdc++.h>

#define processo list<blocoProcesso>

using namespace std;

int tempo_decorrido, tempo_final;

struct blocoProcesso{
    int id;
    int tempo_de_entrada;
    int cpu;
    int io;

    blocoProcesso(int t, int cpu, int io, int id){
        this->tempo_de_entrada = t;
        this->io = io;
        this->cpu = cpu;
        this-> id = id;
    }

    blocoProcesso(){

    }

    int getTempoFim(){
        return cpu + io + tempo_de_entrada;
    }

    int getTempoExecucao(){
        return cpu;
    }

    void print(){
        printf("%d %d %d %d\n", tempo_de_entrada, cpu, io, id);
    }

};


//implementacao da politica de escalonamento FIFO através de uma priority queue
//utilizando o tempo de entrada como criterio de seleção
bool comp(processo a, processo b){
    if(a.front().cpu == 0){
        return false;
    }
    else if(b.front().cpu == 0){
        return true;
    }
    if(a.front().tempo_de_entrada == b.front().tempo_de_entrada) return a.front().id > b.front().id;
    return a.front().tempo_de_entrada > b.front().tempo_de_entrada;
}

//
priority_queue< processo, vector<processo>, decltype(&comp)> fifo_queue(&comp);

int main(){

    //mudando a entrada padrão para um arquivo de texto
    //std::ifstream in("input.txt");
    //std::streambuf *cinbuf = std::cin.rdbuf();
    //std::cin.rdbuf(in.rdbuf());
    
    int cpu, io, val, count = 0;
    string linha, bloco, tipo;
    blocoProcesso executado;
    processo executando;
    bool first;


    //leitura 
    while(getline(cin, linha)){
        count++;
        stringstream L(linha);
        cpu = 0; io = 0;
        processo lista;
        first = true;
        while(getline(L, bloco, ',')){
            istringstream ss;
            ss.str(bloco);
            ss >> val >> tipo;
            if(tipo == "cpu"){
                if(!first){
                    blocoProcesso leitura(0, cpu, io, count);
                    lista.push_back(leitura);
                }
                io = 0;
                cpu = val;
            }
            else{
                io += val;
            }
            first = false;
        }
        blocoProcesso leitura(0, cpu, io, count);
        lista.push_back(leitura);
        fifo_queue.push(lista);
    }


    //simulando a execução dos processos
    tempo_decorrido = 0;
    tempo_final = 0;
    while(!fifo_queue.empty()){
        executando = fifo_queue.top();
        fifo_queue.pop();
        executado = executando.front();
        executado.tempo_de_entrada = tempo_decorrido = max(tempo_decorrido, executado.tempo_de_entrada);
        executado.print();
        tempo_decorrido += executado.getTempoExecucao();
        cout << "tempo total " << tempo_decorrido << endl; 
        executando.pop_front();
        tempo_final = max(tempo_final,executado.getTempoFim());
        if(!executando.empty()){
            executando.front().tempo_de_entrada = executado.getTempoFim();
            fifo_queue.push(executando);
        }
    }
    printf("Tempo Final: %d unidades de tempo", tempo_final);
}