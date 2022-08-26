#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../includes/VEntity.h"

// TEST_CASE("Equalution test for USD and CHF")
// {
//     Dollar usd(12);
//     Frank chf(5);
//     bool b = false;

//     SECTION("12 USD == 12 Money(USD)"){
//         b = usd==Money(12, Currency::USD);
//         REQUIRE(b == true);
//     }

//     SECTION("12 USD != 12 CHF"){
//         b = usd==Money(12,Currency::CHF);
//         REQUIRE(b == false);
//     }

//     SECTION("5 CHF == 5 Money(CHF)"){
//         b = chf==Money(5, Currency::CHF);
//         REQUIRE(b == true);
//     }

//     SECTION("5 CHF != 5 USD"){
//         b = chf==Money(5,Currency::USD);
//         REQUIRE(b == false);
//     }

//     SECTION("5 CHF != 12 USD"){
//         b = chf==usd;
//         REQUIRE(b == false);
//     }
// }

TEST_CASE("Equalution test for Entities")
{
    VEntity ent(0, 0, 'x', true);
    bool b = false;

    SECTION("ent == Ent(0, 0, 'x', true)"){
        b = ent == VEntity(0, 0, 'x', true);
        REQUIRE(b == true);
    }


}