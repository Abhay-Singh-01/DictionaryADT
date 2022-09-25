//-----------------------------------------------------------------------------
// Abhay Singh, abrsingh
// 2022 Spring CSE101 PA#7
// DictionaryTest.cpp
// Test harness for dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

   string s;
   string d;
   int x;
   string S[] = {"I", "like", "to", "eat", "burgers", "and", "fries"};
   string D[] = {"Hello", "my", "name", "is", "Bob"};

   Dictionary A;
   Dictionary B;
   Dictionary E;

   cout << endl;

   //insert some pairs into A
   for(int i=0; i<7; i++){
      A.setValue(S[i], i+2);
   }
   
   // call operator=()
   B = A;

   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;

   B.setValue("I", 100);
   B.setValue("fries", 101);

   for(int i=0; i<5; i++){
      E.setValue(S[i], i+1);
   }

   cout << "E.size() = " << E.size() << endl  << E << endl;

   if (E.hasCurrent()) {
      printf("E has current\n") ;
   } else {
      printf("E does not have current\n");
   }

   if (E.contains("Hello")) {
      printf("E contains Hello\n");
   } else {
      printf("E does not contain Hello\n");
   }

   if (E.contains("Yes")) {
      printf("E contains Yes");
   } else {
      printf("E does not contain Yes\n");
   }

   cout << endl;

   Dictionary C = B;

   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl;

   // check operator==()
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "E==A is " << (E==A?"true":"false") << endl;
   cout << "A==A is " << (A==A?"true":"false") << endl;
   cout << "C==A is " << (C==A?"true":"false") << endl << endl;

   //perform alterations on A
   cout << A.getValue("burgers") << endl;
   A.getValue("burgers") *= 150; // change the value associated with "happy"
   cout << A.getValue("burgers") << endl << endl;
   A.remove("I");
   A.remove("like");
   A.remove("to");

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << A.pre_string() << endl;

   //do forward iteration on B
   for(B.begin(); B.hasCurrent(); B.next()){
      s = B.currentKey();
      x = B.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;

   for(E.begin(); E.hasCurrent(); E.next()){
      s = E.currentKey();
      x = E.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;

   // do reverse iteration on C
   for(C.end(); C.hasCurrent(); C.prev()){
      s = C.currentKey();
      x = C.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;

   E.clear();

   cout << "E.size() = " << E.size() << endl  << E << endl;
   
   // check exceptions
   try{
      A.getValue("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.remove("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentKey();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentVal();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }  
   try{
      A.next();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.prev();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;  

   return( EXIT_SUCCESS );
}
