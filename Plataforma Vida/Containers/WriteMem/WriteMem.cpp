#include "WriteMem.h"
#include "../test_struct.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <sstream>
#include <utility>  
#include <math.h>
#include <ctime>
#include <wiringPi.h>
#include <vector>

using namespace std;

wiringPiSetup();

WriteMem::WriteMem()
{
    
    
    this->data = new PosixShMem("SH_MEM",sizeof(TIMESTAMPED_TEST_DATA));
    this->startActivity();
}

WriteMem::~WriteMem()
{
    this->stopActivity();
}

void WriteMem::startActivity()
{
    ThreadBase::startActivity();
}

void WriteMem::stopActivity()
{
    ThreadBase::stopActivity();
    std::cout << "WRITE" << std::endl;
}

int WriteMem::run()
{

    ReadFiles("M");
    
    this->is_running = 1;
    this->is_alive = 1;
    this->tim1.tv_sec = 0;
    this->tim1.tv_nsec = 500000000L;//20Hz

    TIMESTAMPED_TEST_DATA my_data;
    int my_cont = -1;                           //contador de processos na maquina.
    int cont=0;                                 //controle do if.
    double velocity_angular;                    //Salva o valor da velocidade angular.

    void pinMode(PINOSENSOR, INPUT);

    clock_t t1, t0,t3;                          //Variáveis para manipulação de tempo.
    double t2;                                      
    int parametro=1;                            //parametro de permissão para calcular o tempo e a velocidade angular.
    t0=clock();
    t1=clock();



    while(this->is_alive)
    {   
               
        if(digitalRead(PINOSENSOR)==HIGH){
           t1=clock() +t1;
            //cout<<"t0: "<<t0<<endl;                                      //Incrementação do tempo de execução quando o encoder retorna o valor 1.
            //t0=t1;
            parametro=1;
        }else if(digitalRead(PINOSENSOR)==LOW){
            
    int my_cont = -1;
    int cont=0;
    double velocity_angular;
    clock_t t1, t0,t3,t6,t7;
    double t2;
    int parametro=1;
    t6=clock();
    t6= difftime(t6,t6);
    t0=clock();
    t0= difftime(t0,t0);
    cout<<"t0: "<<t0<<endl;
    while(this->is_alive)
    {   
        
        if(cont<cont_aux){
            
        if(Vetor_velocidades[cont]==1){
            
            t1=clock() -t6;
            
            cout<<"t1: "<<t1<<endl;
            parametro=1;
        }else if(Vetor_velocidades[cont]==0){
            
            t6=clock() -t1;
            cout<<"t6: "<<t6<<endl;
            //t6= clock() -t1;
            if(parametro==1){
                t3=difftime(t1, t0);
                 //double( clock() - startTime ) / (double)CLOCKS_PER_SEC       // Calculo da Velocidade angular quando o encoder para de retornar o valor 1.
                t2= ((double)t3)/(double)CLOCKS_PER_SEC;
                //t2= road_time() - my_data.t5;
                velocity_angular= (0.17453/t2);
                t0=clock() + t1;
                
                
                t3=difftime(t1, t0);
                 //double( clock() - startTime ) / (double)CLOCKS_PER_SEC
                t2= ((double)t3)/(double)CLOCKS_PER_SEC;
                velocity_angular= (0.17453/t2);
                t0=t1;
                cout<<"t0: "<<t0 <<endl; 
            }
            
            my_data.time1 = t2;
            my_data.velocidade = velocity_angular*5;                               //Transformando a velocidade angular em velocidade linear.
            parametro=0;
           
        } 
       
        else{

            my_data.velocidade = 0;                                                 //Quando não é retornado nenhum valor do encoder o valor atribuido à velocidade é zero.
        }
            my_data.data.contador = my_cont++;
            this->data->write(&my_data, sizeof(TIMESTAMPED_TEST_DATA));             //Escreve os valores de velocidade linear na memoria compartilhada.
            //std:: cout<< "Escrita"<< std:: endl;
            nanosleep(&this->tim1, &this->tim2);
       
       
    }
    this->is_running = 0;
    pthread_exit(NULL);
    
    return EXIT_SUCCESS;
}
