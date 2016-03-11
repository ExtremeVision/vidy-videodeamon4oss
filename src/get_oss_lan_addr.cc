#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "cJSON/cJSON.h"

int main(int argc,char* argv[]){
  FILE *pp;
  char json_string[5*BUFSIZ];
  char command[2048];
  sprintf(command,"curl http://i.extremevision.com.cn/v2/all-cameras?access-token=733ZO5TjbI2Byurga8EY_JMjbBcnxJr4\'&\'cid=%s &",argv[1]);
  if (NULL != (pp = popen(command, "r"))){
      fread(json_string,sizeof(json_string), 1, pp);
      //std::cout<<json_string<<std::endl;
  }else{
      pclose(pp);
      std::cout<<"0"<<std::endl;
      return 0;
  }
  pclose(pp);
  cJSON* pJson = cJSON_Parse(json_string);
  if(NULL==pJson){
    std::cout<<"0"<<std::endl;
    return 0;
  }
  cJSON* pSub = cJSON_GetObjectItem(pJson,"lan_addr");
  if(NULL == pSub){
    std::cout<<"0"<<std::endl;
    return 0;
  }
  if(!pSub->valuestring){
    std::cout<<"0"<<std::endl;
    return 0;
  }
  std::cout<<pSub->valuestring<<std::endl;
  return 1;
}
