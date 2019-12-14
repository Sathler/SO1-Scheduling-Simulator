#include <bits/stdc++.h>

using namespace std;

int tempo_decorrido, tempo_final;

struct processo{
    int tempo_de_entrada;
    int cpu;
    int io;

    processo(int t, int cpu, int io){
        this->tempo_de_entrada = t;
        this->io = io;
        this->cpu = cpu;
    }

    processo(){

    }

    int getTempoFim(){
        return cpu + io + tempo_de_entrada;
    }

    int getTempoExecucao(){
        return cpu;
    }

    void print(){
        printf("%d %d %d\n", tempo_de_entrada, cpu, io);
    }

};

bool comp(list<processo> a, list<processo> b){
    if(a.front().cpu == 0){
        return false;
    }
    else if(b.front().cpu == 0){
        return true;
    }
    return a.front().tempo_de_entrada >= b.front().tempo_de_entrada;
}

priority_queue< list<processo>, vector< list <processo> >, decltype(&comp)> fifo_queue(&comp);

int main(){

    std::ifstream in("input.txt");
    std::streambuf *cinbuf = std::cin.rdbuf();
    std::cin.rdbuf(in.rdbuf());
    
    int cpu, io, val;
    string linha, bloco, tipo;
    processo executado;
    list<processo> executando;
    bool first;

    while(getline(cin, linha)){
        stringstream L(linha);
        cpu = 0; io = 0;
        list<processo> lista;
        first = true;
        while(getline(L, bloco, ',')){
            istringstream ss;
            ss.str(bloco);
            ss >> val >> tipo;
            if(tipo == "cpu"){
                if(!first){
                    processo leitura(0, cpu, io);
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
        processo leitura(0, cpu, io);
        lista.push_back(leitura);
        fifo_queue.push(lista);
    }
    tempo_decorrido = 0;
    tempo_final = 0;
    while(!fifo_queue.empty()){
        executando = fifo_queue.top();
        fifo_queue.pop();
        executado = executando.front();
        executado.tempo_de_entrada = tempo_decorrido = max(tempo_decorrido, executado.tempo_de_entrada);
        //executado.print();
        tempo_decorrido += executado.getTempoExecucao();
        //cout << "tempo total " << tempo_decorrido << endl; 
        executando.pop_front();
        tempo_final = max(tempo_final,executado.getTempoFim());
        if(!executando.empty()){
            executando.front().tempo_de_entrada = executado.getTempoFim();
            fifo_queue.push(executando);
        }
    }
    printf("Tempo Final: %d unidades de tempo", tempo_final);
}