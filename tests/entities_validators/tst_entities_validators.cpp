#include "tst_entities_validators.h"
#include "entities/user.h"
// add necessary includes here

entities_validators::entities_validators() {}

entities_validators::~entities_validators() {}

void entities_validators::validate_name()
{
    User::validate_name("Евгений");
    User::validate_name("е в г е н и й");
    User::validate_name("e v g e n i j");
    QVERIFY_EXCEPTION_THROWN(User::validate_name(" евгений "), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(User::validate_name("евгений "), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(User::validate_name(" евгений"), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(User::validate_name("евген"), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(User::validate_name("евген1й"), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(User::validate_name("евг_ений"), std::runtime_error);
}

void entities_validators::validate_login()
{
    User::validate_login("evgeni");
    User::validate_login("EvGeNiY");
    User::validate_login("E_V_G_E_N");
    User::validate_login("evgen_2010");
    QVERIFY_EXCEPTION_THROWN(User::validate_login("evgen"), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(User::validate_login("evgen!"), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(User::validate_login(" evgen "), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(User::validate_login(" evgen"), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(User::validate_login("evgen "), std::runtime_error);
}

void entities_validators::validate_password()
{
    User::validate_password("123456");
    User::validate_password("Ejfiewk@4rw49w)RУаый@#90few..02 3r-");
    QVERIFY_EXCEPTION_THROWN(User::validate_password("wejwf"), std::runtime_error);
}

void entities_validators::validate_role()
{
    User::validate_role(UserRole::Client);
    User::validate_role(UserRole::Worker);
    User::validate_role(UserRole::Admin);
    QVERIFY_EXCEPTION_THROWN(User::validate_role(UserRole::None);, std::runtime_error);
    User::validate_role("Client");
    User::validate_role("Worker");
    User::validate_role("Admin");
    User::validate_role("ClIeNt");
    User::validate_role("WorkER");
    User::validate_role("ADMin");
    QVERIFY_EXCEPTION_THROWN(User::validate_role("None");, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(User::validate_role("Admin ");, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(User::validate_role("_ewjfew");, std::runtime_error);
}

QTEST_APPLESS_MAIN(entities_validators)
