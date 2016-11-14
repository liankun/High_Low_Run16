#include<fstream>
#include<map>
void get_hl_db(){
  double slope[128*24*16]={0.};
  double slope_er[128*24*16]={0.};
  double intercept[128*24*16]={0.};
  double intercept_er[128*24*16]={0.};

  map<int,int> key_key;

  int key;
  int key_switch;
  ifstream in_txt1("key_to_key_map.txt");
  while(in_txt1>>key>>key_switch){
    key_key.insert(pair<int,int>(key,key_switch));
  }

  double slp;
  double slp_er;
  double itcpt;
  double itcpt_er;
  double ci2;
  int nf;

  ifstream in_txt("../work_2016_10_12/fitting_information_50_150.txt");
  while(in_txt>>key>>slp>>slp_er>>itcpt>>itcpt_er>>ci2>>nf){
/*
    cout<<key<<" "<<key_key[key]<<" "
        <<slp<<" "<<slp_er<<" "
	<<itcpt<<" "<<itcpt_er<<" "
	<<ci2<<" "<<nf
	<<endl;
*/    
    int org_key = key_key[key];
//    org_key=key;
    slope[org_key] = slp;
    slope_er[org_key] = slp_er;
    intercept[org_key] = itcpt;
    intercept_er[org_key] = itcpt_er;
  }

  ofstream out_txt("Low_High_ratio_origin.txt");
  for(int i=0;i<128*24*16;i++){
    if(slope[i] > 0){
      out_txt<<i<<" "
             <<slope[i]<<" "<<slope_er[i]<<" "
             <<intercept[i]<<" "<<intercept_er[i]<<" "
	     <<-9999.9<<" "<<-9999.9<<endl;
              
    }
    else{
      out_txt<<i<<" "
             <<-9999.9<<" "<<-9999.9<<" "
             <<-9999.9<<" "<<-9999.9<<" "
	     <<-9999.9<<" "<<-9999.9<<endl;
    }
  }
}
