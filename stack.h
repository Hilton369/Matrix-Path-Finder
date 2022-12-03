#ifndef STACK_H
#define STACK_H
#include <iostream>


template <typename T>
class stack{

    private:

        struct node{
            T data;
            node* next;
        };
        node * top;

    public:
        stack(){
            top = nullptr;
        }

        T pop(){
            T ret = peek();
            node * to_del = top;
            top = top->next;
            delete to_del;
            return ret;
        }

        void push(T x){
            top = new node{x, top};
        }

        T peek(){
            if(isEmpty()){
                std::cout << "STACK IS EMPTY" << std::endl;
                //exit(1);
            }
            return top->data;
        }

        bool isEmpty(){
            return top == nullptr;
        }

};

#endif