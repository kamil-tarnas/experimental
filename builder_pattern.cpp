#include <memory>
#include <string>

class Engine
{
   public:
      explicit Engine(int power)
         : mPower{power}
      {
      }
   private:
      int mPower = 0;
};

class Car
{
   public:
      enum class Type
      {
         Family,
         Sport
      };

      using EnginePtr = std::unique_ptr<Engine>;

      class Builder final
      {
         public:
            using CarPtr = std::unique_ptr<Car>;

            CarPtr create() const
            {
               return std::make_unique<Car>(mWeight, mWidth, mDoorCount, mColor);
            }

            Builder& setWeight(float value) noexcept
            {
               mWeight = value;
               return *this;
            }


            Builder& setWidth(float value) noexcept
            {
               mWidth = value;
               return *this;
            }


            Builder& setDoorCount(int value) noexcept
            {
               mDoorCount = value;
               return *this;
            }


            Builder& setColor(std::string value) noexcept
            {
               mColor = std::move(value);
               return *this;
            }

         private:
            float mWeight = 2;
            float mWidth = 4;
            int mDoorCount = 4;  
            std::string mColor = "black";
      };

      Car(float weight, float width, int doorCount, std::string color, Type type, EnginePtr engine)
         : mWeight{weight}
         , mWidth{width}
         , mDoorCount{doorCount}
         , mColor{std::move(color)}
         , mType{type}
         , mEngine{std::move(engine)}
      {
      }


   private:
      float mWeight = 0;
      float mWidth = 0;
      int mDoorCount = 0;  
      std::string mColor;
      Type mType = Type::Family;
      EnginePtr mEngine;
};

int main()
{
   auto car = Car::Builder{}
      .setColor("blue")
      .setDoorCount(2)
      .setWidth(3.5f)
      .create();

   return 0;
}
