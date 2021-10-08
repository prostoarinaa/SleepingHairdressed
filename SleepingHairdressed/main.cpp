/*Аналогия основана на гипотетической парикмахерской с одним парикмахером. У парикмахера есть одно рабочее место и приёмная с несколькими стульями. Когда парикмахер заканчивает подстригать клиента, он отпускает клиента и затем идёт в приёмную, чтобы посмотреть, есть ли там ожидающие клиенты. Если они есть, он приглашает одного из них и стрижёт его. Если ждущих клиентов нет, он возвращается к своему креслу и спит в нём.Каждый приходящий клиент смотрит на то, что делает парикмахер. Если парикмахер спит, то клиент будит его и садится в кресло. Если парикмахер работает, то клиент идёт в приёмную. Если в приёмной есть свободный стул, клиент садится и ждёт своей очереди. Если свободного стула нет, то клиент уходит. Основываясь на наивном анализе, вышеупомянутое описание по идее должно гарантировать, что парикмахерская функционирует правильно с парикмахером, стригущим любого пришедшего, пока есть клиенты, и затем спящим до появления следующего клиента. На практике же существует несколько конфликтных ситуаций, которые иллюстрируют общие проблемы планирования.*/

#include <iostream>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <semaphore>
#include <chrono>
#include <thread>

#define SITTING 0
#define SLEEPING 0
#define CUTTING 1
#define OUT -1
struct HAIRDRESSER{
    int statusHD = SLEEPING;
};
HAIRDRESSER hairDresser;

using namespace std;
//vector<int> Chairs = {0,0,0,0,0};
mutex seat,client,barber;
int numOfClient = 0;
int clienstsWait = 0;
class CLIENTS {
public:
    
    int numOfCl = 0;
    CLIENTS(int& Number){
        numOfCl = Number;
    };
    CLIENTS(){
        numOfCl = -10;
    };
    
   // HAIRDRESSER hairDresser;
    
    int status = -2;
    
    void Cut() {
       // mtx.lock();
        hairDresser.statusHD = CUTTING;
        cout << "HD is cutting" << endl;
        status = CUTTING;
        this_thread::sleep_for(chrono::milliseconds(5000));
        cout << "HD finished cutting" << endl;
       // mtx.unlock();
    };
    void Sleep() {
        
        cout << "HD is sleeping" << endl;
        hairDresser.statusHD = SLEEPING;
    };
    
    void processHD() {
        this_thread::sleep_for(chrono::milliseconds(4000));
        while(true) {
                Sleep();
               // seat.lock();
            if(clienstsWait != 0) {
                    seat.lock();
                    clienstsWait--;
                    barber.lock();
                    Cut();
                    barber.unlock();
                    seat.unlock();
                }
              }
    };
    void processCL() {
          while(true) {
              this_thread::sleep_for(chrono::milliseconds(4000));
             //   seat.lock(); // Эта строка не должна быть здесь
                if(clienstsWait < 5) {
                      clienstsWait++;
                    cout << "wait, there are =" <<clienstsWait<< endl;
                   //   client.lock();
                  //    seat.unlock();
                   //   barber.lock();
                } else {
                 //   cout << "out" << endl;
                    //  seat.unlock();
                }
          }
    };

//        if (hairDresser.statusHD == SLEEPING && find(Chairs.cbegin(), Chairs.cend(), 0)!=Chairs.cend()) {
//            mtx.lock();
//            Cut();
//            if (find(Chairs.cbegin(), Chairs.cend(), 1) != Chairs.cend()) {
//                cout << "1" << endl;
//                for (int i =0;i<5;i++) {
//                    cout << "2" << endl;
//                    if(Chairs[i] == 1) {
//                        cout << "3" << endl;
//                        status = CUTTING;
//                        Chairs[i] = 0;
//                        break;
//                    }
//            }
//            }
//            else {
//                cout << "4" << endl;
//                hairDresser.statusHD = SLEEPING;
//                cout << "HD is sleeping" << endl;
//            }
//            mtx.unlock();
//        }
//
//         if (find(Chairs.cbegin(), Chairs.cend(), 0)!=Chairs.cend() && hairDresser.statusHD != SLEEPING) {
//             cout << "5" << endl;
//            for (int i =0;i<5;i++) {
//                cout << "6" << endl;
//                if(Chairs[i] == 0) {
//                    cout << "7" << endl;
//                    status = SITTING;
//                    break;
//                }
//            }
//        }
//         else {
//             cout << "8" << endl;
//            status = OUT;
//         }
//    };
//    void processCL() {
//
//    };
};

int main() {
    vector <CLIENTS> vecOfClients = {};
    CLIENTS barber;
    thread tHD([&]() {
        barber.processHD();
    });
    thread tCL([&]() {
        vecOfClients[numOfClient].processCL();
        numOfClient++;
        cout << "Came new client NUM = " << numOfClient << endl;
        
        vecOfClients.push_back(CLIENTS(numOfClient));
        
    });
//    while(1) {
//        //CLIENTS barber;
//      //  numOfClient++;
//       // vecOfClients.push_back(CLIENTS(numOfClient));
//    //    cout << "Came new client NUM = " << numOfClient << endl;
//
//
//        this_thread::sleep_for(chrono::milliseconds(1000));
//    }
    tHD.join();
    tCL.join();
  //  std::cout << "Hello, World!\n";
    return 0;
}
