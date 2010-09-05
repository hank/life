include stdlib // Need for rand() and srand()
include time   // Need for time()
c_rand: extern(rand) func -> Int
c_srand: extern(srand) func(seed: Int) -> Int
c_time: extern(time) func(when: Int) -> Int

import structs/ArrayList

//operator as (b: Boo) -> Int

Boat: abstract class {
  name: String
  status: Int // I'd like this to be an enum, but oh well

  // a horn sound.  Needs to be implemented by children
  horn: abstract func
  crash: abstract func
}

// a new class of boat
Failboat: class extends Boat {
  init: func (=name) { this status = 3 }
  init: func ~withStatus (=name, =status){}

  horn: func 
  {
    printf("SS %s blares his horn: FAIL, %u!\n", this name, this status)
  }

  crash: func {
    if(!status) return
    status -= 1
    match status {
      case 0 => printf("%s sinks!\n", name)
      case 1 => printf("%s starts leaking!\n", name)
      case => printf("%s is unharmed!\n", name)
    }
  }
}

// Crash the boats together.
// This will test their strength based on status
// Return value will be -1 if u wins, 0 for continuation,
//   1 if v wins, and 2 if both destroy eachother
operator + (u,v: Boat) -> Int
{
  printf("Kapow! %s and %s crash into eachother!\n", u name, v name)
  [u,v] as ArrayList<Boat> each(Boat crash)
  printf("%s: %d, %s: %d\n", u name, u status, v name, v status)
  return match {
    case(u status + v status == 0) => 2 
    case(u status == 0) => 1
    case(v status == 0) => -1
    case => 0
  }
}

main: func {
  // Seed rand like we usually do in C
  c_srand(c_time(null))
  boat_a := Failboat new("Godzilla", c_rand() % 4)
  boat_b := Failboat new("Megalon", c_rand() % 4)

  // DANGER AHEAD!  SOUND THE HORNS!
  [boat_a, boat_b] as ArrayList<Boat> each(Boat horn)

  // Fight fight fight!
  status := 0
  while(!status) {
    status = boat_a + boat_b
  }

  // Determine the victor
  printf("The Battle is over.  ")
  match status {
    case 2 => "Both Boats are destroyed!" println()
    case 1 => printf("%s is the victor\n", boat_b name)
    case -1 => printf("%s is the victor\n", boat_a name)
  }
}
