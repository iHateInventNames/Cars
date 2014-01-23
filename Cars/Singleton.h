#pragma once

template<class T>
class Singleton
{
    Singleton(Singleton const&); 
    Singleton& operator=(Singleton const&); 
    T& operator=(T const&); 

protected:
    Singleton()
    {}

    virtual ~Singleton()
    {}

public:
    static T& Instance()
    {
        static T t;
        return t;
    }

};

