#include<bits/stdc++.h>

using namespace std;

class A{
    public :

    virtual void print(){
        cout<<"Hello A"<<endl;
    }
};


class B : public A{
    public:
    void print(){
        cout<<"Hello B"<<endl;
    }
};

class C : public A{
    public:
    // void print(){
    //     cout<<"hello C"<<endl;
    // }
};



int main(){

    A *obj1 = new B();
    A *obj2 = new C();
    A *obj3 = new A();

    obj3->print();
    obj1->print();
    obj2->print();

    return 0 ;

}