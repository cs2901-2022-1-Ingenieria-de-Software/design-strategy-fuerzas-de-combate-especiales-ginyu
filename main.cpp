#include "forecast.h"

int main(){

    string s = "gold.csv";

    Forecast* f = new Forecast();

    Aperture* a = new Aperture(s);
    Closing* c = new Closing(s);
    Maximum* m = new Maximum(s);

    f->setStrategy(a);
    f->strategyExecute();

    f->setStrategy(c);
    f->strategyExecute();

    f->setStrategy(m);
    f->strategyExecute();

    delete f;
    delete a;
    delete c;
    delete m;
}