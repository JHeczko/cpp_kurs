#include <iostream>
#include <string>
#include <memory>

using namespace std;

//===========DISPLAY DRIVER==============
class DisplayDrv{
    public:
        virtual void wykonaj() = 0;
        virtual ~DisplayDrv(){};
};

//=============PRINTER DRIVER============
class PrinterDrv{
    public:
        virtual void wykonaj() = 0;
        virtual ~PrinterDrv(){};
};

//========LOW RES DRIVERS=========
class LowResPrinter : public PrinterDrv{
    public:
        void wykonaj() override{
            cout << "LowResPrinter\n";
        };
};
class LowResDisplay : public DisplayDrv{
    public:
        void wykonaj() override{
            cout << "LowResDisplay\n";
        };
};

//=========HIGH RES DRIVERS========
class HighResPrinter : public PrinterDrv{
    public:
        void wykonaj() override{
            cout << "HighResPrinter\n";
        };
};

class HighResDisplay : public DisplayDrv{
    public:
        void wykonaj() override{
            cout << "HighResDisplay\n";
        };
};

//================ABSTRACT FACTORIES===============

class ResFactory{
    public:
        virtual unique_ptr<DisplayDrv> getDispDrv() = 0;
        virtual unique_ptr<PrinterDrv> getPrintDrv() = 0;
        virtual ~ResFactory(){};
};

class LowResFactory : public ResFactory{
    public:
        virtual unique_ptr<DisplayDrv> getDispDrv() override{
            unique_ptr<DisplayDrv> ptr(new LowResDisplay);
            return ptr;
        };

        virtual unique_ptr<PrinterDrv> getPrintDrv() override{
            unique_ptr<PrinterDrv> ptr(new LowResPrinter);
            return ptr;
        };
};

class HighResFactory : public ResFactory{
    public:
        virtual unique_ptr<PrinterDrv> getPrintDrv() override{
            unique_ptr<PrinterDrv> ptr(new HighResPrinter);
            return ptr;
        };

        virtual unique_ptr<DisplayDrv> getDispDrv() override{
            unique_ptr<DisplayDrv> ptr(new HighResDisplay);
            return ptr;
        };
};


int main() {
unique_ptr<ResFactory> fabryka(new LowResFactory);
unique_ptr<DisplayDrv> ddrv = fabryka->getDispDrv(); 
unique_ptr<PrinterDrv> pdrv = fabryka->getPrintDrv(); 
ddrv->wykonaj();
pdrv->wykonaj();
fabryka.reset(new HighResFactory);
ddrv = fabryka->getDispDrv();
pdrv = fabryka->getPrintDrv(); 
ddrv->wykonaj();
pdrv->wykonaj();
}