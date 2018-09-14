class CBase
{
  private:
    int privateBase;
  protected:
    int protBase;
  public:
    int pubBase;
};
//----------------------private - наследование -------------------------------

class CDerived : private CBase
{
  //унаследованные данные класса
  //недоступно:
  // int privateBase;
  //private:
  // int protBase;
  //private:
  // int pubBase;

  public:
    void updateDerived()
    {
      //privateBase=0; //нельзя доступиться к private данным CBase
      protBase=0;
      pubBase=0;
    }
};

class CDerived1 : public CDerived
{
  public:
    void updateDerived1()
    {
      //privateBase=1; //нельзя доступиться 
                       //к private данным CBase
      //protBase=1;//protBase недоступно, 
                   //потому что CDerived использовал 
                   //private при наследовании от CBase
      //pubBase=1; //pubBase недоступно, потому что 
                   //CDerived использовал private 
                   //при наследовании от CBase
 }
};
CDerived dd;
//dd.privateBase=3; недоступно
//dd.protBase=3; недоступно
//dd.pubBase=3; недоступно
//-------------------------- public - наследование-----------------------------------

class CDerived : public CBase
{
  //унаследованные данные класса
  //недоступно:
  // int privateBase;
  //protected:
  // int protBase;
  //public:
  // int pubBase;

  public:
    void updateDerived()
    {
      //privateBase=0; //нельзя доступиться к 
                       //private данным CBase
      protBase=0;
      pubBase=0;
    }
};

class CDerived1 : public CDerived
{
  public:
    void updateDerived1()
    {
      //privateBase=1; //нельзя доступиться к 
                       //private данным CBase
      protBase=1;
      pubBase=1; 
    }
};


CDerived dd;
//dd.privateBase=3;
//dd.protBase=3;
dd.pubBase=3; //pubBase остался с уровнем доступа public, 
              //к нему теперь можно доступиться.
//-------------------------- protected - наследование-----------------------------------
class CDerived : protected CBase
{
  //унаследованные данные класса
  //недоступно:
  // int privateBase;
  //protected:
  // int protBase;
  //protected:
  // int pubBase;

  public:
    void updateDerived()
    {
      //privateBase=0; //нельзя доступиться к 
                       //private данным CBase
      protBase=0;
      pubBase=0;
    }
};

class CDerived1 : public CDerived
{
  public:
    void updateDerived1()
    {
      //privateBase=1; //нельзя доступиться к 
                       //private данным CBase
      protBase=1; //а тут уже все в порядке, 
                  //в CDerived они стали protected
      pubBase=1;  // что значит, что наследник имеет 
                  //к ним доступ
    }
};
CDerived dd;
//dd.privateBase=3; недоступно
//dd.protBase=3; недоступно
//dd.pubBase=3; недоступно
