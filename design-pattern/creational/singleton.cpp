#include <iostream>

using namespace std;

/*
 *  考虑多线程的Singleto实现方式，用局部静态变量也可以实现单例模型。
 *  单例模型就是解决创建对象时，只用维护一个对象的情况。
 */

class Singleton
{
public:
    static Singleton* getInstance(); //静态函数 
private:
    Singleton();
    virtual ~Singleton(); //虚析构函数 
    static Singleton* m_pInstance;
    int var;
};

Singleton* Singleton::m_pInstance = NULL;

Singleton* Singleton:: getInstance()
{
    if (NULL == m_pInstance) //良好的编程习惯 
    {
        static Singleton p; //局部静态变量，可以多线程并发操作 
        m_pInstance = &p;
    }
    return m_pInstance; 
}

Singleton::Singleton() { var = 2; }

Singleton::~Singleton() {} //在外面是不用加virtual修饰符的 
