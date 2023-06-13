#include "Routeplanner.h"

Routeplanner::Routeplanner(Motorcontroller* m):mc(m),lv(m),bd(m) {

}

void Routeplanner::init() {
  lv.init();
}

void Routeplanner::start() {
  bd.start();
}