#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__

#include <iostream>
#include <vector>
#ifdef CONFIGURE_DLL
    #define CONFIGURE_EXPORT __declspec(dllexport)
#else
    #define CONFIGURE_EXPORT __declspec(dllimport)
#endif


//虚基类,用户只知道这个类
class CONFIGURE_EXPORT ExportConfigure
{
public:

    virtual ~ExportConfigure() = default; //调用默认虚析构,以支持多台
    virtual int addItem(std::string  str)=0;
    virtual std::string  getItem(int index)=0;
    virtual int getSize() const =0;
};



//内部实现类,不向外暴露
class Configure : public ExportConfigure
{
public:
    Configure() = default;
    Configure(const std::vector<std::string>& items);
    ~Configure() = default;
    int addItem(std::string  str) override;
    std::string  getItem(int index) override;
    int getSize() const override;
private:
    std::vector<std::string> m_vItems;
};


extern  "C" CONFIGURE_EXPORT ExportConfigure *getClassObj();
extern  "C" CONFIGURE_EXPORT void releaseClassObj(ExportConfigure *);


#endif // __CONFIGURE_H__