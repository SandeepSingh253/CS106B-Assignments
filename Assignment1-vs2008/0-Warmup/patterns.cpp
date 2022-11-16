#include<iostream>
#include<string>
using namespace std;

string spaceString(int);
void rhombus1(int size);
void rhombus2(int size);
void floydsT(int size);
void rightHalfDiamond(int width);

int main(){
    rhombus1(5);
    rhombus2(5);
    floydsT(4);
    void rightHalfDiamond(6);
    return 0;
}

void rhombus1(int size){
    for(int i=0;i<size;i++){
        cout<<spaceString(i);   
        for(int j=0;j<size;j++){
                cout<<"*";
        }
        cout<<endl;
   } 
   cout<<endl<<endl;
}

void rhombus2(int size){
   for(int i=0;i<size;i++){
        cout<<spaceString(size-i);   
        for(int j=0;j<size;j++){
                cout<<"*";
        }
        cout<<endl;
   } 
   cout<<endl<<endl;
}

void floydsT(int size){
    int num=1;
    for(int i=1;i<=size;i++){
        for(int j=0;j<i;j++){
            cout<<num<<" ";
            num++;
        }    
        cout<<endl;
    }
}

void rightHalfDiamond(int width){
    
    for(int i=1;i<=width;i++){
        cout<<spaceString(width-i);
        for(int j=0;j<i;j++){
           cout<<"*"; 
        }
        cout<<endl;
    }
    
}

string spaceString(int x){
    string spaces;
    while(x--)
    spaces+=" ";
    return spaces;
}