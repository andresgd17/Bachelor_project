void anothe_function();
double square(double x);

void test_2()
{
  cout << "main function" << endl;
  anothe_function();
  cout << square(5) << endl;
}

void anothe_function()
{
  cout << "another function" << endl;
}

double square(double x)
{
  double y = x*x;

  return y;
}