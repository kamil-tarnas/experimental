template <int value>
int returnMyValue()
{
   return value;
}

template <>
int returnMyValue<5>()
{
   return 5;
}

template <>
int returnMyValue<3>()
{
   return 3;
}

int main()
{
   return 0;
}
