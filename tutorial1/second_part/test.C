void otherfunction();
double square(double x);

void test()
{
  cout << "Hi" << endl;
  otherfunction();
  cout << square(4) << endl;
}

void otherfunction()
{
  cout << "other function" << endl;
}

double square(double x)
{
  double y = x*x;
  
  return y;
}