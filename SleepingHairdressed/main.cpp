/*Аналогия основана на гипотетической парикмахерской с одним парикмахером. У парикмахера есть одно рабочее место и приёмная с несколькими стульями. Когда парикмахер заканчивает подстригать клиента, он отпускает клиента и затем идёт в приёмную, чтобы посмотреть, есть ли там ожидающие клиенты. Если они есть, он приглашает одного из них и стрижёт его. Если ждущих клиентов нет, он возвращается к своему креслу и спит в нём.
 Каждый приходящий клиент смотрит на то, что делает парикмахер. Если парикмахер спит, то клиент будит его и садится в кресло. Если парикмахер работает, то клиент идёт в приёмную. Если в приёмной есть свободный стул, клиент садится и ждёт своей очереди. Если свободного стула нет, то клиент уходит. Основываясь на наивном анализе, вышеупомянутое описание по идее должно гарантировать, что парикмахерская функционирует правильно с парикмахером, стригущим любого пришедшего, пока есть клиенты, и затем спящим до появления следующего клиента. На практике же существует несколько конфликтных ситуаций, которые иллюстрируют общие проблемы планирования.*/

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
vector<int> Chairs = {0,0,0,0,0};
mutex mtx,mtx1,mtx2;
int numOfClient = 0;
class CLIENTS {
public:
    int numOfCl = 0;
    CLIENTS(int& Number){
        numOfCl = Number;
    };
    
   // HAIRDRESSER hairDresser;
    
    int status = -2;
    
    void Cut() {
       // mtx.lock();
        hairDresser.statusHD = CUTTING;
        cout << "HD is cutting" << endl;
        status = CUTTING;
        this_thread::sleep_for(chrono::milliseconds(5000));
       // mtx.unlock();
    };
    
    void process() {
       
        if (hairDresser.statusHD == SLEEPING && find(Chairs.cbegin(), Chairs.cend(), 0)!=Chairs.cend()) {
            mtx.lock();
            Cut();
            if (find(Chairs.cbegin(), Chairs.cend(), 1) != Chairs.cend()) {
                cout << "1" << endl;
                for (int i =0;i<5;i++) {
                    cout << "2" << endl;
                    if(Chairs[i] == 1) {
                        cout << "3" << endl;
                        status = CUTTING;
                        Chairs[i] = 0;
                        break;
                    }
            }
            }
            else {
                cout << "4" << endl;
                hairDresser.statusHD = SLEEPING;
                cout << "HD is sleeping" << endl;
            }
            mtx.unlock();
        }
       
         if (find(Chairs.cbegin(), Chairs.cend(), 0)!=Chairs.cend() && hairDresser.statusHD != SLEEPING) {
             cout << "5" << endl;
            for (int i =0;i<5;i++) {
                cout << "6" << endl;
                if(Chairs[i] == 0) {
                    cout << "7" << endl;
                    status = SITTING;
                    break;
                }
            }
        }
         else {
             cout << "8" << endl;
            status = OUT;
         }
    };
   
};
int main() {
    vector <CLIENTS> vecOfClients = {};
    
    while(1) {
        numOfClient++;
        vecOfClients.push_back(CLIENTS(numOfClient));
        cout << "Came new client NUM = " << numOfClient << endl;
        vecOfClients[numOfClient].process();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    
  //  std::cout << "Hello, World!\n";
    return 0;
}
