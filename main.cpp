#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include "main.h"

using namespace std;
int index = 0;

vector<string> mem;

int main(){

    bool exit = true;
    init();
    // cout<<mem[1];
Start:
    cout << "\n~~목록~~\n\n";
    showList();
    
    cout << "\n <새로운 메모 : N, 나가기 : Q";
    if(index == 0){
        goto Init;
    }

    cout << ", 접근할 메모 : (숫자 입력)";
    
Init:
    cout << ">" << endl;

    string input;
    while(1){
        cout << "입력 : ";
        cin  >> input;
        if(input == "N" || input == "n"){
            newMemo();
        }else if(input == "Q" || input == "q"){
            return 0;
        }else{            
            openMemo(stoi(input));
        }
        cout<<"\n-------------------------------------\n\n\n\n";
        goto Start;
    }

    return 0;
}

void showList(){
    index = 0;

    ifstream ifs;
    ifs.open("titles.txt");

    string line;

    while(getline(ifs,line)){
        cout << index + 1 << ". " << line << endl;
        index++;
    }    

    ifs.close();
}

void newMemo(){
    
    char c;
    ofstream ofs;

    string m_title;
    cout << "제목 : ";
    c = getchar();
    getline(cin, m_title);  
    ofs.open("titles.txt", ios_base::out | ios_base::app);
    ofs << m_title << "\n";
    ofs.close();

    mem.push_back(m_title);

    string content;
    cout << "내용 : ";
    getline(cin, content);

    string to_open = m_title + ".txt"; 
    ofs.open(to_open);
    ofs << content;
    ofs.close();

    string pwd="";
    char set_pwd;    

    cout << "비밀번호 설정하시겠습니까? <Y/N>: ";    
    while(1){
        cin  >> set_pwd;
        if(set_pwd == 'N' || set_pwd == 'n'){
            break;
        }else if(set_pwd == 'Y' || set_pwd == 'y'){
            cout << "비밀번호를 입력해주세요 (공백제외) : ";
            cin  >> pwd;
            break;
        }else{
            cout << "비밀번호 설정하시겠습니까? <Y/N>: ";
        }
    }

    ofs.open("pwd.txt", ios_base::out | ios_base::app);    
    ofs << pwd << "\n";
    ofs.close();
}

void openMemo(int num){

    ofstream ofs;
    ifstream ifs;
    string line;
    
    ifs.open("pwd.txt");
    for(int x=0; x<num; x++){
        getline(ifs, line);        
    }
    ifs.close();

    if(line != ""){
        cout << "비밀번호 : ";
        string passkey;
        cin  >> passkey;

        if(line != passkey){
            cout << "틀린 비밀번호!\n\n";
            return;
        }
    }
        

    string to_open = mem[num] + ".txt";    
    ifs.open(to_open);

    cout<<"\n-------------------------------------\n";
    cout<<"\n";    
    while(getline(ifs,line)){
        cout<< line << endl;        
    }  

    ifs.close();
    ofs.close();
}

void init(){

    mem.push_back("0");

    ifstream ifs;
    ifs.open("titles.txt");

    string line;
    while(getline(ifs,line)){        
        index++;
        mem.push_back(line);
    }    

    ifs.close();
}