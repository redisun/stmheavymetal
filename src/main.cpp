extern "C"
{
  static const int a = 7;
  static int b = 8;
  static int sum;

  int main()
  {
    for(;;)
    {
      sum = a * b;
    }
  }
}
