#include "Warlock.hpp"
#include "Dummy.hpp"
#include "Fwoosh.hpp"
#include "Polymorph.hpp"
#include "Fireball.hpp"
#include "BrickWall.hpp"
#include "TargetGenerator.hpp"

int main()
{
  Warlock richard("Richard", "foo");
  richard.setTitle("Hello, I'm Richard the Warlock!");
  BrickWall model1;

  Polymorph* polymorph = new Polymorph();
  TargetGenerator tarGen;

  tarGen.learnTargetType(&model1);
  richard.learnSpell(polymorph);
  richard.learnSpell(NULL); // add for test

  Fireball* fireball = new Fireball();

  richard.learnSpell(fireball);

  ATarget* wall = tarGen.createTarget("Inconspicuous Red-brick Wall");

  richard.introduce();
//   std::cout << "---" << std::endl; // add for test
  richard.launchSpell("Polymorph", *wall);
  richard.launchSpell("Fireball", *wall);
  richard.launchSpell("Fireball1", *wall); // add for test

  ATarget* wall2 = tarGen.createTarget("Inconspicuous Red-brick Wall2"); // add for test
  if (wall2)															 // add for test
  	richard.launchSpell("Fireball", *wall2);							 // add for test
}