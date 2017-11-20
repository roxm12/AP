#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ddt/ddt.h"
using namespace std;
using namespace rapidjson;

char * convert(char *str) {

    char *temp = strtok(str, ",");
    char *retStr = (char*)malloc(300);
    int i = 0;

    while (temp != NULL) {
        retStr[i] = atoi(temp);
        printf("%c", retStr[i]);
        temp = strtok(NULL, ",");
        i++;
    }
    //char nl = '\0';
    //strncat44(retStr, "\0",i);
    retStr[i] = '\0';
    printf("json is00000 %s\n", retStr);

    return retStr;
}
extern "C"{
void parse()
{
    enum category {none=0, ads = 1, drug = 2, gambling = 4, porn = 8 };
    FILE *f = NULL;
    char *json;
    char tempStr[600];
    char hostIp[20]="\0";
    char request_policy[20];
    char hw_addr[20] = "\0";
    int block_policy;
    int pre_block_policy;
    char ip_addr[20] = "\0";
    //    int is_block;

    int ads_block;
    int drug_block;
    int gambling_block;
    int porn_block;

    int ads_block2;
    int drug_block2;
    int gambling_block2;
    int porn_block2;



    f = fopen("test.json", "r");
    if (f != NULL)
    {
        fgets(tempStr, sizeof(tempStr), f);
    }
    fclose(f);
    printf("%s\n", tempStr);

    json = convert(tempStr);

    printf("%s\n", json);
    Document document;

    if (document.Parse(json).HasParseError())
    {
        perror("json Parsing error\n");
    }

    if (document.HasMember("hw_addr"))
    {
        string hwaddr = document["hw_addr"].GetString();
        strcpy(hw_addr, hwaddr.c_str());
        strcpy(hostIp,findIP(hw_addr));
    }


    if (document.HasMember("request_policy"))
    {
        string reqpol = document["request_policy"].GetString();
        strcpy(request_policy, reqpol.c_str());

        //      strcpy(request_policy, document["request_policy"].GetString());

        //장치 추가
        if (!strcmp(request_policy, "reg_host"))
        {
            //ddt 장치추가 함수 불러오기
            regDDT(hw_addr,none);
        }

        //장치 제거 함수
        else if (!strcmp(request_policy, "del_host"))
        {
            //ddt 장치제거함수
            deleteDDT(hw_addr);
        }

        //장치 맥주소 변경 함수
        else if (!strcmp(request_policy, "upd_host"))
        {
            //ddt 맥주소  변경 함수
        }

        //차단정책 변경
        else if (!strcmp(request_policy, "upd_Blist"))
        {
            block_policy = document["block_policy"].GetInt();
            pre_block_policy = document["pre_block_policy"].GetInt();

            ads_block = block_policy&ads;
            drug_block = block_policy&drug;
            gambling_block = block_policy&gambling;
            porn_block = block_policy&porn;

            ads_block2 = pre_block_policy&ads;
            drug_block2 = pre_block_policy&drug;
            gambling_block2 = pre_block_policy&gambling;
            porn_block2 = pre_block_policy&porn;


            if (ads_block2 == 0 && ads_block != 0)
            {
                //ads block 추가
                //여기서는 naver
                char command[100] = {"~/AP/shell/control/category_add.sh 0 "};
                strcat(command,hostIp);
                system(command);
            }
            else if (ads_block2 != 0 && ads_block == 0)
            {
                //ads block 삭제
                char command[100]={"~/AP/shell/control/category_del.sh 0 "};
                strcat(command,hostIp);
                system(command);
            }

            if (drug_block2 == 0 && drug_block != 0)
            {
                //drug block 추가
                char command[100]={"~/AP/shell/control/category_add.sh 1 "};
                strcat(command,hostIp);
                system(command);
            }
            else if (drug_block2 != 0 && drug_block == 0)
            {
                //drug block 삭제
                char command[100]={"~/AP/shell/control/category_del.sh 1 "};
                strcat(command,hostIp);
                system(command);
            }

            if (gambling_block2 == 0 && gambling_block != 0)
            {
                //gambling block 추가
                char command[100]={"~/AP/shell/control/category_add.sh 2 "};
                strcat(command,hostIp);
                system(command);
            }
            else if (gambling_block2 != 0 && gambling_block == 0)
            {
                //gambling block 삭제
                char command[100]={"~/AP/shell/control/category_del.sh 2 "};
                strcat(command,hostIp);
                system(command);
            }
           
            if (porn_block2 == 0 && porn_block != 0)
            {
                //porn block 추가
                char command[100]={"~/AP/shell/control/category_add.sh 3 "};
                strcat(command,hostIp);
                system(command);
            }
            else if (porn_block2 != 0 && porn_block == 0)
            {
                //porn block 삭제
                char command[100]={"~/AP/shell/control/category_del.sh 3 "};
                strcat(command,hostIp);
                system(command);
            }



            //*************해당 카테고리 룰을 iptables에 추가하는 명령어 넣기 ****************************
        }

        //ip 추가
        else if (!strcmp(request_policy, "add_ip"))
        {
            if (document.HasMember("ip_addr"))
            {
                string ipaddr = document["ip_addr"].GetString();
                strcpy(ip_addr, ipaddr.c_str());
                
                //*********해당 ip 차단하는 shell 실행하기
                char command[100]={"~/AP/shell/control/ip_add.sh "};
                strcat(command,hostIp);
                strcat(command," ");
                strcat(command,ip_addr);
                system(command);
            }
        }

        //ip 제거
        else if (!strcmp(request_policy, "del_ip"))
        {
            if (document.HasMember("ip_addr"))
            {
                string ipaddr = document["ip_addr"].GetString();
                strcpy(ip_addr, ipaddr.c_str());

                //****해당 ip 차단 취소하는 shel 실행하기************
                char command[100]={"~/AP/shell/control/ip_del.sh "};
                strcat(command,hostIp);
                strcat(command," ");
                strcat(command,ip_addr);
                system(command);
            }
        }

        //차단 해제할 때
        else if (!strcmp(request_policy, "unblock_ip"))
        {
            if (document.HasMember("ip_addr"))
            {
                string ipaddr = document["ip_addr"].GetString();
                strcpy(ip_addr, ipaddr.c_str());

                //해당 ip주소는 항상 통과시키는 shell 추가
                char command[100]={"~/AP/shell/control/ip_del.sh "};
                strcat(command,hostIp);
                strcat(command," ");
                strcat(command,ip_addr);
                system(command);
            }
        }

        //다시 차단 설정할 때
        else if (!strcmp(request_policy, "block_ip"))
        {
            if (document.HasMember("ip_addr"))
            {
                string ipaddr = document["ip_addr"].GetString();
                strcpy(ip_addr, ipaddr.c_str());

                //위에서 했던거 삭제하는 코드 만들기~
                char command[100]={"~/AP/shell/control/ip_add.sh "};
                strcat(command,hostIp);
                strcat(command," ");
                strcat(command,ip_addr);
                system(command);
            }
        }


    }

}
}



