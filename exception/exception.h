#pragma once

#include <iostream>
#include <string>

class TException {
  private:
    std::string str;
  public:
    TException(std::string _str);
    void Show();
};

TException::TException(std::string _str):str(_str)
{
}

void TException::Show()
{
    std::cout << "\nWarning! \nMessage: " << str << std::endl;
}
