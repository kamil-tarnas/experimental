#include <iostream>
#include <variant>

class Animal
{
public:
	virtual const char* see() const = 0;
	virtual const char* say() const = 0;
};


class Cow : public Animal
{
public:
	virtual const char* see() const override { return "cow"; }
	virtual const char* say() const override { return "moo"; }
};

class Pig : public Animal
{
public:
	virtual const char* see() const override { return "pig"; }
	virtual const char* say() const override { return "oink"; }
};

class Dog : public Animal
{
public:
	virtual const char* see() const override final { return "dog"; }
	virtual const char* say() const override final { return "woof"; }
};

//void seeAndSay(const Animal* const animal_p)
//{
//	std::cout << "The animal " << animal_p->see() << " says " << animal_p->say() << "\n";
//}

class Starfish
{
public:
	virtual const char* see() const final { return "starfish"; }
	virtual const char* say() const final { return "bloop"; }
};

template <typename T>
void seeAndSay(const T* const animal_p)
{
	std::cout << "The animal " << animal_p->see() << " says " << animal_p->say() << "\n";
}


class MyAnimal
{
public:
	virtual const char* see() const = 0;
	virtual const char* say() const = 0;
};


template <typename T>
class AnimalWrapper : public MyAnimal
{
public:
	AnimalWrapper(const T& animal) : animal_m(animal) {}
	virtual const char* see() const override { return animal_m.see(); }
	virtual const char* say() const override { return animal_m.say(); }

private:
	const T& animal_m;
};



int main(int argc, char* argv[])
{
	MyAnimal* animalArray[] = { new AnimalWrapper(Dog()), new AnimalWrapper(Cow()), new AnimalWrapper(Starfish()) };

	for (auto& animal : animalArray)
	{
		animal->say();
	}

	seeAndSay(animalArray[0]);

	Animal* animalHolder_p = new Dog;
	Animal& animalRef = *animalHolder_p;
	const char* myDog = animalHolder_p->see();
	const char* dogSound = animalRef.say();
//	Animal* animalHolder_p = new Dog;
//	seeAndSay(animalHolder_p);
	return 0;
}



