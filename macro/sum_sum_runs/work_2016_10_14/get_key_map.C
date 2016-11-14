#include<fstream>
//key current
//key_modi switch back
void get_key_map(){
  gSystem->Load("libMyMpcEx.so");
  recoConsts* rc = recoConsts::instance();
  rc->set_IntFlag("RUNNUMBER",430013);
  MpcExMapper* mapper = MpcExMapper::instance();
  ofstream out_txt("key_to_key_map.txt");
  for(int i=0;i<128*24*16;i++){
    int key=i;
    int arm = mapper->get_arm(key);
    int packet = mapper->get_packet(key);
    int chain = mapper->get_chain(key);
    int key_modi=key;
    if(arm==0 && packet==7 && chain==0){
      key_modi=key+2304;
    }
    if(arm==0 && packet==7 && chain==3){
      key_modi=key-2304;
    }
    out_txt<<key<<" "<<key_modi<<endl;
  }
}
