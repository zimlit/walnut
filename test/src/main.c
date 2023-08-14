/**
 * Copyright (C) 2023 Devin Rockwell
 *
 * walnut is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * walnut is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with walnut. If not, see <http://www.gnu.org/licenses/>.
 */

#include <check.h>
#include <walnut/debug.h>
#include <walnut/walnut.h>

START_TEST(test_ldi)
{
  Walnut walnut;
  uint64_t code[] = {
    0x100000000040000,
  };
  walnutInit(&walnut, code, 1);
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[0], 4);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_ldm)
{
  Walnut walnut;
  uint64_t code[] = {
    0x200010000000000,
    0,
    0x3,
  };
  walnutInit(&walnut, code, 3);
  walnut.registers[1] = 1;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[0], 3);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_lda)
{
  Walnut walnut;
  uint64_t code[] = {
    0x300010000000000,
    0,
    0xA,
  };
  walnutInit(&walnut, code, 3);
  walnut.registers[1] = 2;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[0], 0xA);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_ldr)
{
  Walnut walnut;
  uint64_t code[] = {
    0x401000000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 4;
  walnutRun(&walnut);
  ck_assert_uint_eq(walnut.registers[1], 4);
  walnutFree(&walnut);
}
END_TEST

Suite *
load_suite()
{
  Suite *s       = suite_create("Loads");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_ldi);
  tcase_add_test(tc_core, test_ldm);
  tcase_add_test(tc_core, test_lda);
  tcase_add_test(tc_core, test_ldr);
  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_sto)
{
  Walnut walnut;
  uint64_t code[] = {
    0x500010000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[1] = 10;
  walnutRun(&walnut);
  ck_assert_int_eq(walnut.mem.data[1], 10);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_sta)
{
  Walnut walnut;
  uint64_t code[] = {
    0x600010000000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[1] = 10;
  walnut.registers[0] = 1;
  walnutRun(&walnut);
  ck_assert_int_eq(walnut.mem.data[1], 10);
  walnutFree(&walnut);
}

Suite *
store_suit()
{
  Suite *s       = suite_create("Stores");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_sto);
  tcase_add_test(tc_core, test_sta);
  suite_add_tcase(s, tc_core);
  return s;
}

START_TEST(test_add)
{
  Walnut walnut;
  uint64_t code[] = {
    0x702000100000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 10;
  walnut.registers[1] = 5;
  walnutRun(&walnut);
  ck_assert_int_eq(walnut.registers[2], 15);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_sub)
{
  Walnut walnut;
  uint64_t code[] = {
    0x802000100000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 10;
  walnut.registers[1] = 5;
  walnutRun(&walnut);
  ck_assert_int_eq(walnut.registers[2], 5);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_mul)
{
  Walnut walnut;
  uint64_t code[] = {
    0x902000100000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 10;
  walnut.registers[1] = 5;
  walnutRun(&walnut);
  ck_assert_int_eq(walnut.registers[2], 50);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_div)
{
  Walnut walnut;
  uint64_t code[] = {
    0xA02000100000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 10;
  walnut.registers[1] = 5;
  walnutRun(&walnut);
  ck_assert_int_eq(walnut.registers[2], 2);
  walnutFree(&walnut);
}
END_TEST

START_TEST(test_mod)
{
  Walnut walnut;
  uint64_t code[] = {
    0xB02000100000000,
  };
  walnutInit(&walnut, code, 1);
  walnut.registers[0] = 10;
  walnut.registers[1] = 4;
  walnutRun(&walnut);
  ck_assert_int_eq(walnut.registers[2], 2);
  walnutFree(&walnut);
}
END_TEST

Suite *
math_suite()
{
  Suite *s       = suite_create("Math");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_add);
  tcase_add_test(tc_core, test_sub);
  tcase_add_test(tc_core, test_mul);
  tcase_add_test(tc_core, test_div);
  tcase_add_test(tc_core, test_mod);
  suite_add_tcase(s, tc_core);
  return s;
}

int
main()
{
  int numberFailed;
  Suite *ld     = load_suite();
  Suite *st     = store_suit();
  Suite *m      = math_suite();
  SRunner *ldSr = srunner_create(ld);
  SRunner *stSr = srunner_create(st);
  SRunner *mSr  = srunner_create(m);

  srunner_run_all(ldSr, CK_NORMAL);
  numberFailed = srunner_ntests_failed(ldSr);

  srunner_run_all(stSr, CK_NORMAL);
  numberFailed += srunner_ntests_failed(stSr);

  srunner_run_all(mSr, CK_NORMAL);
  numberFailed += srunner_ntests_failed(mSr);

  srunner_free(ldSr);
  srunner_free(stSr);
  srunner_free(mSr);
  return (numberFailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}