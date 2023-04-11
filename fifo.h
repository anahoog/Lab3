#ifndef FIFO_H
#define	FIFO_H

template <typename T> class fifo {

    private:
        unsigned int N, cap;
        T * buffer;
        unsigned int inicio, fim;
    
    public:
        fifo(unsigned int max_itens){
            cap = max_itens;
	        N = 0;
	        inicio = 0;
            fim = 0;
            buffer = new T[cap];
        }
       
        ~fifo(){

        }
       
        void enfileira(const T & algo){
            if(not cheia()){
                buffer[fim]=algo;
                fim++;
                N++;    
                if(fim == cap) fim =0;
            }
            else{
                throw -1;
            }
        }
        
        T desenfileira(){
            if(not vazia()){
                T* desen=buffer[inicio];
                inicio ++;
                N--;
                    if(inicio==cap){
                        inicio=0;
                    }
                return desen;
            }
        }
        
        bool vazia() const{
            if(N==0){
    	        return true;
	        }
        }

        bool cheia() const{
            return N==cap;
        }
};

#endif	/* FIFO_H */
