#ifndef FIFO_H
#define	FIFO_H

template <typename T, int cap> class fifo {

    private:
        unsigned int N;
        T buffer[cap];
        unsigned int inicio, fim;
    
    public:
        fifo(){
	        N = 0;
	        inicio = 0;
            fim = 0;
        }
       
        ~fifo(){

        }
       
        void enfileira(const T & algo){
            if(!cheia()){
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
            T desen;
            if(!vazia()){
                desen=buffer[inicio];
                inicio ++;
                N--;
                    if(inicio==cap){
                        inicio=0;
                    }
            }
            return desen;
        }
        
        bool vazia() {
            if(N==0){
    	        return true;
	        }else{
                return false;
            }
        }

        bool cheia() const{
            return N==cap;
        }

    void enfileira_uart(const T & algo){
        buffer[fim]=algo;
        fim++;

            if(!cheia()){
                N++;       
            }
            else{
                inicio++;
            }
            if(inicio == cap) inicio=0;
            if(fim == cap) fim =0;
        }

};

#endif	/* FIFO_H */
