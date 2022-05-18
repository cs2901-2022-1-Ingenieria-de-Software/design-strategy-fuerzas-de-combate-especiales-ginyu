#ifndef FORECAST
#define FORECAST
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
using namespace std;


struct registro{
  char date[11], currency[4];
  float open, high, low, close, volume;
  
  void readCSVLine(string st);
}; 

void registro::readCSVLine(string st){
  sscanf(st.c_str(),"%[^,],%f,%f,%f,%f,%f,%[^,]", date, &open, &high, &low, &close, &volume, currency);
  //cout << "Open: " << open << endl;
}

vector<registro> readCSV(string stpath){
  ifstream file(stpath, ios::in);
  vector<registro> result;
  string temp;
  while (getline(file, temp))
  {
      registro reg;
      reg.readCSVLine(temp);
      result.push_back(reg);
  }
  file.close();
  return result;
}

struct CSV{
  CSV(string path){
    registros = readCSV(path);
  }
  vector<registro> registros;
};


class Strategy {
	protected:
		string csvName;
  
	public:
    Strategy(){}
  	Strategy(string _csvName): csvName(_csvName) {};
  	virtual void execute(){}
      //cout << "esta corriendo este execute";
    //}
};


class Aperture: public Strategy {
  public:
    Aperture(){}
  	Aperture(string _csvName): Strategy(_csvName) {};
  	
  	void execute() override{
      
      vector<registro> registros = readCSV(csvName);
      double suma = 0;
      
      for(auto reg: registros){
        //cout << "Open: " << reg.open << endl;
        suma += reg.open;
      }
      suma /= registros.size();
      cout << "Promedio de apertura: " << suma << endl;
    } 
};


class Closing: public Strategy {
  public:
  	Closing(string _csvName): Strategy(_csvName) {};
  	
  	void execute(){
      vector<registro> registros = readCSV(csvName);
      double suma = 0;
      
      for(auto reg: registros){
        suma += reg.close;
      }
      suma /= registros.size();
      cout << "Promedio de cierre: " << suma << endl;
    }
};

class Maximum: public Strategy {
  public:
    Maximum(string _csvName): Strategy(_csvName) {};
  	
  	void execute() override {
      vector<registro> registros = readCSV(csvName);
      double suma;
      
      for(int i=0; i <registros.size() && i < 100; ++i){
        suma = 0;
        for(int j=i; j < i+7; ++j)
          suma += registros[j+i].high;
        suma /= 7;
        std::cout << "Promedio de dia " << i+1 << " - " << i+8 << ": " << suma << std::endl;
      }
    }
};

class Forecast{
  private:
  	Strategy* strategy;

  public:
  	Forecast(){};
    
  	void setStrategy(Strategy* s){
      this->strategy = s;
    }
  
  	void strategyExecute() {
      //cout << "test";
      strategy->execute();
    }
};




#endif